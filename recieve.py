import time
import math
import serial as ps
import constants
import codecs
import binascii
import string

# User settings
com = 'COM3'
constants = constants.Constants # Check the constants as needed for testing

# Reads the frame recieved by the Xbee
def recieveData(message):
    #with ps.Serial(com, constants.baudRate, constants.timeout) as ser:
        #rawFile = ser.readline()
        #dataList = message.split(" ")
        printable = set(string.printable)
        message = message.replace(' ','').lower()
        message = ''.join(filter(lambda x: x in printable, message))
        
        startDelim = message[:2]# dataList[0]
        # The last thing in here is the setup options. These are between the data and the start delim
        checkSum = message[-2:]
        data = message[34:len(message)-2]

        # PCAN Data 
        packCurrent         = data[:2]  # 0.1 A
        packVoltage         = data[2:4] # 0.1
        packStateOfCharge   = data[4]   # 0.5 %
        relayState          = data[5:7] # n/a
        packDCL             = data[:2]  # 1 A
        packCCL             = data[2:4] # 1 A
        internalTemp        = data[4:6] # 1 degC
        avgCellResistance   = data[4:5] # 0.01 mOhms

        # May not need this
        asciiConvert = bytes.fromhex(data).decode('ascii') # This won't be needed most likely
        asciiMsg = asciiConvert.replace(';', '\n')

        return asciiMsg

# Message is: "Velocity: 25m/s;Speed: 100m/s;Distance Traveled: 1000m;Battery Life: 67%" -> output should be: "Velocity: 25m/s
#                                                                                                              Speed: 100m/s
#                                                                                                              Distance Traveled: 1000m
#                                                                                                              Battery Life: 67%"
print(recieveData('7E 00 13 10 01 00 00 00 00 00 00 FF FF FF FF 00 00 56 65 6C 6F 63 69 74 79 3A 20 32 35 6D 2F 73 3B 53 70 65 65 64 3A 20 31 30 30 6D 2F 73 3B 44 69 73 74 61 6E 63 65 20 54 72 61 76 65 6C 65 64 3A 20 31 30 30 30 6D 3B 42 61 74 74 65 72 79 20 4C 69 66 65 3A 20 36 37 25 20 01'))