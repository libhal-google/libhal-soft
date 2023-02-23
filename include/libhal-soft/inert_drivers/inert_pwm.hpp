#pragma once

#include <libhal/pwm.hpp>

namespace hal {
/**
 * @brief Inert implementation of Pulse Width Modulation (PWM) channel hardware
 *
 */
class inert_pwm : public hal::pwm
{
public:
  /**
   * @brief Factory function to create inert_pwm object
   *
   * @return result<inert_pwm> - Constructed inert_pwm object
   */
  static result<inert_pwm> create()
  {
    return inert_pwm();
  }

private:
  constexpr inert_pwm()
  {
  }

  result<frequency_t> driver_frequency([[maybe_unused]] hertz p_frequency)
  {
    return frequency_t{};
  };

  result<duty_cycle_t> driver_duty_cycle([[maybe_unused]] float p_duty_cycle)
  {
    return duty_cycle_t{};
  };
};
}  // namespace hal
