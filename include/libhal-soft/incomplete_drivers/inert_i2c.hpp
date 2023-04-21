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
 * @brief Inert implementation of Inter-integrated Circuit (I2C) hardware
 *
 */
class inert_i2c : public hal::i2c
{
public:
  /**
   * @brief Factory function to create inert_i2c object
   *
   * @return result<inert_i2c> - Constructed inert_i2c object
   */
  static result<inert_i2c> create()
  {
    return inert_i2c();
  }

private:
  constexpr inert_i2c()
  {
  }

  status driver_configure([[maybe_unused]] const settings& p_settings)
  {
    return hal::success();
  };

  result<transaction_t> driver_transaction(
    [[maybe_unused]] hal::byte p_address,
    [[maybe_unused]] std::span<const hal::byte> p_data_out,
    [[maybe_unused]] std::span<hal::byte> p_data_in,
    [[maybe_unused]] hal::function_ref<hal::timeout_function> p_timeout)
  {
    return transaction_t{};
  };
};
}  // namespace hal
