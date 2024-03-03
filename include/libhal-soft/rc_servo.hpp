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

// Use "#pragma once" as an include guard for headers
// This is required because it ensures that the compiler will process this file
// only once, no matter how many times it is included.
#pragma once

#include <libhal/pwm.hpp>
#include <libhal/servo.hpp>

// Keep drivers within the namespace hal to not pollute global namespace
namespace hal::soft {
/**
 * @brief Generic RC servo driver.
 *
 */
class rc_servo : public hal::servo
{
public:
  /**
   * @brief Information about the RC servo needed to control it properly
   *
   */
  struct settings
  {
    /// @brief PWM signal frequency. Check the documentation for the RC servo to
    /// determine what range of frequencies can be used with it.
    hal::hertz frequency = 50;
    /// @brief The physical minimum angle that the servo shaft can move to
    hal::degrees min_angle = 0;
    /// @brief The physical maximum angle that the servo shaft can move to
    hal::degrees max_angle = 90;
    /// @brief The minimum pulse width in microseconds that maps to the minimum
    /// angle of the servo
    std::uint32_t min_microseconds = 1000;
    /// @brief The maximum pulse width in microseconds that maps to the maximum
    /// angle of the servo.
    std::uint32_t max_microseconds = 2000;
  };

  /**
   * @brief Create a rc_servo object.
   *
   * @param p_pwm - pwm signal connected to the RC servo
   * @param p_settings - RC servo settings
   */
  rc_servo(hal::pwm& p_pwm, settings p_settings);

private:
  struct ranges
  {
    std::pair<float, float> percent{};
    std::pair<float, float> angle{};
  };
  // Use override keyword to make it clear that this api is for virtual
  // functions
  void driver_position(hal::degrees p_position) override;

  // Use m_ prefix for private/protected class members.
  // Use a pointer here rather than a reference, because member references
  // implicitly delete move constructors
  hal::pwm* m_pwm;
  ranges m_ranges{};
};
}  // namespace hal::soft
