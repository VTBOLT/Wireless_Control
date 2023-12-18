# Sending data to the Xbee to check if we are using the correct format

# Use this file in conjunction with the test file to complete the different cases
#hello 

#Import Variables
import time
import math
import serial as ps
import constants
constants = constants.Constants # Check the constants as needed for testing
com='COM9'

#Collect transmitted string from terminal
transmittedString=input()
#Turn string into a list for ease of iteration
transmittedStringList=list(transmittedString)

asciiTransmittedStringList = []
#asciiTransmittedStringList contains the ascii values of the characters in transmittedStringList 
# in decimal
for ele in transmittedStringList:
    asciiTransmittedStringList.extend(ord(num) for num in ele)

dataSum=0
#Sums all values in asciiTransmittedStringList for checksum
for i in range(len(asciiTransmittedStringList)):
    dataSum=dataSum+asciiTransmittedStringList[i]

#Since many values are constant, decided to create an array with them
#Will need to change this when we change adress 
constantHexListInDec=[16,1,0,0,0,0,0,0,255,255,255,255,0,0]

constantDecSum=0
#Sums everything in constantDecSum
for i in range(len(constantHexListInDec)):
    constantDecSum=constantDecSum+constantHexListInDec[i]

#Sums the two sums calculated from constantHexListInDec and asciiTransmittedStringList 
#Necessary for checkSum
hexTotalSumDec=dataSum+constantDecSum

#Gets the last two hex digits from hexTotalSum in decimal
#For example if the string is 1A2, last2HexDec will be 162(A2=16*10+2)
last2HexDec=hexTotalSumDec%pow(16,2)

#Calculates checkSumDec in decimal
checkSumDec=255-last2HexDec

#Calculates length of string combining asciiTransmittedStringList and constantHexListInDec
transmitLength=len(asciiTransmittedStringList)+len(constantHexListInDec)

#Calculates the length of the transmitLength in hex
hexTransmitLength=hex(transmitLength)

#Start the hexTransmitString with 0x7E because of the final string format
hexTransmitLengthString="0x7E"

#Checks if the total length of the string should be split into 1 or 2 bytes and does so
if transmitLength<256:
  hexTransmitLengthString= hexTransmitLengthString+" 0x0 "+str(hexTransmitLength)
else:
   hexTransmitLengthString=hexTransmitLengthString+" "+str(hex(int(transmitLength/pow(16,2))))
   hexTransmitLengthString=hexTransmitLengthString+" "+str(hex(transmitLength%pow(16,2)))


#Creates one long string combining the constant and written data in hex
for i in range(len(constantHexListInDec)):
   hexTransmitLengthString=hexTransmitLengthString+" "+str(hex(constantHexListInDec[i]))

for i in range(len(asciiTransmittedStringList)):
   hexTransmitLengthString=hexTransmitLengthString+" "+str(hex(asciiTransmittedStringList[i]))


#Adds check sum at the end of the hex string
hexTransmitLengthString=hexTransmitLengthString+" "+str(hex(checkSumDec))

#Adds a space as well for easier parsing later on
hexTransmitLengthString=hexTransmitLengthString+" "

#Creates string that will transmit final message
finalTransmit=""

#Creates an iterator that will parse through hex numbers as a whole
stringitr=0

#Needed to determine lenght of iteration
transmitStringLength=len(hexTransmitLengthString)

while stringitr<len(hexTransmitLengthString):

   #Create a substring of the last two characters in a hex
   hexTransmitSubstring=hexTransmitLengthString[stringitr+2:stringitr+4]
   hexSubstringList=list(hexTransmitSubstring)
   
   #If the last character is a space, that means hex is a single digit and a 0 must be added
   #before it
   if hexSubstringList[len(hexSubstringList)-1]==" ":
      hexSubstringList[len(hexSubstringList)-1]=hexSubstringList[len(hexSubstringList)-2]
      hexSubstringList[len(hexSubstringList)-2]=0
      
      #Add the newly formatted hex into the finalTransmitString
      for t in range(len(hexSubstringList)):
       finalTransmit=finalTransmit+str(hexSubstringList[t])
      
      #Updates variables accordingly
      finalTransmit=finalTransmit+" "
      stringitr=stringitr+4
      transmitStringLength=transmitStringLength+1
   else:
      #If the final digit is not a space, then it means that the hex is two digits and can
      #be added to the final string directly
      finalTransmit=finalTransmit+hexTransmitSubstring+" "
      stringitr=stringitr+5

#Uppercase all hex letters
finalTransmit=finalTransmit.upper()

#Add a space at end (Don't know if necessary, did for testing purposes)
finalTransmit=finalTransmit+"\n"


print(finalTransmit)

#Sends from PCB to another PCB
with ps.Serial(com, constants.baudrate,timeout=constants.timeout) as ser:
    while True:
       x=ser.write(bytes.fromhex(finalTransmit))
ser.close()

