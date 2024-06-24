# IoT Architecture for an Infineon Board

This project showcases the development of an IoT system that integrates Alexa with sensors connected to an Infineon board. The system was developed under the guidance of Professor Paolo Bernardi and PhD Giorgio Insinga in 2023. The primary goal was to create a seamless interaction between the Infineon board, Alexa, and various cloud services.

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Technologies Used](#technologies-used)
- [Architecture](#architecture)
- [License](#license)

## Introduction

This project integrates Amazon Alexa with sensors connected to an Infineon board. It leverages the Adafruit cloud for storage and data fetching, and IFTTT services to interconnect Alexa with the Adafruit portal. The implementation includes the use of a real-time operating system (RTOS) to manage the execution of essential routines required for sensor and network communication.

## Features

- **Alexa Integration**: Control and monitor sensors through Amazon Alexa.
- **Real-Time Data Management**: Utilizes RTOS for efficient task scheduling.
- **Cloud Connectivity**: Stores and retrieves data using the Adafruit cloud.
- **IFTTT Automation**: Connects Alexa with Adafruit portal using IFTTT services.
- **Low-Level Communication**: Implements protocols for data communication between the Infineon board and external devices.

## Technologies Used

- **Programming Languages**: C, Python
- **Cloud Services**: Adafruit IO
- **Automation Platform**: IFTTT
- **Voice Assistant**: Amazon Alexa
- **Real-Time Operating System**: RTOS

## Architecture

The system architecture consists of the following components:

1. **Infineon Board**: Equipped with various sensors and connected to the network.
2. **Adafruit Cloud**: Used for storing sensor data and fetching values.
3. **IFTTT Services**: Bridges the communication between Alexa and Adafruit.
4. **Amazon Alexa**: Interacts with the system to control and monitor sensors.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.


