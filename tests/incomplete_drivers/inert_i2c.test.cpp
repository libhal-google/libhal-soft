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

#include <libhal-soft/inert_drivers/inert_i2c.hpp>

#include <boost/ut.hpp>

namespace hal::soft {
void inert_i2c_test()
{
  using namespace boost::ut;
  "inert_i2c"_test = []() {
    // Setup
    constexpr hal::i2c::settings configure_settings{ .clock_rate = 1.0_Hz };
    constexpr hal::byte address{ 100 };
    constexpr std::array<hal::byte, 4> data_out{ 'a', 'b' };
    std::array<hal::byte, 4> data_in{ '1', '2' };
    const hal::function_ref<hal::timeout_function> timeout = []() {
      return success();
    };
    auto test = inert_i2c::create().value();

    // Exercise
    auto configure_result = test.configure(configure_settings);
    auto transaction_result =
      test.transaction(address, data_out, data_in, timeout);

    // Verify
    expect(bool{ configure_result });
    expect(bool{ transaction_result });
  };
};
}  // namespace hal::soft
