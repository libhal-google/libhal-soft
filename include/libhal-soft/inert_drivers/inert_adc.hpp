#pragma once

#include <libhal/adc.hpp>

namespace hal {
/**
 * @brief Inert implementation of Analog to Digital Converter (ADC) hardware
 *
 */
class inert_adc : public hal::adc
{
public:
  /**
   * @brief Factory function to create inert_adc object
   *
   * @param p_result - read_t object to return when reading the inert_adc
   * @return result<inert_adc> - Constructed inert_adc object
   */
  static result<inert_adc> create(read_t p_result)
  {
    return inert_adc(p_result);
  }

private:
  constexpr inert_adc(read_t p_result)
    : m_result(p_result)
  {
  }

  result<read_t> driver_read()
  {
    return m_result;
  };

  read_t m_result;
};
}  // namespace hal
