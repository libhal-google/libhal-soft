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

#include <libhal/interrupt_pin.hpp>

namespace hal::soft {
/**
 * @brief Inert implementation of digital interrupt pin hardware
 *
 */
class inert_interrupt_pin : public hal::interrupt_pin
{
public:
  /**
   * @brief Factory function to create inert_interrupt_pin object
   *
   * @return result<inert_interrupt_pin> - Constructed inert_interrupt_pin
   * object
   */
  static result<inert_interrupt_pin> create()
  {
    return inert_interrupt_pin();
  }

private:
  constexpr inert_interrupt_pin()
  {
  }

  status driver_configure([[maybe_unused]] const settings& p_settings)
  {
    return hal::success();
  };

  void driver_on_trigger([[maybe_unused]] hal::callback<handler> p_callback){};
};
}  // namespace hal::soft
