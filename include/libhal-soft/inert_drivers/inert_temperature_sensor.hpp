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

#include <libhal/temperature_sensor.hpp>

namespace hal {
/**
 * @brief Inert implementation of temperature sensing hardware
 *
 */
class inert_temperature_sensor : public hal::temperature_sensor
{
public:
  /**
   * @brief Factory function to create inert_temperature_sensor object
   *
   * @param p_temperature - read_t object to return when read() is called
   * @return result<inert_temperature_sensor> - Constructed
   * inert_temperature_sensor object
   */
  static result<inert_temperature_sensor> create(read_t p_temperature)
  {
    return inert_temperature_sensor(p_temperature);
  }

private:
  constexpr inert_temperature_sensor(read_t p_temperature)
    : m_temperature(p_temperature)
  {
  }

  result<read_t> driver_read()
  {
    return m_temperature;
  };

  read_t m_temperature;
};
}  // namespace hal
