#pragma once

#include <libhal/dac.hpp>

namespace hal {
/**
 * @brief Inert implementation of Digital to Analog Converter (DAC) hardware
 *
 */
class inert_dac : public hal::dac
{
public:
  /**
   * @brief Factory function to create inert_dac object
   *
   * @return result<inert_dac> - Constructed inert_dac object
   */
  static result<inert_dac> create()
  {
    return inert_dac();
  }

private:
  constexpr inert_dac()
  {
  }

  result<write_t> driver_write([[maybe_unused]] float p_percentage)
  {
    return write_t{};
  };
};
}  // namespace hal
