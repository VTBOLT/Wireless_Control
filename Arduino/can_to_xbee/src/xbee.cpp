/**
 * @file xbee.cpp
 *
 * @brief Header containing macros, variables, and function initializations for xbee.cpp
 *
 * @author Colton Tshudy
 *
 * @date 4/7/2024
 */
#include <Arduino.h>
#include"Inc/xbee.h"
void constructFrame(XbeeFrame *frame_p){
    // Only for constant, non- changing values
    frame_p->startDelim = START_DELIM;
    frame_p->length = calcLength(frame_p);
    frame_p->frameType = FRAME_TYPE;
    frame_p->frameID = FRAME_ID;
    frame_p->bitAddr64 = DESTINATION_64;
    frame_p->bitAddr16 = DESTINATION_16;
    frame_p->broadcastRadius = BROADCAST_RAD;
    frame_p->options = OPTIONS;
    memset(frame_p->data_p, 0x00, DATA_SIZE);
    frame_p->checksum = calcCheckSum(frame_p);
    
}

uint16_t calcLength(XbeeFrame *frame_p){
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

uint8_t calcCheckSum(XbeeFrame *frame_p){
    // The checksum is 0xFF minus 8-bit sum of bytes
    uint8_t sum = 0;
    sum += (frame_p->frameType);
    sum += (frame_p->frameID);
    sum += (frame_p->bitAddr64);
    sum += (frame_p->bitAddr16);
    sum += (frame_p->broadcastRadius);
    sum += (frame_p->options);
    for(int i = 0; i < DATA_SIZE; i++){
        sum += *(frame_p->data_p)[i];
    }
    return 0xFF - sum;
}

void xBeeFillFrame1(XbeeFrame *frame_p, MessageData1 *messageData_p){
    memcpy(frame_p->data_p, messageData_p, sizeof(*messageData_p));
}