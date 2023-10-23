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
#include <libhal-soft/inverter.hpp>

namespace hal::soft {
output_pin_inverter::output_pin_inverter(hal::output_pin& p_output_pin)
  : m_output_pin(&p_output_pin)
{
}

status output_pin_inverter::driver_configure(const settings& p_settings)
{
  return m_output_pin->configure(p_settings);
};
result<hal::output_pin::set_level_t> output_pin_inverter::driver_level(
  bool p_high)
{
  return m_output_pin->level(!p_high);
};
result<hal::output_pin::level_t> output_pin_inverter::driver_level()
{
  auto level = HAL_CHECK(m_output_pin->level());
  level.state = !level.state;
  return level;
};

}  // namespace hal::soft
