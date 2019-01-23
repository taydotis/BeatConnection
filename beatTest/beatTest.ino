#define BCOLUMN1 10
#define BCOLUMN2 11
#define BCOLUMN3 12
#define BCOLUMN4 13

#define BROW1 9 
#define BROW2 8 
#define BROW3 7 
#define BROW4 6 

#define LROW1 5
#define LROW2 4
#define LROW3 3
#define LROW4 2

bool buttonState[16] = { false };
bool ledState[16] = { false };
int columnNumber = 0;
int columnPin[4] = { BCOLUMN1, BCOLUMN2, BCOLUMN3, BCOLUMN4 };
int ledRowPin[4] = { LROW1, LROW2, LROW3, LROW4 };
int buttonRowPin[4] = {BROW1, BROW2, BROW3, BROW4 };


void setup()
{
  pinMode(BROW1,INPUT_PULLUP);
  pinMode(BROW2,INPUT_PULLUP);
  pinMode(BROW3,INPUT_PULLUP);
  pinMode(BROW4,INPUT_PULLUP);

  pinMode(BCOLUMN1, OUTPUT);
  pinMode(BCOLUMN2, OUTPUT);
  pinMode(BCOLUMN3, OUTPUT);
  pinMode(BCOLUMN4, OUTPUT);

  Serial.begin(9600);

  digitalWrite(BCOLUMN1, LOW);
  digitalWrite(BCOLUMN2, LOW);
  digitalWrite(BCOLUMN3, LOW);
  digitalWrite(BCOLUMN4, LOW);

  pinMode(LROW1, OUTPUT);
  pinMode(LROW2, OUTPUT);
  pinMode(LROW3, OUTPUT);
  pinMode(LROW4, OUTPUT);
}

void loop()
{
  delay(1);
  driverCycle();
  for(int i = 0; i < 16; i++){
    ledState[i] = !buttonState[i];
  }
  
}


void driverCycle(){
  // turn off current column
  digitalWrite(columnPin[columnNumber], LOW);
  // increment present column
  columnNumber = (columnNumber + 1) % 4;
  // turn on and off row LEDs
  digitalWrite(ledRowPin[0], !ledState[(columnNumber*4)+0]); 
  digitalWrite(ledRowPin[1], !ledState[(columnNumber*4)+1]);
  digitalWrite(ledRowPin[2], !ledState[(columnNumber*4)+2]);
  digitalWrite(ledRowPin[3], !ledState[(columnNumber*4)+3]);
  // turn on current column
  digitalWrite(columnPin[columnNumber], HIGH);
  // read button states
  buttonState[(columnNumber*4)+0] = digitalRead(buttonRowPin[0]);
  buttonState[(columnNumber*4)+1] = digitalRead(buttonRowPin[1]);
  buttonState[(columnNumber*4)+2] = digitalRead(buttonRowPin[2]);
  buttonState[(columnNumber*4)+3] = digitalRead(buttonRowPin[3]);
}

