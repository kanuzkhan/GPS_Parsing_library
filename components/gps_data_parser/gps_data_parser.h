#ifndef GPS_DATA_PARSER_H
#define GPS_DATA_PARSER_H

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_SENTENCE_LENGTH 80 // Maximum length of a nmea sentence to store it in an array of characters excluding   
typedef struct{
    uint8_t   hours;                                   // Time in HH
    uint8_t   minutes;                                 // Time in MM
    float seconds;                                 // Time in SS.SSS
}frame_time_t;

typedef struct{
    float latitude;                                // Latitude in decimal degrees (DDMM.MMMM)
    char lat_indicator;                            // N for North, S for South
}position_latitude_t;

typedef struct{
    float longitude;                               // Longitude in decimal degrees (DDDMM.MMMM)
    char lon_indicator;                            // E for East, W for West
}position_longitude_t;

typedef struct{
    float altitude;                                // Altitude above sea level
    char unit_altitude;                            // Unit of altitude (M for meters)
}altitude_data_t;

typedef struct{
    float height_geoidal_separation;               // Geoidal separation 
    char unit_geoidal_height;                      // Unit of geoidal separation (M for meters)  
}geoidal_data_t;

typedef struct{
    float time_since_last_dgps;                    // Time since last DGPS update (seconds)
    uint16_t dgps_station_id;                           // DGPS reference station ID
}Differential_GPS_Data_t;

typedef struct {
    frame_time_t time;                             // Time in hour minutes seconds (HHMMSS.SSS) format
    position_latitude_t  latitude;                 // Latitude in decimal degrees (DDMM.MMMM) along with indicator (North or South)
    position_longitude_t longitude;                // Longitude in decimal degrees (DDMM.MMMM) along with indicator (Easth or West)
    uint8_t fix_quality_indicator;                 // 0 = Invalid, 1 = GPS_Fix, 2 = DGPS_Fix, 3 = not_applicable
    uint8_t satellites;                            // Number of satellites used to calculate positions
    float horizontal_dilution_precision;           // The current satellite geometry's effect on position accuracy.
    altitude_data_t altitude;                      // Altitude above sealevel along with its unit 
    geoidal_data_t geoidal_height;                  // The difference between ellipsoid and sea level along with its unit
    Differential_GPS_Data_t differential_info;     // Provides the time since last DGPS update and the reference station id
}GGA_Data_t;

#ifdef __cplusplus
}
#endif

#endif // GPS_DATA_PARSER_H