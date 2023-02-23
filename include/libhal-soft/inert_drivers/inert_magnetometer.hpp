#pragma once

#include <libhal/magnetometer.hpp>

namespace hal {
/**
 * @brief Inert implementation of magnetic field strength sensing hardware
 *
 */
class inert_magnetometer : public hal::magnetometer
{
public:
  /**
   * @brief Factory function to create an inert_magnetometer object
   *
   * @param p_result - read_t object to return when read() is called
   * @return result<inert_magnetometer> - Constructed inert_magnetometer object
   */
  static result<inert_magnetometer> create(read_t p_result)
  {
    return inert_magnetometer(p_result);
  }

private:
  constexpr inert_magnetometer(read_t p_result)
    : m_result(p_result)
  {
  }

  result<read_t> driver_read()
  {
    return m_result;
  };

  read_t m_result;
};
}  // namespace hal
