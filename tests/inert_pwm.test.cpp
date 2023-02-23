#include <libhal-soft/inert_drivers/inert_pwm.hpp>

#include <boost/ut.hpp>

namespace hal {
void inert_pwm_test()
{
  using namespace boost::ut;
  "inert_pwm"_test = []() {
    // Setup
    auto test = inert_pwm::create().value();

    // Exercise
    auto frequency_result = test.frequency(0.1f);
    auto duty_cycle_result = test.duty_cycle(0.1f);

    // Verify
    expect(bool{ frequency_result });
    expect(bool{ duty_cycle_result });
  };
};
}  // namespace hal
