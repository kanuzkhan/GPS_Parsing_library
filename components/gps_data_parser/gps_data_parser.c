#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "gps_data_parser.h"


bool parse_GGA_sentence(const char* gps_sentence, GGA_Data_t *Received_data)
{
    // Parsing the GGA sentence
    sentence_gga_parameters_t field_parsed = 0;
    const char *field_start = gps_sentence + 7;  // Pointing to the start of second field Skipping '$GPGGA,'
    const char *field_end = NULL;
    while (*field_start && (field_parsed < 15)){
        int degrees_lat_lon = 0;

        field_end = strchr(field_start, ',');  // To skip "," while extracting the required information
        
        // To make sure it points to the end of the field properly
        if (field_end == NULL){
            field_end = field_start + strlen(field_start);
        }else{
            // do nothing
        }
        

        switch (field_parsed){
            case GGA_FRAME_TIME:
                if (!((field_end - field_start) >= 6)){
                    Received_data->time.hours = DEFAULT_GGA_FRAME_TIME;
                    Received_data->time.minutes = DEFAULT_GGA_FRAME_TIME;
                    Received_data->time.seconds = DEFAULT_GGA_FRAME_TIME;
                }else{
                    if ((sscanf(field_start, "%2hhd%2hhd%f", &Received_data->time.hours, &Received_data->time.minutes, &Received_data->time.seconds)) != 3){
                        return false;
                    }else {
                        // do nothing
                    }
                }
                break;

            case GGA_LATITUDE_VALUE:
                if (!((field_end - field_start) >= 4)){
                    Received_data->latitude.latitude_val = DEFAULT_GGA_LATITUDE_VALUE;
                }else{
                // Extract degrees and minutes
                    if (sscanf(field_start, "%2d%f", &degrees_lat_lon, &Received_data->latitude.latitude_val) != 2) {
                        return false;
                    }else{
                        // Convert latitude to decimal degrees
                        Received_data->latitude.latitude_val = degrees_lat_lon + (Received_data->latitude.latitude_val / 60.0);
                    }
                }
                break;

            case GGA_LATITUDE_INDICATOR: 
                if ((*field_start != 'N') && (*field_start != 'S')){
                    Received_data->latitude.indicator_lat = DEFAULT_GGA_LATITUDE_INDICATOR;
                }else if (*field_start == 'S'){
                    Received_data->latitude.indicator_lat = *field_start;
                }else if (*field_start == 'N'){
                    Received_data->latitude.indicator_lat = *field_start;
                }else{
                    // do nothing
                }
                break;

            case GGA_LONGITUDE_VALUE: 
                if (!((field_end - field_start) >= 5)){
                    Received_data->longitude.longitude_val = DEFAULT_GGA_LONGITUDE_VALUE;
                }else{
                // Extract degrees and minutes
                    if (sscanf(field_start, "%3d%f", &degrees_lat_lon, &Received_data->longitude.longitude_val) != 2){
                        return false;
                    }else{
                        // Convert longitude to decimal degrees
                        Received_data->longitude.longitude_val = degrees_lat_lon + (Received_data->longitude.longitude_val / 60.0);
                    }
                }
                break;

            case GGA_LONGITUDE_INDICATOR:
                if (*field_start != 'E' && *field_start != 'W'){
                    Received_data->longitude.indicator_lon = DEFAULT_GGA_LONGITUDE_INDICATOR;
                }else if (*field_start == 'W'){
                    Received_data->longitude.indicator_lon = *field_start;
                }else if (*field_start == 'E'){
                    Received_data->longitude.indicator_lon = *field_start;
                }else{
                    // do nothing
                }
                break;

            case GGA_FIX_QUALITY:
                if ((field_end - field_start) != 1 ){
                    Received_data->fix_quality_indicator = DEFAULT_GGA_FIX_QUALITY;
                }else{
                    if (sscanf(field_start, "%hhd", &Received_data->fix_quality_indicator) != 1){
                        return false;
                    }else{
                        // do nothing
                    }
                }
                break;

            case GGA_USED_SATELLITES:
                if (!((field_end - field_start) <= 2 )){
                    Received_data->satellites = DEFAULT_GGA_USED_SATELLITES;
                }else{
                    if (sscanf(field_start, "%hhd", &Received_data->satellites) != 1){
                        return false;
                    }else{
                        // do nothing
                    }
                }
                break;

            case GGA_HDOP:
                if (!((field_end - field_start) >= 3)){
                    Received_data->horizontal_dilution_precision = DEFAULT_GGA_HDOP;
                }else{
                    if (sscanf(field_start, "%f", &Received_data->horizontal_dilution_precision) != 1){
                        return false;
                    }else{
                        // do nothing
                    }
                }
                break;

            case GGA_ALTITUDE:
                if (!((field_end - field_start) >= 3)){
                    Received_data->altitude.altitude_val = DEFAULT_GGA_ALTITUDE;
                }else{
                    if (sscanf(field_start, "%f", &Received_data->altitude.altitude_val) != 1){
                        return false;
                    }else{
                        // do nothing
                    }
                }
                break;

            case GGA_ALTITUDE_UNIT:
                if (*field_start != 'M'){
                    Received_data->altitude.unit_altitude = DEFAULT_GGA_ALTITUDE_UNIT;
                }else if (*field_start == 'M'){
                    Received_data->altitude.unit_altitude = *field_start;
                }else{
                    // do nothing
                }
                break;

            case GGA_GEOID:
                if (!((field_end - field_start) >= 3)){
                    Received_data->geoidal_height.height_geoidal_separation = DEFAULT_GGA_GEOID;
                }else{
                    if (sscanf(field_start, "%f", &Received_data->geoidal_height.height_geoidal_separation) != 1){ 
                        return false;
                    }else{
                        // do nothing
                    }
                }
                break;

            case GGA_GEOID_UNIT:
                if (*field_start != 'M'){
                    Received_data->geoidal_height.unit_geoidal_height = DEFAULT_GGA_GEOID_UNIT;
                }else if (*field_start == 'M'){
                    Received_data->geoidal_height.unit_geoidal_height = *field_start;
                }else{
                    // do nothing
                }
                break;

            case GGA_TIME_DGPS:
                if (!((field_end - field_start) >= 1)){
                    Received_data->differential_info.time_since_last_dgps = DEFAULT_GGA_TIME_DGPS;
                }else{
                    if (sscanf(field_start, "%f", &Received_data->differential_info.time_since_last_dgps) != 1){ 
                        return false;
                    }else{
                        // do nothing
                    }
                }
                break;

            case GGA_ID_STATION:
                if (!((field_end - field_start) >= 3)){
                    Received_data->differential_info.dgps_station_id = DEFAULT_GGA_ID_STATION;
                }else{
                    if (sscanf(field_start, "%hd", &Received_data->differential_info.dgps_station_id) != 1){
                        Received_data->differential_info.dgps_station_id = DEFAULT_GGA_ID_STATION;
                    }else{
                        // do nothing
                    }
                }
                break;

            default:
                break;
        }

        // Move to the next field
        field_parsed++;
        field_start = field_end + 1;
    }
    return true;
}

