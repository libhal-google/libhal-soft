#include <libhal-soft/inert_drivers/inert_temperature_sensor.hpp>

#include <boost/ut.hpp>

namespace hal {
void inert_temperature_sensor_test()
{
  using namespace boost::ut;
  "inert_temperature_sensor"_test = []() {
    // Setup
    constexpr auto expected_temp = temperature_sensor::read_t{ 0.5f };
    auto test = inert_temperature_sensor::create(expected_temp).value();

    // Exercise
    auto result = test.read();

    // Verify
    expect(bool{ result });
    expect(that % expected_temp.temperature == result.value().temperature);
  };
};
}  // namespace hal
