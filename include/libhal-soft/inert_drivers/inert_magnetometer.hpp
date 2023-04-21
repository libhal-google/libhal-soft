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

#include <libhal/magnetometer.hpp>

namespace hal {
/**
 * @brief Inert implementation of magnetic field strength sensing hardware
 *
 */
class inert_magnetometer : public hal::magnetometer
{
public:
  /**
   * @brief Factory function to create an inert_magnetometer object
   *
   * @param p_result - read_t object to return when read() is called
   * @return result<inert_magnetometer> - Constructed inert_magnetometer object
   */
  static result<inert_magnetometer> create(read_t p_result)
  {
    return inert_magnetometer(p_result);
  }

private:
  constexpr inert_magnetometer(read_t p_result)
    : m_result(p_result)
  {
  }

  result<read_t> driver_read()
  {
    return m_result;
  };

  read_t m_result;
};
}  // namespace hal
