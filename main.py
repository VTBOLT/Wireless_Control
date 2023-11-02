import time
import math
import serial as ps

with ps.Serial('COM3', 115200, timeout=20) as ser:
    while True:
        x=ser.readline()
        print(x)
        print()