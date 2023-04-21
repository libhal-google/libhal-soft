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

#include <libhal-soft/inert_drivers/inert_output_pin.hpp>

#include <boost/ut.hpp>

namespace hal {
void inert_output_pin_test()
{
  using namespace boost::ut;
  "inert_output_pin"_test = []() {
    // Setup
    auto test = inert_output_pin::create().value();

    // Exercise
    auto set_level_high_result = test.level(true);
    auto get_level_high_result = test.level();
    auto set_level_low_result = test.level(false);
    auto get_level_low_result = test.level();

    // Verify
    expect(bool{ set_level_high_result });
    expect(bool{ get_level_high_result });
    expect(bool{ set_level_low_result });
    expect(bool{ get_level_low_result });
  };
};
}  // namespace hal
