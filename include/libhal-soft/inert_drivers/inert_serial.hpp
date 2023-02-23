#pragma once

#include <libhal/serial.hpp>

namespace hal {
/**
 * @brief Inert implementation of serial communication protocol hardware
 *
 */
class inert_serial : public hal::serial
{
public:
  /**
   * @brief Factory function to create inert_serial object
   *
   * @param p_write_data - write_t object to return when write() is called
   * @param p_read_data - read_t object to return when read() is called
   * @return result<inert_serial> - Constructed inert_serial object
   */
  static result<inert_serial> create(write_t p_write_data, read_t p_read_data)
  {
    return inert_serial(p_write_data, p_read_data);
  }

private:
  constexpr inert_serial(write_t p_write_data, read_t p_read_data)
    : m_write_data(p_write_data)
    , m_read_data(p_read_data)
  {
  }

  status driver_configure([[maybe_unused]] const settings& p_settings)
  {
    return hal::success();
  };

  result<write_t> driver_write(
    [[maybe_unused]] std::span<const hal::byte> p_data)
  {
    return m_write_data;
  };

  result<read_t> driver_read([[maybe_unused]] std::span<hal::byte> p_data)
  {
    return m_read_data;
  };

  result<flush_t> driver_flush()
  {
    return flush_t{};
  };

  write_t m_write_data;
  read_t m_read_data;
};
}  // namespace hal
