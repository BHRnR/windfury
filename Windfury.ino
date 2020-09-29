const int buttonPin = 2;
const int redLedPin = 10;
const int blueLedPin = 5;

int buttonState = 0;
int lastButtonState = 0;
int currentBrightness = 0;
int targetBrightness = 0;

int procEveryXPress = 3;
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
  targetBrightness = random(256);
  while (currentBrightness != targetBrightness) {
    if (currentBrightness < targetBrightness) {
      dimmBrighter();
    } else {
      dimmDarker();
    }
  }
}

void dimmDarker() {
  analogWrite(blueLedPin, currentBrightness);
  delay(wavyDuration);
  currentBrightness--;
}

void dimmBrighter() {
  analogWrite(blueLedPin, currentBrightness);
  delay(wavyDuration);
  currentBrightness++;
}

bool procChecker() {
  return random(procEveryXPress) == 0;
}

void blinkRed() {
  currentBrightness = 0;
  for (int i = 0; i < blinkTimes; i++) {
    while (currentBrightness > 0) {
      analogWrite(redLedPin, currentBrightness);
      currentBrightness--;
      delay(1);
    }
    while (currentBrightness < 255) {
      analogWrite(redLedPin, currentBrightness);
      currentBrightness++;
      delay(1);
    }
  }
  while (currentBrightness > 0) {
    analogWrite(redLedPin, currentBrightness);
    currentBrightness--;
    delay(5);
  }
}

void loop() {
  waitingState();
  buttonState = digitalRead(buttonPin);
  if (buttonState != lastButtonState && buttonState == HIGH && procChecker()) {
    analogWrite(blueLedPin, 0);
    blinkRed();
    delay(50);
  }
  lastButtonState = buttonState;
}
