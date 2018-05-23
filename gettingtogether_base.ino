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
  stepState != stepState;
  digitalWrite(stepPin,stepState);
}

void setStepperStates() {
  dir = receivedData;
  if(receivedData){
    targetSteps += 5000;
  }else{targetSteps -= 500;}
}



void serialEvent() {
  while (Serial.available()) {
    receivedData = (int)Serial.read();
    Serial.println(receivedData);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  addToArr(senseData, currS, (int)sensor.capacitiveSensor(30));
  int thisAvg = avg(senseData);
  Serial.println(thisAvg);

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

