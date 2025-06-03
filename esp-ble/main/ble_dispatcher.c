#include "ble_dispatcher.h"
#include <string.h>

#define MAX_BLE_SERVICES 8

static ble_service_registration_t* registered_services[MAX_BLE_SERVICES];
static int num_registered_services = 0;

static void ble_dispatcher_gatts_event_handler(esp_gatts_cb_event_t event,
                                               esp_gatt_if_t gatts_if,
                                               esp_ble_gatts_cb_param_t *param)
{
    for (int i = 0; i < num_registered_services; ++i) {
        if (registered_services[i] && registered_services[i]->on_event) {
            registered_services[i]->on_event(event, gatts_if, param);
        }
    }
}

void ble_dispatcher_init(void)
{
    memset(registered_services, 0, sizeof(registered_services));
    num_registered_services = 0;
    esp_err_t err = esp_ble_gatts_register_callback(ble_dispatcher_gatts_event_handler);
    if (err != ESP_OK) {
        printf("ble_dispatcher: Failed to register GATTS callback, err=0x%x\n", err);
    }
}

void ble_dispatcher_register_service(ble_service_registration_t *service)
{
    if (num_registered_services < MAX_BLE_SERVICES) {
        registered_services[num_registered_services++] = service;
    } else {
        printf("ble_dispatcher: Cannot register more than %d services\n", MAX_BLE_SERVICES);
    }
}
