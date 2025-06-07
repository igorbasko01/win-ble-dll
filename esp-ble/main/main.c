#include <stdio.h>
#include "ble_server.h"
#include "nvs_utils.h"
#include "esp_log.h"
#include "ble_dispatcher.h"

static const char *TAG = "main";

void app_main(void)
{
    ESP_LOGI(TAG, "Hello, from ESP32!");

    esp_err_t nvs_ret = nvs_utils_init();
    if (nvs_ret != ESP_OK) {
        ESP_LOGE(TAG, "NVS initialization failed: %s", esp_err_to_name(nvs_ret));
        return;
    } else {
        ESP_LOGI(TAG, "NVS initialized successfully.");
    }

    ble_server_init();
    ESP_LOGI(TAG, "BLE server initialized.");

    ble_dispatcher_init();
    ESP_LOGI(TAG, "BLE dispatcher initialized.");
}