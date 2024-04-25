import eventlet
import socketio

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
    
    

