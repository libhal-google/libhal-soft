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

#include <libhal-soft/inert_drivers/inert_adc.hpp>

#include <boost/ut.hpp>

namespace hal {
void inert_adc_test()
{
  using namespace boost::ut;
  "inert_adc"_test = []() {
    // Setup
    constexpr auto expected = adc::read_t{ 0.5f };
    auto test = inert_adc::create(expected).value();

    // Exercise
    auto result = test.read();

    // Verify
    expect(bool{ result });
    expect(that % expected.sample == result.value().sample);
  };
};
}  // namespace hal
