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

    // set data bytes all to 0x00
    memset(frame.data_p, 0x00, sizeof(frame.data_p));

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

void xBeeFillFrame1(XbeeFrame *frame_p, MessageData1 *messageData_p)
{
    memcpy(frame_p->data_p, messageData_p, sizeof(*messageData_p));
}

// char *toString(XbeeFrame *frame_p)
// {
//     uint32_t frameSize = sizeof(*frame_p); //byte length of the frame
//     uint16_t cursor = 0;


//     char bufferHead[20]
//     char bufferData[]
//     char bufferTail[2]
//     char output[frameSize * 2]; //byte length of the frame

//     snprintf(buffer, sizeof(frame_p->startDelim), "%02x", frame_p->startDelim)

//     for (uint32_t i = 0; i < frameSize; i++)
//     {
//         snprintf(buffer, frameSize * 2, "%02x", );
//     }
// }