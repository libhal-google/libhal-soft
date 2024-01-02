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

#include <libhal-mock/servo.hpp>
#include <libhal-soft/offset_servo.hpp>

#include <boost/ut.hpp>

namespace hal::soft {
void offset_servo_test()
{
  using namespace boost::ut;
  "hal::soft::offset_servo::create"_test = []() {
    // Setup
    hal::mock::servo mock_servo;
    auto offset = hal::degrees(10.0);

    // Exercise
    auto result0 = offset_servo::create(mock_servo, offset);
    auto offset_servo = result0.value();
    auto result1 = offset_servo.get_offset();

    // Verify
    expect(bool{ result0 });

    expect(that % result1 == offset);
  };

  "hal::soft::offset_servo::set_offset"_test = []() {
    // Setup
    hal::mock::servo mock_servo;
    auto offset0 = hal::degrees(10.0);
    auto offset1 = hal::degrees(0.0);
    auto offset2 = hal::degrees(-10.0);

    auto offset_servo = offset_servo::create(mock_servo, offset0).value();

    // Exercise + Verify
    auto result0 = offset_servo.get_offset();
    expect(that % result0 == offset0);

    offset_servo.set_offset(offset1);
    auto result1 = offset_servo.get_offset();
    expect(that % result1 == offset1);

    offset_servo.set_offset(offset2);
    auto result2 = offset_servo.get_offset();
    expect(that % result2 == offset2);
  };

  "hal::soft::offset_servo::position"_test = []() {
    // Setup
    hal::mock::servo mock_servo;
    auto offset0 = hal::degrees(10.0);
    auto offset1 = hal::degrees(0.0);
    auto offset2 = hal::degrees(-10.0);

    auto offset_servo = offset_servo::create(mock_servo, offset0).value();

    auto angle0 = hal::degrees(50.0);
    auto angle1 = hal::degrees(0.0);
    auto angle2 = hal::degrees(-50.0);

    auto expected0 = hal::degrees(60.0);
    auto expected1 = hal::degrees(10.0);
    auto expected2 = hal::degrees(-40.0);
    auto expected3 = hal::degrees(50.0);
    auto expected4 = hal::degrees(00.0);
    auto expected5 = hal::degrees(-50.0);
    auto expected6 = hal::degrees(40.0);
    auto expected7 = hal::degrees(-10.0);
    auto expected8 = hal::degrees(-60.0);

    // Exercise
    auto result0 = offset_servo.position(angle0);
    auto result1 = offset_servo.position(angle1);
    auto result2 = offset_servo.position(angle2);

    offset_servo.set_offset(offset1);
    auto result3 = offset_servo.position(angle0);
    auto result4 = offset_servo.position(angle1);
    auto result5 = offset_servo.position(angle2);

    offset_servo.set_offset(offset2);
    auto result6 = offset_servo.position(angle0);
    auto result7 = offset_servo.position(angle1);
    auto result8 = offset_servo.position(angle2);

    // Verify
    expect(bool{ result0 });
    expect(bool{ result1 });
    expect(bool{ result2 });
    expect(bool{ result3 });
    expect(bool{ result4 });
    expect(bool{ result5 });
    expect(bool{ result6 });
    expect(bool{ result7 });
    expect(bool{ result8 });

    expect(that % std::get<0>(mock_servo.spy_position.call_history().at(0)) ==
           expected0);
    expect(that % std::get<0>(mock_servo.spy_position.call_history().at(1)) ==
           expected1);
    expect(that % std::get<0>(mock_servo.spy_position.call_history().at(2)) ==
           expected2);
    expect(that % std::get<0>(mock_servo.spy_position.call_history().at(3)) ==
           expected3);
    expect(that % std::get<0>(mock_servo.spy_position.call_history().at(3)) ==
           expected3);
    expect(that % std::get<0>(mock_servo.spy_position.call_history().at(4)) ==
           expected4);
    expect(that % std::get<0>(mock_servo.spy_position.call_history().at(5)) ==
           expected5);
    expect(that % std::get<0>(mock_servo.spy_position.call_history().at(6)) ==
           expected6);
    expect(that % std::get<0>(mock_servo.spy_position.call_history().at(7)) ==
           expected7);
    expect(that % std::get<0>(mock_servo.spy_position.call_history().at(8)) ==
           expected8);
  };
};
}  // namespace hal::soft
