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

#include <libhal/input_pin.hpp>

namespace hal {
/**
 * @brief Inert implementation of digital input pin hardware
 *
 */
class inert_input_pin : public hal::input_pin
{
public:
  /**
   * @brief Factory function to create inert_input_pin object
   *
   * @param p_level - level_t object to retrun when level() is called
   * @return result<inert_input_pin> - Constructed inert_input_pin object
   */
  static result<inert_input_pin> create(level_t p_level)
  {
    return inert_input_pin(p_level);
  }

private:
  constexpr inert_input_pin(level_t p_level)
    : m_level(p_level)
  {
  }

  status driver_configure([[maybe_unused]] const settings& p_settings)
  {
    return hal::success();
  };

  result<level_t> driver_level()
  {
    return m_level;
  };

  level_t m_level;
};
}  // namespace hal
