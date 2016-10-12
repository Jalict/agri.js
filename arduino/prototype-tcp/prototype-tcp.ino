// Base-code credit goes to https://www.arduino.cc/en/Tutorial/TelnetClient

#include <SPI.h>
#include <Ethernet.h>

// Networking
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(0,0,0,0);
EthernetClient client;

// I/O
const int humidityPins[]    = {0,1,2,3};    // (Analog In) Humidity Sensors Pins
const int waterpumps[]      = {3,4,5,6};    // (Digital Out) Water Pumps

void setup() {
    for(int i = 0; humidityPins.length;i++){
        pinMode(waterpumps[i], OUTPUT);
    }

    // start the Ethernet connection:
    Ethernet.begin(mac, ip);
    // Open serial communications and wait for port to open:
    Serial.begin(9600);
    while (!Serial) {
      ; // wait for serial port to connect. Needed for native USB port only
    }

    // give the Ethernet shield a second to initialize:
    delay(1000);
    Serial.println("connecting...");

    // if you get a connection, report back via serial:
    if (client.connect(server, 10002)) {
      Serial.println("connected");
    } else {
      // if you didn't get a connection to the server:
      Serial.println("connection failed");
    }
}

void loop() {
    //TODO Make sure humidity is only checked every x min
    int humidityValues[humidityPins.length];
    bool watering[waterpumps.length];

    // Check for humidity levels and if plants should be watered
    for(int i = 0; i < humidityValues.length;i++) {
        humidityValues[i] = analogRead(humidityPins[i]);
        if(humidityValues[i] > 400)
            watering[i] = true;
        else
            watering[i] = false;
    }

    // Send log off to TCP client
    if (client.available()) {
        for(int i = 0; i < humidityValues.length;i++) {
            client.println("index"+i+"humidity"+humidityValues[i]);
            if(watering[i])
                client.println("index"+i+"watering");
        }

        //TODO This can be done in single loop but it should be fine
        for(int i = 0; i < watering.length;i++){
            if(watering[i])
                digitalWrite(waterpumps[i], HIGH);
        }
        sleep(1000);
        for(int i = 0; i < watering.length;i++){
                digitalWrite(waterpumps[i], LOW);
        }
    }
}
