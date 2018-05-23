//////
const int gsr = A0;
const int string = 9;
const int vibes = 10;
const int stdDev  = 3;// base this off gsr data??
//////


int senseData[10]; //gsr sense data
int currS = 0;//
int intensity = 0; //controls tightness of wrist strap and intensity of vibration
int receivedData = 0; // averaged data from base

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(gsr, INPUT);
  pinMode(string, OUTPUT);
  pinMode(vibes, OUTPUT);
}

void act(int intens) { //pulls the string, vibs the vibes
  analogWrite(string, intens);
  analogWrite(vibes, intens);
}



void serialEvent() {
  while (Serial.available()) {
    receivedData = (int)Serial.read();
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  recToIntens(receivedData, intensity);
  act(intensity);
  int currentGsr = (int)analogRead(gsr);
  addToArr(senseData, currS, currentGsr);
  int thisAvg = avg(senseData);
  if (currentGsr > thisAvg + stdDev || currentGsr < thisAvg - stdDev) {
    Serial.println(1);
  } else {
    Serial.println(0);
  }
}


//invisible funcs
int recToIntens(int x, int y) { //Adjust this as needed to accomidate capacitance
  y = map(x, 0, 9999, 0, 1024);
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

