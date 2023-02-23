#include <libhal-soft/inert_drivers/inert_input_pin.hpp>

#include <boost/ut.hpp>

namespace hal {
void inert_input_pin_test()
{
  using namespace boost::ut;
  "inert_input_pin"_test = []() {
    // Setup
    auto level_true = input_pin::level_t{ true };
    auto level_false = input_pin::level_t{ false };
    auto configure_settings = input_pin::settings{};
    auto test1 = inert_input_pin::create(level_true).value();
    auto test2 = inert_input_pin::create(level_false).value();

    // Exercise
    auto configure_result = test1.configure(configure_settings);
    auto level_high_result = test1.level();
    auto level_low_result = test2.level();

    // Verify
    expect(bool{ configure_result });
    expect(bool{ level_high_result });
    expect(bool{ level_low_result });
    expect(that % true == level_high_result.value().state);
    expect(that % false == level_low_result.value().state);
  };
};
}  // namespace hal
