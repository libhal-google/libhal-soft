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

#include <libhal-soft/inert_drivers/inert_distance_sensor.hpp>

#include <boost/ut.hpp>

namespace hal {
void inert_distance_sensor_test()
{
  using namespace boost::ut;
  "inert_distance_sensor"_test = []() {
    // Setup
    constexpr auto expected_read = distance_sensor::read_t{ 0.1f };
    auto test = inert_distance_sensor::create(expected_read).value();

    // Exercise
    auto result = test.read();

    // Verify
    expect(bool{ result });
    expect(that % expected_read.distance == result.value().distance);
  };
};
}  // namespace hal
