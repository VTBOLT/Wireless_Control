/**
 * @file app.h
 *
 * @brief Header containing macros, variables, and function initializations for main.cpp
 *
 * @author Colton Tshudy
 *
 * @date 4/7/2024
 */

/* Arduino Includes */
#include <Arduino.h>
#include <Inc/xbee.h>
#include <Inc/can.h>


/* HAL Includes */
#include <HAL\HAL.h>
#include <HAL\Timer.h>

#ifndef APPLICATION_H_
#define APPLICATION_H_

/* Settings */
#define ECHO_EN 1

/* Parameters */
#define BAUDRATE 115200 // baud/s

/* Macros */
#define MS_IN_SECONDS 1000 // milliseconds in a second

typedef enum
{
    Idle,
    Executing,
    Linear,
    Waiting
} _appStates; // states for the serial reader

/** =================================================
 * Primary struct for the application
 */
struct _Application
{
    SWTimer watchdog_timer;
    XbeeFrame xbeeFrame1;
    MessageData1 messageData1;
   
    
};
typedef struct _Application Application;

/** Constructs the application construct */
Application Application_construct();

/** Primary loop */
void applicationLoop(Application *app_p);

/** Heatbeat of the Arduino */
void nonBlockingLED(Application *app_p);

/**
 * @brief Fills out the data field of frame with ID 0x01
 *
 * @param frame_p
 * @param messageData_p
 */
void xBeeFillFrame1(XbeeFrame *frame_p, MessageData1 *messageData_p); // ID 1


void constructCAN(Application *app_p);

#endif /* APPLICATION_H_ */