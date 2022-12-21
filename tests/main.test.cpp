namespace hal {
extern void minimum_speed_test();
extern void rc_servo_test();
}  // namespace hal

int main()
{
  hal::minimum_speed_test();
  hal::rc_servo_test();
}
