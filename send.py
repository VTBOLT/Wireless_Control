# Sending data to the Xbee to check if we are using the correct format

# Use this file in conjunction with the test file to complete the different cases
#hello 
import time
import math
import serial as ps
import constants
constants = constants.Constants # Check the constants as needed for testing
com='Com9'

transmittedString=input()
transmittedStringList=list(transmittedString)
asciiTransmittedStringList = []
for ele in transmittedStringList:
    asciiTransmittedStringList.extend(ord(num) for num in ele)

dataSum=0

for i in range(len(asciiTransmittedStringList)):
    dataSum=dataSum+asciiTransmittedStringList[i]

constantHexListInDec=[16,1,0,0,0,0,0,0,0,0,255,254,0,0]

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


finalTransmit=""
stringitr=0
while stringitr<=len(hexTransmitLengthString):
   hexTransmistSubstring=hexTransmitLengthString[stringitr+2:stringitr+4]
   hexSubstringList=list(hexTransmistSubstring)
   
   
   if hexSubstringList[len(hexSubstringList)-1]==" ":
      hexSubstringList[len(hexSubstringList)-1]=hexSubstringList[len(hexSubstringList)-2]
      hexSubstringList[len(hexSubstringList)-2]=0

      for t in range(len(hexSubstringList)):
       finalTransmit=finalTransmit+str(hexSubstringList[t])
      finalTransmit=finalTransmit+" "
      stringitr=stringitr+4
   else:
      finalTransmit=finalTransmit+hexTransmistSubstring+" "
      stringitr=stringitr+5



with ps.Serial(com, constants.baudrate,timeout=constants.timeout) as ser:
    while True:
       ser.write(bytearray.fromhex(finalTransmit))
ser.close()





    

    


# User settings
#com = 'COM4' # MUST BE DIFFERENT FROM THE RECIEVE FILE


# Object instatiation
#with ps.Serial(com, constants.baudrate, constants.timeout) as ser:
   # while True:
     #   x=ser.readline()
       # print(x)
       # print()