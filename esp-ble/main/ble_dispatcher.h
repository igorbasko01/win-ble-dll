/**
 * @file ble_dispatcher.h
 * @brief BLE GATT service event dispatcher for ESP BLE applications.
 *
 * The dispatcher is the main entry point for GATT events. It provides
 * registration and unregistration of BLE GATT services, and dispatches
 * GATT events to all registered services.
 */

#pragma once
#include <esp_gatts_api.h>

typedef void (*ble_service_event_callback_t)(esp_gatts_cb_event_t event,
                                             esp_gatt_if_t gatts_if,
                                             esp_ble_gatts_cb_param_t *param);

typedef struct {
    ble_service_event_callback_t on_event;
    uint16_t service_uuid;
} ble_service_registration_t;

typedef void (*ble_dispatcher_register_service_t)(ble_service_registration_t *service);
typedef void (*ble_dispatcher_unregister_service_t)(ble_service_registration_t *service);

typedef struct {
    ble_dispatcher_register_service_t register_service;
    ble_dispatcher_unregister_service_t unregister_service;
} ble_dispatcher_t;

/**
 * @brief Initialize the BLE dispatcher.
 *
 * Must be called before registering any services.
 */
ble_dispatcher_t ble_dispatcher_init(void);

/**
 * @brief Register a BLE service to receive GATT events.
 *
 * @param service Pointer to the service registration structure.
 */
void ble_dispatcher_register_service(ble_service_registration_t *service);

/**
 * @brief Unregister a BLE service so it no longer receives GATT events.
 *
 * @param service Pointer to the service registration structure to remove.
 */
void ble_dispatcher_unregister_service(ble_service_registration_t *service);
