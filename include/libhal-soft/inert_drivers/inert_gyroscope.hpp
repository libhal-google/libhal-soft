#pragma once

#include <libhal/gyroscope.hpp>

namespace hal {
/**
 * @brief Inert implementation of angular velocity sensing hardware
 *
 */
class inert_gyroscope : public hal::gyroscope
{
public:
  /**
   * @brief Factory function to create inert_gyroscope object
   *
   * @param p_result - Values to return when calling read()
   * @return result<inert_gyroscope> - Constructed inert_gyroscope object
   */
  static result<inert_gyroscope> create(read_t p_result)
  {
    return inert_gyroscope(p_result);
  }

private:
  constexpr inert_gyroscope(read_t p_result)
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
