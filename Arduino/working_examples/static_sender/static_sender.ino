void setup() 
{
  Serial.begin(115200);
  Serial1.begin(115200);

  int test = 5;
  Serial.println(test);

  char funTime[20] = {0x7E, 0x00, 0x10, 0x10, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFE, 0x00, 0x00, 0x48, 0x69, 0x42};
  Serial1.write(funTime, 20);
  Serial.write(funTime, 20);
  Serial.println();

}

void loop()
{
  if(Serial1.available()){
    byte InByte = Serial1.read();
    
    if(InByte = 0x7E)
    {
        //Serial.println();
    }
    Serial.print((char)InByte);
  }
}
