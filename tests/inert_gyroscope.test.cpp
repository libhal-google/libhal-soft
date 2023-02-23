#include <libhal-soft/inert_drivers/inert_gyroscope.hpp>

#include <boost/ut.hpp>

namespace hal {
void inert_gyroscope_test()
{
  using namespace boost::ut;
  "inert_gyroscope"_test = []() {
    // Setup
    constexpr auto expected_read = gyroscope::read_t{ 0.1f, 0.2f, 0.3f };
    auto test = inert_gyroscope::create(expected_read).value();

    // Exercise
    auto result = test.read();

    // Verify
    expect(bool{ result });
    expect(that % expected_read.x == result.value().x);
    expect(that % expected_read.y == result.value().y);
    expect(that % expected_read.z == result.value().z);
  };
};
}  // namespace hal
