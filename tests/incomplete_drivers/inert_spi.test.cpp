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

#include <libhal-soft/inert_drivers/inert_spi.hpp>

#include <boost/ut.hpp>

namespace hal::soft {
void inert_spi_test()
{
  using namespace boost::ut;
  "inert_spi"_test = []() {
    // Setup
    const std::array<hal::byte, 4> data_out{ 'a', 'b' };
    std::array<hal::byte, 4> data_in{ '1', '2' };
    const auto data_filler = ' ';
    constexpr auto configure_settings = spi::settings{};
    auto test = inert_spi::create();

    // Exercise
    auto configure_result = test.configure(configure_settings);
    auto transfer_result = test.transfer(data_out, data_in, data_filler);

    // Verify
    expect(bool{ configure_result });
    expect(bool{ transfer_result });
  };
};
}  // namespace hal::soft
