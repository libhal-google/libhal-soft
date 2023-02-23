#include <libhal-soft/inert_drivers/inert_output_pin.hpp>

#include <boost/ut.hpp>

namespace hal {
void inert_output_pin_test()
{
  using namespace boost::ut;
  "inert_output_pin"_test = []() {
    // Setup
    auto test = inert_output_pin::create().value();

    // Exercise
    auto set_level_high_result = test.level(true);
    auto get_level_high_result = test.level();
    auto set_level_low_result = test.level(false);
    auto get_level_low_result = test.level();

    // Verify
    expect(bool{ set_level_high_result });
    expect(bool{ get_level_high_result });
    expect(bool{ set_level_low_result });
    expect(bool{ get_level_low_result });
  };
};
}  // namespace hal
