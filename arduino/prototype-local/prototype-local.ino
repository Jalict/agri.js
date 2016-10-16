/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN takes care
  of use the correct LED pin whatever is the board used.
  If you want to know what pin the on-board LED is connected to on your Arduino model, check
  the Technical Specs of your board  at https://www.arduino.cc/en/Main/Products

  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald

  modified 2 Sep 2016
  by Arturo Guadalupi
*/


const int humiditySensorPinA = A0;    // Humidity Sensor A (Analog Signal Output)
const int manualEnablePin = 2;        // Manual Button for enable (all) pump(s)     
const int waterpumpA = 3;             // Waterpump Pin A
const bool manualOverride = false;    // State of manual override
const int humidityValueA = 0;         // The lateste humidity value A

void setup() {
  Serial.begin(9600);          //  setup serial
  
  pinMode(waterpumpA, OUTPUT);´
  pinMode(manualEnablePin, INPUT);
}



void loop() {
  manualOverride = digitalRead(manualEnablePin);
  humidityValueA = analogRead(humiditySensorPinA);

  if (manualOverride || humidityValueA > 400) {
    digitalWrite(waterpumpA, HIGH);
  } else {
    digitalWrite(waterpumpA, LOW);
  }

  delay(500);
  // read the input pin


  Serial.println(humidityValueA); 
}
