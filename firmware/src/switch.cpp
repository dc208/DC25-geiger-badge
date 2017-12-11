#include "switch.h"
#include "macros.h"

/******************************************************************************/
Switch::Switch(volatile uint8_t& port, uint8_t pin) : m_port(port), m_pin(pin)
{
    // Set the port & pin as an input
    bit_dir_inp(m_port, m_pin);

    // Set the pull-up
    bit_pullup(m_port, m_pin);
}

/******************************************************************************/
bool Switch::read()
{
    return bit_test_in(m_port, m_pin);
}
