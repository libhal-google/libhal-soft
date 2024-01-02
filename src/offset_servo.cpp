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

// Use "#pragma once" as an include guard for headers
// This is required because it ensures that the compiler will process this file
// only once, no matter how many times it is included.
#include <libhal-soft/offset_servo.hpp>
#include <libhal-util/units.hpp>

namespace hal::soft {

result<offset_servo> offset_servo::create(hal::servo& p_servo,
                                          hal::degrees p_offset)
{
  return offset_servo(p_servo, p_offset);
}
hal::degrees offset_servo::get_offset()
{
  return m_offset;
}

void offset_servo::set_offset(hal::degrees p_offset)
{
  m_offset = p_offset;
}
offset_servo::offset_servo(hal::servo& p_servo, hal::degrees p_offset)
  : m_servo(&p_servo)
  , m_offset(p_offset)
{
}

result<hal::servo::position_t> offset_servo::driver_position(
  hal::degrees p_position)
{
  return HAL_CHECK(m_servo->position(p_position + m_offset));
}

}  // namespace hal::soft
