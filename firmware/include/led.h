/*******************************************************************************
 * Declare objects used for LED pattern control
 ******************************************************************************/

#ifndef DC208_LED_H
#define DC208_LED_H

// The number of physical IP pins used for addressing
#define NUMBER_OF_PINS 7

// How man LED's are controlled and addressed by this driver
#define NUMBER_OF_LEDS 32

#include "charlieplex.h"
#include "switch.h"

struct Frame
{
    uint32_t pattern;
    uint8_t repeat;
};

/*******************************************************************************
 * LED driver which abstracts the charliplexing and handles the drawing of
 * patterns
 ******************************************************************************/
class Led
{
public:
    /***************************************************************************
     * Constructor
     *
     * @param[in] led_switch The LED switch to monitor to deterine if the LED's
     *            should give power back to main or not.
     *
     * Initializes LED's in preparation for addressing them for patterns
     **************************************************************************/
    Led(Switch &led_switch);

    /***************************************************************************
     * Pattern drawer
     *
     * @param[in] pattern An integer where each bit represents an LED to light
     * @param[in] repeat The number of times to repeat this pattern
     *
     * @remarks Checks the LED switch and if it gets turned off, returns false,
     *          otherwise returns true.
     **************************************************************************/
    bool draw(uint32_t &pattern, uint8_t repeat);
    
    /***************************************************************************
     * Pattern struct player
     *
     * @param[in] pattern_frames An array of Frame structs
     * @param[in] size The size of the array for populating the loop.  For some
     *            reason, the array size cannot be calculated by this function.
     *
     * @remarks Blocks until the entire pattern set has been played.
     **************************************************************************/
    void play(Frame pattern_frames[], uint8_t size);

private:
    // Array of the pins to use for charlieplex addressing
    uint8_t m_pins[NUMBER_OF_PINS];

    // Define each LED's individual address
    // Current flows from index 0 to index 1
    charliePin m_led1;
    charliePin m_led2;
    charliePin m_led3;
    charliePin m_led4;
    charliePin m_led5;
    charliePin m_led6;
    charliePin m_led7;
    charliePin m_led8;
    charliePin m_led9;
    charliePin m_led10;
    charliePin m_led11;
    charliePin m_led12;
    charliePin m_led13;
    charliePin m_led14;
    charliePin m_led15;
    charliePin m_led16;
    charliePin m_led17;
    charliePin m_led18;
    charliePin m_led19;
    charliePin m_led20;
    charliePin m_led21;
    charliePin m_led22;
    charliePin m_led23;
    charliePin m_led24;
    charliePin m_led25;
    charliePin m_led26;
    charliePin m_led27;
    charliePin m_led28;
    charliePin m_led29;
    charliePin m_led30;
    charliePin m_led31;
    charliePin m_led32;

    // Easily indexible array of LEDs
    charliePin *m_leds[NUMBER_OF_LEDS];

    // Charlieplex object used to manipulate LEDs
    Charlieplex m_charlieplex;

    // LED switch object to check during operation
    Switch &m_led_switch;
};

#endif //DC208_LED_H
