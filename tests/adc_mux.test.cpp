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

#include "../include/libhal-soft/adc_mux.hpp"
#include <boost/ut.hpp>
#include <iostream>
#include <libhal-mock/adc.hpp>
#include <libhal-mock/output_pin.hpp>
#include <queue>
#include <vector>

namespace hal {

void adc_mux_test()
{
  using namespace boost::ut;
  using level_t = hal::output_pin::level_t;
  using read_t = hal::adc::read_t;
  using adc_mux_pin = hal::adc_multiplexer::adc_mux_pin;
  // configure virtual testing pins
  const int NUM_PINS = 2;
  std::array<hal::output_pin*, NUM_PINS> signal_pins = { new mock::output_pin,
                                                         new mock::output_pin };
  for (auto& s : signal_pins) {
    s->level() = level_t{ .state = false };
  }

  mock::adc* source_adc = new mock::adc();
  auto adc_sample_pool =
    std::vector<read_t>{ read_t{ .sample = 0 }, read_t{ .sample = 1.5 } };
  auto sample_queue = std::queue<read_t>();
  for (auto& s : adc_sample_pool) {
    sample_queue.push(s);
  }
  source_adc->set(sample_queue);

  auto signal_span = std::span<output_pin*>(signal_pins);

  "adc_mux"_test = [signal_span, source_adc]() {
    // test the adc mux
    adc_multiplexer test_mux = adc_multiplexer(signal_span, source_adc);

    adc_mux_pin test_adc_port_zero = test_mux.pin_factory(0).value();
    expect(that % 0 == test_adc_port_zero.read().value().sample);
  };

  "adc_mux_pin_switch"_test = [signal_span, source_adc]() {
    adc_multiplexer test_mux = adc_multiplexer(signal_span, source_adc);

    // simulate reading from another pin
    adc_mux_pin test_adc_port_one = test_mux.pin_factory(1).value();
    expect(that % 1.5 == test_adc_port_one.read().value().sample);
    // verify pins were switched
    expect(that % 1 == signal_span[0]->level().value().state);
    expect(that % 0 == signal_span[1]->level().value().state);
  };

  "adc_mux_error"_test = [signal_span, source_adc]() {
    adc_multiplexer test_mux = adc_multiplexer(signal_span, source_adc);

    auto real_mux_pins =
      std::array<hal::result<adc_mux_pin>, 4>{ test_mux.pin_factory(0),
                                               test_mux.pin_factory(1),
                                               test_mux.pin_factory(2),
                                               test_mux.pin_factory(3) };
    auto test_pin = test_mux.pin_factory(4);

    for (auto& p : real_mux_pins) {
      expect(that % true == p.has_value());
    }

    expect(that % true == test_pin.has_error());
  };

  // free virtual pins
  for (auto s : signal_pins) {
    delete s;
  }
  delete source_adc;
};

}  // namespace hal