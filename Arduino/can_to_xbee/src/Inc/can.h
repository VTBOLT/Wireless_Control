/**
 * @file can.h
 *
 * @brief Header containing macros, variables, and function initializations for can.cpp
 *
 * @author Colton Tshudy, Aaron Kanefsky
 *
 * @date 4/13/2024
 */

#ifndef CAN_H_
#define CAN_H_

/* INCLUDES */
#include <Arduino.h>
#include <mcp_can.h>
//#include "imu.h"


/* MACROS */
#define CAN0_INT 2 

// CAN IDs
#define AUX_BATTERY 0x700
#define MAIN_BATTERY 0x6B0
#define MAIN_PACK_TEMP 0x6B4
#define MOTOR_TEMP 0xA2
#define BMS_TEMP 0x6B1
#define MC_TEMP 0xA1
#define RPM 0xA5
#define SPEED 0x00
#define IMU_1 0x0B1
#define IMU_2 0x0B2
#define IMU_3 0x0B3



      

/* STRUCTS */
struct _MessageData1
{
    // Defined from Mason
    uint16_t aux_voltage;
    //uint8_t aux_percent;
    uint8_t pack_state_of_charge;
    uint16_t high_cell_temp;
    uint16_t low_cell_temp;
    uint16_t motor_temperature;
    uint16_t bms_temperature;
    uint16_t mc_temp;
    int16_t motor_speed;
    int16_t bike_speed;
    
    // Not defined yet
    int32_t longitude;
    int32_t latitude;
    uint64_t time_stamp_unix;


};
typedef struct _MessageData1 MessageData1;



void checkCan(MessageData1 *inputData, MCP_CAN canObj);


void printCANFrame(MessageData1 *inputData);


//void sendIMUMessage(IMU_Data data, MCP_CAN canObj);

#endif /* CAN_H */