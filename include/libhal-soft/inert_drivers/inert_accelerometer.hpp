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

#include <libhal/accelerometer.hpp>

namespace hal::soft {
/**
 * @brief Inert implementation of acceleration sensing hardware
 *
 */
class inert_accelerometer : public hal::accelerometer
{
public:
  /**
   * @brief Factory function to create inert_accelerometer object
   *
   * @param p_values - Read values to return when reading the
   * inert_accelerometer.
   * @return result<inert_accelerometer> - Constructed inert_accelerometer
   * object
   */
  static result<inert_accelerometer> create(read_t p_values)
  {
    return inert_accelerometer(p_values);
  }

private:
  constexpr inert_accelerometer(read_t p_values)
    : m_values(p_values)
  {
  }

  result<read_t> driver_read()
  {
    return m_values;
  };

  read_t m_values;
};
}  // namespace hal::soft
