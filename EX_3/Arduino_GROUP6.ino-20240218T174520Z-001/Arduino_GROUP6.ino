#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Define pins for ultrasonic sensor
#define TRIG_PIN 9
#define ECHO_PIN 10

// Define pin for servo motor
#define SERVO_PIN 3
// Create servo object
Servo servo;

// Define pin for temperature sensor
#define TEMP_SENSOR A0

// Define pin for LED (air conditioner indicator)
#define LED_PIN 2

bool Direction = true;
int angle = 0;
int speed = 90;
int countEmployee = 0; // At start day- there isnt employees in the office

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  servo.attach(SERVO_PIN);
  // initialize the LCD
  lcd.init();
  Serial.begin(9600);
}

void loop() {
  long duration=0;
  long distance=0;
  float temperature;

  // Measure the distance
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration/29/2; // Calculate distance
  Serial.print("The distance IS: ");
  Serial.println(distance);
 
  // Attach the servo only if the condition is met and it hasn't been attached yet
  if (distance <= 80) {///////////////////// && distance != 0
    Serial.println("There is employee. open door");
      if (Direction){
        angle +=1;
        speed = 100;
        if (angle >= 3){
          Direction = false;
          speed = 90;
          angle = 3;
        }
      }
    servo.write(speed);
    lcd.setBacklight(1);
    lcd.print("WELCOME!");
    delay(2000); // Keep WELCOME for 2 seconds
    lcd.clear();
    countEmployee++;
  }
  // Attempt to close the door after checking temperature and LED status
  else {
    if (angle <= 3) { // Check if the door is not already closed
      if (!Direction){
        Serial.println("The Employee get in. Closing door.");
        angle -=1;
        speed = 80;
        if (angle <= -50){
          Direction = true;
          speed = 90;
          angle = 0;
        }
      }
      servo.write(speed);
      lcd.setBacklight(0);
    }
  }

  // If employees have been counted, check the temperature
  if (countEmployee > 0) {
    // Measure temperature
    temperature = analogRead(TEMP_SENSOR);
    temperature = (((temperature / 1024.0) * 5.0 * 100) - 50); // Convert to degrees Celsius
    // Check if temperature is higher than 24 degrees Celsius
    if (temperature > 24) {
     Serial.println("Temperature is higher than 24 degrees Celsius. Turning on AC.");
      digitalWrite(LED_PIN, HIGH); // Turn on LED (air conditioner)
    }
    else if (temperature < 16) {
      Serial.println("Temperature is less than 16 degrees Celsius. Turning on AC.");
      digitalWrite(LED_PIN, HIGH); // Turn on LED (air conditioner)
    }
    else {
      digitalWrite(LED_PIN, LOW); // Turn off LED
      Serial.println("Air conditinior turned off.");
    }
  }
}