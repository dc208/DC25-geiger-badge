/*******************************************************************************
 * The DC208 2017 badge!
 ******************************************************************************/

#include <avr/pgmspace.h>
#include <avr/io.h>
#include <stdlib.h>

#include "led.h"
#include "switch.h"
#include "patterns.h"
#include "macros.h"
#include "ir_sensor.h"
#include "clicker.h"
#include "delay.h"

// Main Program
int main()
{
    // Make a switch reader, used to determine LED pattern to draw.
    Switch led_switch(PORTB, PB0);

    // Make a switch reader, used to determine whether to play audio.
    Switch speaker_switch(PORTB, PB3);

    // Make an LED pattern drawer
    Led leds = Led(led_switch);

    // Make an I2C bus communicator (The sensor is at address 0x60)
    I2c i2c_bus = I2c(0x60);

    // Make a sensor reader
    Ir_sensor sensor = Ir_sensor(i2c_bus);

    // Make a clicker to click the speaker
    Clicker clicker(PORTC, PC0);

    // Seed the PRNG
    srand(15);

    while (true)
    {
        // If the LED switch is on, then draw a fancy pattern
        if (led_switch.read())
        {
            leds.play(alternate_orange, get_size(alternate_orange));
            leds.play(alternate_orange, get_size(alternate_orange));
            leds.play(alternate_orange, get_size(alternate_orange));
            leds.play(alternate_orange, get_size(alternate_orange));
            leds.play(reverse_speed_circle_red, get_size(reverse_speed_circle_red));
            leds.play(reverse_speed_circle_red, get_size(reverse_speed_circle_red));
            leds.play(fun_opposite_chase, get_size(fun_opposite_chase));
            leds.play(chasing_with_flash, get_size(chasing_with_flash));
            leds.play(chasing_with_flash, get_size(chasing_with_flash));
            leds.play(top_down_back, get_size(top_down_back));
            leds.play(twoxthree_spin, get_size(twoxthree_spin));
            leds.play(twoxthree_spin, get_size(twoxthree_spin));
            leds.play(twoxthree_spin, get_size(twoxthree_spin));
            leds.play(twoxthree_spin, get_size(twoxthree_spin));
            leds.play(alternate, get_size(alternate));
            leds.play(alternate, get_size(alternate));
            leds.play(alternate, get_size(alternate));
            leds.play(alternate, get_size(alternate));
            leds.play(bounce, get_size(bounce));
            leds.play(bounce, get_size(bounce));
            leds.play(bounce, get_size(bounce));
            leds.play(bounce, get_size(bounce));

        }
        else
        {
            if (speaker_switch.read())
            {
                // All LED's on for testing
                uint32_t led_temp = 4294967295;
                leds.draw(led_temp, 1);
            }
            else
            {
                // LED button is off, let's output the value of the UV index
                uint8_t uv_index = 0;
                uv_index = sensor.uv_index();

                // Grab a random number between 0 and 150
                uint32_t temp = (uint32_t) ((double) rand() /
                                            ((double) RAND_MAX + 1) * 150);

                // Clamp the minimum value
                if (temp == 0)
                    temp = 1;

                // Apply the random value to the delay value
                temp = temp * 4;
                temp = (temp / (uv_index + 1));
                clicker.click();
                delay_ms(temp);

                // All LED's flicker red to the light sensor
                uint32_t led_temp = 4294901760;
                leds.draw(led_temp, 1);
            }
        }
    }
    return(0);
}
