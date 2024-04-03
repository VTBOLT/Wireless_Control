#define START_DELIM     0x7E
#define LENGTH
#define FRAME_TYPE_AND_ID      0x10, 0x01
#define DESTINATION_ADDRESS_FULL 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 255, 255, 0xFF, 0xFE

#define BROADCAST_RAD   0x00
#define OPTIONS         0x00

#define BLANK_FRAME 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
#define INITIAL_CHECKSUM 0x0B

int dataIndex;
uint8_t data[] =         {0x48, 0x69, 0x48, 0x69, 0x48, 0x69, 0x48, 0x69, 0x48, 0x69, 0x48, 0x69, 0x48, 0x69, 0x48, 0x69, 0x48, 0x69, 0x48, 0x69};
uint8_t frame[] = {START_DELIM, 0x00, 0x22, FRAME_TYPE_AND_ID, DESTINATION_ADDRESS_FULL, BROADCAST_RAD, OPTIONS, BLANK_FRAME, INITIAL_CHECKSUM};
                            //^^^^^^^^^ these are the length
uint8_t doCheckSum(uint8_t checksum, uint8_t data[]);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial1.begin(115200);

  for(dataIndex = 0; dataIndex < 20; dataIndex++){
    frame[dataIndex + 17] = (data[dataIndex]);
    
  }
  frame[37] = doCheckSum(frame[37], *data);
  for (dataIndex = 0; dataIndex < 38; dataIndex++){
    Serial.print(frame[dataIndex], HEX);
  }
  Serial.println();

  Serial.println("Init Done");
  
  Serial1.write(frame, 38);

  //Serial.println((int)data);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  Serial1.write(frame, 38);
  delay(100);
}


uint8_t doCheckSum(uint8_t checksum, uint8_t data[]){

  for (int dataIndex = {}; dataIndex < 21; dataIndex++) {
	checksum += data[dataIndex];
}
  return (0xFF - checksum) & 0xFF;
  //(0xFF - checksum) & 0xFF
}

