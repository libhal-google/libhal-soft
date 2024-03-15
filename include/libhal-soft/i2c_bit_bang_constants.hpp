#include <cstdint>

namespace hal {
enum class i2c_host_state : std::uint32_t
{
  bus_error = 0x00,
  start = 1,
  repeated_start = 2,
  write_address = 3,
  write = 4,
  read = 5,
  send_stop = 6,
  done = 7,
  //   arbitration_lost = ,
  //   own_address_received = ,
  //   do_nothing =
};
}