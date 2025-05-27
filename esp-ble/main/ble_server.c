/** 
 * @file ble_server.c
 *
 * This file implements initialization and basic event handling for a BLE (Bluetooth Low Energy)
 * server on the ESP32 platform using the ESP-IDF framework. It sets up BLE advertising parameters,
 * configures advertising data, and starts advertising when the BLE stack is ready.
 */

#include "esp_err.h"
#include "esp_mac.h"
#include "esp_bt.h"
#include "esp_bt_main.h"
#include "esp_log.h"
#include "esp_gap_ble_api.h"

static const char *TAG = "BLE_SERVER";

static esp_ble_adv_params_t adv_params = {
    // Minimum advertising interval: how often (minimum) the device sends advertising packets (0x20 = 20ms)
    .adv_int_min = 0x20,
    // Maximum advertising interval: how often (maximum) the device sends advertising packets (0x40 = 40ms)
    .adv_int_max = 0x40,
    // Advertising type: general, connectable, undirected (allows any device to connect)
    .adv_type = ADV_TYPE_IND,
    // Address type: use the device's public Bluetooth address (not random)
    .own_addr_type = BLE_ADDR_TYPE_PUBLIC,
    // Advertising channels: use all three primary BLE advertising channels (37, 38, 39)
    .channel_map = ADV_CHNL_ALL,
    // Filter policy: allow scan and connection requests from any device (no filtering)
    .adv_filter_policy = ADV_FILTER_ALLOW_SCAN_ANY_CON_ANY,
};

/**
 * @brief GAP event handler for BLE events.
 *
 * This function is called by the ESP-IDF BLE stack when a GAP event occurs.
 * It logs the event and starts advertising when the advertising data is set.
 *
 * @param event The GAP BLE callback event type.
 * @param param Parameters for the event.
 */
void gap_event_handler(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param)
{
    ESP_LOGI(TAG, "GAP event received: %d", event);
    if (event == ESP_GAP_BLE_ADV_DATA_SET_COMPLETE_EVT) {
        ESP_LOGI(TAG, "Advertising data set complete, starting advertising...");
        esp_ble_gap_start_advertising(&adv_params);
    }
    // Add event-specific handling here as needed
}

/**
 * @brief Initialize the BLE server.
 *
 * This function initializes the Bluetooth controller and Bluedroid stack,
 * registers the GAP event handler, sets the device name, and configures
 * advertising data for BLE advertising.
 */
void ble_server_init(void)
{
    esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();

    ESP_ERROR_CHECK(esp_bt_controller_init(&bt_cfg));
    ESP_ERROR_CHECK(esp_bt_controller_enable(ESP_BT_MODE_BLE));

    ESP_ERROR_CHECK(esp_bluedroid_init());
    ESP_ERROR_CHECK(esp_bluedroid_enable());

    esp_ble_gap_register_callback(gap_event_handler);

    esp_ble_gap_set_device_name("ESP32_BLE_Server");

    // Advertising data configuration
    esp_ble_adv_data_t adv_data = {
        .set_scan_rsp = false,           // If true, this data is for scan response, not advertisement
        .include_name = true,            // Include device name in advertising packet
        .include_txpower = true,         // Include TX power in advertising packet
        .min_interval = 0x0006,          // Minimum connection interval (in units of 1.25ms)
        .max_interval = 0x0010,          // Maximum connection interval (in units of 1.25ms)
        .appearance = 0x00,              // Appearance value (0 = unknown)
        .manufacturer_len = 0,           // Length of manufacturer specific data
        .p_manufacturer_data = NULL,     // Pointer to manufacturer specific data
        .service_data_len = 0,           // Length of service data
        .p_service_data = NULL,          // Pointer to service data
        .service_uuid_len = 0,           // Length of service UUIDs
        .p_service_uuid = NULL,          // Pointer to service UUIDs
        .flag = (ESP_BLE_ADV_FLAG_GEN_DISC | ESP_BLE_ADV_FLAG_BREDR_NOT_SPT) // Advertising flags: general discoverable, BR/EDR not supported
    };

    ESP_ERROR_CHECK(esp_ble_gap_config_adv_data(&adv_data));
}