# GPS_parsing_library

## Description
GPS_parsing_library is intended for resource-constrained contexts like System-on-Chip (SoC) or general microcontrollers, where it can parse GGA sentences properly and extract useful information from it. It currently supports GGA type sentences only.


## Directory Structure     
```
GPS_Parsing_library/
├── CMakeLists.txt
├── unit_tests/
│   ├── CMakeLists.txt
│   ├── README.md
│   └── main/
│       ├── test_gps_data_parser_main.c
│       └── CMakeLists.txt
├── main/
│   ├── CMakeLists.txt
│   └── main.c
├── components/gps_data_parser/
    ├── CMakeLists.txt
    ├── gps_data_parser.c
    ├── gps_data_parser.h
    ├── Component.md
├── outputs
└── README.md
```

This repository source code is further divided into following parts:
- unit_tests: This is a sub_project for running unit test (details for buidling and flashing are in the respective readme file).
- main: This includes example for parsing gps data.
- components: This includes the gps_data_parser files which contain the implementation for our gps parsing library
- outputs: This contains the outputs for different input sentences. Please refer to these images for further clarification.


## Getting Started
In-order to get this repository setup on your local development machine, make sure to have all the pre-requisites installed as mentioned below

### Prerequisities
The following is required to run the source code:  
ESP32:
- Install esp-idf version "5.0"

### Setup
In-order to have development setup ready on the machine, make sure that aforementioned pre-reqs are installed. After that, download the Git repository on local machine. 

### Building
The following is required to build the projects:
ESP32:
- Open ESP-IDF command prompt and go to project directory for GPS_Parsing_library. 
- Run idf.py build

### Flashing
ESP32:
- Open ESP-IDF command prompt and go to project directory for esp32. 
- Run idf.py -p  (COM port you are using) flash

### Debugging
The following can be used for debugging:  
ESP32:
- Print logs on console
- Monitor outputs using idf.py monitor after flashing

## Default values
Incase a field is missing it will be filled with a default value as mentioned in the table below
| Fields      | Default value |
|-----------|-----|
| Time      | 000000.000  |
| latitude     | 0000.0000  |
| latitude indicator     | 0  |
| longitude   | 00000.0000  |
| longitude indicator   | 0  |
| fix quality   | 10  |
| satellites   | 100  |
| HDOP   | 0  |
| altitude   | 0  |
| altitude_unit  | 0  |
| geoidal height   | 0  |
| geoidal height unit   | 0  |
| DGPS time   | 0  |
| DGPS station id   | 0000  |