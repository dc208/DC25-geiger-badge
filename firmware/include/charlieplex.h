/*******************************************************************************
 * This charlieplex library was inspired by the arduino library located at
 * https://playground.arduino.cc/Code/Charlieplex
 * with the arduino stuff stripped out and replaced with general AVR GPIO.
 ******************************************************************************/
#ifndef CHARLIEPLEX_H
#define CHARLIEPLEX_H

#include <stdint.h>

/*******************************************************************************
 * Object used to define a charlieplex pin.
 *
 * @param vcc defines which physical pin must provide current to the
 *            charlieplexed pin
 * @param gnd defines the physical pin which must receive current.
 ******************************************************************************/
struct CharliePin
{
    uint8_t vcc;
    uint8_t gnd;
};
typedef CharliePin charliePin;

/*******************************************************************************
 * Object to abstract & manage a set of charlieplexed pins.
 ******************************************************************************/
class Charlieplex
{
public:
    /***************************************************************************
     * Constructor
     *
     * @param port What ATTINY1364 port the charlieplexed pins are connected to
     * @param userPins Array containing which GPIO pins on port are used for
     *                 addressing charlieplexed pins
     * @param numberOfUserPins How many GPIO pins are used for addressing
     *
     * @remarks Clears all pins for initial state
     **************************************************************************/
    Charlieplex(volatile uint8_t& port, uint8_t* userPins,
                uint8_t numberOfUserPins);

    /***************************************************************************
     * Change the state of a charlieplexed pin
     *
     * @param pin The addressed pin to change state
     * @param state True to turn the addressed pin on, False otherwise
     **************************************************************************/
    void charlieWrite(charliePin pin, bool state);

    /***************************************************************************
     * Sets all charlieplexed pins off
     **************************************************************************/
    void clear();

private:
    /***************************************************************************
     * Helper method to configure pin to provide current
     *
     * @param pin The pin to set
     **************************************************************************/
    void setVcc(uint8_t pin);

    /***************************************************************************
     * Helper method to configure pin to sink current
     *
     * @param pin The pin to set
     **************************************************************************/
    void setGnd(uint8_t pin);

    /***************************************************************************
     * Helper method to configure pin as input
     *
     * @param pin The pin to set
     **************************************************************************/
    void setInput(uint8_t pin);

    // The port used for charlieplexing
    volatile uint8_t& m_port;

    // Array of pins on m_port used for charlieplexing
    uint8_t* m_pins;

    // How many pins are used for charlieplexing
    uint8_t m_numberOfPins;
};

#endif // CHARLIEPLEX_H
