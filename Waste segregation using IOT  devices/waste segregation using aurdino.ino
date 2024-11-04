#include <Servo.h>

const int moistureSensorPin = 2;    // Digital pin for soil moisture sensor (D0)
const int ultrasonicTrigPin = 9;    // Trigger pin for ultrasonic sensor
const int ultrasonicEchoPin = 10;   // Echo pin for ultrasonic sensor
const int servoPin = 3;            // Pin to control the servo motor

Servo myServo;

void setup() {
  Serial.begin(9600);
  pinMode(moistureSensorPin, INPUT);
  pinMode(ultrasonicTrigPin, OUTPUT);
  pinMode(ultrasonicEchoPin, INPUT);
  pinMode(servoPin, OUTPUT);

  myServo.attach(servoPin);
}

void loop() {
  int moistureValue = digitalRead(moistureSensorPin);
  int distance = getUltrasonicDistance();

  Serial.print("Moisture: ");
  Serial.print(moistureValue);
  Serial.print(", Distance: ");
  Serial.println(distance);

  if (moistureValue == HIGH) { // Digital HIGH means dry soil
    // Dry waste - Turn left 90 degrees
    
    rotateServo(0); // Move servo to left position
    delay(2000);
    if(distance < 10){
      rotateServo(90); // Move servo to right position
      delay(2000);
    }      // Delay for stability
  }

  else{
    rotateServo(-270);
    delay(2000);
    rotateServo(0);
    delay(2000);
  }
}


int getUltrasonicDistance() {
  digitalWrite(ultrasonicTrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(ultrasonicTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(ultrasonicTrigPin, LOW);
  return pulseIn(ultrasonicEchoPin, HIGH) * 0.034 / 2;
}

void rotateServo(int angle) {
  myServo.write(90 + angle); // Adjust the base angle as needed
  delay(1000);               // Adjust this delay based on your servo speed
}
