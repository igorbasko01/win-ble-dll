#pragma once
#include <esp_gatts_api.h>

typedef void (*ble_service_event_callback_t)(esp_gatts_cb_event_t event,
                                             esp_gatt_if_t gatts_if,
                                             esp_ble_gatts_cb_param_t *param);

typedef struct {
    ble_service_event_callback_t on_event;
} ble_service_registration_t;

void ble_dispatcher_init(void);

void ble_dispatcher_register_service(ble_service_registration_t *service);
