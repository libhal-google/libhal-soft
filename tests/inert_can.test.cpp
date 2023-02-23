#include <libhal-soft/inert_drivers/inert_can.hpp>

#include <boost/ut.hpp>

namespace hal {
void inert_can_test()
{
  using namespace boost::ut;
  "inert_can"_test = []() {
    // Setup
    constexpr hal::can::settings settings{
      .baud_rate = 1.0_Hz,
    };
    constexpr hal::can::message_t message{ .id = 1, .length = 0 };
    auto test = inert_can::create(true).value();
    auto test2 = inert_can::create(false).value();

    // Exercise
    auto configure_result = test.configure(settings);
    auto send_result = test.send(message);
    auto bus_on_result = test.bus_on();
    auto bus_off_result = test2.bus_on();

    // Verify
    expect(bool{ configure_result });
    expect(bool{ send_result });
    expect(bool{ bus_on_result });
    expect(!bool{ bus_off_result });
  };
};
}  // namespace hal
