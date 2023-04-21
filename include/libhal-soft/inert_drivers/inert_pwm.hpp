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

#include <libhal/pwm.hpp>

namespace hal {
/**
 * @brief Inert implementation of Pulse Width Modulation (PWM) channel hardware
 *
 */
class inert_pwm : public hal::pwm
{
public:
  /**
   * @brief Factory function to create inert_pwm object
   *
   * @return result<inert_pwm> - Constructed inert_pwm object
   */
  static result<inert_pwm> create()
  {
    return inert_pwm();
  }

private:
  constexpr inert_pwm()
  {
  }

  result<frequency_t> driver_frequency([[maybe_unused]] hertz p_frequency)
  {
    return frequency_t{};
  };

  result<duty_cycle_t> driver_duty_cycle([[maybe_unused]] float p_duty_cycle)
  {
    return duty_cycle_t{};
  };
};
}  // namespace hal
