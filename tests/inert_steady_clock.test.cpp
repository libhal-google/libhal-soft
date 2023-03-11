#include <libhal-soft/inert_drivers/inert_steady_clock.hpp>

#include <boost/ut.hpp>

namespace hal {
void inert_steady_clock_test()
{
  using namespace boost::ut;
  "inert_steady_clock"_test = []() {
    // Setup
    constexpr auto expected_frequency = steady_clock::frequency_t{ 0.5f };
    constexpr auto start_uptime = steady_clock::uptime_t{ 99 };
    constexpr auto expected_uptime = steady_clock::uptime_t{ 100 };
    auto test =
      inert_steady_clock::create(expected_frequency, start_uptime).value();

    // Exercise
    auto frequency_result = test.frequency();
    auto uptime_result = test.uptime();

    // Verify
    expect(bool{ frequency_result });
    expect(bool{ uptime_result });
    expect(that % expected_frequency.operating_frequency ==
           frequency_result.value().operating_frequency);
    expect(that % expected_uptime.ticks == uptime_result.value().ticks);
  };
};
}  // namespace hal
