# Copyright 2023 Google LLC
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
cmake_minimum_required(VERSION 3.15)

project(libhal-soft LANGUAGES CXX)

libhal_test_and_make_library(
  LIBRARY_NAME libhal-soft

  SOURCES
  src/rc_servo.cpp
  src/i2c_minimum_speed.cpp
  src/adc_mux.cpp

  TEST_SOURCES
  tests/inert_drivers/inert_accelerometer.test.cpp
  tests/inert_drivers/inert_adc.test.cpp
  tests/inert_drivers/inert_dac.test.cpp
  tests/inert_drivers/inert_distance_sensor.test.cpp
  tests/inert_drivers/inert_gyroscope.test.cpp
  tests/inert_drivers/inert_input_pin.test.cpp
  tests/inert_drivers/inert_interrupt_pin.test.cpp
  tests/inert_drivers/inert_magnetometer.test.cpp
  tests/inert_drivers/inert_motor.test.cpp
  tests/inert_drivers/inert_pwm.test.cpp
  tests/inert_drivers/inert_rotation_sensor.test.cpp
  tests/inert_drivers/inert_steady_clock.test.cpp
  tests/inert_drivers/inert_temperature_sensor.test.cpp
  tests/inert_drivers/inert_timer.test.cpp
  tests/adc_mux.test.cpp
  tests/i2c_minimum_speed.test.cpp
  tests/rc_servo.test.cpp
  tests/main.test.cpp

  PACKAGES
  libhal
  libhal-util

  LINK_LIBRARIES
  libhal::libhal
  libhal::util

  TEST_PACKAGES
  libhal-mock

  TEST_LINK_LIBRARIES
  libhal::mock
)
