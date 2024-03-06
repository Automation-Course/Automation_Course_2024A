// Loading Libraries
#include <Servo.h> // Include servo library for controlling the servo motor
#include <Wire.h> // Include Wire library for I2C communication (possibly for LCD)
#include <LiquidCrystal_I2C.h> // Include LiquidCrystal_I2C library for controlling the LCD

// Define pin constants
#define trigPin 2  // Trigger pin for ultrasonic sensor
#define echoPin 3   // Echo pin for ultrasonic sensor
#define servoPin 9  // Pin connected to the servo motor
#define buttonPin 0 // Pin connected to the button
#define ledPin 13   // Pin connected to the LED

// Define variables
long duration;       // Stores the duration of the ultrasonic pulse
float distance;      // Stores the calculated distance
LiquidCrystal_I2C lcd(0x27, 16, 2); // Create an I2C LiquidCrystal object
Servo servo;          // Create a Servo object
int angle = 0;        // Current angle of the servo motor
int speed = 0;         // Speed at which the servo moves (0 or 180)
bool Direction = true;  // Boolean flag for servo direction (true: clockwise, false: counter-clockwise)
int dist = 0;          // Not used in the provided code
int buttonState = 0;    // Stores the current state of the button (0: not pressed, 1: pressed)
bool ledState = false;  // Variable to track LED state (true: on, false: off)

void setup() {
  servo.attach(servoPin);  // Attach the servo to the specified pin
  lcd.init();              // Initialize the LCD display
  pinMode(trigPin, OUTPUT); // Set trigger pin as output
  pinMode(echoPin, INPUT);  // Set echo pin as input
  pinMode(buttonPin, INPUT); // Set button pin as input
  pinMode(ledPin, OUTPUT);  // Set LED pin as output

  Serial.begin(9600);       // Initialize serial communication at 9600 baud
}

void loop() {

  // Trigger pulse (sends a short high pulse)
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the duration of the echo pulse
  duration = pulseIn(echoPin, HIGH);

  // Calculate the distance based on the duration
  distance = duration * 0.034 / 2;

  lcd.backlight();

  // Set cursor position and print "Distance: " on the LCD
  lcd.setCursor(0, 0);
  lcd.print("Distance: ");

  // Print the calculated distance on the LCD
  lcd.print(distance);

  // If distance is greater than 20 cm, start the servo movement
  if (distance > 20) {
    startServo();
  } else {
    // Otherwise, set the servo to the center position (90 degrees)
    servo.write(90);
  }
}

void startServo() {
  if (Direction) {
    angle += 1;  // Increase angle by 1 degree (clockwise)
    speed = 180; // Set speed to 180 (fast)
  } else {
    angle -= 1;  // Decrease angle by 1 degree (counter-clockwise)
    speed = 0;   // Set speed to 0 (stop)
  }

  // Write the angle to the servo motor
  servo.write(speed);

  // Delay for 15 milliseconds
  delay(15);

  // Update direction based on angle limits (0 or 180 degrees)
  if (angle == 180) {
    Direction = false;
  } else if (angle == 0) {
    Direction = true;
  }
}
