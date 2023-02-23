#pragma once

#include <libhal/temperature_sensor.hpp>

namespace hal {
/**
 * @brief Inert implementation of temperature sensing hardware
 *
 */
class inert_temperature_sensor : public hal::temperature_sensor
{
public:
  /**
   * @brief Factory function to create inert_temperature_sensor object
   *
   * @param p_temperature - read_t object to return when read() is called
   * @return result<inert_temperature_sensor> - Constructed
   * inert_temperature_sensor object
   */
  static result<inert_temperature_sensor> create(read_t p_temperature)
  {
    return inert_temperature_sensor(p_temperature);
  }

private:
  constexpr inert_temperature_sensor(read_t p_temperature)
    : m_temperature(p_temperature)
  {
  }

  result<read_t> driver_read()
  {
    return m_temperature;
  };

  read_t m_temperature;
};
}  // namespace hal
