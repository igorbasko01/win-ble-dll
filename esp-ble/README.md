# ESP32-BLE
This project is a sample project for an ESP32 board that enables BLE on the device
and allows communicating with it.

The basic components of the project are:
1. `ble_server` - responsible for initializing a BLE server and advertising.
1. `ble_dispatcher` - responsible for listening to GATT events and passing them to relevant BLE service.
1. `ble_service_*` - can be multiple different BLE services that are responsible for several characteristics. 
Should handle initializing and updating characteristics.

## BLE Services
Basically each service is responsible for some aspect of the device. Each service should register with the
dispatcher and be ready to handle events. The service should ignore events that are not related to it.