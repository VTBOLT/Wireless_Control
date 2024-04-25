import eventlet
import socketio
import socketio.server

# Create a Socket.IO server
sio = socketio.Server(cors_allowed_origins='*')
app = socketio.WSGIApp(sio)



# Define the event handler for when a client connects
@sio.event
def connect(sid, environ):
    print('Client connected:')


@sio.event
def sendCoord(sid, data):
    lat = input("latitude: ")
    long = input("longitude: ")
    time = 0
    aux_voltage = 1
    aux_percent = 2
    charge_state = 3
    high_cell_temp = 4
    low_cell_temp = 5
    motor_temp = 6
    bms_temp = 7
    motor_speed = 9
    bike_speed = 10
    data = {'time': time,
            'aux_voltage': aux_voltage,
            'aux_percent': aux_percent,
            'charge_state': charge_state,
            'high_cell_temp': high_cell_temp,
            'low_cell_temp': low_cell_temp,
            'motor_temp': motor_temp,
            'bms_temp': bms_temp,
            'motor_speed': motor_speed,
            'bike_speed': bike_speed,
            'latitude': lat, 
            'longitude': long

            }
    sendData(data)


# Define the event handler for when a client disconnects
@sio.event
def disconnect(sid):
    print('Client disconnected:')

def sendData(data):
    try:        
        # Emit the latitude and longitude data to the Socket.IO clients
        sio.emit('coordinates', data)
    except websockets.exceptions.ConnectionClosedOK:
        print("Client disconnected")

if __name__ == '__main__':
    # Start the Socket.IO server
    eventlet.wsgi.server(eventlet.listen(('localhost', 5005)), app)
    
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


