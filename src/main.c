#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/gap.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/bluetooth/conn.h>
#include <dk_buttons_and_leds.h>

#ifdef CONFIG_BLEFUNCTION
#include "ble.h"
#endif

#define DEVICE_NAME CONFIG_BT_DEVICE_NAME
#define DEVICE_NAME_LEN (sizeof(DEVICE_NAME) - 1)

#define STACKSIZE 1024
#define PRIORITY 7

#define RUN_STATUS_LED DK_LED1
#define CON_STATUS_LED DK_LED2
/*Button to be controlled*/
#define USER_BUTTON DK_BTN1_MSK
/*Led to be controlled */
#define USER_LED DK_LED3
/*Interval for status led */
#define RUN_LED_BLINK_INTERVAL 1000
/*Interval at which the sensor data is sent*/
#define NOTIFY_INTERVAL 500

LOG_MODULE_REGISTER(Application_code, LOG_LEVEL_INF);

static bool app_button_state;
static uint32_t app_sensor_value = 100;

static uint32_t app_sensor2_value = 300;

/*Function to simulate data*/
static void simulate_data(void)
{
	app_sensor_value++;
	app_sensor2_value++;
	if (app_sensor_value == 200) {
		app_sensor_value = 100;
	}

	if (app_sensor2_value == 500) {
		app_sensor2_value = 500;
	}
}

/*Thread to send sensor data*/
void send_data_thread(void)
{
	while(1){
		/* Simulate data */
		simulate_data();
		/* Send notification, the function sends notifications only if a client is subscribed */
		my_lbs_send_sensor_notify(app_sensor_value);

		my_lbs_send_sensor2_notify(app_sensor2_value);

		k_sleep(K_MSEC(NOTIFY_INTERVAL));
	}
		
}

/*Parmeters for advertising data*/
static const struct bt_le_adv_param *adv_param = BT_LE_ADV_PARAM(
	(BT_LE_ADV_OPT_CONNECTABLE |
	 BT_LE_ADV_OPT_USE_IDENTITY), /* Connectable advertising and use identity address */
	800, /* Min Advertising Interval 500ms (800*0.625ms) */
	801, /* Max Advertising Interval 500.625ms (801*0.625ms) */
	NULL); /* Set to NULL for undirected advertising */

/*Data to be sent during advertising */
static const struct bt_data ad[] = {
	BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
	BT_DATA(BT_DATA_NAME_COMPLETE, DEVICE_NAME, DEVICE_NAME_LEN),

};

/*Data to be sent during a scan response */
static const struct bt_data sd[] = {
	BT_DATA_BYTES(BT_DATA_UUID128_ALL, BT_UUID_LBS_VAL),
};

/* Define the application callback function for controlling the LED */
static void app_led_cb(bool led_state)
{
	dk_set_led(USER_LED, led_state);
}

/* Define the application callback function for reading the state of the button */
static bool app_button_cb(void)
{
	return app_button_state;
}

/* Declare a varaible app_callbacks of type my_lbs_cb and initiate its members to the applications call back functions we developed in steps 8.2 and 9.2. */
static struct my_lbs_cb app_callbacks = {
	.led_cb = app_led_cb,
	.button_cb = app_button_cb,
};

static void button_changed(uint32_t button_state, uint32_t has_changed)
{
	if (has_changed & USER_BUTTON) {
		uint32_t user_button_state = button_state & USER_BUTTON;
                // send indication to button press
                my_lbs_send_button_state_indicate(user_button_state);
		app_button_state = user_button_state ? true : false;
	}
}

/*Callback function to be called when connected */
static void on_connected(struct bt_conn *conn, uint8_t err)
{
	if (err) {
		printk("Connection failed (err %u)\n", err);
		return;
	}

	printk("Connected\n");

	dk_set_led_on(CON_STATUS_LED);
}

/*Callback function to be called when disconnected*/
static void on_disconnected(struct bt_conn *conn, uint8_t reason)
{
	printk("Disconnected (reason %u)\n", reason);

	dk_set_led_off(CON_STATUS_LED);
}

/*Register the connected and disconnected callbacks*/
struct bt_conn_cb connection_callbacks = {
	.connected = on_connected,
	.disconnected = on_disconnected,
};

static int init_button(void)
{
	int err;

	err = dk_buttons_init(button_changed);
	if (err) {
		printk("Cannot init buttons (err: %d)\n", err);
	}

	return err;
}

int main(void)
{	
        int blink_status = 0;
	int err;

	LOG_INF("Starting Application Code");

	err = dk_leds_init();
	if (err) {
		LOG_ERR("LEDs init failed (err %d)\n", err);
		return -1;
	}

	err = init_button();
	if (err) {
		printk("Button init failed (err %d)\n", err);
		return -1;
	}

	err = bt_enable(NULL);
	if (err) {
		LOG_ERR("Bluetooth init failed (err %d)\n", err);
		return -1;
	}
	bt_conn_cb_register(&connection_callbacks);

        err = my_lbs_init(&app_callbacks);
	if (err) {
		printk("Failed to init LBS (err:%d)\n", err);
		return -1;
	}

	LOG_INF("Bluetooth initialized\n");
	err = bt_le_adv_start(adv_param, ad, ARRAY_SIZE(ad), sd, ARRAY_SIZE(sd));
	if (err) {
		LOG_ERR("Advertising failed to start (err %d)\n", err);
		return -1;
	}

	LOG_INF("Advertising successfully started\n");

        while(1){

                dk_set_led(RUN_STATUS_LED, (++blink_status) % 2);
		k_sleep(K_MSEC(RUN_LED_BLINK_INTERVAL));
        }
}

/*Thread defined to send sensor data*/
K_THREAD_DEFINE(send_data_thread_id, STACKSIZE, send_data_thread, NULL, NULL, NULL, PRIORITY, 0, 0);