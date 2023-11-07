# Sending data to the Xbee to check if we are using the correct format

# Use this file in conjunction with the test file to complete the different cases
#hello 
import time
import math
import serial as ps
import constants
constants = constants.Constants # Check the constants as needed for testing

# User settings
com = 'COM4' # MUST BE DIFFERENT FROM THE RECIEVE FILE


# Object instatiation
with ps.Serial(com, constants.baudrate, constants.timeout) as ser:
    while True:
        x=ser.readline()
        print(x)
        print()