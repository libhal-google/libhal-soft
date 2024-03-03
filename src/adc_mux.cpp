#include <libhal-soft/adc_mux.hpp>
#include <libhal-util/steady_clock.hpp>

namespace hal::soft {
using namespace hal::literals;
using namespace std::chrono_literals;

// Implementations for adc_multiplexer

adc_multiplexer::adc_multiplexer(std::span<output_pin*> p_signal_pins,
                                 hal::adc& p_source_pin,
                                 hal::steady_clock& p_clock)
  : m_signal_pins{ p_signal_pins }
  , m_source_pin{ &p_source_pin }
  , m_clock{ &p_clock } {};

int adc_multiplexer::get_max_channel()
{
  return 1 << m_signal_pins.size();
}

/**
 * @brief Set the ADC mux to a specific channel.
 *
 * @param p_position The desired channel.
 * @param p_signal_pins A span of the source pins.
 * @param p_clock A steady clock used for delaying 500ns to give time to the mux
 * to have an updated signal
 * @return The status of the operation.
 */
void adc_multiplexer::set_mux_channel(std::uint16_t p_position)
{
  for (std::size_t i = 0; i < m_signal_pins.size(); i++) {
    bool value = bool(p_position & (1 << i));
    hal::delay(*m_clock, 500ns);
    m_signal_pins[i]->level(value);
  }
}

float adc_multiplexer::read_channel(std::uint16_t p_mux_port)
{
  set_mux_channel(p_mux_port);
  hal::delay(*m_clock, 500ns);
  return m_source_pin->read();
}

// Implementations for adc_mux_pin

adc_mux_pin::adc_mux_pin(adc_multiplexer& p_mux, std::uint8_t p_mux_port)
  : m_mux{ &p_mux }
  , m_mux_port{ p_mux_port }
{
  if (p_mux_port > p_mux.get_max_channel()) {
    hal::safe_throw(hal::argument_out_of_domain(&p_mux));
  }
};

float adc_mux_pin::driver_read()
{
  return m_mux->read_channel(m_mux_port);
}

adc_mux_pin make_adc(adc_multiplexer& p_multiplexer, std::uint8_t p_channel)
{
  return { p_multiplexer, p_channel };
}
}  // namespace hal::soft