const int buttonPin = 2;
const int redLedPin = 10;
const int blueLedPin = 5;

int timer = 0;
int buttonState = 0;
int lastButtonState = 0;

int blinkTimes = 3;
int blinkDuration = 200;
int onAfterBlink = 1000;
int blinkEveryXPress = 5;

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(blueLedPin, OUTPUT);
  Serial.begin(9600); // initialize serial communication
}

void waitingState() {
  digitalWrite(redLedPin, LOW);
  digitalWrite(blueLedPin, HIGH);
}

bool randomGenerator() {
  return timer % blinkEveryXPress == 0;
}

void blinkRed() {
  for (int i = 0; i < blinkTimes; i++) {
    digitalWrite(redLedPin, HIGH);
    delay(blinkDuration);
    digitalWrite(redLedPin, LOW);
    delay(blinkDuration);
  }
  digitalWrite(redLedPin, HIGH);
  delay(onAfterBlink);
  digitalWrite(redLedPin, LOW);
}

void loop() {
  waitingState();
  buttonState = digitalRead(buttonPin);
  if (buttonState != lastButtonState && buttonState == HIGH && randomGenerator()) {
    digitalWrite(blueLedPin, LOW);
    blinkRed();
    digitalWrite(blueLedPin, HIGH);
    delay(50);
  }
  lastButtonState = buttonState;
  timer++;
}
