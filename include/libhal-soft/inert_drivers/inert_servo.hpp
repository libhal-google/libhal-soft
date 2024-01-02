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

#include <libhal/servo.hpp>

namespace hal::soft {
/**
 * @brief Inert implementation of position controlled actuator
 *
 */
class inert_servo : public hal::servo
{
public:
  /**
   * @brief Factory function to create inert_servo object
   *
   * @return result<inert_servo> - Constructed inert_servo object
   */
  static result<inert_servo> create()
  {
    return inert_servo();
  }

private:
  constexpr inert_servo()
  {
  }

  result<position_t> driver_position([[maybe_unused]] float p_position)
  {
    return position_t{};
  };
};
}  // namespace hal::soft
