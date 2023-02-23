#include <libhal-soft/inert_drivers/inert_interrupt_pin.hpp>

#include <boost/ut.hpp>

namespace hal {
void inert_interrupt_pin_test()
{
  using namespace boost::ut;
  "inert_interrupt_pin"_test = []() {
    // Setup
    auto configure_settings = interrupt_pin::settings{};
    auto test = inert_interrupt_pin::create().value();

    // Exercise
    auto result = test.configure(configure_settings);

    // Verify
    expect(bool{ result });
  };
};
}  // namespace hal
