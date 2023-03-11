#pragma once

#include <libhal/output_pin.hpp>

namespace hal {
/**
 * @brief Inert implementation of digital output pin hardware
 *
 */
class inert_output_pin : public hal::output_pin
{
public:
  /**
   * @brief Factory function to create inert_output_pin
   *
   * @param p_level - level_t object to return when level() is called. This
   * value can be changed by using level(bool) after creation.
   * @return result<inert_output_pin> - Constructed inert_output_pin object
   */
  static result<inert_output_pin> create(bool p_level)
  {
    return inert_output_pin(p_level);
  }

private:
  constexpr inert_output_pin(bool p_level)
    : m_level(&p_level)
  {
  }

  status driver_configure(const settings& p_settings)
  {
    return hal::success();
  };

  result<set_level_t> driver_level(bool p_high)
  {
    m_level = p_high;
    return set_level_t{};
  };

  result<level_t> driver_level()
  {
    return level_t{ .state = m_level };
  };

  bool m_level;
};
}  // namespace hal
