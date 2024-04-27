#pragma once

#include <arduino.h>

class IMU{
    public:
        void read_imu_data();
        void check_sync_byte();
        unsigned short calculate_imu_crc(byte data[], unsigned int length);
        bool imu_sync_detected = false; // check if the sync byte (0xFA) is detected
        const float* getYaw(); //gets the address of the 8 bytes
        const float* getPitch(); //gets the address of the 8 bytes
        const float* getRoll(); //gets the address of the 8 bytes
        const float* getXAccel(); //gets the address of the 8 bytes
        const float* getYAccel(); //gets the address of the 8 bytes
        const float* getZAccel(); //gets the address of the 8 bytes

    private:
        union{float f;  byte b[4];} yaw;
        union{float f;  byte b[4];} pitch;
        union{float f;  byte b[4];} roll;

        // Acceleration
        union{float f;  byte b[4];} a_x;
        union{float f;  byte b[4];} a_y;
        union{float f;  byte b[4];} a_z;

        byte in[100]; // array to save data send from the IMU

};








