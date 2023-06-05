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

#include <libhal/i2c.hpp>

namespace hal {
/**
 * @brief A i2c wrapper to ensure that the lowest i2c device frequency is used.
 *
 */
class minimum_speed_i2c : public hal::i2c
{
public:
  constexpr static auto default_max_speed = 2'000'000;
  /**
   * @brief Factory function to create minimum_speed_i2c object.
   *
   * @param p_i2c - i2c object that the device will use
   * @param p_frequency - the maximum starting frequency the device can use
   * @return minimum_speed_i2c - the configured i2c object using the lowest seen
   * frequency
   */
  static result<minimum_speed_i2c> create(
    hal::i2c& p_i2c,
    hertz p_frequency = default_max_speed);

private:
  minimum_speed_i2c(hal::i2c& p_i2c, hertz p_frequency);

  status driver_configure(const settings& p_new_setting) override;

  result<transaction_t> driver_transaction(
    hal::byte p_address,
    std::span<const hal::byte> p_data_out,
    std::span<hal::byte> p_data_in,
    hal::function_ref<hal::timeout_function> p_timeout) override;

  hal::i2c* m_i2c;
  hertz m_lowest_seen_frequency;
};
}  // namespace hal
