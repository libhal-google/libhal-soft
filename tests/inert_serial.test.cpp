#include <libhal-soft/inert_drivers/inert_serial.hpp>

#include <boost/ut.hpp>

namespace hal {
void inert_serial_test()
{
  using namespace boost::ut;
  "inert_serial"_test = []() {
    // Setup
    std::array<hal::byte, 4> buffer;
    constexpr auto write_data = serial::write_t{};
    constexpr auto read_data = serial::read_t{};
    constexpr auto configure_settings = serial::settings{};
    auto test = inert_serial::create(write_data, read_data).value();

    // Exercise
    auto configure_result = test.configure(configure_settings);
    auto write_result = test.write(buffer);
    auto read_result = test.read(buffer);
    auto flush_result = test.flush();

    // Verify
    expect(bool{ configure_result });
    expect(bool{ write_result });
    expect(bool{ read_result });
    expect(bool{ flush_result });
  };
};
}  // namespace hal
