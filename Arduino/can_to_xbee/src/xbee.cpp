/**
 * @file xbee.cpp
 *
 * @brief Header containing macros, variables, and function initializations for xbee.cpp
 *
 * @author Colton Tshudy, Aaron Kanefsky
 *
 * @date 4/13/2024
 */

/* Includes */
#include <Arduino.h>
#include "Inc/xbee.h"


/* Function Definitions */

XbeeFrame constructFrame()
{
    XbeeFrame frame;

    // set static frame elements
    frame.startDelim = START_DELIM;
    frame.frameType = FRAME_TYPE;
    frame.frameID = FRAME_ID;
    frame.bitAddr64 = DESTINATION_64;
    frame.bitAddr16 = DESTINATION_16;
    frame.broadcastRadius = BROADCAST_RAD;
    frame.options = OPTIONS;

    // char buf[9];
    // snprintf(buf, 8, "%d", DESTINATION_64);
    // Serial.println((unsigned long)frame.bitAddr16);

    // set data bytes all to 0x00
    memset(frame.data_p, 0, sizeof(frame.data_p));

    // set dynamic frame elements
    frame.length = calcLength(&frame);
    frame.checksum = calcCheckSum(&frame);

    return frame;
}

/* Function Definitions */

uint16_t calcLength(XbeeFrame *frame_p)
{
    uint16_t length = 0;
    length += sizeof(frame_p->frameType);
    length += sizeof(frame_p->frameID);
    length += sizeof(frame_p->bitAddr64);
    length += sizeof(frame_p->bitAddr16);
    length += sizeof(frame_p->broadcastRadius);
    length += sizeof(frame_p->options);
    length += sizeof(frame_p->data_p);

    return length;
}

uint8_t calcCheckSum(XbeeFrame *frame_p)
{
    // The checksum is 0xFF minus 8-bit sum of bytes
    uint8_t sum = 0;
    sum += (frame_p->frameType);
    sum += (frame_p->frameID);
    sum += (frame_p->bitAddr64);
    sum += (frame_p->bitAddr16);
    sum += (frame_p->broadcastRadius);
    sum += (frame_p->options);
    for (int i = 0; i < DATA_SIZE; i++)
    {
        sum += frame_p->data_p[i];
    }
    return 0xFF - sum;
}


void printFrame(XbeeFrame *frame_p){
    unsigned int test = 1;
    uint8_t bit_endian_swap;
    for(int i=0; i<7;++i){
        bit_endian_swap = (bit_endian_swap|(test>>i)&0x01)<<1; 
    }   
    //uint8_t outFrame[20] = {0x7E, 0x00, 0x10, 0x10, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFE, 0x00, 0x00, 0x48, 0x69, 0x42};
    uint8_t outFrame[FRAME_SIZE];
    memset(outFrame, 0, sizeof(outFrame));
    memcpy(outFrame, &(frame_p->startDelim), sizeof(frame_p->startDelim));
    memcpy(outFrame + 1, &test, sizeof(frame_p->length));
    //memcpy(outFrame + 1, &(frame_p->length), sizeof(frame_p->length));


    const uint8_t *ptr = (const uint8_t*) frame_p;
    char msgString[3];
    for(size_t i = 0; i < sizeof(outFrame); i++){
        sprintf(msgString, " %.2X", *(outFrame+i));
        Serial.print(msgString);
    }
    Serial1.write(outFrame, 20);



}

