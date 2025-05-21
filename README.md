# BLE Unity Plugin
This project holds the implementation of a BLE client plugin for Unity on Windows.
It might be mostly used when developing on Unity and would like to test the game
with BLE compatibility withtout building and running it on other platforms just for 
validating that BLE related features are working.

## Project Overview
This project contains several projects that will allow streamlined development
of the Unity plugin.

It would contain the following projects:
 - BLE-DLL - The project that will contain the low level implementation of the BLE client using
 WinRT.
 - Unity BLE package - A project that will hold the Unity BLE package that would contain the DLL and 
 related C#/Unity code and a sample scene.
 - ESP32 - A project for a simple ESP32 implementation that will serve as a BLE server.

## ESP32 project
The `esp-ble` project, is an ESP32 compatible implementation for a BLE server, that should
be used for testing the `BLE-DLL` and Unity BLE package as a real BLE device.

It is developed using VSCode and uses the `ESP-IDF` extension. Install it before using the 
`esp-ble` project.