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
        checkSum = message[-2:]
        data = message[34:len(message)-2]

        asciiConvert = bytes.fromhex(data).decode('ascii')
        asciiMsg = asciiConvert.replace(';', '\n')

        return asciiMsg

# Message is: "hëllo world;test!" -> output should be: "hllo world
#                                                       test!"
print(recieveData('7E 00 13 10 01 00 00 00 00 00 00 FF FF FF FF 00 00 68 65 6C 6C 6F 20 77 6F 72 6C 64 3B 74 65 73 74 21 01'))