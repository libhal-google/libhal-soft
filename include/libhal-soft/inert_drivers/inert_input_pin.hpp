#pragma once

#include <libhal/input_pin.hpp>

namespace hal {
/**
 * @brief Inert implementation of digital input pin hardware
 *
 */
class inert_input_pin : public hal::input_pin
{
public:
  /**
   * @brief Factory function to create inert_input_pin object
   *
   * @param p_level - level_t object to retrun when level() is called
   * @return result<inert_input_pin> - Constructed inert_input_pin object
   */
  static result<inert_input_pin> create(level_t p_level)
  {
    return inert_input_pin(p_level);
  }

private:
  constexpr inert_input_pin(level_t p_level)
    : m_level(p_level)
  {
  }

  status driver_configure([[maybe_unused]] const settings& p_settings)
  {
    return hal::success();
  };

  result<level_t> driver_level()
  {
    return m_level;
  };

  level_t m_level;
};
}  // namespace hal
