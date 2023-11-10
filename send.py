# Sending data to the Xbee to check if we are using the correct format

# Use this file in conjunction with the test file to complete the different cases
#hello 
import time
import math
import serial as ps
import constants
constants = constants.Constants # Check the constants as needed for testing
com='COM9'

transmittedString=input()
transmittedStringList=list(transmittedString)
asciiTransmittedStringList = []
for ele in transmittedStringList:
    asciiTransmittedStringList.extend(ord(num) for num in ele)

dataSum=0

for i in range(len(asciiTransmittedStringList)):
    dataSum=dataSum+asciiTransmittedStringList[i]

constantHexListInDec=[16,1,0,0,0,0,0,0,255,255,255,255,0,0]

constantDecSum=0
for i in range(len(constantHexListInDec)):
    constantDecSum=constantDecSum+constantHexListInDec[i]

hexTotalSumDec=dataSum+constantDecSum
last2HexDec=hexTotalSumDec%pow(16,2)


checkSumDec=255-last2HexDec
transmitLength=len(asciiTransmittedStringList)+len(constantHexListInDec)
hexTransmitLength=hex(transmitLength)
hexTransmitLengthString="0x7E"

if transmitLength<256:
  hexTransmitLengthString= hexTransmitLengthString+" 0x0 "+str(hexTransmitLength)
else:
   hexTransmitLengthString=hexTransmitLengthString+" "+str(hex(int(transmitLength/pow(16,2))))
   hexTransmitLengthString=hexTransmitLengthString+" "+str(hex(transmitLength%pow(16,2)))



for i in range(len(constantHexListInDec)):
   hexTransmitLengthString=hexTransmitLengthString+" "+str(hex(constantHexListInDec[i]))

for i in range(len(asciiTransmittedStringList)):
   hexTransmitLengthString=hexTransmitLengthString+" "+str(hex(asciiTransmittedStringList[i]))



hexTransmitLengthString=hexTransmitLengthString+" "+str(hex(checkSumDec))
print(hexTransmitLengthString)

hexTransmitLengthString=hexTransmitLengthString+" "
finalTransmit=""
stringitr=0
transmitStringLength=len(hexTransmitLengthString)

while stringitr<len(hexTransmitLengthString):
   hexTransmitSubstring=hexTransmitLengthString[stringitr+2:stringitr+4]
   hexSubstringList=list(hexTransmitSubstring)
   
   
   if hexSubstringList[len(hexSubstringList)-1]==" ":
      hexSubstringList[len(hexSubstringList)-1]=hexSubstringList[len(hexSubstringList)-2]
      hexSubstringList[len(hexSubstringList)-2]=0

      for t in range(len(hexSubstringList)):
       finalTransmit=finalTransmit+str(hexSubstringList[t])
      finalTransmit=finalTransmit+" "
      stringitr=stringitr+4
      transmitStringLength=transmitStringLength+1
   else:
      finalTransmit=finalTransmit+hexTransmitSubstring+" "
      stringitr=stringitr+5

finalTransmit=finalTransmit.upper()
finalTransmit=finalTransmit+"\n"
print(finalTransmit)
actualString= "7E 00 19 10 01 00 00 00 00 00 00 FF FF FF FF 00 00 48 65 6C 6C 6F 20 57 6F 72 6C 64 D6"

with ps.Serial(com, constants.baudrate,timeout=constants.timeout) as ser:
    while True:
       x=ser.write(bytes.fromhex(finalTransmit))#bytearray.fromhex(finalTransmit))
ser.close()





    

    


# User settings
#com = 'COM4' # MUST BE DIFFERENT FROM THE RECIEVE FILE


# Object instatiation
#with ps.Serial(com, constants.baudrate, constants.timeout) as ser:
   # while True:
     #   x=ser.readline()
       # print(x)
       # print()