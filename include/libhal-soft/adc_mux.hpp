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
#include <span>

#include <libhal/adc.hpp>
#include <libhal/output_pin.hpp>
#include <libhal/steady_clock.hpp>

namespace hal {

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
   * @return The constructed adc_multiplexer.
   */
  static adc_multiplexer create(std::span<hal::output_pin*> p_signal_pins,
                                hal::adc& p_source_pin,
                                hal::steady_clock& p_clock);

  /**
   * @brief Reads a channel on the mux.
   *
   * @param p_mux_port The port to be read. If an out of bounds port number is
   * passed, an error-typed result is returned.
   * @return The hal::adc::read_t struct of the read value or an error if an
   * invalid port is given.
   */
  hal::result<hal::adc::read_t> read_channel(std::uint16_t p_mux_port);

  /**
   * @brief Gets the highest capacity channel held by the ADC mux object.
   * This is caluclated based off of how many source pins are available.
   *
   * @return The maximum channel number for this mux (2^n states, where n is
   * number of source pins).
   */
  int get_max_channel();

private:
  adc_multiplexer(std::span<output_pin*> p_signal_pins,
                  hal::adc& p_source_pin,
                  hal::steady_clock& p_clock);

private:
  std::span<output_pin*> m_signal_pins;
  hal::adc* m_source_pin;
  hal::steady_clock* m_clock;
};

/**
 * @brief A class that represents a multiplexer pin for ADC.
 */
class adc_mux_pin : public hal::adc
{
  friend result<adc_mux_pin> make_adc(adc_multiplexer& p_multiplexer,
                                      std::uint8_t p_channel);

private:
  adc_mux_pin(adc_multiplexer& p_mux, std::uint8_t p_mux_port);
  hal::result<read_t> driver_read() override;

  adc_multiplexer* m_mux;
  std::uint8_t m_mux_port;
};

/**
 * @brief Returns a multiplexer ADC pin.
 *
 * @param p_multiplexer The multiplexer object to manage each mux pin.
 * @param p_channel The channel number of the pin.
 * @return A newly constructed ADC multiplexer pin.
 */
result<adc_mux_pin> make_adc(adc_multiplexer& p_multiplexer,
                             std::uint8_t p_channel);

}  // namespace hal
