/**
 * @file can.h
 *
 * @brief Header containing macros, variables, and function initializations for can.cpp
 *
 * @author Colton Tshudy
 *
 * @date 4/7/2024
 */
#include <Arduino.h>
struct _MessageData
{
    uint8_t aux_voltage;
    uint8_t aux_percent;
    uint8_t pack_state_of_charge;
    uint16_t high_cell_temp;
    uint16_t low_cell_temp;
    uint16_t motor_temperature;
    uint16_t bms_temperature;
    uint16_t motor_speed;
    uint16_t bike_speed;
    uint32_t longitude;
    uint32_t latitude;
    uint64_t time_stamp_unix;


};
typedef struct _MessageData MessageData;