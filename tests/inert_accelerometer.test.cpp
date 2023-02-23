#include <libhal-soft/inert_drivers/inert_accelerometer.hpp>

#include <boost/ut.hpp>

namespace hal {
void inert_accelerometer_test()
{
  using namespace boost::ut;
  "inert_accelerometer"_test = []() {
    // Setup
    constexpr auto expected = accelerometer::read_t{ 0.1f, 0.2f, 0.3f };
    auto test = inert_accelerometer::create(expected).value();

    // Exercise
    auto result = test.read();

    // Verify
    expect(that % expected.x == result.value().x);
    expect(that % expected.y == result.value().y);
    expect(that % expected.z == result.value().z);
  };
};
}  // namespace hal
