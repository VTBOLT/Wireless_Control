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
// https://forum.arduino.cc/t/arduino-nano-mcp2515-tja1050-coryjfowler-can-not-get-work/623811
MCP_CAN CAN0(10);      // For the NANO
//MCP_CAN CAN0(53);   // For the MEGA
Application app; // Application struct

void setup()
{
    // Constructs the application struct
    app = Application_construct();

    Serial.begin(115200);  

    CAN0.setMode(MCP_NORMAL); // Set operation mode to normal so the MCP2515 sends acks to received data.

    pinMode(CAN0_INT, INPUT); // Configuring pin for /INT input
}

void loop()
{
    // Should blink every second, if not, the Arduino is hung
    nonBlockingLED(&app);
    printFrame(&(app.xbeeFrame1));
    delay(100);
    // Primary source of action, baby
    applicationLoop(&app);
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
    //Serial.println();
    //encodeData(&app_p->xbeeFrame1, &app_p->messageData1);
    // If so, keep reading
    calcLength(&app_p->xbeeFrame1);
    calcCheckSum(&app_p->xbeeFrame1);
    printFrame(&app_p->xbeeFrame1);
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

