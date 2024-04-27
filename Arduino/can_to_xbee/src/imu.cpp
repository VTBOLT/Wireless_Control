#include <Inc/imu.h>

void check_sync_byte(void)
{

  Serial2.readBytes(in, 4);
  if (in[0] == 0xFA && in[1] == 0x10 && in[2] == 0x42 && in[3] == 0x00)
  {
    imu_sync_detected = true;
    // Serial.print("sync ");
  }
}

// Read the IMU bytes
void read_imu_data(IMU_Data data)
{
  Serial2.readBytes(in, 26);

  for (int i = 0; i < 4; i++)
  {
    data.yaw.b[i] = in[0 + i];
    data.pitch.b[i] = in[4 + i];
    data.roll.b[i] = in[8 + i];
    data.a_x.b[i] = in[12 + i];
    data.a_y.b[i] = in[16 + i];
    data.a_z.b[i] = in[20 + i];
  }
}