static int char_to_int(char k) 
{
    if (k >= '0' && k <= '9') {
        return ( k - '0');
    } else if (k >= 'a' && k <= 'f') {
        return (( k - 'a') + 10);
    } else if (k >= 'A' && k <= 'F') {
        return ((k - 'A')  + 10);
    } else {
        return -1; // Invalid hexadecimal character
    }
}

bool check_sentence_validity_and_integrity(const char* gps_sentence)
{
    uint8_t checksum_calculated = 0x00;

    // Initial check for valid sentence.
    if (*gps_sentence++ != '$')
    {
        return false;
    }else{
        // do nothing
    }

    // Checksum for Packet integrity.
    while (*gps_sentence && (*gps_sentence != '*'))
    {
        checksum_calculated ^= *gps_sentence++;     // XOR of all the bytes between $ and * 
    }

    // check for sentence integrity by comparing the calculated checksum and received checksum
    if (*gps_sentence == '*') {
        // Extract checksum which are basically two characters after *
        gps_sentence++;
        int upper_nibble_checksum = char_to_int(*gps_sentence);
        if (upper_nibble_checksum == -1){
            return false;
        } else {
            gps_sentence++;
        }

        int lower_nibble_checksum = char_to_int(*gps_sentence);
        if (lower_nibble_checksum == -1){
            return false;
        } else {
            gps_sentence++;
        }

        int checksum_received = ((upper_nibble_checksum << 4) | lower_nibble_checksum); //    xxxx0000 | 0000xxxx = xxxxxxxx 

        // Check integrity by comparing calculated and received checksums
        if (checksum_calculated != checksum_received){
            return false;
        } else {
            // do nothing
        }
    }

    // Check for terminating sequence
    while (*gps_sentence == '\r' || *gps_sentence == '\n') {
        gps_sentence++;
    }

    // Check to see if there are still values after end sequence if yes then its invalid  
    if (*gps_sentence) {
        return false;
    }else {
        // do nothing
    }

    return true;
}
bool sentence_type_GGA(const char *gps_sentence)
{
    // Check if the sentence is a GGA sentence
    if (strncmp(gps_sentence, "$GPGGA,", 7) == 0){
        return true;
    }else{
        return false;
    } 
}

bool Parse_gps_data(const char *gps_sentence, GGA_Data_t *Received_data)
{
    // Check for validity and integrity
    if (!(check_sentence_validity_and_integrity(gps_sentence))){
        return false;
    }else{
        if (!(sentence_type_GGA(gps_sentence))){
        return false;
        }else{
            if (!(parse_GGA_sentence(gps_sentence, Received_data))){
                return false;
            }else{
                return true;
            }
        }
    }
}