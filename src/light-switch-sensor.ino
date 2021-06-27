#include <Servo.h>

int lightPin = A0;   // Analog pin for CdS Photoresistor (light sensor)
int motionPin = 7;  // Pin for input from PIR Sensor (motion sensor)
int nightLight = 13;    // Pin for output to light bulb

// status of light
bool LIGHT_ON = false;
bool LIGHT_OFF = true;

const int INITIAL_POS = 0;
const int TURN_ON_POS = ;
const int TURN_OFF_POS = 30;

const int servoPin = 8;

int pos = 0;

Servo SERVO_MOTOR;

void setup() {
  Serial.begin(9600);
  
  pinMode(nightLight, OUTPUT);
  pinMode(lightPin, INPUT);
  pinMode(motionPin, INPUT);
  
  //make sure the light is off
  digitalWrite(nightLight, LOW); 
	
  // configure the Servo motor
  SERVO_MOTOR.attach(servoPin, 500, 2500);
  // set the servo to be at 180 degrees
  SERVO_MOTOR.write(INITIAL_POS);
}
   
void loop() {
  	// get the reading of the motion detector
  	int motionReading = digitalRead(motionPin); 
  	
	// condition to check if any motion was detected
  	if (motionReading) {
      if (lightPin < 200) { 
        digitalWrite(nightLight,HIGH);
        turn_on_the_light();
      }
    }else {
    	digitalWrite(nightLight,LOW);
      	turn_off_the_light();
    }
  	// delay for 200 miliseconds
	delay(200);
 }

// functions to turn on and off the lights
void turn_on_the_light(){
  if (!LIGHT_ON) {
    LIGHT_ON = true;
    LIGHT_OFF = false;
    SERVO_MOTOR.write(TURN_ON_POS);
    delay(500);
    SERVO_MOTOR.write(INITIAL_POS);
	Serial.println("LIGHT TURNED ON!");
  }
}
void turn_off_the_light(){
  if (!LIGHT_OFF){
    LIGHT_OFF = true;
    LIGHT_ON = false;
    SERVO_MOTOR.write(TURN_OFF_POS);
    delay(500);
    SERVO_MOTOR.write(INITIAL_POS);
  	Serial.println("LIGHT TURNED OFF!");
  }
}


