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

char frame[] = {0x7E, 0x00, 0x10, 0x10, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFE, 0x00, 0x00, 0x48, 0x69, 0x40};


void setup() {
  // put your setup code here, to run once:
  Serial1.begin(115200);
  Serial1.write(frame,20);
  Serial.begin(115200);

   
 

}

void loop() {
  // put your main code here, to run repeatedly:
 
  if(Serial.available())
  {
  inputData=Serial.read();
  if(inputData!=10)
  transmittedString=transmittedString+(char)inputData;
  }
 

  int datasum=0;
  for(int i=0;i<transmittedString.length();i++)
  datasum=datasum+transmittedString.charAt(i);

  
  
  int constantHexListInDec[14]={16,1,0,0,0,0,0,0,0,0,255,254,0,0};
  
  int constantDecSum=0;
  for(int i=0;i<sizeof(constantHexListInDec)/sizeof(constantHexListInDec[0]);i++)
  constantDecSum=constantDecSum+constantHexListInDec[i];

  int hexTotalSumDec=datasum+constantDecSum;
  int last2HexDec=hexTotalSumDec%(int)pow(16,2);
  
  int checksum=255-last2HexDec;

  int transmitLength=transmittedString.length()+sizeof(constantHexListInDec)/sizeof(constantHexListInDec[0]);
  String hextransmitLength=String(transmitLength,HEX);
  String hexTransmitString="0x7E";
  int iteratorHexTransLengthVar=transmitLength;

  
  if(transmitLength<256)
   hexTransmitString=hexTransmitString+" 0x00"+" 0x"+hextransmitLength;
   else
   hexTransmitString=hexTransmitString+" 0x"+String(transmitLength/(int)pow(16,2),HEX);+" 0x"+String(transmitLength%(int)pow(16,2),HEX);

   for(int i=0;i<sizeof(constantHexListInDec)/sizeof(constantHexListInDec[0]);i++)
    if(constantHexListInDec[i]<16)
     hexTransmitString=hexTransmitString+" 0x0"+String(constantHexListInDec[i],HEX);
     else
     hexTransmitString=hexTransmitString+" 0x"+String(constantHexListInDec[i],HEX);
     
   for(int i=0;i<transmittedString.length();i++)
   if(transmittedString.charAt(i)<16)
      hexTransmitString=hexTransmitString+" 0x0"+String(transmittedString.charAt(i),HEX);
   else
      hexTransmitString=hexTransmitString+" 0x"+String(transmittedString.charAt(i),HEX);
      
    
    if(checksum<16)
    hexTransmitString=hexTransmitString+" 0x0"+String(checksum,HEX);
    else
    hexTransmitString=hexTransmitString+" 0x"+String(checksum,HEX);
    

   
  Serial1.write(frame,20);
  Serial.write(frame,20);
  Serial.println();
  //Serial.println(hexTransmitString);
  //for(int i=0;i<hexTransmitString.length();i++)
  
 // Serial1.println(hexTransmitString);
  delay(100);

   

}



