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
#define FRAME_SIZE 64
#define FRAME_LENGTH FRAME_SIZE-6
#define CONSTANT_SIZE 12



char frame[] = {0x7E, 0x00, 0x10, 0x10, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFE, 0x00, 0x00, 0x48, 0x69, 0x42};


void setup() {
  // put your setup code here, to run once:
  Serial1.begin(115200);
  //Serial1.write(frame,20);
  Serial.begin(115200);

   
 

}

void loop() {
  // put your main code here, to run repeatedly:
 char transmittedStringArray[FRAME_LENGTH];
  if(Serial.available())
  {
  inputData=Serial.read();
  if(inputData!=10)
  transmittedStringArray[element]=inputData;
  element++;
  }
 

  int datasum=0;
  for(int i=0;i<FRAME_LENGTH;i++)
  datasum=datasum+transmittedStringArray[i];

  
  
  uint8_t constantHexListInDec[CONSTANT_SIZE]={16,1,0,0,0,0,0x10,0x00,0xFF,254,0,0};
  
  int constantDecSum=0;
  for(int i=0;i<CONSTANT_SIZE;i++)
  constantDecSum=constantDecSum+constantHexListInDec[i];

  int hexTotalSumDec=datasum+constantDecSum;
  int last2HexDec=hexTotalSumDec%(int)pow(16,2);
  
  int checksum=255-last2HexDec;

 char outputCharArray[FRAME_SIZE];
  outputCharArray[0]=0x7E;
  outputCharArray[1]=0x00;
  outputCharArray[2]=FRAME_LENGTH;

  for(int i=0;i<CONSTANT_SIZE;i++)
  outputCharArray[i+3]=constantHexListInDec[i];


  for(int i=0;i<FRAME_LENGTH;i++)
  outputCharArray[i+CONSTANT_SIZE]=transmittedStringArray[i];

  outputCharArray[FRAME_SIZE-1]=checksum;
  
  
  
  Serial1.write(outputCharArray,20);
  Serial.write(outputCharArray);


  for(int i=0;i<FRAME_SIZE;i++)
  {
   Serial.print(outputCharArray[i],HEX);
   Serial.print(" ");
  }
  Serial.println();
  //Serial.println(hexTransmitString);
  //for(int i=0;i<hexTransmitString.length();i++)
  
 // Serial1.println(hexTransmitString);
  delay(100);

   

}
