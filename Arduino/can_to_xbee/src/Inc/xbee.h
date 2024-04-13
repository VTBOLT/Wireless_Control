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
#include <Inc/can.h>

#ifndef XBEE_H
#define XBEE_H
// Macros for the constants
#define START_DELIM 0x7E
#define FRAME_TYPE 0x10
#define FRAME_ID 0x01
#define DESTINATION_64 0x000000000000FFF
#define DESTINATION_16 0xFFFE
#define BROADCAST_RAD 0x00
#define OPTIONS 0x00
#define SCAFFOLD_SIZE 18    // Constant size of the frame's scaffolding
#define DATA_SIZE 46        //User defined size of the data contained in the frame

struct _XbeeFrame
{
    uint8_t startDelim;
    uint16_t length;
    uint8_t frameType;
    uint8_t frameID;
    uint64_t bitAddr64;
    uint16_t bitAddr16;
    uint8_t broadcastRadius;
    uint8_t options;
    byte* data_p[DATA_SIZE];
    uint8_t checksum;
};
typedef struct _XbeeFrame XbeeFrame;

XbeeFrame constructFrame(XbeeFrame *frame);
uint16_t calcLength(XbeeFrame *frame_p);
uint8_t calcCheckSum(XbeeFrame *frame_p);
void xBeeFillFrame1(XbeeFrame *frame_p, MessageData1 *messageData_p);    // ID 1

#endif /* XBEE_H */