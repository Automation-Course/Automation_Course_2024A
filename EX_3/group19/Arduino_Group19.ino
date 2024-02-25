#include <Servo.h>
#include <LiquidCrystal_I2C.h>
//#include <Adafruit_LiquidCrystal.h>
#include <Ultrasonic.h>

#define TRIG_PIN 6
#define ECHO_PIN 5
#define LDR_PIN A0
#define SERVO_PIN 11
#define LED_PIN 10

Servo myServo;
LiquidCrystal_I2C lcd(0x27, 16, 2);
//Adafruit_LiquidCrystal lcd_1(0);

bool feedingInProgress = false;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LDR_PIN, INPUT);
  pinMode(SERVO_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  myServo.attach(SERVO_PIN);
  lcd.begin(16, 2);
  lcd.init();
  lcd.backlight();
  //lcd_1.begin(16, 2);
  //lcd_1.print("hello Dogs");
}

void loop() {
  // put your main code here, to run repeatedly:
  int distance = getDistance();
  int lightValue = analogRead(LDR_PIN);
  
  Serial.println("distance: "+ distance);
  Serial.println("Light: "+ lightValue);

  if (distance <= 20 && lightValue < 700) {
    feedDog();
  }else {
    retractServo();
  }
  delay(100);
}

int getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH); // Adjust the timeout value (in microseconds) as needed
  int distance = duration / 29 / 2;
  
  return distance;
}

void feedDog() {
  if (!feedingInProgress) {
    feedingInProgress = true;
  myServo.write(180); // Turn servo 180 degrees
  delay(900);
  myServo.write(90);
  lcd.print("Bon Appetit!");
  digitalWrite(LED_PIN, HIGH); // Turn on green LED
  }
}

void retractServo() {
  if (feedingInProgress) {
  feedingInProgress = false;
  myServo.write(0); // Retract servo to initial position
  delay(900);
  myServo.write(90);
  lcd.clear();
  digitalWrite(LED_PIN, LOW); // Turn off green LED
  }
}