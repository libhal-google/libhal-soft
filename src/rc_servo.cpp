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

#include <libhal-soft/rc_servo.hpp>

#include <libhal-util/map.hpp>

namespace hal::soft {
rc_servo::rc_servo(hal::pwm& p_pwm, settings p_settings)
  : m_pwm(&p_pwm)
{
  // Check if any errors happened while setting the frequency of the pwm.
  // Using HAL_CHECK will return any errors that occur from the factory
  // function allowing the caller to choose what to do with the error
  // information.
  p_pwm.frequency(p_settings.frequency);

  // Calculate the wavelength in microseconds.
  auto wavelength = (1.0f / p_settings.frequency) * std::micro::den;
  // min_percent represents the minimum float to be used with the pwm
  // signal. The float is calculated by using the minimum width of the
  // signal in microseconds divided by the wavelength to get the decimal
  // representation of the float.
  auto min_percent =
    static_cast<float>(p_settings.min_microseconds) / wavelength;
  // max_percent represents the maximum float to be used with the pwm
  // signal. The float is calculated by using the maximum width of the
  // signal in microseconds divided by the wavelength to get the decimal
  // representation of the float.
  auto max_percent =
    static_cast<float>(p_settings.max_microseconds) / wavelength;
  // percent_range holds float value of min_percent and max_percent for use
  // with map function used in position().
  auto percent_range = std::make_pair(min_percent, max_percent);
  // angle_range holds degrees values of MinAngle and MaxAngle for use with
  // map function and range checking used in postion()
  auto angle_range = std::make_pair(static_cast<float>(p_settings.min_angle),
                                    static_cast<float>(p_settings.max_angle));
  // If no errors happen, call the constructor with verified parameters
  m_ranges = ranges{ .percent = percent_range, .angle = angle_range };
}

// Drivers must implement functions that are listed in interface.
void rc_servo::driver_position(hal::degrees p_position)
{
  // The angle of p_position should be within the min and max
  // angles of the servo. If the provided position is out of the
  // provided range, an invalid_argument error is thrown.
  if (p_position < std::get<0>(m_ranges.angle) ||
      p_position > std::get<1>(m_ranges.angle)) {
    hal::safe_throw(hal::argument_out_of_domain(this));
  }
  // The range of p_position should be within the servo's angle
  // range that was defined during creation. The value of
  // p_position is mapped within the float range of the pwm
  // signal to get the decimal value of the scaled_float.
  //
  // Example:
  // pwm min float: float(0.05)
  // pwm max float: float(0.25)
  // min angle: float(0.0)
  // max angle: float(180.0)
  //
  // float(0.05) = position(float(0.0))
  // float(0.10) = position(float(45.0))
  // float(0.15) = position(float(90.0))
  // float(0.20) = position(float(135.0))
  // float(0.25) = position(float(180.0))
  auto scaled_percent_raw = map(p_position, m_ranges.angle, m_ranges.percent);
  auto scaled_percent = float(scaled_percent_raw);
  // Set the duty cycle of the pwm with the scaled percent.
  m_pwm->duty_cycle(scaled_percent);
}
}  // namespace hal::soft
