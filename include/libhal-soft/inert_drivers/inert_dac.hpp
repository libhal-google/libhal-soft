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

#pragma once

#include <libhal/dac.hpp>

namespace hal {
/**
 * @brief Inert implementation of Digital to Analog Converter (DAC) hardware
 *
 */
class inert_dac : public hal::dac
{
public:
  /**
   * @brief Factory function to create inert_dac object
   *
   * @return result<inert_dac> - Constructed inert_dac object
   */
  static result<inert_dac> create()
  {
    return inert_dac();
  }

private:
  constexpr inert_dac()
  {
  }

  result<write_t> driver_write([[maybe_unused]] float p_percentage)
  {
    return write_t{};
  };
};
}  // namespace hal
