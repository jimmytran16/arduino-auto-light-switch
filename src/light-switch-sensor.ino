#include <Servo.h>

// constants
const int lightPin = A0; // Analog pin for CdS Photoresistor (light sensor)
const int motionPin = 7; // Pin for input from PIR Sensor (motion sensor)
const int nightLight = 13; // Pin for output to light bulb
const int servoPin = 8; // Pin for the servo device

const int initialPosition = 90; // initial position for the servo
const int turnOnPosition = 85; // position of the servo to turn on the light
const int turnOffPosition = 95; // position of the servo to turn off the light

// status of light
bool isLightOn = false;
bool isLightOff = true;

// Servo instance
Servo servoMotorInstance;

void setup() {
  Serial.begin(9600);
  pinMode(nightLight, OUTPUT);
  pinMode(lightPin, INPUT);
  pinMode(motionPin, INPUT);
  
  //make sure the light is off
  digitalWrite(nightLight, LOW);
  // configure the Servo motor
  servoMotorInstance.attach(servoPin);
  // set the servo to be at 180 degrees
  servoMotorInstance.write(initialPosition);
}

void loop() {
  // get the reading of the motion detector
  int motionReading = digitalRead(motionPin);

  // condition to check if any motion was detected
  if (motionReading) {
    if (lightPin < 200) {
      digitalWrite(nightLight, HIGH);
      turnOnLight();
    }
  } else {
    digitalWrite(nightLight, LOW);
    turnOffLight();
  }
  // delay for 200 miliseconds
  delay(200);
}

// functions to turn on and off the lights
void turnOnLight() {
  if (!isLightOn) {
    rePositionServoMotor(turnOnPosition, true, false);
  }
}
void turnOffLight() {
  if (!isLightOff) {
    rePositionServoMotor(turnOffPosition, false, true);
  }
}

// function to reposition the servo motor
void rePositionServoMotor(int position, bool lightOn, bool lightOff) {
  servoMotorInstance.write(position);
  isLightOn = lightOn;
  isLightOff = lightOff;
  delay(500);
  servoMotorInstance.write(initialPosition);

  String message = (lightOn) ? "LIGHT TURNED ON!" : "LIGHT TURNED OFF!";
  Serial.println(message);
}