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

namespace hal::soft {
extern void adc_mux_test();
extern void minimum_speed_test();
extern void rc_servo_test();
extern void output_pin_iverter_test();
extern void input_pin_iverter_test();

extern void inert_accelerometer_test();
extern void inert_adc_test();
extern void inert_dac_test();
extern void inert_distance_sensor_test();
extern void inert_gyroscope_test();
extern void inert_input_pin_test();
extern void inert_interrupt_pin_test();
extern void inert_magnetometer_test();
extern void inert_motor_test();
extern void inert_pwm_test();
extern void inert_rotation_sensor_test();
extern void inert_steady_clock_test();
extern void inert_temperature_sensor_test();
extern void inert_timer_test();
}  // namespace hal::soft

int main()
{
  hal::soft::adc_mux_test();
  hal::soft::minimum_speed_test();
  hal::soft::rc_servo_test();
  hal::soft::output_pin_iverter_test();
  hal::soft::input_pin_iverter_test();

  hal::soft::inert_accelerometer_test();
  hal::soft::inert_adc_test();
  hal::soft::inert_dac_test();
  hal::soft::inert_distance_sensor_test();
  hal::soft::inert_gyroscope_test();
  hal::soft::inert_input_pin_test();
  hal::soft::inert_interrupt_pin_test();
  hal::soft::inert_magnetometer_test();
  hal::soft::inert_motor_test();
  hal::soft::inert_pwm_test();
  hal::soft::inert_rotation_sensor_test();
  hal::soft::inert_steady_clock_test();
  hal::soft::inert_temperature_sensor_test();
  hal::soft::inert_timer_test();
}
