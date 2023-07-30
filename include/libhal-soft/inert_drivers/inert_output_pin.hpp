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

#include <libhal/output_pin.hpp>

namespace hal::soft {
/**
 * @brief Inert implementation of digital output pin hardware
 *
 */
class inert_output_pin : public hal::output_pin
{
public:
  /**
   * @brief Factory function to create inert_output_pin
   *
   * @param p_level - level_t object to return when level() is called. This
   * value can be changed by using level(bool) after creation.
   * @return result<inert_output_pin> - Constructed inert_output_pin object
   */
  static result<inert_output_pin> create(bool p_level)
  {
    return inert_output_pin(p_level);
  }

private:
  constexpr inert_output_pin(bool p_level)
    : m_level(&p_level)
  {
  }

  status driver_configure(const settings& p_settings)
  {
    return hal::success();
  };

  result<set_level_t> driver_level(bool p_high)
  {
    m_level = p_high;
    return set_level_t{};
  };

  result<level_t> driver_level()
  {
    return level_t{ .state = m_level };
  };

  bool m_level;
};
}  // namespace hal::soft
