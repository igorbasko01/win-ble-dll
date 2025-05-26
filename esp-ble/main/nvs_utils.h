#ifndef NVS_UTILS_H
#define NVS_UTILS_H

#include "esp_err.h"

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
esp_err_t nvs_utils_init(void);

#endif // NVS_UTILS_H
