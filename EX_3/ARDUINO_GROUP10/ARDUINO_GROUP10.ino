#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <Wire.h>
Servo servo;
  LiquidCrystal_I2C lcd_1(0x27, 16, 2); // Adjust the address (0x27) if needed
  int piezo = 7;
  int servoPin = 9;
  int angle = 0;
  bool Direction = true;
  bool Is_LED_OFF = true;
  int ledRed = 2;
  int trigPin = 11;
  int echoPin = 10;
  long duration, distance;
  unsigned long ultraSonicPreviousMillis = 0;
  const long ultraSonicInterval = 60; // Interval in milliseconds for the UltraSonic function 
  unsigned long byecrowPreviousMillis = 0;
  const long byecrowInterval = 1000; // Interval in milliseconds for the Bye_Crow function
  unsigned long servoPreviousMillis = 0;
  const long servoInterval = 15; // Interval in milliseconds for the Serv function

void setup() {
  lcd_1.begin(16, 2); // Initialize the LCD
  lcd_1.backlight();
  lcd_1.blink_on();
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(piezo, OUTPUT);
  servo.attach(servoPin);
  Serial.begin(9600);
  }
void loop() {
  UltraSonic();
  Distance_Calculation();
  lcd();
  if (distance < 70) {
    Bye_Crow();
    ServoFunction(); // Call ServoFunction only when something is detected within 70 cm
  } else {
    return_normal();
    }
}
void UltraSonic() {
  unsigned long currentMillis = millis();
  if (currentMillis - ultraSonicPreviousMillis >= ultraSonicInterval) {
    ultraSonicPreviousMillis = currentMillis;
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
  }
}
void Distance_Calculation() {
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
}
void lcd() {
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  String disp = String(distance);
  lcd_1.clear();
  lcd_1.print("Distance :");
  lcd_1.setCursor(0, 1);
  lcd_1.print(disp);
  lcd_1.print(" cm");
}
void Bye_Crow() {
  unsigned long currentMillis = millis();
    if (currentMillis - byecrowPreviousMillis >= byecrowInterval) {
    byecrowPreviousMillis = currentMillis;
    blink(ledRed);
    buzz(piezo);
    ServoFunction();
  }
}
void return_normal() {
  noTone(piezo);
  servo.write(90);
  digitalWrite(ledRed, LOW);
}
void blink(int led) {
  if (Is_LED_OFF) {
    digitalWrite(led, HIGH);
    Is_LED_OFF = false;
  } else {
      digitalWrite(led, LOW);
      Is_LED_OFF = true;
      }
  }
void buzz(int piezoName) {
  tone(piezoName, 2000);
}
void ServoFunction() {
  unsigned long currentMillis = millis();
  if (currentMillis - servoPreviousMillis >= servoInterval) {
    servoPreviousMillis = currentMillis;
     if (Direction) {
      angle = 0; // Start from 0 degrees
      Direction = false;
   } else {
     angle = 180; // Move to 180 degrees
     Direction = true;
   }
  servo.write(angle);
  }
  }