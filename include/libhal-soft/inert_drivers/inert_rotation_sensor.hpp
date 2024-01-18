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

#include <libhal/rotation_sensor.hpp>

namespace hal::soft {
/**
 * @brief Inert implementation of rotation measuring hardware
 *
 */
class inert_rotation_sensor : public hal::rotation_sensor
{
public:
  /**
   * @brief Factory function to create inert_rotation_sensor object
   *
   * @param p_position - read_t object to return when read() is called
   * @return result<inert_rotation_sensor> - Constructed inert_rotation_sensor
   * onject
   */
  static result<inert_rotation_sensor> create(read_t p_position)
  {
    return inert_rotation_sensor(p_position);
  }

private:
  constexpr inert_rotation_sensor(read_t p_position)
    : m_position(p_position)
  {
  }

  result<read_t> driver_read()
  {
    return m_position;
  };

  read_t m_position;
};
}  // namespace hal::soft
