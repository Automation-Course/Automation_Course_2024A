#include <Servo.h>
#include <Wire.h>
#include <Adafruit_LiquidCrystal.h>

Adafruit_LiquidCrystal lcd(0);

#define Echo_PIN 2
#define Trig_PIN 3
#define Led_PIN 4
#define RST_PIN 6

Servo servo;
int pushButton = 8;
bool ledShouldBeOff = false; // Tracks if LED should be manually kept off
bool distanceWasLessThan100 = true; // Tracks if the last distance was less than 100

void setup() {
  servo.attach(RST_PIN);
  pinMode(Led_PIN, OUTPUT);
  pinMode(Trig_PIN, OUTPUT);
  pinMode(Echo_PIN, INPUT);
  pinMode(pushButton, INPUT_PULLUP); // Use internal pull-up resistor
  lcd.begin(16, 2);
  lcd.setBacklight(1);
  lcd.clear();
  lcd.setCursor(0,0);
}

void loop() {
  static bool lastButtonState = LOW; // Tracks the last state of the button
  bool currentButtonState = digitalRead(pushButton);
  int distance = getDistance();
  int tiltAngle = map(distance, 0, 100, 0, 180);

  // Button press detection (rising edge)
  if (currentButtonState == HIGH && lastButtonState == LOW) {
    ledShouldBeOff = !ledShouldBeOff; // Toggle LED off state
    digitalWrite(Led_PIN, LOW); // Turn off LED immediately upon pressing
    delay(50); // Debounce delay
  }
  lastButtonState = currentButtonState;

  // Control LED based on distance and manual override
  if (distance < 100) {
    digitalWrite(Led_PIN, LOW); // Turn off if too close
    distanceWasLessThan100 = true;
  } else if (distance > 100 && (!ledShouldBeOff || (ledShouldBeOff && distanceWasLessThan100))) {
    digitalWrite(Led_PIN, HIGH); // Turn on if the distance becomes more than 100 and it was previously less or if manual off is not active
    distanceWasLessThan100 = false;
  }

  // Display information
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Dist: ");
  lcd.print(distance);
  lcd.print(" cm");
  lcd.setCursor(0, 1);
  lcd.print("Angle: ");
  lcd.print(tiltAngle);
  lcd.print(" deg");

  tiltScreen(tiltAngle); // Adjust screen tilt based on distance
  delay(100);
}

int getDistance() {
  digitalWrite(Trig_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig_PIN, LOW);
  return pulseIn(Echo_PIN, HIGH) * 0.034 / 2;
}

void tiltScreen(int angle) {
  servo.write(angle);
  delay(20); // Ensure servo has time to reach the position
}