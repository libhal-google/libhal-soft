// Copyright 2023 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once
#include <array>
#include <libhal-util/map.hpp>
#include <libhal-util/math.hpp>
#include <libhal/adc.hpp>
#include <libhal/error.hpp>
#include <libhal/output_pin.hpp>
#include <libhal/steady_clock.hpp>
#include <span>

using namespace hal::literals;
using namespace std::chrono_literals;

namespace hal {

// This function does not take into account setup and hold times.
hal::status set_mux_channel(uint32_t p_position,
                            std::span<hal::output_pin*> p_signal_pins)
{

  for (int i = 0; i < static_cast<int>(p_signal_pins.size()); i++) {

    bool value = bool(p_position & (1 << i));
    HAL_CHECK(p_signal_pins[i]->level(value));
  }
  return hal::success();
}

/**
 * @brief A driver for Analog to Digital mulitplexers, creates adc pin objects
 * for each mux output
 */
class adc_multiplexer
{
public:
  /**
   * @brief An internal class of a hal ADC implimentation to represent a
   * multiplexer pin
   */
  class adc_mux_pin : public hal::adc
  {
  public:
    /** @brief An internal constructor to build an adc mux pin.
     * @param p_mux_port the channel port of the pin on the mux itself.
     * @param p_mux A pointer to the multiplexer.
     * */
    adc_mux_pin(uint8_t p_mux_port, adc_multiplexer* p_mux)
      : m_mux_port{ p_mux_port }
      , m_mux{ p_mux } {};  // TODO add m_mux

    /**
     * @brief Reads the pin.
     */
    hal::result<read_t> driver_read() override
    {
      return m_mux->read_channel(m_mux_port);
    }

  private:
    const uint8_t m_mux_port;
    adc_multiplexer* m_mux;
  };

  /**
   * @param p_signal_pins A span of output pins to represent the signal pins of
   * the mux, assuming the mux signals digitally.
   * @param p_source_pin The adc source pin that reads the output of the mux.
   */
  adc_multiplexer(std::span<hal::output_pin*> p_signal_pins,
                  hal::adc* p_source_pin)
    : m_signal_pins{ p_signal_pins }
    , m_source_pin{ p_source_pin } {};

  /**
   * @brief Returns a multiplexer ADC pin
   * @param p_channel The channel number of the pin.
   */
  hal::result<adc_mux_pin> pin_factory(uint8_t p_channel)
  {
    // TODO: Ask if we should keep track of channels in use, if a port is asked
    // for again, disallow it.
    const std::uint32_t max_size = 1 << m_signal_pins.size();
    if (p_channel >= max_size) {
      return hal::new_error(
        "Unable to add any more pins to this multiplexer.\n");
    }

    return adc_mux_pin(p_channel, this);
  }

private:
  /**
   * @brief Reads the channel
   *
   * @param p_mux_port
   * @return hal::result<hal::adc::read_t>
   */
  hal::result<hal::adc::read_t> read_channel(uint8_t p_mux_port)
  {
    set_mux_channel(p_mux_port, m_signal_pins);
    return HAL_CHECK(m_source_pin->read());
  }

private:
  std::span<hal::output_pin*> m_signal_pins;
  hal::adc* m_source_pin;
};

}  // namespace hal
