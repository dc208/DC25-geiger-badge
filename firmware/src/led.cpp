#include <avr/io.h>

#include "charlieplex.h"
#include "led.h"
#include "delay.h"

Led::Led(Switch &led_switch) : m_pins{PA0, PA1, PA2, PA3, PA4, PA5, PA6},
                               m_led1({PA0, PA1}),
                               m_led2({PA1, PA2}),
                               m_led3({PA2, PA3}),
                               m_led4({PA3, PA4}),
                               m_led5({PA4, PA5}),
                               m_led6({PA5, PA6}),
                               m_led7({PA0, PA2}),
                               m_led8({PA1, PA3}),
                               m_led9({PA2, PA4}),
                               m_led10({PA3, PA5}),
                               m_led11({PA4, PA6}),
                               m_led12({PA0, PA3}),
                               m_led13({PA1, PA4}),
                               m_led14({PA2, PA5}),
                               m_led15({PA3, PA6}),
                               m_led16({PA0, PA4}),
                               m_led17({PA1, PA0}),
                               m_led18({PA2, PA1}),
                               m_led19({PA3, PA2}),
                               m_led20({PA4, PA3}),
                               m_led21({PA5, PA4}),
                               m_led22({PA6, PA5}),
                               m_led23({PA2, PA0}),
                               m_led24({PA3, PA1}),
                               m_led25({PA4, PA2}),
                               m_led26({PA5, PA3}),
                               m_led27({PA6, PA4}),
                               m_led28({PA3, PA0}),
                               m_led29({PA4, PA1}),
                               m_led30({PA5, PA2}),
                               m_led31({PA6, PA3}),
                               m_led32({PA4 ,PA0}),
                               m_leds{&m_led1, &m_led2, &m_led3, &m_led4, &m_led5, &m_led6,
                                      &m_led7, &m_led8, &m_led9, &m_led10, &m_led11, &m_led12,
                                      &m_led13, &m_led14, &m_led15, &m_led16, &m_led17, &m_led18,
                                      &m_led19, &m_led20, &m_led21, &m_led22, &m_led23, &m_led24,
                                      &m_led25, &m_led26, &m_led27, &m_led28, &m_led29, &m_led30,
                                      &m_led31, &m_led32},
                               m_charlieplex(PORTA, m_pins, NUMBER_OF_PINS),
                               m_led_switch(led_switch)
{
    // Nothing to see here...
}

/******************************************************************************/
bool Led::draw(uint32_t &pattern, uint8_t repeat)
{
    // Loop the number of repeats
    for (uint8_t i = 0; i < repeat; i++)
    {
        // Loop through all LED's, checking whether or not each needs to be lit
        for (uint8_t j = 0; j < NUMBER_OF_LEDS; j++)
        {
            if ((0 != (pattern & (0x80000000 >> j))))
            {
                // LED should be on, light the sucker for a tick
                m_charlieplex.charlieWrite(*m_leds[j], true);
                m_charlieplex.charlieWrite(*m_leds[j], false);
            }
            else
            {
                // LED should be off... make sure that's the case.
                m_charlieplex.charlieWrite(*m_leds[j], false);
            }
        }

        if (!m_led_switch.read())
        {
            // How rude, someone turned the LED switch off... I guess I'll
            // go home now.
            return false;
        }
    }
    return true;
}

void Led::play(Frame pattern_frames[], uint8_t size)
{
    for (uint8_t i = 0; i < size; i++)
    {
        if (this->draw(pattern_frames[i].pattern, pattern_frames[i].repeat))
        {
          delay_ms(1);
        }
        else
        {
          break;
        }
    }
}
