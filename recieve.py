import time
import math
import serial as ps
import constants
import codecs
import binascii
import string
constants = constants.Constants # Check the constants as needed for testing

# User settings
com = 'COM3'


# Reads the frame recieved by the Xbee
with ps.Serial(com, constants.baudRate, constants.timeout) as ser:
    run = True
    while run:
        rawFile = ser.readline()
        
        printable = set(string.printable)
        ''.join(filter(lambda x: x in printable, rawfile))

        asciiConvert = bytes.fromhex(rawFile).decode("ASCII")
        trimmedMsg = asciiConvert.replace(';', '\n- ')
        print(timmedMsg)
        run = False