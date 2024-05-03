#include <EEPROM.h>

const int EEPROM_Address = 0; // Define the EEPROM address to store the variable

const int stepPin = 3; // define pin for step
const int dirPin = 4;  // define pin for direction

const int irSensorPin1 = 6; // IR sensor pin for floor 1
const int irSensorPin2 = 7; // IR sensor pin for floor 2
const int irSensorPin3 = 8; // IR sensor pin for floor 3

int currentFloor = 1;  // variable to track current floor
int stepsPerFloor = 1150; // adjust this value based on your motor to reach each floor


void setup() {
  pinMode(stepPin, OUTPUT); 
  pinMode(dirPin, OUTPUT);

  pinMode(irSensorPin1, INPUT); // Set IR sensor pins as input
  pinMode(irSensorPin2, INPUT);
  pinMode(irSensorPin3, INPUT);  

  
  EEPROM.get(EEPROM_Address, currentFloor); // Read the stored value from EEPROM
  if (currentFloor <= 0 || currentFloor > 3) {
    currentFloor = 1; // Set default floor to 1
    EEPROM.put(EEPROM_Address, currentFloor); // Store the default floor in EEPROM
  }
  
}

void goToFloor(int targetFloor) {
  if (targetFloor > currentFloor) {
    digitalWrite(dirPin, HIGH); // Set direction to go up
    int stepsToMove = (targetFloor - currentFloor) * stepsPerFloor;
    
    for (int i = 0; i < stepsToMove; i++) {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(2000);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(2000);
    }
    currentFloor = targetFloor;
    EEPROM.put(EEPROM_Address, currentFloor);
  } else if (targetFloor < currentFloor) {
    digitalWrite(dirPin, LOW); // Set direction to go down
    int stepsToMove = (currentFloor - targetFloor) * stepsPerFloor;
    
    for (int i = 0; i < stepsToMove; i++) {                   
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(2000);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(2000);
    }
    currentFloor = targetFloor;
    EEPROM.put(EEPROM_Address, currentFloor);
  }
}

void loop() {
  if (digitalRead(irSensorPin1) == LOW) {
    int targetFloor = 1; // Set target floor to 1
    goToFloor(targetFloor);
  }

  if (digitalRead(irSensorPin2) == LOW) {
    int targetFloor = 2; // Set target floor to 2
    goToFloor(targetFloor);
  }
  
  if (digitalRead(irSensorPin3) == LOW) {
    int targetFloor = 3; // Set target floor to 3
    goToFloor(targetFloor);
  }
}
