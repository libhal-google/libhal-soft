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

#include <libhal-soft/inert_drivers/inert_timer.hpp>

#include <boost/ut.hpp>

namespace hal::soft {
void inert_timer_test()
{
  using namespace boost::ut;
  "inert_timer"_test = []() {
    // Setup
    const hal::callback<void(void)> callback = []() {};
    const hal::time_duration delay = {};
    auto is_running = timer::is_running_t{ true };
    auto is_not_running = timer::is_running_t{ false };
    auto test1 = inert_timer::create(is_running).value();
    auto test2 = inert_timer::create(is_not_running).value();

    // Exercise
    auto is_running_result1 = test1.is_running();
    auto is_running_result2 = test2.is_running();
    auto cancel_result = test1.cancel();
    auto schedule_result = test1.schedule(callback, delay);

    // Verify
    expect(bool{ is_running_result1 });
    expect(bool{ is_running_result2 });
    expect(bool{ cancel_result });
    expect(bool{ schedule_result });
    expect(that % true == is_running_result1.value().is_running);
    expect(that % false == is_running_result2.value().is_running);
  };
};
}  // namespace hal::soft
