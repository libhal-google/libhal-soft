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

#include <libhal-soft/inert_drivers/inert_socket.hpp>

#include <boost/ut.hpp>

namespace hal::soft {
void inert_socket_test()
{
  using namespace boost::ut;
  "inert_socket"_test = []() {
    // Setup
    hal::function_ref<timeout_function> always_succeed = []() -> hal::status {
      return hal::success();
    };
    std::array<hal::byte, 4> buffer;
    auto write_data = socket::write_t{};
    auto read_data = socket::read_t{};
    auto test = inert_socket::create(write_data, read_data);

    // Exercise
    auto write_result = test.write(buffer, always_succeed);
    auto read_result = test.read(buffer);

    // Verify
    expect(bool{ write_result });
    expect(bool{ read_result });
  };
};
}  // namespace hal::soft
