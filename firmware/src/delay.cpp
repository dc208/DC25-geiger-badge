#include "delay.h"

/******************************************************************************/
void delay_ms(uint32_t count)
{
    while (count--)
    {
        _delay_ms(1);
    }
}

/******************************************************************************/
void delay_us(uint32_t count)
{
    while (count--)
    {
        _delay_us(1);
    }
}