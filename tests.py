import csv

data_test = bytearray([0xb6, 0x85, 0x1f])

with open('xBeeData.csv', 'w', newline='') as csvfile:
    fieldnames = ['Status', 'Pull Voltage', 'Speed']
    writer = csv.DictWriter(csvfile, fieldnames=fieldnames)

    
    writer.writeheader()
    writer.writerow({fieldnames[0]: hex(data_test[0]), fieldnames[1] : hex(data_test[1]), fieldnames[2] : hex(data_test[2])})
    writer.writerow({fieldnames[0]: hex(data_test[0]), fieldnames[1] : hex(data_test[1]), fieldnames[2] : hex(data_test[2])})
