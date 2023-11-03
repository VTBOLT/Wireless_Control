import time
import math
import serial as ps
import constants
constants = constants.Constants # Check the constants as needed for testing

# User settings
com = 'COM3'


# Object instatiation
with ps.Serial(com, constants.baudRate, constants.timeout) as ser:
    while True:
        x=ser.readline()
        print(x)
        print()