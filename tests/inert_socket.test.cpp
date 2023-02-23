#include <libhal-soft/inert_drivers/inert_socket.hpp>

#include <boost/ut.hpp>

namespace hal {
void inert_socket_test()
{
  using namespace boost::ut;
  "inert_socket"_test = []() {
    // Setup
    hal::function_ref<timeout_function> always_succeed = []() -> hal::status {
      return hal::success();
    };
    std::array<hal::byte, 4> buffer;
    auto write_data = socket::write_t{};
    auto read_data = socket::read_t{};
    auto test = inert_socket::create(write_data, read_data).value();

    // Exercise
    auto write_result = test.write(buffer, always_succeed);
    auto read_result = test.read(buffer);

    // Verify
    expect(bool{ write_result });
    expect(bool{ read_result });
  };
};
}  // namespace hal
