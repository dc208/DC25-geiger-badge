/*******************************************************************************
 * Here be some helpful macros for manipulating GPIO on the ATTINY1634
 ******************************************************************************/

#ifndef DC208_MARCOS_H
#define DC208_MARCOS_H

// Set bit y on port x. For example: bit_set(PORTA, PA1)
#define bit_set(...)        bit_set_(__VA_ARGS__)
#define bit_set_(x, y)      x |= 1<<y // set a bit

// Clear bit y on port x. For example: bit_clear(PORTA, PA1)
#define bit_clear(...)      bit_clear_(__VA_ARGS__)
#define bit_clear_(x, y)    x &= ~(1<<y) // clear a bit

// Check to see if bit y is set on port x. For example: bit_test(PORTA, PA1)
#define bit_test(...)       bit_test_(__VA_ARGS__)
#define bit_test_(x, y)     (!!(x & (1<<y))) // test a bit

// Set bit y on port x as an output. For example: bit_dir_outp(PORTA, PA1)
#define bit_dir_outp(...)   bit_dir_outp_(__VA_ARGS__)
#define bit_dir_outp_(x, y) *(&x-1) |= 1<<y //access DDRx of PORTx !

// Set bit y on port x as an input. For example: bit_dir_inp(PORTA, PA1)
#define bit_dir_inp(...)    bit_dir_inp_(__VA_ARGS__)
#define bit_dir_inp_(x, y)  *(&x-1) &= ~(1<<y) //access DDRx of PORTx !

// Read input value of pin y on port x. For example: bit_test_in(PORTA, PA1)
#define bit_test_in(...)    bit_test_in_(__VA_ARGS__)
#define bit_test_in_(x, y)  (!!(*(&x-2) & (1<<y))) //access PINx of PORTx !

// Enable pull-up for bit y on port x. For example: bit_pullup(PORTB, PB0)
#define bit_pullup(...)     bit_pullup_(__VA_ARGS__)
#define bit_pullup_(x, y)   (*(&x+1)) |= 1<<y

// Returns the size of an array if array is in scope.  Example: get_size(pattern)
#define get_size(x)         sizeof(x)/sizeof(*x)

#endif //DC208_MARCOS_H
