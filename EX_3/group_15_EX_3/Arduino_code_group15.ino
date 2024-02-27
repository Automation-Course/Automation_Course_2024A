#include <Servo.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define ledPin 12
#define buttonPin 2
#define triggerPin 3
#define echoPin 4
#define servoPin 9

//LCD 
LiquidCrystal_I2C lcd(0x27, 16, 2);
bool messagePrinted = false;

//button
bool buttonPressed = false;      // flag indicating whether the button is pressed
int currentButtonState = 0;      // current state of the button (HIGH or LOW)

//ultrasonic sensor
long lastDistanceTime = 0;       // last distance measured

//servo
Servo chair;
int angle = 0;                   
int speed = 90;                  
bool returning = false;
int returnSpeed = 150;

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  chair.attach(servoPin);
  lcd.init();
  lcd.backlight();
}

void loop() {
  occupiedPosition();

  // printing welcoming message whan the chair is empty
  if (currentButtonState == LOW) {
    lcd.clear();
    lcd.print("Have a good day");
  }

  if (currentButtonState == HIGH && !buttonPressed) {
    buttonPressed = true;
  }
  if (currentButtonState == LOW && buttonPressed) {
    buttonPressed = false;
    returning = true; // set the returning state
  }

  // if the button is pressed, move the chair and measure the distance
  if (buttonPressed) {
    pushChair();
    measureDistance();
  }

  //returnig the chair to its initial place
  if (returning) {
    returnChairToPlace();
  }

  delay(10); 
}

// if the chair is occupied the LED turns on, and the state of the button is updated
void occupiedPosition() {
  currentButtonState = digitalRead(buttonPin);
  digitalWrite(ledPin, currentButtonState);
}

// move the chair if the employee is sitting on it
void pushChair() {
  if (buttonPressed == true) {
    if (angle < 45) {
      speed = 0;
      angle += 1;
    } else {
      angle = 45;
      speed = 90;  
    }
    chair.write(speed);
  } 
}

// return the chair if the employee is not sitting on it
void returnChairToPlace() {
  if (angle > 0 and angle <= 45) {
    chair.write(100);
    delay(10); // Adjust the delay as needed to control the servo speed
    angle -= 1;
  } else {
    // Make sure the servo stops after reaching the desired angle
    chair.write(90);
    angle = 0;
    returning = false; // reset the returning state
  }
}

// measure the distance from the screen and alert the employee if he is sitting too close
void measureDistance() {
  // measure the distance every 0.5 second
  if (millis() - lastDistanceTime >= 500) {
    long duration, cm;

    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);

    duration = pulseIn(echoPin, HIGH);
    cm = microsecondsToCentimeters(duration);

    // alert the employee if he is sitting too close
    if (cm < 20) {
      if (!messagePrinted) {
        lcd.clear();
        lcd.print("Sit further :)");
        lcd.setCursor(0, 1);
        lcd.print("Distance:");
        lcd.print(cm);
        delay(1000);
        messagePrinted = true; 
      }
    }
    // update the employee on his current distance from the screen
    else {
      lcd.clear();
      lcd.print("Your distance is:");
      lcd.setCursor(0, 1);
      lcd.print(cm);
      delay(100);
      messagePrinted = false;
    }

    lastDistanceTime = millis();  // update the last distance measured
  }
}

// convert microseconds to centimeters
long microsecondsToCentimeters(long microseconds) {
  // speed of sound in air is 343 meters per second 
  // divide the duration by 2 because the sound travels to the object and back
  return microseconds / 2 * 0.0343;
}
