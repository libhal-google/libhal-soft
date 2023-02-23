#pragma once

#include <libhal/motor.hpp>

namespace hal {
/**
 * @brief Inert implementation of open loop motorized actuator hardware
 *
 */
class inert_motor : public hal::motor
{
public:
  /**
   * @brief Factory function to create inert_motor object
   *
   * @return result<inert_motor> - Constructed inert_motor object
   */
  static result<inert_motor> create()
  {
    return inert_motor();
  }

private:
  constexpr inert_motor()
  {
  }

  result<power_t> driver_power([[maybe_unused]] float p_power)
  {
    return power_t{};
  };
};
}  // namespace hal
