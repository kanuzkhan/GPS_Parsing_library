#include <string.h>
#include "unity.h"
#include "gps_data_parser.h"



GGA_Data_t test_data;

static const char* valid_sentences_gga[] = {
    "$GPGGA,,,,,,0,00,99.99,,,,,,*48",
    "$GPGGA,002153.000,3342.6618,N,11751.3858,W,1,10,1.2,27.0,M,-34.2,M,,0000*5E",
    "$GPGGA,092750.000,5321.6802,N,00630.3372,W,1,8,1.03,61.7,M,55.2,M,,*76",
    "$GPGGA,210230,3855.4487,N,09446.0071,W,1,07,1.1,370.5,M,-29.5,M,,*7A",
    "$GPGGA,123204.00,5106.94086,N,01701.51680,E,1,06,3.86,127.9,M,40.5,M,,*51"
};

static const char* invalid_sentences_gga[] = {
    "$GPGGA,,,,,,0,00,99.99,,,,,,*48,999",
    "$$GPGGA,002153.000,,N,,W,1,10,1.2,27.0,M,-34.2,M,,0000*5E",
    "$GPGGA,456789.012,4567.8901,N,8901.4567,W,1,14,1.3,55.0,M,-38.0,M,,4321*89",
    "$GPGGA,111222.333,6000.000,N,08000.000,E,1,05,1.5,100.0,M,5.6,M,,*99",
    "$GPGGA,123456.789,1234.5678,N,5678.1234,W,1,08,1.2,50.0,M,-34.2,M,,1234*45"
};

static const char* invalid_sentence_not_GGA[] = {
    "$GPGSA,*A,1,,,,,,,,,,,,,99.99,99.99,99.99*30",
    "$GPGSV,*124445,1,13,02,28,259,33,04,12,212,27,05,34,305,30,07,79,138,*7F",
    "$GPRMC,12*3205.00,A,5106.94085,N,01701.51689,E,0.016,,280214,,,A*7B",
    "$GPVTG,*,,,,,,,,N*30",
    "$GPGLL,,**,,,,V,N*64"
};

void set_up(void)
{
    // do nothing
}

void tear_down(void)
{
    //do nothing
}

void test_sentence_validity_integrity(void)
{
    // Tests for valid inputs, should be true and for invalid inputs it should be false
    for (int sample_data = 0; sample_data < 5; sample_data++ ){
        TEST_ASSERT_TRUE(check_sentence_validity_and_integrity(valid_sentences_gga[sample_data]));
        TEST_ASSERT_FALSE(check_sentence_validity_and_integrity(invalid_sentences_gga[sample_data]));
    }
}

void test_sentence_type(void)
{
    // Tests for valid inputs, should be true and for invalid inputs it should be false
    for (int sample_data = 0; sample_data < 5; sample_data++ ){
        TEST_ASSERT_TRUE(sentence_type_GGA(valid_sentences_gga[sample_data]));
        TEST_ASSERT_FALSE(sentence_type_GGA(invalid_sentence_not_GGA[sample_data]));
    }
}

void test_parse_GGA_sentence(void)
{
    // Tests for valid inputs, should be true and for invalid inputs it should be false
    for (int sample_data = 0; sample_data < 5; sample_data++ ){
        TEST_ASSERT_TRUE(parse_GGA_sentence(valid_sentences_gga[sample_data], &test_data));
        TEST_ASSERT_FALSE(parse_GGA_sentence(invalid_sentence_not_GGA[sample_data], &test_data));
    }
}

void test_Parse_gps_data()
{
    // Tests for valid inputs, should be true and for invalid inputs it should be false
    for (int sample_data = 0; sample_data < 5; sample_data++ ){
        TEST_ASSERT_TRUE(Parse_gps_data(valid_sentences_gga[sample_data], &test_data));
        TEST_ASSERT_FALSE(Parse_gps_data(invalid_sentences_gga[sample_data], &test_data));
    }
    
}

int app_main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_sentence_validity_integrity); 
    RUN_TEST(test_sentence_type); 
    RUN_TEST(test_parse_GGA_sentence); 
    RUN_TEST(test_Parse_gps_data); 
    return(UNITY_END());
}