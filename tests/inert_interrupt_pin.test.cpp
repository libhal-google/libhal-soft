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

#include <libhal-soft/inert_drivers/inert_interrupt_pin.hpp>

#include <boost/ut.hpp>

namespace hal {
void inert_interrupt_pin_test()
{
  using namespace boost::ut;
  "inert_interrupt_pin"_test = []() {
    // Setup
    auto configure_settings = interrupt_pin::settings{};
    auto test = inert_interrupt_pin::create().value();

    // Exercise
    auto result = test.configure(configure_settings);

    // Verify
    expect(bool{ result });
  };
};
}  // namespace hal
