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

namespace hal {
/**
 * @brief A bit bang implementation for i2c. This implementation of i2c only
 * needs 2 gpio's to work correctly. In its current implementation we only
 * support single controller multiple peripheral. But have intentions of
 * supporting multiple controller soon. Additionally, it's important to note that bit bang
 * is a best try implementation of i2c. As in it will do it's best to reach the requested frequency but will typically be slower then requested
 * with brief testing it seems that the error is about 2us per period for the lpc4078 , so you can try to account for this error with the frequency you set
 * for example, achieving the correct period for 100kHz would result in setting slightly more then a 125kHz frequency. Additionally, the fastest frequency this bit bang can handle is around 200kHz.
 */
class i2c_bit_bang : public i2c
{
public:

  /// holds all of the information for an i2c bus
  struct bus_info
  {
    float duty_cycle = 0.5f;
  };

  /**
   * @brief Construct a new i2c bit bang object
   *
   * @param p_scl an output pin which will imitate the scl pin in a normal i2c
   * hardware interface
   * @param p_sda an output pin which will imitate the sda pin in a normal i2c
   * hardwar interface
   * @param p_steady_clock a steady clock that should have a higher frequency then the configured frequency for the bit bang
   * @param p_bus the bus information which will be used which configuring the bit bang interface
   */

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
  /**
   * @brief this function will send the start condition and it will always pull the pins high before sending the start condition
   */
  void send_start_condition();

  /**
   * @brief this function will send the stop condition while also making sure the sda pin is pulled low before sending the stop condition
   * 
   */
  void send_stop_condition();

  /**
   * @brief this function will go through the steps of writing the address of the peripheral the controller wishes to speak to while also ensuring the data written is acknowledged
   * 
   * @param p_address the address of the peripheral, configured with the read/write bit already that the controller is requesting to talk to
   * @param p_timeout a timeout function which is primarily used for clock stretching to ensure the peripheral doesn't hold the line too long
   * 
   * @throws hal::io_error when the address written to the bus was not acknowledged
   */
  void write_address(hal::byte p_address,
                     function_ref<hal::timeout_function> p_timeout);

  /**
   * @brief this function will write the entire contents of the span out to the bus while making sure all data gets acknowledged
   * 
   * @param p_data_out this is a span of bytes which will be written to the bus
   * @param p_timeout a timeout function which is primarily used for clock stretching to ensure the peripheral doesn't hold the line too long
   */
  void write(std::span<const hal::byte> p_data_out,
             function_ref<hal::timeout_function> p_timeout);

  /**
   * @brief this function will handle writing a singular byte each call while also retrieving the acknowledge bits
   * 
   * @param p_byte_to_write this is the byte that will be written to the bus
   * @param p_timeout a timeout function which is primarily used for clock stretching to ensure the peripheral doesn't hold the line too long
   * @return bool - true when the byte written was ack'd and false when it was nack'd 
   */
  bool write_byte(hal::byte p_byte_to_write,
                  function_ref<hal::timeout_function> p_timeout);

  /**
   * @brief this function will write a single bit at a time, dealing with simulating the clock and the clock stretching feature
   * 
   * @param p_bit_to_write the bit which will be written on the bus
   * @param p_timeout a timeout function which is primarily used for clock stretching to ensure the peripheral doesn't hold the line too long
   */
  void write_bit(hal::byte p_bit_to_write,
                 function_ref<hal::timeout_function> p_timeout);

  /**
   * @brief this function will read in as many bytes as allocated inside of the span while also acking or nacking the data
   * 
   * @param p_data_in a span which will be filled with the bytes that will be read from the bus
   * @param p_timeout a timeout function which is primarily used for clock stretching to ensure the peripheral doesn't hold the line too long
   */
  void read(std::span<hal::byte> p_data_in,
            function_ref<hal::timeout_function> p_timeout);

  /**
   * @brief this function is responsible for reading a byte at a time off the bus and also creating the byte from bits
   * 
   * @return hal::byte the byte that has been read off of the bus
   */
  hal::byte read_byte();

  /**
   * @brief this function is responsible for reading a single bit at a time off of the bus while also managing the clock line. It will release (pull sda high) every time it is called
   * 
   * @return hal::byte 
   */
  hal::byte read_bit();

  /**
   * @brief this function is a high speed version of the hal::delay function which operates on ticks rather then a time duration
   * where hal::delay provides delays up to 17us, this function will provide delays up to about 2.7us making it optimal for high accuracy delay
   * 
   * @param ticks the amount of ticks this function will delay for, this should be based on the frequency of the clock passed into the bit_bang class
   */
  [[gnu::always_inline]] inline void high_speed_delay(uint64_t ticks);

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
  uint64_t m_scl_high_ticks;
  /**
   * @brief the time that scl will be held low for
   */
  uint64_t m_scl_low_ticks;

  /**
   * @brief the amount of ticks that the uptime function takes to run, we store this so we save computation time in our high speed delay function
   */
  uint32_t m_uptime_ticks;

  /**
   * @brief all the information that the bus will need to operate on
   */
  bus_info m_bus;
};
}  // namespace hal
