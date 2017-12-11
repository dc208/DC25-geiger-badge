#include "TWI_master.h"
#include "delay.h"

/******************************************************************************/
I2c::I2c(uint8_t address) : m_address(address)
{
    // Prepare the bus
    twi_init();
}

/******************************************************************************/
void I2c::twi_init()
{
    // Set both clock and data lines as inputs (tristate) which will allow both
    // lines to idle high due to the external pull-up resistors.
    SET_SCL_IN();
    SET_SDA_IN();
}

/******************************************************************************/
void I2c::twi_start_cond()
{
    // Pull data low
    write_sda(0);
    delay_us(DELAY);

    // Pull clock low while data is low
    write_scl(0);
    delay_us(DELAY);
}

/******************************************************************************/
bool I2c::send_slave_address(unsigned char read)
{
    return i2c_write_byte((m_address << 1) | read);
}

/******************************************************************************/
bool I2c::write_data(unsigned char* data, uint8_t bytes)
{
    bool ack = false;

    twi_start_cond();

    if(!send_slave_address(WRITE))
    {
        return false;
    }

    for(uint8_t index = 0; index < bytes; index++)
    {
        ack = i2c_write_byte(data[index]);
        if(!ack)
        {
            break;
        }
    }

    //put stop here
    write_scl(1);
    delay_us(SCL_SDA_DELAY);
    write_sda(1);

    return ack;
}

/******************************************************************************/
bool I2c::i2c_write_byte(unsigned char byte)
{
    // Wright each bit in the byte, MSB first
    for (uint8_t bit = 0; bit < 8; bit++)
    {
        write_sda((byte & 0x80) != 0);
        toggle_scl();//goes high
        delay_us(DELAY);
        toggle_scl();//goes low
        byte <<= 1;
        delay_us(DELAY);
    }

    //release SDA to allow for the slave to ack
    SET_SDA_IN();
    toggle_scl(); //goes high for the 9th clock

    //Check for acknowledgment
    if(READ_SDA())
    {
        // Slave failed to ACK
        return false;
    }
    delay_us(DELAY);

    //Pull SCL low
    toggle_scl(); //end of byte with acknowledgment.
    delay_us(DELAY);

    return true;
}

/******************************************************************************/
bool I2c::read_bytes(unsigned char* data, uint8_t bytes)
{
    bool success = false;

    twi_start_cond();

    if(!send_slave_address(READ))
    {
        return false;
    }

    for(uint8_t index = 0; index < bytes; index++)
    {
        success = i2c_read_byte(data, bytes, index);
        if(!success)
        {
            break;
        }
    }

    //put stop here
    write_scl(1);
    delay_us(SCL_SDA_DELAY);
    write_sda(1);

    return success;
}

/******************************************************************************/
bool I2c::i2c_read_byte(unsigned char* rcvdata, uint8_t bytes, uint8_t index)
{
    unsigned char byte = 0;
    unsigned char bit = 0;

    //release SDA
    SET_SDA_IN();

    // Assemble a byte from the wire
    for (bit = 0; bit < 8; bit++)
    {
        toggle_scl();//goes high
        if(READ_SDA())
        {
            byte |= (1 << (7 - bit));
        }
        delay_us(DELAY);
        toggle_scl();//goes low
        delay_us(DELAY);
    }
    rcvdata[index] = byte;

    // If we have more bytes to read, send ACK
    if(index < (bytes-1))
    {
        write_sda(0);
        toggle_scl(); //goes high for the 9th clock
        delay_us(DELAY);
        //Pull SCL low
        toggle_scl(); //end of byte with acknowledgment.
        // release SDA
        write_sda(1);
        delay_us(DELAY);
    }
    else //send NACK on the last byte
    {
        write_sda(1);
        toggle_scl(); //goes high for the 9th clock
        delay_us(DELAY);
        //Pull SCL low
        toggle_scl(); //end of byte with acknowledgment.
        // release SDA
        delay_us(DELAY);
    }
    return true;
}

/******************************************************************************/
void I2c::write_scl (uint8_t x)
{
    if(x)
    {
        // tri-state it, external pull-ups will do their job.
        SET_SCL_IN();
        // check clock stretching
        while(!READ_SCL());
    }
    else
    {
        SET_SCL_OUT();
        PORT_SCL &= ~(1 << SCL); //set it low
    }
}

/******************************************************************************/
void I2c::write_sda (uint8_t x)
{
    if(x)
    {
        //tri-state it, external pull-ups will do their job.
        SET_SDA_IN();
    }
    else
    {
        SET_SDA_OUT();
        PORT_SDA &= ~(1 << SDA); //set it low

    }
}

/******************************************************************************/
void I2c::toggle_scl()
{
    if(PIN_SCL & (1<<SCL))
    {
        // clock is high, set it low
        write_scl(0);
    }
    else
    {
        // clock is low, set it high
        write_scl(1);
    }
}
