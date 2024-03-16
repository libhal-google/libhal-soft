#include <chrono>

#include <libhal-soft/i2c_bit_bang.hpp>
#include <libhal-util/bit.hpp>
#include <libhal-util/i2c.hpp>
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

  hal::i2c_operation operation;
  hal::byte address_to_write;

  // select read or write
  if (!p_data_out.empty()) {
    send_start_condition();
    operation = hal::i2c_operation::write;
    address_to_write = hal::to_8_bit_address(p_address, operation);

    write_address(address_to_write, p_timeout);

    write(p_data_out, p_timeout);
  }

  // if the first bit is 1 then we read
  if (!p_data_in.empty()) {
    send_start_condition();

    operation = hal::i2c_operation::read;
    address_to_write = hal::to_8_bit_address(p_address, operation);

    write_address(address_to_write, p_timeout);

    read(p_data_in, p_timeout);
  }

  send_stop_condition();
}

// private

void i2c_bit_bang::send_start_condition()
{
  using namespace std::chrono_literals;
  // the start condition requires both the sda and scl lines to be pulled high
  // before sending, so we do that here.
  m_sda->level(true);
  // delay(*m_clock, m_scl_high_time);
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
  
  m_scl->level(true);
  delay(*m_clock, m_scl_high_time);
  m_sda->level(true);
  delay(*m_clock, m_scl_high_time);
}

void i2c_bit_bang::write_address(hal::byte p_address,
                                 function_ref<hal::timeout_function> p_timeout)
{
  // write the address
  auto acknowledged = write_byte(p_address, p_timeout);

  if (!acknowledged) {
    hal::safe_throw(hal::no_such_device((p_address >> 1), this));
  }
}

void i2c_bit_bang::write(std::span<const hal::byte> p_data_out,
                         function_ref<hal::timeout_function> p_timeout)
{
  bool acknowledged;
  for (const hal::byte& data : p_data_out) {

    acknowledged = write_byte(data, p_timeout);

    if (!acknowledged) {
      hal::safe_throw(hal::io_error(this));
    }
  }
}

bool i2c_bit_bang::write_byte(hal::byte p_byte_to_write,
                              function_ref<hal::timeout_function> p_timeout)
{
  using namespace std::chrono_literals;
  constexpr auto byte_length = 8;
  constexpr hal::byte bit_select = 0b0000'0001;
  hal::byte bit_to_write = 0;
  uint32_t i;
  for (i = 0; i < byte_length; i++) {

    bit_to_write = static_cast<hal::byte>(
      (p_byte_to_write >> (byte_length - (i + 1))) & bit_select);

    write_bit(bit_to_write, p_timeout);
  }

  // look for the ack
  auto ack_bit = read_bit();
  // if ack bit is 0, then it was acknowledged (true)
  return (ack_bit == 0);
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

  // if scl is still low after we set it high, then the peripheral is clock
  // stretching
  while (m_scl->level() == 0) {
    p_timeout();
  }

  m_scl->level(false);
  delay(*m_clock, m_scl_low_time);
}

void i2c_bit_bang::read(std::span<hal::byte> p_data_in,
                        function_ref<hal::timeout_function> p_timeout)
{
  uint32_t size_of_span = p_data_in.size(), i = 0;
  for (hal::byte& data : p_data_in) {
    data = read_byte();
    i++;

    if (i < size_of_span) {
      // if the iterator isn't done, then we ack whatever data we read
      write_bit(0, p_timeout);

    } else {
    // when the data is done being read in, then send a NACK to tell the
    // slave to stop reading
      write_bit(1, p_timeout);
    }
  }
}

hal::byte i2c_bit_bang::read_byte()
{
  constexpr auto byte_length = 8;
  hal::byte read_byte = 0;
  uint32_t i;
  for (i = 1; i <= byte_length; i++) {
    read_byte |= (read_bit() << (byte_length - i));
  }
  return read_byte;
}

hal::byte i2c_bit_bang::read_bit()
{
  m_sda->level(true);
  m_scl->level(true);
  delay(*m_clock, m_scl_high_time);

  auto bit_read = static_cast<hal::byte>(m_sda->level());

  m_scl->level(false);
  delay(*m_clock, m_scl_low_time);

  return bit_read;
}

}  // namespace hal
