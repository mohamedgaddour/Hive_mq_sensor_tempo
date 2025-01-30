# Project Description

Sensor DHT11 with ESP32 Board

This project demonstrates the integration of the DHT11 temperature and humidity sensor with an ESP32-WROOM-32U microcontroller board. The system reads temperature data when a button is pressed and interacts with the HiveMQ platform as an IoT hub.

## Features

Temperature Reading: On button press, the DHT11 sensor measures the temperature.

Red LED Indicator: The LED illuminates to indicate an active reading or specific conditions.

HiveMQ Integration: Sensor data is transmitted to the HiveMQ platform for monitoring and further processing.

## Hardware Components

DHT11 Sensor: Measures temperature and humidity.

Red LED: Provides visual feedback.

Button: Triggers the sensor reading.

ESP32-WROOM-32U: Microcontroller board for managing sensor data and connecting to HiveMQ.

## Software Requirements

PlatformIO IDE: For development and programming of the ESP32 board.

HiveMQ Broker: Acts as the MQTT broker for IoT communication.

Arduino Libraries: Includes support for the DHT11 sensor and MQTT communication.

### How It Works

Press the button to initiate a temperature reading.

The DHT11 sensor captures the temperature.

The red LED lights up to verify the connection with the platform Hive_mq .

The ESP32 board sends the data to HiveMQ over MQTT for monitoring or analysis.

# Setup Instructions for windows 

1. Copy the example secrets file to create your own `secrets.h`:

# Setup Instructions for Linux/MacOs

1) For macOs/Linux Users, you can create a script (setup.sh)  toa automate  copying teh file 
--------setup.sh ----------------

#!/bin/bash
if [ ! -f secrets.h ]; then
    cp secrets.example.h secrets.h
    echo "secrets.h created! Please update it with your WiFi credentials."
else
    echo "secrets.h already exists."
fi

-----------end setup.sh--------------


2) to  Make it ececutable : chmod +x setup.sh


3) to run the script :  ./setup.sh 