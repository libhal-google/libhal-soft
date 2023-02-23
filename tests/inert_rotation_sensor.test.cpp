#include <libhal-soft/inert_drivers/inert_rotation_sensor.hpp>

#include <boost/ut.hpp>

namespace hal {
void inert_rotation_sensor_test()
{
  using namespace boost::ut;
  "inert_rotation_sensor"_test = []() {
    // Setup
    constexpr auto expected_read = rotation_sensor::read_t{ 0.1f };
    auto test = inert_rotation_sensor::create(expected_read).value();

    // Exercise
    auto result = test.read();

    // Verify
    expect(bool{ result });
    expect(that % expected_read.angle == result.value().angle);
  };
};
}  // namespace hal
