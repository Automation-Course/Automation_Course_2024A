#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>


// Pins definition
#define led 13
#define servo_pin 9
#define buzer_pin 7
#define PIR_pin 2
#define inpin 4

int volume = 0;
int buttonState = LOW;
bool alarm_on = false;
int alarmCounter = 6;
int speed = 0 ; 
bool direction = true ; 
int angel = 0 ; 
Servo servo;
LiquidCrystal_I2C lcd(0x27, 16, 2);


void setup() {
  lcd.init();
  lcd.begin(16, 2);
  lcd.backlight();
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(buzer_pin, OUTPUT);
  pinMode(PIR_pin, INPUT);
  servo.attach(servo_pin);
  digitalWrite(PIR_pin, LOW);
  pinMode(inpin, INPUT);
}

void loop() {
  buttonState = digitalRead(inpin);
  if (buttonState == HIGH) {
    Serial.print ("Push Button");
    push_button();
  } 
 
  if (motion() || alarm_on){
  alarm(); // turn on the alarm and the buzzer
  alarmCounter --;
    if (alarmCounter == 0) {
      alarm_on = false;
      alarmCounter = 6;
    }
  }
  else{
    no_alarm();
    }
   delay(500);
}

bool motion() { // PIR sensor detection check input
  if (digitalRead(PIR_pin) == HIGH) { // Movement detected
    Serial.println("PIR - high");
    alarm_on = true;
    return true;
  } else { // No movement
    Serial.println("PIR - low");
    return false;
  }
}

void alarm() { // Alarm set on
  Serial.print ("alarm is on!");
  digitalWrite(led, HIGH); // Turn on lamp
  Serial.print ("lamp is on!");
  write_lcd(true);
  buzer_on();
  servo_movement();
}

void no_alarm() { // Alarm set off
 // alarm_on=false;
 
  Serial.print ("alarm is off!");
  digitalWrite(led, LOW); // Turn off lamp
  Serial.print ("lamp is off!");
  noTone(buzer_pin); // Restart buzzer
  servo.write(90);   // Restart servo
  Serial.print ("servo is off!");
  write_lcd(false);
}

void servo_movement() { // Servo movement for the alarm
  Serial.print ("servo is on!");
  if (direction) {
    angel +=30 ; 
    speed = 180;
  } 
  else {
    angel-=30;
    speed = 0;
  }
  servo.write(angel);
  if(angel == 180){
    direction = false;
  }
  if(angel == 0){
    direction = true;
  }    
}

void buzer_on() { // Buzzer on for the alarm
  if (volume >= 300) {
    volume = 100;
  } else {
    volume += 10;
  }
  tone(buzer_pin, volume);
  delay(100);
  Serial.print("Buzzer is on,the volume is: " + String(volume));
}

void write_lcd(bool alarm) { // LCD display for state
  lcd.clear();
  if (alarm) { // Alarm on
    lcd.print ("Plankton");
    lcd.setCursor(0, 1);
    lcd.print ("is here!");
    Serial.print ("LCD is on");
  } else { // Alarm off
      lcd.print (" Welcome To Mr.");
      lcd.setCursor(0, 1);
      lcd.print (" Crab's office :)! ");
      Serial.print ("LCD is on");
    }
}

void push_button() {
  servo.write(90); // Restart servo
  Serial.print ("servo is off!");
  lcd.clear();
  lcd.print (" Calling to");
  lcd.setCursor(0, 1);
  lcd.print (" the police");
  Serial.print ("Someone pressed the emergency button and a call is made to the police ");
  delay(1500);
}