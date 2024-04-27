/**
 * @file main.cpp
 *
 * @brief Constructs XBee frames based on CAN messages
 *
 * @author Colton Tshudy
 *
 * @date 4/13/2024
 */

#include <Inc/app.h>
#include "UniversalTimer.h"
#include "Inc/imu.h"

MCP_CAN CAN0(53);
Application app; // Application struct
#define FRAME_INTERVAL 500

UniversalTimer frameSendTimer(FRAME_INTERVAL, true);

IMU imuData;

void setup()
{
    // Constructs the application struct
    app = Application_construct();

    Serial.begin(115200);
    Serial1.begin(115200);
    frameSendTimer.start();

    // Initialize MCP2515 running at 16MHz with a baudrate of 500kb/s and the masks and filters disabled.
    if (CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ) == CAN_OK)
        Serial.println("MCP2515 Initialized Successfully!");
    else
        Serial.println("Error Initializing MCP2515...");

    CAN0.setMode(MCP_NORMAL); // Set operation mode to normal so the MCP2515 sends acks to received data.

    pinMode(CAN0_INT, INPUT); // Configuring pin for /INT input

    Serial.println("MCP2515 Library Receive Example...");
}

void loop()
{
    // Should blink every second, if not, the Arduino is hung
    nonBlockingLED(&app);

    // Primary source of action, baby
    applicationLoop(&app);

    imuData.imu_sync_detected = false;

     // Check if new IMU data is available
    if (Serial2.available() > 29)
        imuData.check_sync_byte();

    // If sync byte is detected, read the rest of the data
    if (imuData.imu_sync_detected){
        imuData.read_imu_data();
        // sendIMUMessage(data, CAN0);
    }
}

// First time setup for the Application
Application Application_construct()
{
    Application app;

    app.watchdog_timer = SWTimer_construct(MS_IN_SECONDS);
    
    app.xbeeFrame1 = constructFrame();
    return app;
    
}

void applicationLoop(Application *app_p)
{
    checkCan(&app_p->messageData1, CAN0);

    if (frameSendTimer.check())
    {
        
        encodeData(&app_p->xbeeFrame1, &app_p->messageData1);
        // If so, keep reading
        calcLength(&app_p->xbeeFrame1);
        calcCheckSum(&app_p->xbeeFrame1);
        printFrame(&app_p->xbeeFrame1);
    }

}

// Blinks an LED once a second as a visual indicator of processor hang
void nonBlockingLED(Application *app_p)
{
    static bool state = true;

    if (SWTimer_expired(&app_p->watchdog_timer))
    {
        digitalWrite(LED_PIN, state);
        state = !state;
        SWTimer_start(&app_p->watchdog_timer);
    }
}

// Pin state setup
void InitializePins()
{
    pinMode(LED_PIN, OUTPUT);
    pinMode(CS_PIN, OUTPUT);
    pinMode(INC_PIN, OUTPUT);
    pinMode(UD_PIN, OUTPUT);
}
