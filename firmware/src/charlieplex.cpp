/*******************************************************************************
 * Charlieplexing library implementation
 ******************************************************************************/
#include <avr/io.h>

#include "macros.h"
#include "charlieplex.h"

/******************************************************************************/
Charlieplex::Charlieplex(volatile uint8_t& port, uint8_t* userPins,
                         uint8_t numberOfUserPins) :
        m_port(port), m_pins(userPins), m_numberOfPins(numberOfUserPins)
{
    // Initialize all pins off.
    clear();
}

/******************************************************************************/
void Charlieplex::charlieWrite(charliePin pin, bool state)
{
    if(state)
    {
        // Turning the pin on, set the source and drain appropriately
        setVcc(pin.vcc);
        setGnd(pin.gnd);
    }
    else
    {
        // Turning the pin off, set both vcc and gnd pins as inputs.
        setInput(pin.vcc);
        setInput(pin.gnd);
    }
}

/******************************************************************************/
void Charlieplex::clear()
{
    for (uint8_t i = 0; i < m_numberOfPins; i++)
    {
        setInput(m_pins[i]);
    }
}

/******************************************************************************/
void Charlieplex::setVcc(uint8_t pin)
{
    // Set the source pin as an output
    bit_dir_outp(m_port, m_pins[pin]);
    bit_set(m_port, m_pins[pin]);
}

/******************************************************************************/
void Charlieplex::setGnd(uint8_t pin)
{
    // Set the drain pin
    bit_dir_outp(m_port, m_pins[pin]);
    bit_clear(m_port, m_pins[pin]);
}

/******************************************************************************/
void Charlieplex::setInput(uint8_t pin)
{
    // Clear the pin & set as input
    bit_clear(m_port, m_pins[pin]);
    bit_dir_inp(m_port, m_pins[pin]);
}