/**
 * @file ble_dispatcher.c
 * @brief BLE dispatcher for managing BLE GATTS event distribution and service registration.
 */

#include "ble_dispatcher.h"
#include <string.h>

#define MAX_BLE_SERVICES 8

static ble_service_registration_t* registered_services[MAX_BLE_SERVICES];
static int num_registered_services = 0;

/**
 * @brief GATTS event handler that dispatches events to all registered services.
 *
 * @param event     The GATTS event type.
 * @param gatts_if  The GATTS interface.
 * @param param     Pointer to event parameters.
 */
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

/**
 * @brief Initializes the BLE dispatcher and registers the GATTS event handler.
 */
void ble_dispatcher_init(void)
{
    memset(registered_services, 0, sizeof(registered_services));
    num_registered_services = 0;
    esp_err_t err = esp_ble_gatts_register_callback(ble_dispatcher_gatts_event_handler);
    if (err != ESP_OK) {
        printf("ble_dispatcher: Failed to register GATTS callback, err=0x%x\n", err);
    }
}

/**
 * @brief Registers a BLE service with the dispatcher.
 *
 * @param service Pointer to the service registration structure.
 */
void ble_dispatcher_register_service(ble_service_registration_t *service)
{
    if (num_registered_services < MAX_BLE_SERVICES) {
        registered_services[num_registered_services++] = service;
    } else {
        printf("ble_dispatcher: Cannot register more than %d services\n", MAX_BLE_SERVICES);
    }
}

/**
 * @brief Unregisters a BLE service from the dispatcher.
 *
 * @param service Pointer to the service registration structure to remove.
 */
void ble_dispatcher_unregister_service(ble_service_registration_t *service)
{
    for (int i = 0; i < num_registered_services; ++i) {
        if (registered_services[i] == service) {
            // Shift remaining services down
            for (int j = i; j < num_registered_services - 1; ++j) {
                registered_services[j] = registered_services[j + 1];
            }
            registered_services[num_registered_services - 1] = NULL;
            num_registered_services--;
            return;
        }
    }
    printf("ble_dispatcher: Service not found for unregistration\n");
}
