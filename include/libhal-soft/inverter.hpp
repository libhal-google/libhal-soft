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

#include <libhal/input_pin.hpp>
#include <libhal/output_pin.hpp>

/**
 * @defgroup Inverter Inverter
 *
 */

namespace hal::soft {
/**
 * @ingroup Inverter
 * @brief An output_pin wrapper to get the negation of an output pin's state.
 * For example, if the output pin is high, then this inverter is low.
 *
 */
class output_pin_inverter : public hal::output_pin
{
public:
  /**
   * @brief Construct a new output_pin_inverter object from a source output_pin
   *
   * @param p_output_pin The output pin whose signal should be inverted.
   */
  output_pin_inverter(hal::output_pin& p_output_pin);

private:
  void driver_configure(const settings& p_settings) override;
  void driver_level(bool p_high) override;
  bool driver_level() override;

  hal::output_pin* m_output_pin;
};

/**
 * @ingroup Inverter
 * @brief An input_pin wrapper to get the negation of an input pin's state.
 * For example, if the input pin is high, then this inverter is low.
 *
 */
class input_pin_inverter : public hal::input_pin
{
public:
  /**
   * @brief Construct a new input_pin_inverter object from a source input_pin
   *
   * @param p_input_pin The output pin whose signal should be inverted.
   */
  input_pin_inverter(hal::input_pin& p_input_pin);

private:
  void driver_configure(const settings& p_settings) override;
  bool driver_level() override;

  hal::input_pin* m_input_pin;
};
}  // namespace hal::soft
