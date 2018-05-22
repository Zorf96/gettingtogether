#include <CapacitiveSensor.h>

CapacitiveSensor sensor = CapacitiveSensor(12, 13);
const int stepsPerRot = 200; //???
int senseData[10]; //cap wire sense data
int currS = 0;
int motorRevs = 0; //# of revolutions of stepper motor, 0 is fully extended
bool dir = true; //true is retract, false is extend
int receivedData = 0; //Avgeraged data from HID

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void moveMot(int x){ //rotates motor a certain number of revolutions
  
}

void loop() {
  // put your main code here, to run repeatedly:
  addToArr(senseData, currS, (int)sensor.capacitiveSensor(30));
  int thisAvg = avg(senseData);
  Serial.println(thisAvg);
    
}

void serialEvent() {
  while (Serial.available()) {
    receivedData = (int)Serial.read();
    Serial.println(receivedData);
  }
}


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

