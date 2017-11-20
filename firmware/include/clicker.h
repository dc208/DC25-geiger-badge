#ifndef DC208_CLICKER_H
#define DC208_CLICKER_H

#include <stdint.h>

/*******************************************************************************
 * Object to represent a speaker to click
 ******************************************************************************/
class Clicker
{
public:
    /***************************************************************************
     * Constructor
     * @param port The port that this speaker is connected to.
     * @param pin The pin on the port.
     **************************************************************************/
    Clicker(volatile uint8_t& port, uint8_t pin);

    /***************************************************************************
     * Clicks the speaker for one click
     **************************************************************************/
    void click();

private:
    volatile uint8_t& m_port;
    uint8_t m_pin;
};

#endif //DC208_CLICKER_H
