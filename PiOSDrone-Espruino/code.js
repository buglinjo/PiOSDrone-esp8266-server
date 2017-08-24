var wifi = require("Wifi");
require("ESP8266").setCPUFreq(160);

wifi.disconnect();
wifi.startAP("PiOSDrone", {password:"piosdrone"});

wifi.on('sta_joined', function(device) { 
  setTimeout(function() {
    console.log(device.mac);
    wifi.getAPDetails(function(details) {
      console.log(details.stations);
    });
  }, 1000);
});

var server = require('ws').createServer();
server.listen(81);
server.on("websocket", function(ws) {
    ws.on('open', function() {
      console.log("Connected to server");
    });

    ws.on('message', function(msg) {
      console.log(msg);
    });

    ws.on('close', function() {
      console.log("Connection closed");
    });
});

