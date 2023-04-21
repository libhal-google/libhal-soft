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

#include <libhal-soft/inert_drivers/inert_can.hpp>

#include <boost/ut.hpp>

namespace hal {
void inert_can_test()
{
  using namespace boost::ut;
  "inert_can"_test = []() {
    // Setup
    constexpr hal::can::settings settings{
      .baud_rate = 1.0_Hz,
    };
    constexpr hal::can::message_t message{ .id = 1, .length = 0 };
    auto test = inert_can::create(true).value();
    auto test2 = inert_can::create(false).value();

    // Exercise
    auto configure_result = test.configure(settings);
    auto send_result = test.send(message);
    auto bus_on_result = test.bus_on();
    auto bus_off_result = test2.bus_on();

    // Verify
    expect(bool{ configure_result });
    expect(bool{ send_result });
    expect(bool{ bus_on_result });
    expect(!bool{ bus_off_result });
  };
};
}  // namespace hal
