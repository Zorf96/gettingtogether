#include <CapacitiveSensor.h>

CapacitiveSensor sensor = CapacitiveSensor(12, 13);
const int stepPin = 4;
const int dirPin = 5;

//////
const long maxSteps = 10000; //???
//////

long motorSteps = 0; //current # of revolutions of stepper motor, 0 is fully extended
long targetSteps = 0;
bool stepState = false;
bool dir = true; //true is retract, false is extend
bool receivedData = false; //current data from HID, same states as dir
int test = 0;

//don't mind these
int senseData[10]; //cap wire sense data
int currS = 0; //indexing var for senseData



//Code:



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
}

void moveMot() { //rotates motor to target ///
  if (motorSteps > maxSteps || motorSteps < 0) { //sets targetSteps within the bounds
    if (motorSteps > maxSteps) {
      targetSteps = maxSteps;
    } else {
      targetSteps = 0;
    }
  }
  if (targetSteps != motorSteps) {
    if (targetSteps > motorSteps) {
      dir = true;
      motorSteps++;
    }
    else {
      dir = false;
      motorSteps--;
    }

    stepState = !stepState;
    digitalWrite(stepPin, stepState);
    delay(1);
  }
}

void setStepperStates() {
  if (receivedData) {
    targetSteps += 2000;
  } else {
    targetSteps -= 10;
  }
  digitalWrite(dirPin,dir);
}



void serialEvent() {
  while (Serial.available()) {
    test = Serial.readString().toInt();
    Serial.println(receivedData);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  //addToArr(senseData, currS, (int)sensor.capacitiveSensor(30));
  //int thisAvg = avg(senseData);
  //Serial.println(thisAvg);
  setStepperStates();
  targetSteps = test;
  Serial.print(motorSteps);
  Serial.print('\t');
  Serial.println(targetSteps);
  for (int i = 0; i < 50; i++) {
    moveMot();
  }
}







//invisible funcs
int avg (int x[10]) {
  int sum = 0;
  for (int i = 0; i++; i < 10) {
    sum += x[i];
  }
  return sum / 10;
}

void addToArr(int x[], int curr, int add) {
  x [curr] = add;
  curr ++;
  if (curr > 10) {
    curr = 0;
  }
}

