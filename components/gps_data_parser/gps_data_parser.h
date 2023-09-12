#ifndef GPS_DATA_PARSER_H
#define GPS_DATA_PARSER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#define MAX_SENTENCE_LENGTH 90   // Maximum length of a nmea sentence to store it in an array of characters excluding terminating sequence

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

typedef struct{
    int8_t   hours;                               // Time in HH
    int8_t   minutes;                             // Time in MM
    float    seconds;                             // Time in SS.SSS
}frame_time_t;

typedef struct{
    float latitude_val;                            // Latitude in decimal degrees
    char  indicator_lat;                           // N for North, S for South
}position_latitude_t;

typedef struct{
    float longitude_val;                           // Longitude in decimal degrees
    char  indicator_lon;                           // E for East, W for West
}position_longitude_t;

typedef struct{
    float altitude_val;                            // Altitude above sea level
    char unit_altitude;                            // Unit of altitude (M for meters)
}altitude_data_t;

typedef struct{
    float height_geoidal_separation;               // Geoidal separation 
    char unit_geoidal_height;                      // Unit of geoidal separation (M for meters)  
}geoidal_data_t;

typedef struct{
    float time_since_last_dgps;                    // Time (seconds) since last DGPS updateNull when DGPS is not used
    uint16_t dgps_station_id;                      // DGPS reference station ID
}Differential_GPS_Data_t;

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


bool check_sentence_validity_and_integrity(const char* gps_sentence);
bool sentence_type_GGA(const char *gps_sentence);
bool parse_GGA_sentence(const char *gps_sentence, GGA_Data_t *Received_data);

#ifdef __cplusplus
}
#endif

#endif // GPS_DATA_PARSER_H