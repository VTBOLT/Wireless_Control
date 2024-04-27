/**
 * @file can.cpp
 *
 * @brief Functions for reading CAN messages
 *
 * @author Colton Tshudy, Aaron Kanefsky
 *
 * @date 4/13/2024
 */

#include <Inc/can.h>
#include <Inc/imu.h>

void checkCan(MessageData1 *messageData, MCP_CAN canObj)
{
    if (!digitalRead(CAN0_INT)) // If CAN0_INT pin is low, read receive buffer
    {
        long unsigned int rxId;
        unsigned char len;
        unsigned char rxBuf[8];
        canObj.readMsgBuf(&rxId, &len, rxBuf);
        switch (rxId)
        {
        case AUX_BATTERY:
            messageData->aux_voltage = rxBuf[1] << 8;
            messageData->aux_voltage += rxBuf[0];
            // messageData->aux_percent = rxBuf[1];
            break;
        case MAIN_BATTERY:
            messageData->pack_state_of_charge = rxBuf[4];
            break;
        case MAIN_PACK_TEMP:
            messageData->high_cell_temp = rxBuf[1] << 8;
            messageData->high_cell_temp += rxBuf[0];
            messageData->low_cell_temp = rxBuf[3] << 8;
            messageData->low_cell_temp += rxBuf[2];
            break;
        case MOTOR_TEMP:
            messageData->motor_temperature = rxBuf[5] << 8;
            messageData->motor_temperature += rxBuf[4];
            break;
        case BMS_TEMP:
            messageData->bms_temperature = rxBuf[5] << 8;
            messageData->bms_temperature += rxBuf[4];
            break;
        case MC_TEMP:
            messageData->mc_temp = rxBuf[1] << 8;
            messageData->mc_temp += rxBuf[0];
            break;
        case RPM:
            messageData->motor_speed = rxBuf[3] << 8;
            messageData->motor_speed += rxBuf[2];
            break;
        case SPEED:
            messageData->bike_speed = rxBuf[1] << 8;
            messageData->bike_speed += rxBuf[0];
            break;
        default:
            break;
        }
    }
}

void printCANFrame(MessageData1 *inputData)
{
    // for(size_t i = 0; i < sizeof(MessageData1); i++){
    //  Serial.print(inputData->aux_voltage, HEX);
    //  Serial.print(" ");
    //  Serial.print(inputData->aux_percent, HEX);
    //  Serial.print(" ");
    //  Serial.print(inputData->pack_state_of_charge, HEX);
    //  Serial.print(" ");
    //  Serial.print(inputData->high_cell_temp, HEX);
    //  Serial.print(" ");
    //  Serial.print(inputData->low_cell_temp, HEX);
    //  Serial.print(" ");
    //  Serial.print(inputData->motor_temperature, HEX);
    //  Serial.print(" ");
    // Serial.print(inputData->bms_temperature, HEX);
    // Serial.print(" ");
    // Serial.print(inputData->mc_temp, HEX);
    // Serial.print(" ");
    Serial.println(inputData->motor_speed, HEX);
    // Serial.print(" ");
    //}
}

void sendIMUMessage(IMU imuData, MCP_CAN canObj) {
    byte msg_status[3];
    byte IMU_1[8]; //for concatinating data
    byte IMU_2[8];
    byte IMU_3[8];

    memcpy(&IMU_1[0], imuData.getYaw(), 4);
    memcpy(&IMU_1[4], imuData.getPitch(), 4);

    memcpy(&IMU_2[0], imuData.getRoll(), 4);
    memcpy(&IMU_2[4], imuData.getXAccel(), 4);

    memcpy(&IMU_3[0], imuData.getYAccel(), 4);
    memcpy(&IMU_3[4], imuData.getZAccel(), 4);

    msg_status[0] = canObj.sendMsgBuf(IMU2CAN_1, 0, DLC, IMU_1);
    msg_status[1] = canObj.sendMsgBuf(IMU2CAN_2, 0, DLC, IMU_2);
    msg_status[2] = canObj.sendMsgBuf(IMU2CAN_3, 0, DLC, IMU_3);
}
