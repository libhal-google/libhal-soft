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

#include <libhal/distance_sensor.hpp>

namespace hal::soft {
/**
 * @brief Inert implementation of linear distance hardware
 *
 */
class inert_distance_sensor : public hal::distance_sensor
{
public:
  /**
   * @brief Factory function to create inert_distance_sensor object
   *
   * @param p_result - read_t data to be returned when calling read()
   * @return result<inert_distance_sensor> - Constructed inert_distance_sensor
   * object
   */
  static result<inert_distance_sensor> create(read_t p_result)
  {
    return inert_distance_sensor(p_result);
  }

private:
  constexpr inert_distance_sensor(read_t p_result)
    : m_result(p_result)
  {
  }

  result<read_t> driver_read()
  {
    return m_result;
  };

  read_t m_result;
};
}  // namespace hal::soft
