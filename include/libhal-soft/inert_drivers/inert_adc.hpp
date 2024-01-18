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

#pragma once

#include <libhal/adc.hpp>

namespace hal::soft {
/**
 * @brief Inert implementation of Analog to Digital Converter (ADC) hardware
 *
 */
class inert_adc : public hal::adc
{
public:
  /**
   * @brief Factory function to create inert_adc object
   *
   * @param p_result - read_t object to return when reading the inert_adc
   * @return result<inert_adc> - Constructed inert_adc object
   */
  static result<inert_adc> create(read_t p_result)
  {
    return inert_adc(p_result);
  }

private:
  constexpr inert_adc(read_t p_result)
    : m_result(p_result)
  {
  }

  result<read_t> driver_read()
  {
    return m_result;
  };

  read_t m_result;
};
}  // namespace hal::soft
