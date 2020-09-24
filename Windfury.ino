const int buttonPin = 2;
const int redLedPin = 10;
const int blueLedPin = 5;

int timer = 0;
int buttonState = 0;
int lastButtonState = 0;

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(blueLedPin, OUTPUT);
  Serial.begin(9600); // initialize serial communication
}

void loop() {
  digitalWrite(redLedPin, LOW); 
  digitalWrite(blueLedPin, HIGH);
  buttonState = digitalRead(buttonPin);
  if (buttonState != lastButtonState) {
    if (buttonState == HIGH) {
      if (timer % 5 == 0) {
        digitalWrite(blueLedPin, LOW);
        for (int i=0; i<3; i++) {
          digitalWrite(redLedPin, HIGH);
          delay(200);
          digitalWrite(redLedPin, LOW);
          delay(200);
        }
        digitalWrite(redLedPin, HIGH);
        delay(1000);
        digitalWrite(redLedPin, LOW);
        digitalWrite(blueLedPin, HIGH);
      }
    }
    delay(50);
  }
  lastButtonState = buttonState;
  timer++;
}
