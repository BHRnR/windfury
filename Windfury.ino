const int buttonPin = 2;
const int redLedPin = 10;
const int blueLedPin = 5;

int pseudoRandomNumber = 0;
int buttonState = 0;
int lastButtonState = 0;
int brightness = 0;

int proccEveryXPress = 1;
int wavyDuration = 7;
int blinkTimes = 3;

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(blueLedPin, OUTPUT);
  Serial.begin(9600);
}

void waitingState() {
  analogWrite(redLedPin, 0);
  analogWrite(blueLedPin, 255);
  if (brightness < 20) {
    while (brightness < 255) {
      dimmBrighter();
    }
  } else {
    dimmDarker();
  }
}

void dimmDarker () {
  analogWrite(blueLedPin, brightness);
  delay(wavyDuration);
  brightness--;
}

void dimmBrighter () {
  analogWrite(blueLedPin, brightness);
  delay(wavyDuration);
  brightness++;
}

bool proccChecker() {
  return pseudoRandomNumber % proccEveryXPress == 0;
}

void blinkRed() {
  brightness = 0;
  for (int i = 0; i < blinkTimes; i++) {
    while (brightness > 0) {
      analogWrite(redLedPin, brightness);
      brightness--;
      delay(1);
    }
    while (brightness < 255) {
      analogWrite(redLedPin, brightness);
      brightness++;
      delay(1);
    }
  }
  while (brightness > 0) {
    analogWrite(redLedPin, brightness);
    brightness--;
    delay(5);
  }
}

void loop() {
  waitingState();
  buttonState = digitalRead(buttonPin);
  if (buttonState != lastButtonState && buttonState == HIGH && proccChecker()) {
    analogWrite(blueLedPin, 0);
    blinkRed();
    delay(50);
  }
  lastButtonState = buttonState;
  pseudoRandomNumber++;
}
