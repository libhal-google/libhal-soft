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

#include <chrono>
#include <libhal/i2c.hpp>
#include <libhal/output_pin.hpp>
#include <libhal/units.hpp>

#include "i2c_bit_bang_constants.hpp"

namespace hal {
/**
 * @brief A bit bang implementation for I2C. This implementation of I2c only
 * needs 2 gpio's to work correctly. In its current implementation we only
 * support single controller multiple peripheral. But have intentions of
 * supporting multiple controller soon.
 *
 */
class i2c_bit_bang : public i2c
{
public:
  using write_iterator = std::span<const hal::byte>::iterator;
  using read_iterator = std::span<hal::byte>::iterator;

  /// holds all of the information for an i2c bus
  struct bus_info
  {
    float duty_cycle;
  };

  i2c_bit_bang(output_pin& p_scl,
               output_pin& p_sda,
               steady_clock& p_steady_clock,
               bus_info p_bus);

  void driver_configure(const settings& p_settings) override;

  virtual void driver_transaction(
    hal::byte p_address,
    std::span<const hal::byte> p_data_out,
    std::span<hal::byte> p_data_in,
    function_ref<hal::timeout_function> p_timeout) override;

private:
  void send_start_condition();

  void send_stop_condition();

  void write_address(hal::byte p_address,
                     function_ref<hal::timeout_function> p_timeout);

  void write(std::span<const hal::byte> p_data_out,
             function_ref<hal::timeout_function> p_timeout);

  bool write_byte(hal::byte p_byte_to_write,
                  function_ref<hal::timeout_function> p_timeout);

  void write_bit(hal::byte p_bit_to_write,
                 function_ref<hal::timeout_function> p_timeout);

  void read(std::span<hal::byte> p_data_in,
            function_ref<hal::timeout_function> p_timeout);

  hal::byte read_byte();

  hal::byte read_bit();

  /**
   * @brief an output pin which will mimic the behavior of an I2C scl pin
   */
  output_pin* m_scl;
  /**
   * @brief an output pin which will mimic the bahavior of an I2C sda pin
   */
  output_pin* m_sda;
  /**
   * @brief a steady_clock which will be used to correctly time the different
   * frequencies
   */
  steady_clock* m_clock;

  /**
   * @brief the time that scl will be held high for
   */
  std::chrono::nanoseconds m_scl_high_time;
  /**
   * @brief the time that scl will be held low for
   */
  std::chrono::nanoseconds m_scl_low_time;

  /**
   * @brief all the information that the bus will need to operate on
   */
  bus_info m_bus;
};
}  // namespace hal