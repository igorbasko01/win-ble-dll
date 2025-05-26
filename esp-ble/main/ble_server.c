#include "esp_err.h"
#include "esp_mac.h"
#include "esp_bt.h"
#include "esp_bt_main.h"
#include "esp_log.h"
#include "esp_gap_ble_api.h"

static const char *TAG = "BLE_SERVER";

void gap_event_handler(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param)
{
    ESP_LOGI(TAG, "GAP event received: %d", event);
    // Add event-specific handling here as needed
}

void ble_server_init(void)
{
    esp_err_t ret;

    esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();

    ESP_ERROR_CHECK(esp_bt_controller_init(&bt_cfg));
    ESP_ERROR_CHECK(esp_bt_controller_enable(ESP_BT_MODE_BLE));

    ESP_ERROR_CHECK(esp_bluedroid_init());
    ESP_ERROR_CHECK(esp_bluedroid_enable());

    esp_ble_gap_register_callback(gap_event_handler);

    esp_ble_adv_params_t adv_params = {
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

    esp_ble_gap_set_device_name("ESP32_BLE_Server");
}