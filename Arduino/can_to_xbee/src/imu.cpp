#include <Inc/imu.h>

const unsigned char* IMU::getYaw(){
  return yaw.b;
}
const unsigned char* IMU::getPitch(){
  return pitch.b;
}
const unsigned char* IMU::getRoll(){
  return roll.b;
}
const unsigned char* IMU::getXAccel(){
  return a_x.b;
}
const unsigned char* IMU::getYAccel(){
  return a_y.b;
}
const unsigned char* IMU::getZAccel(){
  return a_z.b;
}

void IMU::check_sync_byte(){
  Serial2.readBytes(in, 4);
  if (in[0] == 0xFA && in[1] == 0x10 && in[2] == 0x42 && in[3] == 0x00)
  {
    imu_sync_detected = true;
    // Serial.print("sync ");
  }
}

// Read the IMU bytes
void IMU::read_imu_data(){
  Serial2.readBytes(in, 26);

  for (int i = 0; i < 4; i++){
    yaw.b[i] = in[0 + i];
    pitch.b[i] = in[4 + i];
    roll.b[i] = in[8 + i];
    a_x.b[i] = in[12 + i];
    a_y.b[i] = in[16 + i];
    a_z.b[i] = in[20 + i];
  }
}

unsigned short IMU::calculate_imu_crc(byte data[], unsigned int length){
  unsigned int i;
  unsigned short crc = 0;
  for(i=0; i<length; i++){
    crc = (byte)(crc >> 8) | (crc << 8);
    crc ^= data[i];
    crc ^= (byte)(crc & 0xff) >> 4;
    crc ^= crc << 12;
    crc ^= (crc & 0x00ff) << 5;
  }
  return crc;
}