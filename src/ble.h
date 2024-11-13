/**************************************************************************//**
* @file      ble.h
* @brief     Template for ESE516 with Doxygen-style comments
* @author    Tarush Sharma
* @date      2024-11-07

******************************************************************************/

#pragma once
#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
* Includes
******************************************************************************/
#include <zephyr/types.h>
/******************************************************************************
* Defines
******************************************************************************/
#define BT_UUID_LBS_VAL \
	BT_UUID_128_ENCODE(0x00001523, 0x1212, 0xefde, 0x1523, 0x785feabcd123)

/** @brief Button Characteristic UUID. */
#define BT_UUID_LBS_BUTTON_VAL \
	BT_UUID_128_ENCODE(0x00001524, 0x1212, 0xefde, 0x1523, 0x785feabcd123)

/** @brief LED Characteristic UUID. */
#define BT_UUID_LBS_LED_VAL \
	BT_UUID_128_ENCODE(0x00001525, 0x1212, 0xefde, 0x1523, 0x785feabcd123)

/** @brief Sensor Characteristic UUID. */
#define BT_UUID_LBS_MYSENSOR_VAL \
	BT_UUID_128_ENCODE(0x00001526, 0x1212, 0xefde, 0x1523, 0x785feabcd123)    

/** @brief Sensor Characteristic UUID. */
#define BT_UUID_LBS_MYSENSOR2_VAL \
	BT_UUID_128_ENCODE(0x00001527, 0x1212, 0xefde, 0x1523, 0x785feabcd123)  

/*Converting array to generic UUID*/
#define BT_UUID_LBS           BT_UUID_DECLARE_128(BT_UUID_LBS_VAL)
#define BT_UUID_LBS_BUTTON    BT_UUID_DECLARE_128(BT_UUID_LBS_BUTTON_VAL)
#define BT_UUID_LBS_LED       BT_UUID_DECLARE_128(BT_UUID_LBS_LED_VAL)
#define BT_UUID_LBS_MYSENSOR       BT_UUID_DECLARE_128(BT_UUID_LBS_MYSENSOR_VAL)
#define BT_UUID_LBS_MYSENSOR2       BT_UUID_DECLARE_128(BT_UUID_LBS_MYSENSOR2_VAL)
/******************************************************************************
* Structures and Enumerations
******************************************************************************/
/** @brief Callback type for when an LED state change is received. */
typedef void (*led_cb_t)(const bool led_state);

/** @brief Callback type for when the button state is pulled. */
typedef bool (*button_cb_t)(void);

/** @brief sttructure used by the LBS service*/
struct my_lbs_cb {
	/** LED state change callback. */
	led_cb_t led_cb;
	/** Button read callback. */
	button_cb_t button_cb;
};



/******************************************************************************
* Global Function Declaration
******************************************************************************/
/** @brief function used to initilase the lbs service */
int my_lbs_init(struct my_lbs_cb *callbacks);

/** @brief function used to indicate the button state */
int my_lbs_send_button_state_indicate(bool button_state);

/** @brief  function used to send notification value to sensor charcateristic*/
int my_lbs_send_sensor_notify(uint32_t sensor_value);

int my_lbs_send_sensor2_notify(uint32_t sensor_value);

#ifdef __cplusplus
}
#endif