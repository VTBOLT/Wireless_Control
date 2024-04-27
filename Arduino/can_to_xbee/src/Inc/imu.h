#pragma once

#include <arduino.h>

struct _IMU_Data{
    union{float f;  byte b[4];} yaw;
    union{float f;  byte b[4];} pitch;
    union{float f;  byte b[4];} roll;

    // Acceleration
    union{float f;  byte b[4];} a_x;
    union{float f;  byte b[4];} a_y;
    union{float f;  byte b[4];} a_z;

    bool imu_sync_detected = false; // check if the sync byte (0xFA) is detected
    byte in[100]; // array to save data send from the IMU
}; typedef struct _IMU_Data IMU_Data;

void read_imu_data(IMU_Data data);
void check_sync_byte(void);
unsigned short calculate_imu_crc(byte data[], unsigned int length);





