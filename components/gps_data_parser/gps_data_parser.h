/*
 * File: gps_data_parser.h
 * Description: Declaration of functions for the GPS parsing library along with the required structures, enums and variables.
 * Author: Kanuz Khan
 * Date: September 13, 2023
 */

#ifndef GPS_DATA_PARSER_H
#define GPS_DATA_PARSER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#define MAX_SENTENCE_LENGTH 90   // Maximum length of a nmea sentence

//------------------------------------------------------------------------------
//This type of enumeration lists all fields in a GGA sentence
//-----------------------------------------------------------------------------

typedef enum
{
    GGA_FRAME_TIME = 0,
    GGA_LATITUDE_VALUE,
    GGA_LATITUDE_INDICATOR,
    GGA_LONGITUDE_VALUE,
    GGA_LONGITUDE_INDICATOR,
    GGA_FIX_QUALITY,
    GGA_USED_SATELLITES,
    GGA_HDOP,
    GGA_ALTITUDE,
    GGA_ALTITUDE_UNIT,
    GGA_GEOID,
    GGA_GEOID_UNIT,
    GGA_TIME_DGPS,
    GGA_ID_STATION,
    GGA_CHECKSUM,
    GGA_ERROR
}sentence_gga_parameters_t;

//------------------------------------------------------------------------------
//This type of enumeration lists all default values in case of a missing fields
//-----------------------------------------------------------------------------

typedef enum
{
    DEFAULT_GGA_FRAME_TIME = 0,
    DEFAULT_GGA_LATITUDE_VALUE = 0,
    DEFAULT_GGA_LATITUDE_INDICATOR = 0,
    DEFAULT_GGA_LONGITUDE_VALUE = 0,
    DEFAULT_GGA_LONGITUDE_INDICATOR = 0,
    DEFAULT_GGA_FIX_QUALITY = 10,
    DEFAULT_GGA_USED_SATELLITES = 100,
    DEFAULT_GGA_HDOP = 0,
    DEFAULT_GGA_ALTITUDE = 0,
    DEFAULT_GGA_ALTITUDE_UNIT= 0,
    DEFAULT_GGA_GEOID = 0,
    DEFAULT_GGA_GEOID_UNIT = 0,
    DEFAULT_GGA_TIME_DGPS = 0,
    DEFAULT_GGA_ID_STATION = 0000
}default_missing_field_values_GGA_t;

 /** 
     * Define user-specific datatypes:  frame_time_t
     * This structure defines the individual hours, minutes and seconds of the corresponding time field */

typedef struct{
    int8_t   hours;                               // Time in HH
    int8_t   minutes;                             // Time in MM
    float    seconds;                             // Time in SS.SSS
}frame_time_t;

 /** 
     * Define user-specific datatypes:  position_latitude_t
     * This structure defines the latitude value in degree decimals along with its indicator */

typedef struct{
    float latitude_val;                            // Latitude in decimal degrees
    char  indicator_lat;                           // N for North, S for South
}position_latitude_t;

 /** 
     * Define user-specific datatypes:  position_longitude_t
     * This structure defines the longitude value in degree decimals along with its indicator */

typedef struct{
    float longitude_val;                           // Longitude in decimal degrees
    char  indicator_lon;                           // E for East, W for West
}position_longitude_t;

 /** 
     * Define user-specific datatypes:  altitude_data_t
     * This structure defines the altitude value along with its unit */

typedef struct{
    float altitude_val;                            // Altitude above sea level
    char unit_altitude;                            // Unit of altitude (M for meters)
}altitude_data_t;

 /** 
     * Define user-specific datatypes:  geoidal_data_t
     * This structure defines the geoidal seperation (height) value along with its unit */

typedef struct{
    float height_geoidal_separation;               // Geoidal separation 
    char unit_geoidal_height;                      // Unit of geoidal separation (M for meters)  
}geoidal_data_t;

 /** 
     * Define user-specific datatypes:  Differential_GPS_Data_t
     * This structure defines the differential time (seconds) along with the station used for transmission null incase when DGPS in not used */

typedef struct{
    float time_since_last_dgps;                    // Time (seconds) since last DGPS updateNull when DGPS is not used
    uint16_t dgps_station_id;                      // DGPS reference station ID
}Differential_GPS_Data_t;

 /** 
     * Define user-specific datatypes:  GGA_Data_t
     * This structure defines the individual components of the GGA sentence */

typedef struct {
    frame_time_t time;                             // Time in hour minutes seconds format
    position_latitude_t  latitude;                 // Latitude in decimal degrees along with indicator (North or South)
    position_longitude_t longitude;                // Longitude in decimal degrees along with indicator (Easth or West)
    uint8_t fix_quality_indicator;                 // 0 = Invalid, 1 = GPS_Fix, 2 = DGPS_Fix, 3 = not_applicable
    uint8_t satellites;                            // Number of satellites used to calculate positions
    float horizontal_dilution_precision;           // The current satellite geometry's effect on position accuracy.
    altitude_data_t altitude;                      // Altitude above sealevel along with its unit 
    geoidal_data_t geoidal_height;                 // The difference between ellipsoid and sea level along with its unit
    Differential_GPS_Data_t differential_info;     // Provides the time since last DGPS update and the reference station id
}GGA_Data_t;


/*----------------------------------------------------------------------------*/
/** 
* \brief                           This function checks sentence validity and integrity  
* \param data [pointer]            Pointer to the GGA sentence
* \return [bool]                   True if sentence is valid and vice versa
*/
bool check_sentence_validity_and_integrity(const char* gps_sentence);

/*----------------------------------------------------------------------------*/
/** 
* \brief                           This function checks if the sentenca is GGA type 
* \param data [pointer]            Pointer to the GGA sentence
* \return [bool]                   True if sentence is GGA type and vice versa
*/
bool sentence_type_GGA(const char *gps_sentence);

/*----------------------------------------------------------------------------*/
/** 
* \brief                           This function parses a valid GGA sentence and extracts the required information 
* \param data [pointer]            Pointer to the GGA sentence
* \param data [pointer]            Pointer to the data struct to store information
* \return [bool]                   True if sentence is properly parsed and data is extracted
*/
bool parse_GGA_sentence(const char *gps_sentence, GGA_Data_t *Received_data);

/*----------------------------------------------------------------------------*/
/** 
* \brief                           This function parses a sentence, checks validity,integrity and type, extracts the required information 
* \param data [pointer]            Pointer to the GGA sentence
* \param data [pointer]            Pointer to the data struct to store information
* \return [bool]                   True if sentence is properly parsed and data is extracted
*/
bool Parse_gps_data(const char *gps_sentence, GGA_Data_t *Received_data);

#ifdef __cplusplus
}
#endif

#endif // GPS_DATA_PARSER_H