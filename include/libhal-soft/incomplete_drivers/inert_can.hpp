#pragma once

#include <libhal/can.hpp>

#include <functional>

namespace hal {
/**
 * @brief Inert implementation of Controller Area Network (CAN bus) hardware
 *
 */
class inert_can : public hal::can
{
public:
  /**
   * @brief Factory function to create inert_can object
   *
   * @param p_bus_on - State of inert can bus. Setting this value to true will
   * return success when bus_on() is called, and setting this value to false
   * will return an error when bus_on() is caled.
   * @return result<inert_can> - Constructed inert_can object
   */
  static result<inert_can> create(bool p_bus_on)
  {
    return inert_can(p_bus_on);
  }

private:
  inert_can(bool p_bus_on)
    : m_bus_on(p_bus_on)
  {
  }

  status driver_configure([[maybe_unused]] const settings& p_settings)
  {

    return hal::success();
  };

  status driver_bus_on()
  {
    if (m_bus_on) {
      return hal::success();
    }
    return hal::new_error();
  };

  result<send_t> driver_send([[maybe_unused]] const message_t& p_message)
  {
    return send_t{};
  };

  void driver_on_receive([[maybe_unused]] hal::callback<handler> p_handler){};

  bool m_bus_on;
};
}  // namespace hal
