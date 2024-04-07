/**
 * @file main.cpp
 *
 * @brief Constructs XBee frames based on CAN messages
 *
 * @author Colton Tshudy
 *
 * @version 4/7/2024
 */

#include <Arduino.h>
#include <app.h>
#include <HAL\HAL.h>
#include <HAL\Timer.h>

Application app; // Application struct

void setup()
{
    // Constructs the application struct
    app = Application_construct();
}

void loop()
{
    // Should blink every second, if not, the Arduino is hung
    WatchdogLED(&app);


}

// First time setup for the Application
Application Application_construct()
{
    Application app;

    app.watchdog_timer = SWTimer_construct(MS_IN_SECONDS);

    return app;
}

// Blinks an LED once a second as a visual indicator of processor hang
void WatchdogLED(Application *app_p)
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