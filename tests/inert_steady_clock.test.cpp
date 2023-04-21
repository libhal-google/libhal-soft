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

#include <libhal-soft/inert_drivers/inert_steady_clock.hpp>

#include <boost/ut.hpp>

namespace hal {
void inert_steady_clock_test()
{
  using namespace boost::ut;
  "inert_steady_clock"_test = []() {
    // Setup
    constexpr auto expected_frequency = steady_clock::frequency_t{ 0.5f };
    constexpr auto start_uptime = steady_clock::uptime_t{ 99 };
    constexpr auto expected_uptime = steady_clock::uptime_t{ 100 };
    auto test =
      inert_steady_clock::create(expected_frequency, start_uptime).value();

    // Exercise
    auto frequency_result = test.frequency();
    auto uptime_result = test.uptime();

    // Verify
    expect(bool{ frequency_result });
    expect(bool{ uptime_result });
    expect(that % expected_frequency.operating_frequency ==
           frequency_result.value().operating_frequency);
    expect(that % expected_uptime.ticks == uptime_result.value().ticks);
  };
};
}  // namespace hal
