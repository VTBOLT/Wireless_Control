from digi.xbee.devices import XBeeDevice
import digi.xbee.util.utils

# TODO: Replace with the serial port where your local module is connected to.
PORT = "COM3"
# TODO: Replace with the baud rate of your local module.
BAUD_RATE = 115200

DATA_TO_SEND = [0x12, 0x29, 0xF7, 0x1B]
REMOTE_NODE_ID = "VTBOLT"  # Any changes to this MUST be done in XCTU as well. Or at least send an AT command


def main():
    device = XBeeDevice(PORT, BAUD_RATE)

    DATA_TO_SEND = digi.xbee.util.utils.hex_to_string(bytearray([0x12, 0x29, 0xF7, 0x1B]))

    NUM_TO_SEND = 5
    while NUM_TO_SEND > 0:
      try:
         device.open()

         # Obtain the remote XBee device from the XBee network.
         xbee_network = device.get_network()
         remote_device = xbee_network.discover_device(REMOTE_NODE_ID)
         if remote_device is None:
               print("Could not find the remote device")
               exit(1)

         print("Sending data asynchronously to %s >> %s..." % (remote_device.get_64bit_addr(), DATA_TO_SEND))
         
         device.send_data_async(remote_device, DATA_TO_SEND)
                  

         print("Success")

      finally:
         if device is not None and device.is_open():
               device.close()
      NUM_TO_SEND -= 1


if __name__ == '__main__':
    main()