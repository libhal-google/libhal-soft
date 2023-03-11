#pragma once

#include <libhal/steady_clock.hpp>

namespace hal {
/**
 * @brief Inert implementation of steady clock mechanism
 *
 */
class inert_steady_clock : public hal::steady_clock
{
public:
  /**
   * @brief Factory function to create inert_steady_clock object
   *
   * @param p_frequency - frequency_t object to return when frequency() is
   * called
   * @param p_uptime - uptime_t object with the starting value that will be
   * returned when uptime() is called. The uptime will increment by 1 each time
   * uptime() is called.
   * @return result<inert_steady_clock> - Constructed inert_steady_clock object
   */
  static result<inert_steady_clock> create(frequency_t p_frequency,
                                           uptime_t p_uptime)
  {
    return inert_steady_clock(p_frequency, p_uptime);
  }

private:
  constexpr inert_steady_clock(frequency_t p_frequency, uptime_t p_uptime)
    : m_frequency(p_frequency)
    , m_uptime(p_uptime)
  {
  }
  result<frequency_t> driver_frequency()
  {
    return m_frequency;
  };
  result<uptime_t> driver_uptime()
  {
    m_uptime.ticks++;
    return m_uptime;
  };

  frequency_t m_frequency;
  uptime_t m_uptime;
};
}  // namespace hal
