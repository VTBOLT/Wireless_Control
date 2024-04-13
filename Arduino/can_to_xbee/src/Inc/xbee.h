/**
 * @file xbee.h
 *
 * @brief Header containing macros, variables, and function initializations for xbee.cpp
 *
 * @author Colton Tshudy
 *
 * @date 4/7/2024
 */

#include <Arduino.h>


// Macros for the constants
#define START_DELIM 0x7E
#define FRAME_TYPE 0x10
#define FRAME_ID 0x01
const byte DESTINATION_64[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF};
const byte DESTINATION_16[2] = {0xFF, 0xFE};
#define BROADCAST_RAD 0x00
#define OPTIONS 0x00
#define SCAFFOLD_SIZE 18    // Constant size of the frame's scaffolding
#define DATA_SIZE 46        //User defined size of the data contained in the frame

struct _XbeeFrame
{
    byte *startDelim[1];
    byte *length[2];
    byte *frameType[1];
    byte *frameID[1];
    byte *bitAddr64[8];
    byte *bitAddr16[2];
    byte *broadcastRadius[1];
    byte *options[1];
    byte *frame_p[DATA_SIZE];
    byte *checksum[1];
};
typedef struct _XbeeFrame XbeeFrame;

XbeeFrame constructFrame(XbeeFrame *frame);
uint8_t calcCheckSum(XbeeFrame *frame);