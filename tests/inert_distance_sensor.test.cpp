#include <libhal-soft/inert_drivers/inert_distance_sensor.hpp>

#include <boost/ut.hpp>

namespace hal {
void inert_distance_sensor_test()
{
  using namespace boost::ut;
  "inert_distance_sensor"_test = []() {
    // Setup
    constexpr auto expected_read = distance_sensor::read_t{ 0.1f };
    auto test = inert_distance_sensor::create(expected_read).value();

    // Exercise
    auto result = test.read();

    // Verify
    expect(bool{ result });
    expect(that % expected_read.distance == result.value().distance);
  };
};
}  // namespace hal
