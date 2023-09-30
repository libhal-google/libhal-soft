#include <libhal-soft/adc_mux.hpp>
#include <libhal-util/steady_clock.hpp>

namespace hal::soft {
using namespace hal::literals;
using namespace std::chrono_literals;

namespace {
/**
 * @brief Set the ADC mux to a specific channel.
 *
 * @param p_position The desired channel.
 * @param p_signal_pins A span of the source pins.
 * @param p_clock A steady clock used for delaying 500ns to give time to the mux
 * to have an updated signal
 * @return The status of the operation.
 */
hal::status set_mux_channel(std::uint16_t p_position,
                            std::span<output_pin*> p_signal_pins,
                            hal::steady_clock& p_clock)
{
  for (std::size_t i = 0; i < p_signal_pins.size(); i++) {
    bool value = bool(p_position & (1 << i));
    hal::delay(p_clock, 500ns);
    HAL_CHECK(p_signal_pins[i]->level(value));
  }
  return success();
}
}  // namespace

// Implementations for adc_multiplexer

adc_multiplexer::adc_multiplexer(std::span<output_pin*> p_signal_pins,
                                 hal::adc& p_source_pin,
                                 hal::steady_clock& p_clock)
  : m_signal_pins{ p_signal_pins }
  , m_source_pin{ &p_source_pin }
  , m_clock{ &p_clock } {};

adc_multiplexer adc_multiplexer::create(
  std::span<hal::output_pin*> p_signal_pins,
  hal::adc& p_source_pin,
  hal::steady_clock& p_clock)
{
  return { p_signal_pins, p_source_pin, p_clock };
}

int adc_multiplexer::get_max_channel()
{
  return 1 << this->m_signal_pins.size();
}

hal::result<hal::adc::read_t> adc_multiplexer::read_channel(
  std::uint16_t p_mux_port)
{
  set_mux_channel(p_mux_port, m_signal_pins, *m_clock);
  hal::delay(*m_clock, 500ns);
  return HAL_CHECK(m_source_pin->read());
}

// Implementations for adc_mux_pin

adc_mux_pin::adc_mux_pin(adc_multiplexer& p_mux, std::uint8_t p_mux_port)
  : m_mux{ &p_mux }
  , m_mux_port{ p_mux_port } {};

hal::result<hal::adc::read_t> adc_mux_pin::driver_read()
{
  return m_mux->read_channel(m_mux_port);
}

result<adc_mux_pin> make_adc(adc_multiplexer& p_multiplexer,
                             std::uint8_t p_channel)
{
  if (p_channel > p_multiplexer.get_max_channel()) {
    return hal::new_error(std::errc::result_out_of_range);
  }
  return adc_mux_pin(p_multiplexer, p_channel);
}
}  // namespace hal::soft