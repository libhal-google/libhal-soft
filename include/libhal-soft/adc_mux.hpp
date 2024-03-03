// Copyright 2024 Khalil Estell
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
#include <span>

#include <libhal/adc.hpp>
#include <libhal/output_pin.hpp>
#include <libhal/steady_clock.hpp>

/**
 * @defgroup AdcMux Adc Mux
 *
 */

namespace hal::soft {
/**
 * @brief A driver for an ADC multiplexer that manages and reads ADC mux pins.
 * This driver is intended to be used with multiplexers that use digital
 * signals. An ADC multiplexer can be used to expand the number of input
 * channels of an ADC.
 */
class adc_multiplexer
{
public:
  /**
   * @brief Constructs a new adc_multiplexer object.
   *
   * @param p_signal_pins A span of the output signal pins used to determine the
   * channel on the mux.
   * @param p_source_pin The output adc pin of the multiplexer.
   * @param p_clock A steady clock used for delaying 500ns to give time to the
   * mux to have an updated signal.
   */
  adc_multiplexer(std::span<output_pin*> p_signal_pins,
                  hal::adc& p_source_pin,
                  hal::steady_clock& p_clock);

  /**
   * @brief Reads a channel on the mux.
   *
   * @param p_mux_port The port to be read. If an out of bounds port number is
   * passed, an error-typed result is returned.
   * @return float - adc sample from the selected channel.
   */
  float read_channel(std::uint16_t p_mux_port);

  /**
   * @brief Gets the highest capacity channel held by the ADC mux object.
   * This is calculated based off of how many source pins are available.
   *
   * @return the maximum channel number for this mux (2^n states, where n is
   * number of source pins).
   */
  int get_max_channel();

private:
  void set_mux_channel(std::uint16_t p_position);

  std::span<output_pin*> m_signal_pins;
  hal::adc* m_source_pin;
  hal::steady_clock* m_clock;
};

/**
 * @ingroup AdcMux
 * @brief A class that represents a multiplexer pin for ADC.
 */
class adc_mux_pin : public hal::adc
{
public:
  adc_mux_pin(adc_multiplexer& p_mux, std::uint8_t p_mux_port);

private:
  float driver_read() override;

  adc_multiplexer* m_mux;
  std::uint8_t m_mux_port;
};

/**
 * @ingroup AdcMux
 * @brief Returns an ADC pin from the multiplexer.
 *
 * @param p_multiplexer the adc multiplexer with the desire adc channel pin
 * @param p_channel The channel number of the pin
 * @return A newly constructed ADC multiplexer pin.
 * @throws std::errc::result_out_of_range if p_channel greater than the
 * available number of channels in the multiplexer.
 */
adc_mux_pin make_adc(adc_multiplexer& p_multiplexer, std::uint8_t p_channel);
}  // namespace hal::soft

namespace hal {
using hal::soft::make_adc;
}  // namespace hal
