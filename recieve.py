from digi.xbee.devices import XBeeDevice


# TODO: Replace with the serial port where  your local module is connected to.
PORT = "COM5"
# TODO: Replace with the baud rate of your local module.
BAUD_RATE = 115200


def main():
    print(" +-----------------------------------------+")
    print(" | XBee Python Library Receive Data Sample |")
    print(" +-----------------------------------------+\n")
    
    
    device = XBeeDevice(PORT, BAUD_RATE)

    try:
        device.open()

        def data_receive_callback(xbee_message):
            incomingData = xbee_message.data
            print(incomingData)
            

        device.add_data_received_callback(data_receive_callback)
        
        
        print("Waiting for data...\n")
        input()

    finally:
        if device is not None and device.is_open():
            device.close()


if __name__ == '__main__':
    main()