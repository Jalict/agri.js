var JsonDB = require('node-json-db');

var db = new JsonDB("farm", true, true);
var min = 200;
var max = 500;
var elementsLength = 100;
var time = Date.now();
var interval = 30; // Minutes

for(var i = 0; i < elementsLength;i++)
{
    db.push("/plants[0]/humidity[]", {
        "time": time + (i * (30 * 60 * 1000)),
        "value": parseInt(Math.random() * (max - min) + min)
    });
}

console.log("done");
