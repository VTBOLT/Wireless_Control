var map
const WS_URL = 'ws://localhost:5005/';
let reconnectTimeout;



function onload() {
    renderMap(37.143,-80.613);
}

function renderMap( lat, long) {
    map = L.map('map', {
        center: [lat, long],
        zoom: 19
    });

    L.tileLayer('https://tile.openstreetmap.org/{z}/{x}/{y}.png', {
        attribution: '&copy; <a href="https://www.openstreetmap.org/copyright">OpenStreetMap</a> contributors'
    }).addTo(map);
    markMap(37.143,-80.613)
}

function markMap(lat,long)
{
    options = {
                interactive: true,
                riseOnHover: true
              }
    L.marker([lat,long],options).addTo(map);
}


// Connect to the Socket.IO server
const socket = io('ws://localhost:5005'); 

// Event handler for successful connection
socket.on('connect', () => {
  var connectionStatus = document.getElementById("connectionStatus");
  connectionStatus.innerHTML= 'Connected!'
  console.log('Connected to server');
  socket.emit('sendCoord', {})
});

// Event handler for receiving coordinates from the server
socket.on('coordinates', (data) => {

  // Find a <table> element with id="myTable":
var table = document.getElementById("dataTable");

// Create an empty <tr> element and add it to the 1st position of the table:
var row = table.insertRow(1);

// Insert new cells (<td> elements) at the 1st and 2nd position of the "new" <tr> element:
var time = row.insertCell(0);
var aux_voltage = row.insertCell(1);
var aux_percent = row.insertCell(2);
var charge_state = row.insertCell(3);
var high_cell_temp = row.insertCell(4);
var low_cell_temp = row.insertCell(5);
var motor_temp = row.insertCell(6);
var bms_temp = row.insertCell(7);
var motor_speed = row.insertCell(8);
var bike_speed = row.insertCell(9);
var latitude = row.insertCell(10);
var longitude = row.insertCell(11);

// Add some text to the new cells:
time.innerHTML = data.time;
aux_voltage.innerHTML = data.aux_voltage;
aux_percent.innerHTML = data.aux_percent;
charge_state.innerHTML = data.charge_state;
high_cell_temp.innerHTML = data.high_cell_temp;
low_cell_temp.innerHTML = data.low_cell_temp;
motor_temp.innerHTML = data.motor_temp;
bms_temp.innerHTML = data.bms_temp;
motor_speed.innerHTML = data.motor_speed;
bike_speed.innerHTML = data.bike_speed;
latitude.innerHTML = data.latitude;
longitude.innerHTML = data.longitude;


  console.log('Received coordinates:', data);
  markMap(data.latitude,data.longitude);
  // Do something with the received coordinates
  socket.emit('sendCoord', {})
});

// Event handler for disconnection
socket.on('disconnect', () => {
  var connectionStatus = document.getElementById("connectionStatus");
  connectionStatus.innerHTML= 'Disconnected'
  console.log('Disconnected from server');
});