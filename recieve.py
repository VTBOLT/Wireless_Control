from digi.xbee.devices import XBeeDevice


# TODO: Replace with the serial port where  your local module is connected to.
PORT = "COM11"
# TODO: Replace with the baud rate of your local module.
BAUD_RATE = 115200

def parseXBeeFrame(ByteArray): 
    if ByteArray[0] != 0x01:
        return -1

    data = {
            'aux_voltage': int.from_bytes(ByteArray[1], byteorder='little', signed=False),
            'aux_percent': int.from_bytes(ByteArray[2], byteorder='little', signed=False),
            'charge_state': int.from_bytes(ByteArray[3], byteorder='little', signed=False),
            'high_cell_temp': int.from_bytes(ByteArray[4:6], byteorder='little', signed=True),
            'low_cell_temp': int.from_bytes(ByteArray[6:8], byteorder='little', signed=True),
            'motor_temp': int.from_bytes(ByteArray[8:10], byteorder='little', signed=True),
            'bms_temp': int.from_bytes(ByteArray[10:12], byteorder='little', signed=False),
            'motor_speed': int.from_bytes(ByteArray[12:14], byteorder='little', signed=True),
            'bike_speed': int.from_bytes(ByteArray[14:16], byteorder='little', signed=True),
            'latitude': int.from_bytes(ByteArray[16:20], byteorder='little', signed=True), 
            'longitude': int.from_bytes(ByteArray[20:24], byteorder='little', signed=True),
            'time': int.from_bytes(ByteArray[24:32], byteorder='little', signed=False)
            }

    return data


def main(): 
    device = XBeeDevice(PORT, BAUD_RATE)

    try:
        device.open()

        def data_receive_callback(xbee_message):
            incomingData = xbee_message.data
            data = parseXBeeFrame(incomingData)
            if( data != -1):
                data.print()
            
            

        device.add_data_received_callback(data_receive_callback)
        
        
       
        input()

    finally:
        if device is not None and device.is_open():
            device.close()


if __name__ == '__main__':
    main()

