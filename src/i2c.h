#ifndef I2C_H
#define I2C_H

#include <zephyr/drivers/i2c.h>

#define SENSOR1_ADDR 0x77
#define SENSOR2_ADDR 0x70

int i2c_init(void);
void read_sensor_data(uint32_t *sensor1_value, uint32_t *sensor2_value);

#endif // I2C_H
