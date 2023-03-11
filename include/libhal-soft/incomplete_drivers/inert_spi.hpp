#pragma once

#include <libhal/spi.hpp>

namespace hal {
/**
 * @brief Inert implementation of Serial peripheral interface (SPI)
 * communication protocol hardware
 *
 */
class inert_spi : public hal::spi
{
public:
  /**
   * @brief Factory function to create inert_spi object
   *
   * @return result<inert_spi> - Constructed inert_spi object
   */
  static result<inert_spi> create()
  {
    return inert_spi();
  }

private:
  constexpr inert_spi()
  {
  }

  status driver_configure([[maybe_unused]] const settings& p_settings)
  {
    return hal::success();
  };

  result<transfer_t> driver_transfer(
    [[maybe_unused]] std::span<const hal::byte> p_data_out,
    [[maybe_unused]] std::span<hal::byte> p_data_in,
    [[maybe_unused]] hal::byte p_filler)
  {
    return transfer_t{};
  };
};
}  // namespace hal
