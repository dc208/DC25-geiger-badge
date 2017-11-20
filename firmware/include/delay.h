/*******************************************************************************
 * We need to define our own delay functions since AVR's util/delay.h can't
 * handle dynamic (run-time) variables for its delay functions.
 ******************************************************************************/
#ifndef DC208_DELAY_H
#define DC208_DELAY_H

// In order for the delay functions to work right, we have to tell them how fast
// the CPU is running.
#define F_CPU 1000000UL // 1Mhz
#include <util/delay.h>

/*******************************************************************************
 * Millisecond Delay
 *
 * @param[in] count The number of milliseconds to delay for
 ******************************************************************************/
void delay_ms(uint32_t count);

/*******************************************************************************
 * Microsecond Delay
 *
 * @param[in] count The number of microseconds to delay for
 ******************************************************************************/
void delay_us(uint32_t count);

#endif //DC208_DELAY_H
