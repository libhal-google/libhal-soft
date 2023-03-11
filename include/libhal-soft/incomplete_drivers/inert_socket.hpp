#pragma once

#include <libhal/socket.hpp>

namespace hal {
/**
 * @brief Inert implementation of generic network sockets
 *
 */
class inert_socket : public hal::socket
{
public:
  /**
   * @brief Factory function to create inert_socket object
   *
   * @param p_write_data - write_t object to return when write() is called
   * @param p_read_data - read_t object to return when read() is called
   * @return result<inert_socket> - Constructed inert_socket object
   */
  static result<inert_socket> create(write_t p_write_data, read_t p_read_data)
  {
    return inert_socket(p_write_data, p_read_data);
  }

private:
  constexpr inert_socket(write_t p_write_data, read_t p_read_data)
    : m_write_data(p_write_data)
    , m_read_data(p_read_data)
  {
  }

  hal::result<write_t> driver_write(
    [[maybe_unused]] std::span<const hal::byte> p_data,
    [[maybe_unused]] hal::function_ref<hal::timeout_function> p_timeout)
  {
    return m_write_data;
  };

  hal::result<read_t> driver_read([[maybe_unused]] std::span<hal::byte> p_data)
  {
    return m_read_data;
  };

  write_t m_write_data;
  read_t m_read_data;
};
}  // namespace hal
