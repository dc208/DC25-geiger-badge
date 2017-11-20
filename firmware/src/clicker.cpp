#include <avr/io.h>

#include "clicker.h"
#include "macros.h"
#include "delay.h"

/******************************************************************************/
Clicker::Clicker(volatile uint8_t &port, uint8_t pin) : m_port(port), m_pin(pin)
{
    // Set the speaker as an output.
    bit_dir_outp(m_port, m_pin);
}

/******************************************************************************/
void Clicker::click()
{
    bit_dir_outp(m_port, m_pin);
    bit_set(m_port, m_pin);
    delay_ms(1);
    bit_clear(m_port, m_pin);
    delay_ms(1);
}
