/*******************************************************************************
 * Declare objects used for reading DIP switches
 ******************************************************************************/
#ifndef DC208_SWITCH_H
#define DC208_SWITCH_H

#include <stdint.h>

/*******************************************************************************
 * Object to represent a DIP switch
 ******************************************************************************/
class Switch
{
public:
    /***************************************************************************
     * Constructor
     * @param port The port that this switch is connected to.
     * @param pin The pin on the port.
     * @remarks Sets the pin with pullup, expects a connected switch to ground
     *          the pin.
     **************************************************************************/
    Switch(volatile uint8_t& port, uint8_t pin);

    /***************************************************************************
     * Return the value of the switch. True of voltage is detected, false
     * otherwise.
     **************************************************************************/
    bool read();

private:
    volatile uint8_t& m_port;
    uint8_t m_pin;
};

#endif //DC208_SWITCH_H
