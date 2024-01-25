import csv
import binascii

with open('xBeeData.csv', 'w', newline='') as csvfile:
    spamwriter = csv.writer(csvfile, delimiter=' ',
                            quotechar='|', quoting=csv.QUOTE_MINIMAL)
    spamwriter.writerow(bytearray([0x12, 0x29, 0xF7, 0x1B]).hex())
    