#include <libhal-soft/inert_drivers/inert_adc.hpp>

#include <boost/ut.hpp>

namespace hal {
void inert_adc_test()
{
  using namespace boost::ut;
  "inert_adc"_test = []() {
    // Setup
    constexpr auto expected = adc::read_t{ 0.5f };
    auto test = inert_adc::create(expected).value();

    // Exercise
    auto result = test.read();

    // Verify
    expect(bool{ result });
    expect(that % expected.sample == result.value().sample);
  };
};
}  // namespace hal
