#include "i2c.h"
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(i2c_module, LOG_LEVEL_INF);

#define I2C_NODE DT_NODELABEL(i2c1)

static const struct device *i2c_dev;

int i2c_init(void)
{
    i2c_dev = DEVICE_DT_GET(I2C_NODE);
    if (!device_is_ready(i2c_dev)) {
        LOG_ERR("I2C device not ready");
        return -1;
    }
    return 0;
}

void read_sensor_data(uint32_t *sensor1_value, uint32_t *sensor2_value)
{
    uint8_t data[2];
    int ret;

    // Read from Sensor 1
    ret = i2c_read(i2c_dev, data, sizeof(data), SENSOR1_ADDR);
    if (ret == 0) {
        *sensor1_value = (data[0] << 8) | data[1];
    } else {
        LOG_ERR("Failed to read Sensor 1");
    }

    // Read from Sensor 2
    ret = i2c_read(i2c_dev, data, sizeof(data), SENSOR2_ADDR);
    if (ret == 0) {
        *sensor2_value = (data[0] << 8) | data[1];
    } else {
        LOG_ERR("Failed to read Sensor 2");
    }
}
