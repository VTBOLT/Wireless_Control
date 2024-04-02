#define START_DELIM     0x7E
#define LENGTH
#define FRAME_TYPE_AND_ID      0x10, 0x01
#define DESTINATION_ADDRESS_FULL 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFE

#define BROADCAST_RAD   0x00
#define OPTIONS         0x00

#define BLANK_FRAME 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
#define INITIAL_CHECKSUM 0x0B

int dataIndex;
char data[] =         {0x48, 0x69, 0x48, 0x69, 0x48, 0x69, 0x48, 0x69, 0x48, 0x69, 0x48, 0x69, 0x48, 0x69, 0x48, 0x69, 0x48, 0x69, 0x48, 0x69};
char frame[] = {START_DELIM, 0x00, 0x22, FRAME_TYPE_AND_ID, DESTINATION_ADDRESS_FULL, BROADCAST_RAD, OPTIONS, BLANK_FRAME, INITIAL_CHECKSUM};
                            //^^^^^^^^^ these are the length
char doCheckSum(char checksum, char data[]);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial1.begin(115200);

  for(dataIndex = 0; dataIndex < 20; dataIndex++){
    frame[dataIndex + 17] = data[dataIndex];
  }
  

  Serial.print("Init Done");
  Serial1.write(frame, 38);

  //Serial.println((int)data);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  Serial1.write(frame, 38);
  delay(100);
}


char doCheckSum(char checksum, char data[]){

  for (int dataIndex = {}; dataIndex < 20; dataIndex++) {
	checksum += data[dataIndex];
}
  return ((0xFF - checksum) & 0xFF);
}

