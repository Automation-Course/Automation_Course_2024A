// Include necessary libraries for LCD display, communication, and servo motor control
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Servo.h>

// Create a servo object to control a servo motor
Servo myservo;

// Variables to manage time for the application's functionality
unsigned long elapsedTime = 0;
unsigned long startTime = 0;
boolean counterRunning = false;
unsigned long pauseStartTime = 0;
unsigned long lastPrintMinute = -1; // Initialize with a value that can't be a real minute to ensure the first time is printed

// Define pins and thresholds for LED, ultrasonic sensor, and servo
const int LED = 13;
const int TRIGGER_PIN = 7;
const int ECHO_PIN = 6;
const int DISTANCE_THRESHOLD = 5;
const int servoPin = 9;

// Initialize LCD display with I2C address and size (16x2)
LiquidCrystal_I2C lcd_1(0x27, 16, 2);

// Setup function to initialize pin modes, attach servo, and setup LCD
void setup() {
  pinMode(LED, OUTPUT); // LED as output for visual signal
  pinMode(TRIGGER_PIN, OUTPUT); // Ultrasonic sensor trigger pin as output
  pinMode(ECHO_PIN, INPUT); // Ultrasonic sensor echo pin as input
  myservo.attach(servoPin); // Attach servo motor to its control pin
  lcd_1.init(); // Initialize the LCD
  lcd_1.backlight(); // Turn on LCD backlight
  lcd_1.clear(); // Clear LCD display
  lcd_1.print("Start"); // Display startup message
  Serial.begin(9600); // Begin serial communication
  Serial.println("Start of the day, each minute will appear here:");
}

// Main loop function, runs repeatedly
void loop() {
  long duration, distance;
  // Trigger ultrasonic sensor to measure distance
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * 0.034 / 2; // Calculate distance based on sound speed

  // Check if detected distance is below threshold
  if (distance < DISTANCE_THRESHOLD) {
    digitalWrite(LED, HIGH); // Turn on LED if object is close
    myservo.write(3); // Adjust servo position
    delay(15); // Short delay for servo movement
    // Start or resume the counter
    if (!counterRunning) {
      if (pauseStartTime != 0) {
        // Calculate pause duration and adjust startTime accordingly
        unsigned long pauseDuration = millis() - pauseStartTime;
        startTime += pauseDuration;
        pauseStartTime = 0;
      } else {
        // Start the timer if it wasn't already running
        startTime = millis();
      }
      counterRunning = true;
    }
  } else {
    // Turn off LED and reset servo position if no object is detected
    digitalWrite(LED, LOW);
    myservo.write(90);
    delay(15);
    // Pause the counter
    if (counterRunning) {
      counterRunning = false;
      pauseStartTime = millis();
    }
  }

  // Update and display the time elapsed if the counter is running
  if (counterRunning) {
    unsigned long currentTime = millis();
    elapsedTime = currentTime - startTime;

    // Calculate hours, minutes, and seconds
    unsigned long seconds = elapsedTime / 1000;
    unsigned long minutes = seconds / 60;
    unsigned long hours = minutes / 60;
    seconds %= 60;
    minutes %= 60; // Ensure minutes and seconds don't exceed their max values

    // Print the time to the serial monitor at the start of each new minute
    if (minutes != lastPrintMinute) {
      Serial.print("Work time today: ");
      if (hours < 10) Serial.print("0");
      Serial.print(hours);
      Serial.print(":");
      if (minutes < 10) Serial.print("0");
      Serial.print(minutes);
      Serial.print(":");
      if (seconds < 10) Serial.print("0");
      Serial.println(seconds);

      lastPrintMinute = minutes; // Update last printed minute
    }

    // Update LCD display with the elapsed time
    lcd_1.clear();
    lcd_1.setCursor(0, 0);
    lcd_1.print("Time: ");
    if (hours < 10) lcd_1.print("0");
    lcd_1.print(hours);
    lcd_1.print(":");
    if (minutes < 10) lcd_1.print("0");
    lcd_1.print(minutes);
    lcd_1.print(":");
    if (seconds < 10) lcd_1.print("0");
    lcd_1.print(seconds);
    lcd_1.setCursor(0, 1);
    lcd_1.print("Human detected"); // Display message when an object is detected
  } else {
    // Display a different message when no object is detected
    lcd_1.clear();
    lcd_1.setCursor(0, 0);
    lcd_1.print("Not detecting");
  }
}
