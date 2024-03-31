long int inputData;
String transmittedString;
int prevInput=0;

#define START_DELIM     0x7E
#define FRAME_TYPE      0x10
#define FRAME_ID        0x01
#define DESTINATION_64  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF
#define DESTINATION_16  0xFF, 0xFE
#define BROADCAST_RAD   0x00
#define OPTIONS         0x00

char frame[] = {0x7E, 0x00, 0x10, 0x10, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFE, 0x00, 0x00, 0x48, 0x69, 0x42};



void setup() {
  // put your setup code here, to run once:

  Serial1.begin(115200);
  Serial1.write(frame,20);
  Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:

  Serial1.write(frame,20);
  Serial.write(frame);
  Serial.println();
  //Serial.println(hexTransmitString);
  //for(int i=0;i<hexTransmitString.length();i++)
  
 // Serial1.println(hexTransmitString);
  delay(100);

  

}



