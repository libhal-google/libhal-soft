#pragma once

#include <libhal/rotation_sensor.hpp>

namespace hal {
/**
 * @brief Inert implementation of rotation measuring hardware
 *
 */
class inert_rotation_sensor : public hal::rotation_sensor
{
public:
  /**
   * @brief Factory function to create inert_rotation_sensor object
   *
   * @param p_position - read_t object to return when read() is called
   * @return result<inert_rotation_sensor> - Constructed inert_rotation_sensor
   * onject
   */
  static result<inert_rotation_sensor> create(read_t p_position)
  {
    return inert_rotation_sensor(p_position);
  }

private:
  constexpr inert_rotation_sensor(read_t p_position)
    : m_position(p_position)
  {
  }

  result<read_t> driver_read()
  {
    return m_position;
  };

  read_t m_position;
};
}  // namespace hal
