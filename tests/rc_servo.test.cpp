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

#include <libhal-mock/pwm.hpp>
#include <libhal-mock/testing.hpp>

#include <boost/ut.hpp>

namespace hal::soft {
void rc_servo_test()
{
  using namespace boost::ut;

  "hal::servo::rc_servo::create"_test = []() {
    // Setup
    hal::mock::pwm pwm0;
    hal::mock::pwm pwm1;
    hal::mock::pwm pwm2;

    // Exercise
    // Verify

    // use defaults
    [[maybe_unused]] rc_servo servo0(pwm0, {});
    // 100Hz (or 10ms per update) with 500us being max negative start and 2500us
    // being max positive.
    [[maybe_unused]] rc_servo servo1(pwm1,
                                     {
                                       .frequency = 100,
                                       .min_microseconds = 500,
                                       .max_microseconds = 2500,
                                     });

    pwm2.spy_frequency.trigger_error_on_call(
      1, []() { hal::safe_throw(hal::operation_not_supported(nullptr)); });

    [[maybe_unused]] auto f = throws([&]() { rc_servo servo2(pwm2, {}); });
  };

  "hal::servo::rc_servo::position"_test = []() {
    // Setup
    constexpr auto expected0 = float(0.05);
    constexpr auto expected1 = float(0.10);
    constexpr auto expected2 = float(0.15);
    constexpr auto expected3 = float(0.20);
    constexpr auto expected4 = float(0.25);

    constexpr auto angle0 = hal::degrees(0);
    constexpr auto angle1 = hal::degrees(45);
    constexpr auto angle2 = hal::degrees(90);
    constexpr auto angle3 = hal::degrees(135);
    constexpr auto angle4 = hal::degrees(180);

    hal::mock::pwm pwm;
    rc_servo servo(pwm,
                   {
                     .frequency = 100,
                     .min_angle = 0,
                     .max_angle = 180,
                     .min_microseconds = 500,
                     .max_microseconds = 2500,
                   });

    // Exercise
    servo.position(angle0);
    servo.position(angle1);
    servo.position(angle2);
    servo.position(angle3);
    servo.position(angle4);

    // Verify
    expect(that % expected0 ==
           std::get<0>(pwm.spy_duty_cycle.call_history().at(0)));
    expect(that % expected1 ==
           std::get<0>(pwm.spy_duty_cycle.call_history().at(1)));
    expect(that % expected2 ==
           std::get<0>(pwm.spy_duty_cycle.call_history().at(2)));
    expect(that % expected3 ==
           std::get<0>(pwm.spy_duty_cycle.call_history().at(3)));
    expect(that % expected4 ==
           std::get<0>(pwm.spy_duty_cycle.call_history().at(4)));
  };

  "hal::servo::rc_servo::position negative angles"_test = []() {
    // Setup
    constexpr auto expected0 = float(0.05);
    constexpr auto expected1 = float(0.10);
    constexpr auto expected2 = float(0.15);
    constexpr auto expected3 = float(0.20);
    constexpr auto expected4 = float(0.25);

    constexpr auto angle0 = hal::degrees(-90);
    constexpr auto angle1 = hal::degrees(-45);
    constexpr auto angle2 = hal::degrees(0);
    constexpr auto angle3 = hal::degrees(45);
    constexpr auto angle4 = hal::degrees(90);

    hal::mock::pwm pwm;
    rc_servo servo(pwm,
                   {
                     .frequency = 100,
                     .min_angle = -90,
                     .max_angle = 90,
                     .min_microseconds = 500,
                     .max_microseconds = 2500,
                   });

    // Exercise
    servo.position(angle0);
    servo.position(angle1);
    servo.position(angle2);
    servo.position(angle3);
    servo.position(angle4);

    // Verify
    expect(that % expected0 ==
           std::get<0>(pwm.spy_duty_cycle.call_history().at(0)));
    expect(that % expected1 ==
           std::get<0>(pwm.spy_duty_cycle.call_history().at(1)));
    expect(that % expected2 ==
           std::get<0>(pwm.spy_duty_cycle.call_history().at(2)));
    expect(that % expected3 ==
           std::get<0>(pwm.spy_duty_cycle.call_history().at(3)));
    expect(that % expected4 ==
           std::get<0>(pwm.spy_duty_cycle.call_history().at(4)));
  };

  "servo errors test"_test = []() {
    // Setup
    hal::mock::pwm pwm;
    constexpr hal::degrees min_angle = 0.0f;
    constexpr hal::degrees max_angle = 90.0f;
    rc_servo test(pwm,
                  {
                    .frequency = 100,
                    .min_angle = min_angle,
                    .max_angle = max_angle,
                    .min_microseconds = 500,
                    .max_microseconds = 2500,
                  });

    // Exercise
    // Verify
    [[maybe_unused]] auto f = throws<hal::argument_out_of_domain>(
      [&]() { test.position(max_angle + 45.0f); });
  };
};
}  // namespace hal::soft
