//////
const int gsr = A0;
const int string = 9;
const int vibes = 10;
const int stdDev  = 3;// base this off gsr data??
const int dataLength = 10;
//////


long senseData[10]; //gsr sense data
int currS = 0;//
int intensity = 0; //controls tightness of wrist strap and intensity of vibration
long receivedData = 0; // averaged data from base
long thisAvg = 0;

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
  long currentGsr = analogRead(gsr);
  addToArr(currentGsr);
  thisAvg = avg();
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

long avg () {
  long sum = 0;
  for (int i = 0; i < dataLength; i++) {
    sum += senseData[i];  
  }
  return sum / dataLength ;
}

void addToArr(long add) {
  senseData[currS] = add;
  currS ++;
  if (currS > dataLength-1) {
    currS = 0;
  }
}

