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

#include <libhal-soft/inverter.hpp>

#include <libhal-mock/input_pin.hpp>
#include <libhal-mock/output_pin.hpp>

#include <boost/ut.hpp>

namespace hal::soft {
void output_pin_iverter_test()
{
  using namespace boost::ut;

  "hal::output_pin_inverter::configure"_test = []() {
    "configure() with default settings"_test = []() {
      // Setup
      hal::mock::output_pin mock_output_pin;
      hal::output_pin::settings expected_settings;
      auto inverted_output_pin = output_pin_inverter(mock_output_pin);

      // Exercise
      inverted_output_pin.configure(expected_settings);
      auto result_settings =
        std::get<0>(mock_output_pin.spy_configure.call_history().at(0));

      // Verify
      expect(false == result_settings.open_drain);
      expect(pin_resistor::none == result_settings.resistor);
    };

    "configure() with set values for settings"_test = []() {
      // Setup
      hal::mock::output_pin mock_output_pin;
      hal::output_pin::settings expected_settings;
      expected_settings.open_drain = true;
      expected_settings.resistor = pin_resistor::pull_down;
      auto inverted_output_pin = output_pin_inverter(mock_output_pin);

      // Exercise
      inverted_output_pin.configure(expected_settings);
      auto result_settings =
        std::get<0>(mock_output_pin.spy_configure.call_history().at(0));

      // Verify
      expect(true == result_settings.open_drain);
      expect(pin_resistor::pull_down == result_settings.resistor);
    };
  };

  "hal::output_pin_inverter::level"_test = []() {
    "level(true)"_test = []() {
      // Setup
      hal::mock::output_pin mock_output_pin;
      auto inverted_output_pin = output_pin_inverter(mock_output_pin);

      // Exercise
      inverted_output_pin.level(true);
      auto value_sent_to_level =
        std::get<0>(mock_output_pin.spy_level.call_history().at(0));
      auto level_result = inverted_output_pin.level();

      // Verify
      expect(that % false == value_sent_to_level);
      expect(that % true == level_result);
    };

    "level(false)"_test = []() {
      // Setup
      hal::mock::output_pin mock_output_pin;
      auto inverted_output_pin = output_pin_inverter(mock_output_pin);

      // Exercise
      inverted_output_pin.level(false);
      auto value_sent_to_level =
        std::get<0>(mock_output_pin.spy_level.call_history().at(0));
      auto level_result = inverted_output_pin.level();

      // Verify
      expect(that % true == value_sent_to_level);
      expect(that % false == level_result);
    };
  };
}

void input_pin_iverter_test()
{
  using namespace boost::ut;

  "hal::input_pin_inverter::configure"_test = []() {
    "configure() with default settings"_test = []() {
      // Setup
      hal::mock::input_pin mock_input_pin;
      hal::input_pin::settings expected_settings;
      auto inverted_input_pin = input_pin_inverter(mock_input_pin);

      // Exercise
      inverted_input_pin.configure(expected_settings);
      auto result_settings =
        std::get<0>(mock_input_pin.spy_configure.call_history().at(0));

      // Verify
      expect(pin_resistor::pull_up == result_settings.resistor);
    };

    "configure() with set values for settings"_test = []() {
      // Setup
      hal::mock::input_pin mock_input_pin;
      hal::input_pin::settings expected_settings;
      expected_settings.resistor = pin_resistor::pull_down;
      auto inverted_input_pin = input_pin_inverter(mock_input_pin);

      // Exercise
      inverted_input_pin.configure(expected_settings);
      auto result_settings =
        std::get<0>(mock_input_pin.spy_configure.call_history().at(0));

      // Verify
      expect(pin_resistor::pull_down == result_settings.resistor);
    };
  };

  "hal::input_pin_inverter::level"_test = []() {
    "level()"_test = []() {
      // Setup
      hal::mock::input_pin mock_input_pin;
      auto inverted_input_pin = input_pin_inverter(mock_input_pin);
      std::deque inputs{ true, false };
      std::queue queue(inputs);
      mock_input_pin.set(queue);

      // Exercise
      auto result1 = inverted_input_pin.level();
      auto result2 = inverted_input_pin.level();

      // Verify
      expect(that % false == result1);
      expect(that % true == result2);
    };
  };
}
}  // namespace hal::soft
