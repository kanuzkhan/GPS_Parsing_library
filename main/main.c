/*
 * File: main.c
 * Description: Example for gps_parsing_library to extract the required information.
 * Author: Kanuz Khan
 * Date: September 13, 2023
 */

#include <stdio.h>
#include <ctype.h>
#include "gps_data_parser.h"
void app_main(void)
{
    char sentence_gps_gga [MAX_SENTENCE_LENGTH]= "$GPGGA,,,,,,0,00,99.99,,,,,,*48";

    GGA_Data_t data;

    printf("%s\n",sentence_gps_gga );
    
    if (Parse_gps_data(sentence_gps_gga, &data)){
        printf("Successful!!\n"
        "%d Hours %d Minutes %f Seconds\n"
        "Latitude value: %f Latitude Indicator: %c\n" 
        "Longitude value: %f Longitude Indicator: %c\n"
        "Fix quality: %d\n"
        "Satellites tracked: %d\n"
        "HDOP: %f\n"
        "Altitude value: %f Altitude unit: %c\n"
        "Geoidal height: %f Geoidal unit: %c\n"
        "Time (DGPS): %f Station ID: %d\n",
        data.time.hours,data.time.minutes,data.time.seconds,
        data.latitude.latitude_val,data.latitude.indicator_lat,
        data.longitude.longitude_val,data.longitude.indicator_lon,
        data.fix_quality_indicator,
        data.satellites,
        data.horizontal_dilution_precision,
        data.altitude.altitude_val, data.altitude.unit_altitude,
        data.geoidal_height.height_geoidal_separation, data.geoidal_height.unit_geoidal_height,
        data.differential_info.time_since_last_dgps, data.differential_info.dgps_station_id); 
    }else{
        printf("Error!!\n");
    }
}
