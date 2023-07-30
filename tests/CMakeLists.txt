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

project(unit_test VERSION 0.0.1 LANGUAGES CXX)

if(DEFINED ENABLE_ASAN)
  set(ASAN_FLAG "-fsanitize=address" CACHE INTERNAL "Use AddressSanatizer")
endif(DEFINED ENABLE_ASAN)

find_package(ut REQUIRED CONFIG)
find_package(libhal REQUIRED CONFIG)
find_package(libhal-util REQUIRED CONFIG)
find_package(libhal-mock REQUIRED CONFIG)

add_executable(${PROJECT_NAME}

  # Source
  ../src/adc_mux.cpp
  ../src/i2c_minimum_speed.cpp
  ../src/rc_servo.cpp

  # Tests
  adc_mux.test.cpp
  i2c_minimum_speed.test.cpp
  rc_servo.test.cpp

  inert_drivers/inert_accelerometer.test.cpp
  inert_drivers/inert_adc.test.cpp
  inert_drivers/inert_dac.test.cpp
  inert_drivers/inert_distance_sensor.test.cpp
  inert_drivers/inert_gyroscope.test.cpp
  inert_drivers/inert_input_pin.test.cpp
  inert_drivers/inert_interrupt_pin.test.cpp
  inert_drivers/inert_magnetometer.test.cpp
  inert_drivers/inert_motor.test.cpp
  inert_drivers/inert_pwm.test.cpp
  inert_drivers/inert_rotation_sensor.test.cpp
  inert_drivers/inert_steady_clock.test.cpp
  inert_drivers/inert_temperature_sensor.test.cpp
  inert_drivers/inert_timer.test.cpp

  # Main
  main.test.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC . ../include ../src)
target_compile_options(${PROJECT_NAME} PRIVATE
  --coverage
  -fprofile-arcs
  -ftest-coverage
  ${ASAN_FLAG}
  -Werror
  -Wall
  -Wextra
  -Wshadow
  -Wnon-virtual-dtor
  -Wno-gnu-statement-expression
  -pedantic)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
target_link_options(${PROJECT_NAME} PRIVATE
  --coverage
  -fprofile-arcs
  -ftest-coverage
  ${ASAN_FLAG})
target_link_libraries(${PROJECT_NAME} PRIVATE
  boost-ext-ut::ut
  libhal::libhal
  libhal::util
  libhal::mock)
