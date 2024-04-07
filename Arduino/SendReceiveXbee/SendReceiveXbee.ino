uint8_t inputData;
int prevInput=0;
int element=0;

#define START_DELIM     0x7E
#define FRAME_TYPE      0x10
#define FRAME_ID        0x01
#define DESTINATION_64  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF
#define DESTINATION_16  0xFF, 0xFE
#define BROADCAST_RAD   0x00
#define OPTIONS         0x00
#define FRAME_SIZE 27 // 29 for abcdefghijk
#define FRAME_LENGTH FRAME_SIZE-4
#define CONSTANT_SIZE 14



//char frame[] = {0x7E, 0x00, 0x10, 0x10, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFE, 0x00, 0x00, 0x48, 0x69, 0x42};


void setup() {
  // put your setup code here, to run once:
  Serial1.begin(115200);
  //Serial1.write(frame,20);
  Serial.begin(115200);

   
 

}

void loop() {
  // put your main code here, to run repeatedly:
 uint8_t transmittedStringArray[FRAME_LENGTH];
  // read in one character from serial, increment elment
  while(Serial.available())
  {
  inputData=Serial.read();
  transmittedStringArray[element]=inputData;
  element++;
  }
 
  // sum of the data bytes
  uint8_t datasum=0;
  for(int i=0;i<element;i++) {
    datasum=datasum+transmittedStringArray[i];
  }

  
  // bytes 3 to 16 (zero indexed, zero left)
  uint8_t constantHexListInDec[CONSTANT_SIZE]={16,1,0,0,0,0,0,0,255,255,255,254,0,0};
  
  // sum of the constant bytes
  uint8_t constantDecSum=0;
  for(int i=0;i<CONSTANT_SIZE;i++) {
    constantDecSum=constantDecSum+constantHexListInDec[i];
  }
  
  // sum of constant bytes and data bytes
  uint8_t hexTotalSumDec = datasum + constantDecSum;

  // final checksum calculation  
  uint8_t checksum = 255 - hexTotalSumDec;

  // build the frame to send
 uint8_t outputCharArray[FRAME_SIZE];
  outputCharArray[0]=0x7E;
  outputCharArray[1]=0x00;
  outputCharArray[2]=FRAME_LENGTH;

  // constant bytes
  for(int i=0;i<CONSTANT_SIZE;i++)
    outputCharArray[i+3]=constantHexListInDec[i];
 
  // data bytes
  for(int i=0;i<element;i++)
    outputCharArray[i+CONSTANT_SIZE+3]=transmittedStringArray[i];

  // checksum
  outputCharArray[FRAME_SIZE-1]=checksum;
  
  Serial1.write(outputCharArray,FRAME_SIZE);

  for(int i=0;i<FRAME_SIZE;i++)
  {
   Serial.print(outputCharArray[i],HEX);
   Serial.print(" ");
  }
  Serial.println();

  delay(100);

   

}