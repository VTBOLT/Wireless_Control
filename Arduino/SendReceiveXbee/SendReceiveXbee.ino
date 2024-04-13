uint8_t inputData;
int prevInput=0;

#define START_DELIM     0x7E
#define FRAME_TYPE      0x10
#define FRAME_ID        0x01
#define DESTINATION_64  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF
#define DESTINATION_16  0xFF, 0xFE
#define BROADCAST_RAD   0x00
#define OPTIONS         0x00
#define FRAME_SIZE 64 // 29 for abcdefghijk
#define CONSTANT_SIZE 14
#define CAN_DATA_LENGTH FRAME_SIZE - (CONSTANT_SIZE + 4)  // DOES NOT include the ID
#define RECEIVE_DATA_LENGTH CAN_DATA_LENGTH + 1           // DOES include the ID

////////////////////////////////////////////////////////////////////////
// CAN setup
#include "AA_MCP2515.h"
const CANBitrate::Config CAN_BITRATE = CANBitrate::Config_8MHz_500kbps;
const uint8_t CAN_PIN_CS = 53;
const int8_t CAN_PIN_INT = 2;

CANConfig config(CAN_BITRATE, CAN_PIN_CS, CAN_PIN_INT);
CANController CAN(config);
////////////////////////////////////////////////////////////////////////


//void getDataByteSum (uint8_t can_id, uint8_t canDataArray[CAN_DATA_LENGTH]);

void setup() {
  // put your setup code here, to run once:
  Serial1.begin(115200);
  Serial.begin(115200);

  // Initialize and Verify CAN
  while(CAN.begin(CANController::Mode::Normal) != CANController::OK) {
    Serial.println("CAN begin FAIL - delaying for 1 second");
    delay(1000);
  }

  // If it is good, confirm and move on
  Serial.println("CAN begin OK");
}

void loop() {
  // read in one character from serial, increment elment
  uint8_t canDataArray[CAN_DATA_LENGTH] = {0x12, 0x01, 0xF1, 0xF3, 0x04, 0x05, 0xF6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  uint8_t can_id = 0x01;
  CANFrame frame;

  // if (CAN.read(frame) == CANController::IOResult::OK) {
  //  // frame.print("RX");
  //   frame.getData(canDataArray, CAN_DATA_LENGTH);
  //   can_id = frame.getId();
  // }
 
  // sum of the data bytes
  uint8_t datasum=0x01;
  for(int i=0;i<RECEIVE_DATA_LENGTH;i++) {
    datasum=datasum+canDataArray[i];
  }

  
  // bytes 3 to 16 (zero indexed, zero left)
  uint8_t constantHexListInDec[CONSTANT_SIZE]={16,1,0,0,0,0,0,0,255,255,255,254,0,0};
  
  // sum of the constant bytes
  uint8_t constantDecSum=0;  // To account for the ID
  for(int i=0;i<CONSTANT_SIZE;i++) {
    constantDecSum=constantDecSum+constantHexListInDec[i];
  }
  
  // sum of constant bytes and data bytes
  uint8_t hexTotalSumDec = datasum + constantDecSum;

  // final checksum calculation  
  uint8_t checksum = 0xFF - hexTotalSumDec;

  // build the frame to send
 uint8_t outputCharArray[FRAME_SIZE];
  outputCharArray[0]=0x7E;
  outputCharArray[1]=0x00;
  outputCharArray[2]=FRAME_SIZE - 4;

  // constant bytes
  for(int i=0;i<CONSTANT_SIZE;i++)
    outputCharArray[i+3]=constantHexListInDec[i];
 
  
  // id goes first
  outputCharArray[CONSTANT_SIZE+3] = can_id;

  // data bytes
  for(int i=0;i<CAN_DATA_LENGTH;i++)
    outputCharArray[i+CONSTANT_SIZE+4]=canDataArray[i];

  // checksum
  //checksum = 0x0C;   // For Debug only
  outputCharArray[FRAME_SIZE-1]=checksum;
  
  Serial1.write(outputCharArray,FRAME_SIZE);

  for(int i=0;i<FRAME_SIZE;i++)
  {
   Serial.print(outputCharArray[i],HEX);
   Serial.print(" ");
  }
  Serial.println();   

}