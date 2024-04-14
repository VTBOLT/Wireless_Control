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



Application app; // Application struct

void setup()
{
    // Constructs the application struct
    app = Application_construct();

    Serial.begin(115200);
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
    
    // Fill a message
    //app.messageData1 = {};

    app.watchdog_timer = SWTimer_construct(MS_IN_SECONDS);

    return app;
}

void applicationLoop(Application *app_p)
{
    app_p->xbeeFrame1 = constructFrame();
    for(int i = 0; i < DATA_SIZE; i++){
        Serial.print(*app_p->xbeeFrame1.data_p[i]);
    }
    Serial.println();
    
    //xBeeFillFrame1(&app_p->xbeeFrame1, &app_p->messageData1);
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