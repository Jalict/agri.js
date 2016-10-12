var JsonDB = require('node-json-db');
net = require('net');
//The second argument is used to tell the DB to save after each push
//If you put false, you'll have to call the save() method.
//The third argument is to ask JsonDB to save the database in an human readable format. (default false)

var clients = [];
var db = new JsonDB("farm", true, true);
db.push("/devices/connected", clients.length);

// Start a TCP Server
net.createServer(function (socket) {
  //TODO Find unique identifier for Sockets

  clients.push(socket);

  db.push("/devices/connected", clients.length);

  console.log("New device connected, active devices: " + clients.length);

  // Handle incoming messages from clients.
  socket.on('data', function (data) {
    var message = String(data);             // Convert data to string
    var index = -1;                         // Init index,
    var time =  Date.now();                 // When I received this message
    if(message.substring(0,5) == "index")   // Check if message contains index
      index = message.substring(5,6);       // Get index

    if(index === -1)
      return;         // if -1, then invalid index and discard message

    try {
      var name = db.getData("/plants[" + index + "]/name");
    } catch(error) {
      db.push("/plants[" + index + "]/name", "noname")
    }

    //TODO Make substringing more clever. Be able to detect cmds better
    if(message.substring(6,14) == "humidity") {
      var value = parseInt(message.substring(14, message.length - 2)); // Ends with \n MAYBE

      if(value > 1023) {
        console.log(value + " is too high humidity");
        return;
      } else if(value < 0) {
        console.log(value + " is too low humidity");
        return;
      } else if(value == "") {
        console.log("humidity value is empty");
        return;
      }

      db.push("/plants[" + index + "]/humidity[]", {
        "time": time,
        "value": value
      });
      console.log("Added humidity " + value + " for index " + index);
    } else if(message.substring(6,13) == "watered") {
      db.push("/plants[" + index + "]/watered[]", {"time": time});
      console.log("Added watered for index " + index);
    }
  });

  // Remove the client from the list when it leaves
  socket.on('end', function () {
    clients.splice(clients.indexOf(socket), 1);
    db.push("/devices/connected", clients.length);
    console.log("Device disconnected, active devices: " + clients.length);
  });

}).listen(5000);

console.log("Chat server running at port 5000\n");
