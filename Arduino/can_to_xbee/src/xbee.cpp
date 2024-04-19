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
    frame.bitAddr16 = REV16(DESTINATION_16);
    frame.broadcastRadius = BROADCAST_RAD;
    frame.options = OPTIONS;

    // set data bytes all to 0x00
    memset(frame.data_p, 0x00, sizeof(frame.data_p));
    frame.data_p[0] = XBEE_FRAME_ID_1;
    
    // update the dynamic frame elements
    frame.length = REV16(calcLength(&frame));
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
    return 0xFF - (sum-3);
}

void encodeData(XbeeFrame * frame_p, MessageData1* messageData1){
    // set static frame elements
    frame_p->startDelim = START_DELIM;
    frame_p->frameType = FRAME_TYPE;
    frame_p->frameID = FRAME_ID;
    frame_p->bitAddr64 = DESTINATION_64;
    frame_p->bitAddr16 = REV16(DESTINATION_16);
    frame_p->broadcastRadius = BROADCAST_RAD;
    frame_p->options = OPTIONS;

    // set data bytes all to 0x00
    memset(frame_p->data_p, 0x00, sizeof(frame_p->data_p));
    frame_p->data_p[0] = XBEE_FRAME_ID_1;
    frame_p->data_p[1] = messageData1->aux_voltage;
    frame_p->data_p[3] = messageData1->pack_state_of_charge;
    frame_p->data_p[4] = messageData1->high_cell_temp;
    frame_p->data_p[6] = messageData1->low_cell_temp;
    frame_p->data_p[8] = messageData1->motor_temperature;
    frame_p->data_p[10] = messageData1->bms_temperature;
    frame_p->data_p[12] = messageData1->mc_temp;
    frame_p->data_p[14] = messageData1->motor_speed;
    frame_p->data_p[16] = messageData1->bike_speed;

    
    // set dynamic frame elements
    frame_p->length = REV16(calcLength(frame_p));
    frame_p->checksum = calcCheckSum(frame_p);
    
}

void printFrame(XbeeFrame *frame_p){    
    //uint8_t outFrame[20] = {0x7E, 0x00, 0x10, 0x10, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFE, 0x00, 0x00, 0x48, 0x69, 0x42};
    uint8_t outFrame[FRAME_SIZE];
    memset(outFrame, 0, sizeof(outFrame));  // Empty the frame
   
    
    
    // Fill the frame
    memcpy(outFrame, &(frame_p->startDelim), sizeof(frame_p->startDelim));
    memcpy(outFrame + 1, &(frame_p->length), sizeof(frame_p->length));
    memcpy(outFrame + 3, &(frame_p->frameType), sizeof(frame_p->frameType));
    memcpy(outFrame + 4, &(frame_p->frameID), sizeof(frame_p->frameID));
    //memcpy(outFrame + 11, &test, sizeof(test));
    memcpy(outFrame + 11, &(frame_p->bitAddr64), sizeof(frame_p->bitAddr64));
    memcpy(outFrame + 13, &(frame_p->bitAddr16), sizeof(frame_p->bitAddr16));     // 0xFE = 0b 1111 1110
    memcpy(outFrame + 15, &(frame_p->broadcastRadius), sizeof(frame_p->broadcastRadius));
    memcpy(outFrame + 16, &(frame_p->options), sizeof(frame_p->options));
    memcpy(outFrame + 17, &(frame_p->data_p), sizeof(frame_p->data_p));
    memcpy(outFrame + 63, &(frame_p->checksum), sizeof(frame_p->checksum));
    
    //Verify the frame is correct in ascii format (Only for debugging the frame)
    // const uint8_t *ptr = (const uint8_t*) frame_p;
    // char msgString[3];
    // for(size_t i = 0; i < sizeof(outFrame); i++){
    //     sprintf(msgString, " %02X", *(outFrame+i));
    //     Serial.print(msgString);
    // }
    // Serial.println();
   
    
    // This will be used to actually send the frame
    Serial.write(outFrame, sizeof(outFrame));

}