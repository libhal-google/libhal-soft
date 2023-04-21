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

#include <libhal/timer.hpp>

namespace hal {
/**
 * @brief Inert implementation of timer hardware
 *
 */
class inert_timer : public hal::timer
{
public:
  /**
   * @brief Factory function to create inert_timer object
   *
   * @param p_is_running - is_running_t object to return when is_running() is
   * called
   * @return result<inert_timer> - Constructed inert_timer object
   */
  static result<inert_timer> create(is_running_t p_is_running)
  {
    return inert_timer(p_is_running);
  }

private:
  constexpr inert_timer(is_running_t p_is_running)
    : m_is_running(p_is_running)
  {
  }

  result<is_running_t> driver_is_running()
  {
    return m_is_running;
  };

  result<cancel_t> driver_cancel()
  {
    return cancel_t{};
  };

  result<schedule_t> driver_schedule(
    [[maybe_unused]] hal::callback<void(void)> p_callback,
    [[maybe_unused]] hal::time_duration p_delay)
  {
    return schedule_t{};
  };

  is_running_t m_is_running;
};
}  // namespace hal
