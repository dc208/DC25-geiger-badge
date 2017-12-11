/*******************************************************************************
 * Bit bang TWI master driver based off the Atmel Application Note 156.
 * To use this code on different pins/ports, simply change the definitions in
 * this header file.
 ******************************************************************************/
#ifndef TWI_MASTER_H_
#define TWI_MASTER_H_

#include <avr/io.h>

// Definition of pin used as SCL.
#define SCL PC5

// Definition of pin used as SDA.
#define SDA PC4

// Definition of PORT used as SCL.
#define PORT_SCL PORTC

// Definition of DDR used as SCL.
#define DDR_SCL DDRC

// Definition of PIN used as SCL.
#define PIN_SCL PINC

// Definition of PORT used as SDA.
#define PORT_SDA PORTC

// Definition of DDR used as SDA.
#define DDR_SDA DDRC

// Definition of PIN used as SDA.
#define PIN_SDA PINC

// Helper macros to set I2C pin direction
#define SET_SDA_OUT() DDR_SDA |= (1 << SDA)
#define SET_SDA_IN() DDR_SDA &= ~(1 << SDA)
#define SET_SCL_OUT() DDR_SCL |= (1 << SCL)
#define SET_SCL_IN() DDR_SCL &= ~(1 << SCL)

// Helper macros to read clock & data lines
#define READ_SDA() (PIN_SDA & (1 << SDA))
#define READ_SCL() (PIN_SCL & (1 << SCL))?1:0

// Define the read/write bits used in the address header
#define WRITE 0x0
#define READ 0x1

// Delay used to generate clock in micro-seconds
#define DELAY 2

// Delay used for STOP condition
#define SCL_SDA_DELAY 1

/*******************************************************************************
 * Object to encapsulate the TWI master connection with a single slave
 ******************************************************************************/
class I2c
{
public:
    /***************************************************************************
     * Make a new I2c object.
     *
     * @param[in] address The I2C address of the slave device this master will
     *                    talk to.
     **************************************************************************/
    I2c(uint8_t address);

    /***************************************************************************
     * Writes one or more data bytes to the slave
     *
     * @param[in] data Pointer to data buffer
     * @param[in] bytes  Number of bytes to transfer
     *
     * @return true if successful, otherwise false
     **************************************************************************/
    bool write_data(unsigned char* data, uint8_t bytes);

    /***************************************************************************
     * Reads one or more date bytes received from the slave.
     *
     * @param[out] data Pointer to data buffer
     * @param[in] bytes Number of bytes to read
     *
     * @return true if successful, otherwise false
     **************************************************************************/
    bool read_bytes(unsigned char* data, uint8_t bytes);

private:
    /***************************************************************************
     * Initialize twi master mode.
     *
     * @remarks Depends on external pull-up resistors, doesn't drive the pin
     * high.
     **************************************************************************/
    void twi_init();

    /***************************************************************************
     * Sends start condition, used by read and write
     **************************************************************************/
    void twi_start_cond();

    /***************************************************************************
     * Sends slave address and specifies whether we're going to do a read or
     * write operation
     *
     * @param[in] read Value to set the read/write bit to.
     *
     * @return True if the transmission was successful and the slave ack'd,
     * false otherwise.
     **************************************************************************/
    bool send_slave_address(unsigned char read);

    /***************************************************************************
     * Writes a single byte on the I2C bus.
     *
     * @param[in] byte Data
     *
     * @return true if successful, otherwise false
     **************************************************************************/
    bool i2c_write_byte(unsigned char byte);

    /***************************************************************************
     * Reads a single byte on the I2C bus.
     *
     * @param[out] data Pointer to data buffer
     * @param[in] bytes  Number of bytes to read
     * @param[in] index Position of the incoming byte in the receive buffer
     *
     * @return true if successful, otherwise false
     **************************************************************************/
    bool i2c_read_byte(unsigned char* data, uint8_t bytes, uint8_t index);

    /***************************************************************************
     * Sets the clock to a specific value.
     *
     * @param[in] x tristates SCL when x = 1, other wise 0
     **************************************************************************/
    void write_scl(uint8_t x);

    /***************************************************************************
     * Writes the data line to a specific value.
     *
     * @param[in] x tristates SDA when x = 1, other wise 0
     **************************************************************************/
    void write_sda(uint8_t x);

    /***************************************************************************
     * Toggles the clock.
     **************************************************************************/
    void toggle_scl();

    // Slave address
    uint8_t m_address;
};

#endif /* TWI_MASTER_H_ */
