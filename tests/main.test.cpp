namespace hal {
extern void minimum_speed_test();

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
extern void rc_servo_test();

}  // namespace hal

int main()
{
  hal::minimum_speed_test();

  hal::inert_accelerometer_test();
  hal::inert_adc_test();
  hal::inert_dac_test();
  hal::inert_distance_sensor_test();
  hal::inert_gyroscope_test();
  hal::inert_input_pin_test();
  hal::inert_interrupt_pin_test();
  hal::inert_magnetometer_test();
  hal::inert_motor_test();
  hal::inert_pwm_test();
  hal::inert_rotation_sensor_test();
  hal::inert_steady_clock_test();
  hal::inert_temperature_sensor_test();
  hal::inert_timer_test();
  hal::rc_servo_test();
}
