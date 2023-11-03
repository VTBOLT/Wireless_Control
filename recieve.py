import time
import math
import serial as ps

# User settings
com = 'COM3'
baudRate = 115200
timeout = 20

# Object instatiation
with ps.Serial(com, baudRate, timeout) as ser:
    while True:
        x=ser.readline()
        print(x)
        print()