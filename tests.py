import serial
ser = serial.Serial(port="COM4")
received_hex_data = ""
bytesToRead = 3
# Example usage
serial_port = "COM4"  # Replace with your actual serial port
while 1:
    inWaiting = ser.in_waiting
    if inWaiting >= bytesToRead:
        received_hex_data = ser.read(bytesToRead).hex()
    
    print( received_hex_data)