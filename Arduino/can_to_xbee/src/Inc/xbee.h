/**
 * @file xbee.h
 *
 * @brief Header containing macros, variables, and function initializations for xbee.cpp
 *
 * @author Colton Tshudy, Aaron Kanefsky
 *
 * @date 4/13/2024
 */

#ifndef XBEE_H
#define XBEE_H

/* INCLUDES */
#include <Arduino.h>
#include <Inc/can.h>

/* MACROS */
#define START_DELIM 0x7E
#define FRAME_TYPE 0x10
#define FRAME_ID 0x01
#define DESTINATION_64 0x000000000000FFF
#define DESTINATION_16 0xFFFE
#define BROADCAST_RAD 0x00
#define OPTIONS 0x00
#define SCAFFOLD_SIZE 18 // Constant size of the frame's scaffolding
#define DATA_SIZE 46     // User defined size of the data contained in the frame
#define FRAME_SIZE DATA_SIZE + SCAFFOLD_SIZE
/* STRUCTS */
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
    byte data_p[DATA_SIZE];
    uint8_t checksum;
};
typedef struct _XbeeFrame XbeeFrame;

/* FUNCTION DECLARATIONS */

/**
 * @brief Constructs an empty XBee frame with static scaffolding elements
 *
 * @return XbeeFrame
 */
XbeeFrame constructFrame();

/**
 * @brief Calculates the length field of the frame
 *
 * @param frame_p
 * @return uint16_t
 */
uint16_t calcLength(XbeeFrame *frame_p);

/**
 * @brief Caclulates the checksum field of the frame
 *
 * @param frame_p
 * @return uint8_t
 */
uint8_t calcCheckSum(XbeeFrame *frame_p);

/**
 * @brief Prints out the entire Xbee frame using Serial and Serial1
 *
 * @param frame_p
 * @return void
 */
void printFrame(XbeeFrame *frame_p);

#endif /* XBEE_H */