#include <libhal-soft/i2c_bit_bang.hpp>
#include <libhal-util/bit.hpp>

namespace hal {
    // public
void i2c_bit_bang::i2c_bit_bang(output_pin& p_scl, output_pin& p_sda, steady_clock& p_clock, bus_info p_bus) : m_scl(p_scl),
    m_sda(p_sda), m_clock(p_clock), m_bus(p_bus)
    {
    m_sda.level(true);
    m_scl.level(true);
    }

i2c_host_state i2c_bit_bang::operation_state_machine(i2c_host_state p_state, function_ref<hal::timeout_function> p_timeout) {
    constexpr auto read_write_bit_mask = hal::bit_mask::from<0, 0>();
    switch(p_state) {
        case i2c_host_state::start:
        case i2c_host_state::repeated_start:
            send_start_condition();
            p_state = i2c_host_state::write_address;
        break;

        case i2c_host_state::write_address:
            hal::byte address_to_write;

            // select read or write
            if(m_write_iterator != m_write_end) {
                p_state = i2c_host_state::write;
                address_to_write = hal::bit_modify(m_address).clear<read_write_bit_mask>();
            } else {
                p_state = i2c_host_state::read;
                address_to_write = hal::bit_modify(m_address).set<read_write_bit_mask>();
            }
            auto acknowledged = write_byte(address_to_write, p_timeout);

            // if ack_bit = 1 then this indicates that no peripheral responded (nack)
            if(!acknowledged) {
                p_state = i2c_host_state::bus_error;
            }
        break;

        case i2c_host_state::write:

            for (; m_write_iterator < m_write_end; m_write_iterator++) {
                auto acknowledged = write_byte(*m_write_iterator, p_timeout);

                // if ack_bit = 1 then an error has occured (nack)
                if(!acknowledged) {
                    p_state = i2c_host_state::bus_error;
                }
            }

            // after writing, if the read iterators aren't done, then it's a repeated_start
            if(m_read_iterator != m_read_end) {
                p_state = i2c_host_state::repeated_start;
            } else {
                p_state = i2c_host_state::stop;
            }
        break;

        case i2c_host_state::read:
            while(true) {
                read_byte();
                m_read_iterator++
                // when the data is done being read in, then send a NACK to tell the slave to stop reading
                if(m_read_iterator < m_read_end) {
                    write_bit(1, p_timeout);
                    p_timeout();
                    break;
                } else {
                    // if the iterator isn't done, then we ack whatever data we read
                    write_bit(0, p_timeout);
                }
            }
            p_state = 
        break;
        case i2c_host_state::stop:
        case i2c_host_state::bus_error:
            send_stop_condition();
        break;
    }
    return p_state;
}

void i2c_bit_bang::driver_configure(const settings& p_settings) {

}

void i2c_bit_bang::driver_transaction(hal::byte p_address,
std::span<const hal::byte> p_data_out,
std::span<hal::byte> p_data_in,
function_ref<hal::timeout_function> p_timeout) {

    i2c_host_state state = i2c_host_state::start;
    m_address = p_address;
    m_write_iterator = p_data_out.begin();
    m_write_end = p_data_out.end();
    m_read_iterator = p_data_in.begin();
    m_read_end = p_data_in.end();

    for() {
        state = operation_state_machine(state, p_timeout);
        p_timeout();
    }
}

// private 

void i2c_bit_bang::send_start_condition() {
    m_sda.level(false);
    m_scl.level(false);
}

void i2c_bit_bang::send_stop_condition() {
    m_sda.level(false);
    m_scl.level(true);
    m_sda.level(true);
}

bool i2c_bit_bang::write_byte(hal::byte p_byte_to_write, function_ref<hal::timeout_function> p_timeout) {
    constexpr auto byte_length = 8;
    constexpr hal::byte bit_select = 0b1000'0000;
    hal::byte bit_to_write = 0;
    // not using the bit library here since it's a serialization
    for(int i = 0; i < byte_length; i++) {
        bit_to_write = static_cast<hal::byte>(p_byte_to_write & (bit_select >> i));
        write_bit(bit_to_write, p_timeout);
    }
    // look for the ack
    auto ack_bit = read_bit();
    // if ack bit is 0, then it was acknowledged
    auto acknowledged = (ack_bit == 0);

    // release the sda line
    write_bit(1, p_timeout);

    return acknowledged;

}
/* 
    for writing a bit you want to make set the data line first, then toggle the level of the clock
    then check if the level was indeed toggled or if the peripheral is stretching the clock.
    After this is done, you are able to set the clock back low.
*/
void i2c_bit_bang::write_bit(hal::byte p_bit_to_write, function_ref<hal::timeout_function> p_timeout) {
    m_sda.level(static_cast<bool>(p_bit_to_write));
    m_scl.level(true);
    // if scl is still low after we set it high, then the peripheral is clock
    // stretching
    while(m_scl.level() == 0)
    {
        p_timeout();
    }
    m_scl.level(false);
}
/* 
    after reading out the entire byte you then want to have the reciever send 
*/
void i2c_bit_bang::read_byte() {
    constexpr auto byte_length = 8;
    constexpr auto bit_select = 0b1000'0000;
    hal::byte read_byte = 0;
    for(int i = 0; i < byte_length; i++) {
        read_byte |= (read_bit() << (byte_length - i));
    }
    *m_read_iterator = read_byte;
}

hal::byte i2c_bit_bang::read_bit() {
    m_scl.level(true);
    auto bit_read = static_cast<hal::byte>(m_sda.level());
    m_scl.level(false);
    return bit_read;
}

}