#include <chrono>

#include <libhal-soft/i2c_bit_bang.hpp>
#include <libhal-util/bit.hpp>
#include <libhal-util/steady_clock.hpp>
#include <libhal/error.hpp>
#include <libhal/units.hpp>

namespace hal {
// public
i2c_bit_bang::i2c_bit_bang(output_pin& p_scl,
                           output_pin& p_sda,
                           steady_clock& p_clock,
                           bus_info p_bus)
  : m_scl(&p_scl)
  , m_sda(&p_sda)
  , m_clock(&p_clock)
  , m_bus(p_bus)
{
}

i2c_host_state i2c_bit_bang::operation_state_machine(
  i2c_host_state p_state,
  function_ref<hal::timeout_function> p_timeout)
{
  constexpr auto read_write_bit_mask = hal::bit_mask::from<0, 0>();
  switch (p_state) {
    case i2c_host_state::start:
    case i2c_host_state::repeated_start: 
      send_start_condition();
      p_state = i2c_host_state::write_address;
      break;

    case i2c_host_state::write_address: {
      hal::byte address_to_write;

      // select read or write
      if (m_write_iterator != m_write_end) {
        p_state = i2c_host_state::write;
        address_to_write = hal::bit_modify(m_address)
                             .clear<read_write_bit_mask>()
                             .to<hal::byte>();
      } 
      else {
        p_state = i2c_host_state::read;
        address_to_write =
          hal::bit_modify(m_address).set<read_write_bit_mask>().to<hal::byte>();
      }
      // write the address
      auto acknowledged = write_byte(address_to_write, p_timeout);

      // if ack_bit = 1 then this indicates that no peripheral responded (nack)
      if (!acknowledged) {
        p_state = i2c_host_state::bus_error;
      }
      break;
    }
    case i2c_host_state::write: {

      auto acknowledged = write_byte(*m_write_iterator, p_timeout);
      m_write_iterator++;

      // if acknowledged = 1 then an error has occured (nack)
      if (!acknowledged) {
        p_state = i2c_host_state::bus_error;
        return p_state;
      }

      // after writing, if the read iterators aren't done, then it's a
      // repeated start otherwise continue writing
      if (m_write_iterator < m_write_end) {
        p_state = p_state;
      }
      else if (m_read_iterator != m_read_end) {
        p_state = i2c_host_state::repeated_start;
      } else {
        p_state = i2c_host_state::send_stop;
      }
      
    break;
    }
    case i2c_host_state::read: {

      read_byte();
      m_read_iterator++;

      // when the data is done being read in, then send a NACK to tell the
      // slave to stop reading
      if (m_read_iterator >= m_read_end) {
        write_bit(1, p_timeout);
        p_timeout();
        p_state = i2c_host_state::send_stop;
      } else {
        // if the iterator isn't done, then we ack whatever data we read
        write_bit(0, p_timeout);
        p_state = p_state;
      }
      break;
    }
    case i2c_host_state::send_stop:
    case i2c_host_state::bus_error: {
      send_stop_condition();
      p_state = i2c_host_state::done;
      break;
    }
    case i2c_host_state::done: {
      // do nothing
    }
  }
  return p_state;
}



void i2c_bit_bang::driver_configure(const settings& p_settings)
{
  using namespace std::chrono_literals;

  if (p_settings.clock_rate > m_clock->frequency()) {
    throw hal::operation_not_supported(this);
  }
  // calculate period in microsecond
  float nanoseconds_per_second = 1'000'000'000.0f;
  uint32_t period_ns = nanoseconds_per_second / p_settings.clock_rate;
  m_scl_high_time = static_cast<std::chrono::nanoseconds>(
    static_cast<uint32_t>(period_ns * m_bus.duty_cycle));
  m_scl_low_time =
    static_cast<std::chrono::nanoseconds>(period_ns) - m_scl_high_time;
}

void i2c_bit_bang::driver_transaction(
  hal::byte p_address,
  std::span<const hal::byte> p_data_out,
  std::span<hal::byte> p_data_in,
  function_ref<hal::timeout_function> p_timeout)
{

  i2c_host_state state = i2c_host_state::start;
  // the address should always be in the last 7 bits, so shift it by 1
  m_address = p_address << 1;
  m_write_iterator = p_data_out.begin();
  m_write_end = p_data_out.end();
  m_read_iterator = p_data_in.begin();
  m_read_end = p_data_in.end();

  while (state != i2c_host_state::done) {
    state = operation_state_machine(state, p_timeout);
    p_timeout();
  }
}

// private

void i2c_bit_bang::send_start_condition()
{
  using namespace std::chrono_literals;
  // the start condition requires both the sda and scl lines to be pulled high before sending, so we do that here.
  m_sda->level(true);
  m_scl->level(true);
  delay(*m_clock, m_scl_high_time);
  m_sda->level(false);
  delay(*m_clock, m_scl_low_time);
  m_scl->level(false);
  delay(*m_clock, m_scl_low_time);
}

void i2c_bit_bang::send_stop_condition()
{
  m_sda->level(false);
  delay(*m_clock, m_scl_high_time);
  m_scl->level(true);
  delay(*m_clock, m_scl_high_time);
  m_sda->level(true);
  delay(*m_clock, m_scl_high_time);
}

bool i2c_bit_bang::write_byte(hal::byte p_byte_to_write,
                              function_ref<hal::timeout_function> p_timeout)
{
  constexpr auto byte_length = 8;
  constexpr hal::byte bit_select = 0b0000'0001;
  hal::byte bit_to_write = 0;
  // not using the bit library here since it's a serialization
  for (int i = 0; i < byte_length; i++) {
    bit_to_write = static_cast<hal::byte>((p_byte_to_write >> (byte_length - (i+1))) & bit_select);
    write_bit(bit_to_write, p_timeout);
  }

  m_sda->level(true);
  // delay(*m_clock, m_scl_high_time);
  // look for the ack
  auto ack_bit = read_bit();
  // if ack bit is 0, then it was acknowledged
  auto acknowledged = (ack_bit == 0);

  return acknowledged;
}
/*
   for writing a bit you want to make set the data line first, then toggle the
   level of the clock then check if the level was indeed toggled or if the
   peripheral is stretching the clock. After this is done, you are able to set
   the clock back low.
*/
void i2c_bit_bang::write_bit(hal::byte p_bit_to_write,
                             function_ref<hal::timeout_function> p_timeout)
{

  m_sda->level(static_cast<bool>(p_bit_to_write));

  m_scl->level(true);
  delay(*m_clock, m_scl_high_time);

  // if(p_bit_to_write != m_sda->level()) {
  //     return
  // }
  // if scl is still low after we set it high, then the peripheral is clock
  // stretching
  while (m_scl->level() == 0) {
    p_timeout();
  }

  m_scl->level(false);
  delay(*m_clock, m_scl_low_time);
}
/*
    after reading out the entire byte you then want to have the reciever send
*/
void i2c_bit_bang::read_byte()
{
  constexpr auto byte_length = 8;
  hal::byte read_byte = 0;
  for (int i = 0; i < byte_length; i++) {
    read_byte |= (read_bit() << (byte_length - i));
  }
  *m_read_iterator = read_byte;
}

hal::byte i2c_bit_bang::read_bit()
{
  m_scl->level(true);
  delay(*m_clock, m_scl_high_time);

  auto bit_read = static_cast<hal::byte>(m_sda->level());

  m_scl->level(false);
  delay(*m_clock, m_scl_low_time);

  return bit_read;
}

}  // namespace hal
