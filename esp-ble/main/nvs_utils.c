/**
 * @file nvs_utils.c
 * @brief Utilities for initializing and managing ESP-IDF Non-Volatile Storage (NVS).
 *
 * Non-Volatile Storage (NVS) is a library provided by ESP-IDF that allows
 * storing key-value pairs in flash memory. It is commonly used for storing
 * configuration data, calibration values, and other persistent information
 * that must be retained across device resets and power cycles.
 *
 * This file provides a function to initialize the NVS subsystem. Initialization
 * must be performed before using any NVS APIs. If the NVS partition is truncated
 * or contains data in an incompatible format, the initialization function will
 * attempt to erase and re-initialize the partition.
 */

#include <stdio.h>
#include "nvs_flash.h"
#include "esp_log.h"
#include "sdkconfig.h"

static const char *TAG = "nvs_utils";

/**
 * @brief Initialize the Non-Volatile Storage (NVS) flash partition.
 *
 * This function must be called before any other NVS operations.
 * It handles common initialization errors by erasing the NVS partition
 * if necessary and retrying the initialization.
 *
 * @return
 *      - ESP_OK on success
 *      - Appropriate esp_err_t code otherwise
 */
esp_err_t nvs_utils_init(void)
{
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_LOGW(TAG, "NVS partition was truncated or has a new version, erasing...");
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    if (ret == ESP_OK) {
        ESP_LOGI(TAG, "NVS initialized successfully");
    } else {
        ESP_LOGE(TAG, "Failed to initialize NVS: %s", esp_err_to_name(ret));
    }
    return ret;
}