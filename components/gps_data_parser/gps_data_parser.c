#include <stdio.h>
#include <stdbool.h>
#include "gps_data_parser.h"



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
        printf("Invalid sentence type");
        return false;
    }else{
        printf("valid sentence");
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

    // To check of there is any other garbage value after checksum
    while (*gps_sentence == '\r' || *gps_sentence == '\n') {
        gps_sentence++;
    }

    // Extra check to see if there are still values after end sequence if yes then its invalid  
    if (*gps_sentence) {
        return false;
    }else {
        // do nothing
    }

    return true;
}