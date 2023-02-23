#pragma once

#include <libhal/accelerometer.hpp>

namespace hal {
/**
 * @brief Inert implementation of acceleration sensing hardware
 *
 */
class inert_accelerometer : public hal::accelerometer
{
public:
  /**
   * @brief Factory function to create inert_accelerometer object
   *
   * @param p_values - Read values to return when reading the
   * inert_accelerometer.
   * @return result<inert_accelerometer> - Constructed inert_accelerometer
   * object
   */
  static result<inert_accelerometer> create(read_t p_values)
  {
    return inert_accelerometer(p_values);
  }

private:
  constexpr inert_accelerometer(read_t p_values)
    : m_values(p_values)
  {
  }

  result<read_t> driver_read()
  {
    return m_values;
  };

  read_t m_values;
};
}  // namespace hal
