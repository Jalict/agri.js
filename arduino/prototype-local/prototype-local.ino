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


int analogPin = 0;     // potentiometer wiper (middle terminal) connected to analog pin 3
const int buttonPin = 2;
const int outputPin = 3;
                       // outside leads to ground and +5V
int buttonState = 0; 
int val = 0;           // variable to store the value read



void setup()

{

  Serial.begin(9600);          //  setup serial
   pinMode(outputPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);

}



void loop()

{
  
  buttonState = digitalRead(buttonPin);
  val = analogRead(analogPin);
  
  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH || val > 400) {
    // turn LED on:
    digitalWrite(outputPin, HIGH);
  } else {
    // turn LED off:
    digitalWrite(outputPin, LOW);
  }
  
  delay(500);  
  // read the input pin


  Serial.println(val);             // debug value

}
