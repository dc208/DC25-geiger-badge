/*******************************************************************************
 * UV sensor object
 ******************************************************************************/
#ifndef DC208_IR_SENSOR_H
#define DC208_IR_SENSOR_H

#include "TWI_master.h"

/*******************************************************************************
 * Object to encapsulate the complexity of the UV/IR sensor
 ******************************************************************************/
class Ir_sensor
{
public:
    /***************************************************************************
     * Construct a new IR sensor.
     *
     * @param[in] i2c The I2C bus configured to communicate with the sensor
     **************************************************************************/
    Ir_sensor(I2c &i2c);

    /***************************************************************************
     * Read the UV index from the sensor.
     *
     * @return The UV index.
     **************************************************************************/
    uint8_t uv_index();

private:
    /***************************************************************************
     * Initialize Sensor
     *
     * @return 0 success
     *         1 i2c write error - probably because slave failed to ack
     **************************************************************************/
     uint8_t init();

    /***************************************************************************
     * Run a command by following the command sequence outlined by the sensor
     * data sheet
     *
     * @param[in] value The value to write to the command register
     *
     * @return True if the command executed successfully, false otherwise
     **************************************************************************/
     bool run_command(uint8_t value);

    I2c &m_i2c;
};


#endif //DC208_IR_SENSOR_H
