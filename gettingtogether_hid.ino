int gsr = A0;
int senseData[10]; //gsr sense data
int currS = 0;
int intensity = 0; //controls tightness of wrist strap and intensity of vibration
int receivedData = 0; // averaged data from base

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(gsr,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  addToArr(senseData, currS, (int)analogRead(gsr));
  int thisAvg = avg(senseData);
  Serial.println(thisAvg);
    
}

void serialEvent() {
  while (Serial.available()) {
    receivedData = (int)Serial.read();
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

