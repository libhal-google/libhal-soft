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

#include <libhal-soft/inert_drivers/inert_serial.hpp>

#include <boost/ut.hpp>

namespace hal::soft {
void inert_serial_test()
{
  using namespace boost::ut;
  "inert_serial"_test = []() {
    // Setup
    std::array<hal::byte, 4> buffer;
    constexpr auto write_data = serial::write_t{};
    constexpr auto read_data = serial::read_t{};
    constexpr auto configure_settings = serial::settings{};
    auto test = inert_serial::create(write_data, read_data);

    // Exercise
    auto configure_result = test.configure(configure_settings);
    auto write_result = test.write(buffer);
    auto read_result = test.read(buffer);
    auto flush_result = test.flush();

    // Verify
    expect(bool{ configure_result });
    expect(bool{ write_result });
    expect(bool{ read_result });
    expect(bool{ flush_result });
  };
};
}  // namespace hal::soft
