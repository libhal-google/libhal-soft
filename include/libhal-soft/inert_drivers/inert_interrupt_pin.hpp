#pragma once

#include <libhal/interrupt_pin.hpp>

namespace hal {
/**
 * @brief Inert implementation of digital interrupt pin hardware
 *
 */
class inert_interrupt_pin : public hal::interrupt_pin
{
public:
  /**
   * @brief Factory function to create inert_interrupt_pin object
   *
   * @return result<inert_interrupt_pin> - Constructed inert_interrupt_pin
   * object
   */
  static result<inert_interrupt_pin> create()
  {
    return inert_interrupt_pin();
  }

private:
  constexpr inert_interrupt_pin()
  {
  }

  status driver_configure([[maybe_unused]] const settings& p_settings)
  {
    return hal::success();
  };

  void driver_on_trigger([[maybe_unused]] hal::callback<handler> p_callback){};
};
}  // namespace hal
