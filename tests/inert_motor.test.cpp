#include <libhal-soft/inert_drivers/inert_motor.hpp>

#include <boost/ut.hpp>

namespace hal {
void inert_motor_test()
{
  using namespace boost::ut;
  "inert_motor"_test = []() {
    // Setup
    auto test = inert_motor::create().value();

    // Exercise
    auto result = test.power(0.1f);

    // Verify
    expect(bool{ result });
  };
};
}  // namespace hal
