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

#include <libhal-soft/i2c_minimum_speed.hpp>

namespace hal {
struct stub_i2c : public hal::i2c
{
private:
  status driver_configure(const settings& p_settings)
  {
    return hal::success();
  }
  result<transaction_t> driver_transaction(
    [[maybe_unused]] hal::byte p_address,
    [[maybe_unused]] std::span<const hal::byte> p_data_out,
    [[maybe_unused]] std::span<hal::byte> p_data_in,
    [[maybe_unused]] hal::function_ref<hal::timeout_function> p_timeout)
  {
    return transaction_t{};
  }
};
}  // namespace hal

int main()
{
  hal::stub_i2c i2c;
  [[maybe_unused]] auto min_speed_i2c = hal::minimum_speed_i2c::create(i2c);

  return 0;
}
