#include <libhal-soft/inert_drivers/inert_spi.hpp>

#include <boost/ut.hpp>

namespace hal {
void inert_spi_test()
{
  using namespace boost::ut;
  "inert_spi"_test = []() {
    // Setup
    const std::array<hal::byte, 4> data_out{ 'a', 'b' };
    std::array<hal::byte, 4> data_in{ '1', '2' };
    const auto data_filler = ' ';
    constexpr auto configure_settings = spi::settings{};
    auto test = inert_spi::create().value();

    // Exercise
    auto configure_result = test.configure(configure_settings);
    auto transfer_result = test.transfer(data_out, data_in, data_filler);

    // Verify
    expect(bool{ configure_result });
    expect(bool{ transfer_result });
  };
};
}  // namespace hal
