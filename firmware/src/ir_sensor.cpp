#include "ir_sensor.h"
#include "delay.h"

/******************************************************************************/
Ir_sensor::Ir_sensor(I2c &i2c) : m_i2c(i2c)
{
    // Initialize the sensor upon creation
    init();
}

/******************************************************************************/
uint8_t Ir_sensor::uv_index()
{
    // Local buffers to store register values
    unsigned char data1;
    unsigned char data2;
    uint16_t uv = 0;

    // Take a single measurement
    run_command(0x06);

    // Give the sensor enough time to compute the new value
    delay_ms(1);

    // Read UV Index registers
    data1 = 0x2C;
    data2 = 0x2D;
    m_i2c.write_data(&data1, 1);
    m_i2c.read_bytes(&data1, 1);
    m_i2c.write_data(&data2, 1);
    m_i2c.read_bytes(&data2, 1);

    // Combine the two bytes into one number
    uv = ((uint16_t)data2 << 8) | data1;

    // The sensor gives us the UV index * 100, so let's devide so we get the
    // real index
    uv = uv / 100;

    return uv;
}

/******************************************************************************/
uint8_t Ir_sensor::init()
{
    // Local buffer used for sending/receiving commands to the sensor
    unsigned char data[2];

    // Need to wait a minimum of 25ms for the sensor to start up per datasheet.
    delay_ms(25);

    /***************************************************************************
     * Configure direct registers
     **************************************************************************/
    // Per section 3.2 of the datasheet, write 0x17 to HW_KEY register to start
    // operation.
    data[0] = 0x07;
    data[1] = 0x17;
    if (!m_i2c.write_data(data, 2))
    {
        return 1;
    }

    // Set the MEAS_RATE to 0 in order to use Forced Measurement Mode
    data[0] = 0x08;
    data[1] = 0x00;
    if (!m_i2c.write_data(data, 2))
    {
        return 1;
    }
    data[0] = 0x09;
    data[1] = 0x00;
    if (!m_i2c.write_data(data, 2))
    {
        return 1;
    }

    // Enable UVindex measurement coefficients UCOEF[0:3] to default values as
    // specified by the datasheet

    // Select COFF-1 register
    data[0] = 0x13;
    data[1] = 0x7B;
    if (!m_i2c.write_data(data, 2))
    {
        return 1;
    }

    // Select COFF-2 register
    data[0] = 0x14;
    data[1] = 0x6B;
    if (!m_i2c.write_data(data, 2))
    {
        return 1;
    }

    // Select COFF-3 register
    data[0] = 0x15;
    data[1] = 0x01;
    if (!m_i2c.write_data(data, 2))
    {
        return 1;
    }

    // Select COFF-4 register
    data[0] = 0x16;
    data[1] = 0x00;
    if (!m_i2c.write_data(data, 2))
    {
        return 1;
    }

    /***************************************************************************
     * Configure RAM values
     **************************************************************************/
    // Enable UV Index, Visible light, and IR sensing.
    // Select PARAM_WR register
    data[0] = 0x17;
    data[1] = 0xB0;
    if (!m_i2c.write_data(data, 2))
    {
        return 1;
    }
    // Run PARAM_SET command to set CHLIST
    while(!run_command(0x01 | 0xA0));

    // Enable ALS_IR_ADCMUX
    // Select PARAM_WR register
    data[0] = 0x17;
    // Small IR photodiode
    data[1] = 0x00;
    if (!m_i2c.write_data(data, 2))
    {
        return 1;
    }
    while(!run_command(0x0E | 0xA0));

    return 0;
}

/******************************************************************************/
bool Ir_sensor::run_command(uint8_t value)
{
    // Local buffer used for sending/receiving commands to the sensor
    unsigned char data[2];

    // This sequence is required per the datasheet for each command run.

    // Clear the response register by sending a NOP
    // NOP
    data[0] = 0x18;
    data[1] = 0x00;
    if (!m_i2c.write_data(data, 2))
    {
        return false;
    }

    // Verify the NOP by reading RESPONSE register
    data[0] = 0x20;
    if (!m_i2c.write_data(data, 1))
    {
        return false;
    }
    uint8_t retry_count = 0;
    while (data[0] != 0)
    {
        m_i2c.read_bytes(data, 1);
        retry_count++;
        if(retry_count > 10)
        {
            return false;
        }
    }

    // Send the command
    data[0] = 0x18;
    data[1] = (unsigned char)value;
    if (!m_i2c.write_data(data, 2))
    {
        return false;
    }

    // Wait for the command to complete
    data[0] = 0x20;
    if (!m_i2c.write_data(data, 1))
    {
        return false;
    }
    data[0] = 0x00;
    retry_count = 0;
    while(data[0] == 0)
    {
        m_i2c.read_bytes(data, 1);
        retry_count++;
        if (retry_count > 10)
        {
            return false;
        }
    }

    // Check response for error
    if (data[0] >= 0x80)
    {
        // Response register has an error in it. Leave it up to the caller to
        // determine what to do next.
        return false;
    }

    return true;
}