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


MCP_CAN CAN0(53);
Application app; // Application struct

void setup()
{
    // Constructs the application struct
    app = Application_construct();

    Serial.begin(115200);

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
}

// First time setup for the Application
Application Application_construct()
{
    Application app;

    app.watchdog_timer = SWTimer_construct(MS_IN_SECONDS);

    return app;
}

void applicationLoop(Application *app_p)
{
    app_p->xbeeFrame1 = constructFrame();

  checkCan(&app_p->messageData1, CAN0);
  printCANFrame(&app_p->messageData1);
  Serial.println();
  // If so, keep reading
    calcLength(&app_p->xbeeFrame1);
    calcCheckSum(&app_p->xbeeFrame1);
    //printFrame(&app_p->xbeeFrame1);
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

void xBeeFillFrame1(XbeeFrame *frame_p, MessageData1 *messageData_p)
{
    memcpy(frame_p->data_p, messageData_p, sizeof(*messageData_p));
    calcCheckSum(frame_p);
}
