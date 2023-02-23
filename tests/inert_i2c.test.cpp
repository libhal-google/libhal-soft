#include <libhal-soft/inert_drivers/inert_i2c.hpp>

#include <boost/ut.hpp>

namespace hal {
void inert_i2c_test()
{
  using namespace boost::ut;
  "inert_i2c"_test = []() {
    // Setup
    constexpr hal::i2c::settings configure_settings{ .clock_rate = 1.0_Hz };
    constexpr hal::byte address{ 100 };
    constexpr std::array<hal::byte, 4> data_out{ 'a', 'b' };
    std::array<hal::byte, 4> data_in{ '1', '2' };
    const hal::function_ref<hal::timeout_function> timeout = []() {
      return success();
    };
    auto test = inert_i2c::create().value();

    // Exercise
    auto configure_result = test.configure(configure_settings);
    auto transaction_result =
      test.transaction(address, data_out, data_in, timeout);

    // Verify
    expect(bool{ configure_result });
    expect(bool{ transaction_result });
  };
};
}  // namespace hal
