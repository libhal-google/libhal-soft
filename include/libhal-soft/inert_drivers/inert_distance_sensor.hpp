#pragma once

#include <libhal/distance_sensor.hpp>

namespace hal {
/**
 * @brief Inert implementation of linear distance hardware
 *
 */
class inert_distance_sensor : public hal::distance_sensor
{
public:
  /**
   * @brief Factory function to create inert_distance_sensor object
   *
   * @param p_result - read_t data to be returned when calling read()
   * @return result<inert_distance_sensor> - Constructed inert_distance_sensor
   * object
   */
  static result<inert_distance_sensor> create(read_t p_result)
  {
    return inert_distance_sensor(p_result);
  }

private:
  constexpr inert_distance_sensor(read_t p_result)
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
