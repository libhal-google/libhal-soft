#include <libhal-soft/rc_servo.hpp>

#include <libhal-mock/pwm.hpp>
#include <libhal-mock/testing.hpp>

#include <boost/ut.hpp>

namespace hal {
void rc_servo_test() {
  using namespace boost::ut;

  "hal::servo::rc_servo::create"_test = []() {
    // Setup
    hal::mock::pwm pwm0;
    hal::mock::pwm pwm1;
    hal::mock::pwm pwm2;

    // Exercise
    // use defaults
    auto servo0 = hal::rc_servo::create(pwm0);
    // 100Hz (or 10ms per update) with 500us being max negative start and 2500us
    // being max positive.
    auto servo1 = hal::rc_servo::create<100, 500, 2500>(pwm1);
    pwm2.spy_frequency.trigger_error_on_call(1);
    auto servo2 = hal::rc_servo::create(pwm2);

    // Verify
    expect(bool{ servo0 });
    expect(bool{ servo1 });
    expect(!servo2);
  };

  "hal::servo::rc_servo::position"_test = []() {
    // Setup
    constexpr auto expected0 = float(0.05);
    constexpr auto expected1 = float(0.10);
    constexpr auto expected2 = float(0.20);
    constexpr auto expected3 = float(0.25);

    constexpr auto percent_neg_100 = float(-1.0);
    constexpr auto percent_neg_50 = float(-0.5);
    constexpr auto percent_50 = float(0.5);
    constexpr auto percent_100 = float(1.0);

    hal::mock::pwm pwm;
    auto servo = hal::rc_servo::create<100, 500, 2500>(pwm).value();

    // Exercise
    auto result0 = servo.position(percent_neg_100);
    auto result1 = servo.position(percent_neg_50);
    auto result2 = servo.position(percent_50);
    auto result3 = servo.position(percent_100);

    // Verify
    expect(bool{ result0 });
    expect(bool{ result1 });
    expect(bool{ result2 });
    expect(bool{ result3 });

    expect(that % expected0 ==
           std::get<0>(pwm.spy_duty_cycle.call_history().at(0)));
    expect(that % expected1 ==
           std::get<0>(pwm.spy_duty_cycle.call_history().at(1)));
    expect(that % expected2 ==
           std::get<0>(pwm.spy_duty_cycle.call_history().at(2)));
    expect(that % expected3 ==
           std::get<0>(pwm.spy_duty_cycle.call_history().at(3)));
  };
};
}  // namespace hal
