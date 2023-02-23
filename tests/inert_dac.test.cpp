#include <libhal-soft/inert_drivers/inert_dac.hpp>

#include <boost/ut.hpp>

namespace hal {
void inert_dac_test()
{
  using namespace boost::ut;
  "inert_dac"_test = []() {
    // Setup
    auto test = inert_dac::create().value();

    // Exercise
    auto result = test.write(0.1f);

    // Verify
    expect(bool{ result });
  };
};
}  // namespace hal
