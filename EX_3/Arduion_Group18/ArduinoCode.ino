// Libraries
#include <LiquidCrystal_I2C.h>;
LiquidCrystal_I2C lcd(0x27, 16, 2);
#include <wire.h>;
#include <Servo.h>;

Servo systemServo;

// Initializing Variable
#define led 5
#define buzzer 6
#define servoPin 10
#define resetAlarmButton 2
#define turnSystemOnButton 4
#define trigPin 12
#define echoPin 13
long distance = 0;
long duration = 0;
int buttonState = 0;
int onButton = 0;
bool alarmActive = false;
int speed = 0;
bool ComputerLocks = false;
bool pushButton = false;
bool systemOn = false;

void setup()
{
  lcd.begin(16, 2);
  
  Serial.begin(9600);

  // Set the LED pin as an output
  pinMode(led, OUTPUT);

  // Set the piezo buzzer pin as an output
  pinMode(buzzer, OUTPUT);

  // Set the servo pin as an output
  systemServo.attach(servoPin);

  // Set the ultrasonic 
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Set the push button pin as an input
  pinMode(resetAlarmButton, INPUT_PULLUP);
  
   // Set the push button pin as an input
  pinMode(turnSystemOnButton, INPUT_PULLUP);

  // Print the initial message on the LCD screen
  lcd.init();
  lcd.backlight();
  lcd.print("");
}

void loop()
{
  checkSystemState();
  if (systemOn==true)
  { 
    checkButtonState();
 	checkUltraSonicSensor();
   if (pushButton==false)
   {
     keepAlarmActive();
   }
  	delay(50); // add a small delay to prevent flickering of the LCD screen
  	checkButtonState();
	    if (pushButton==true)
  		{   
    	turnOffAlarm(); //כבה את האזעקה אם המנהל בא לסגור את האירוע
      delay(1000);
  		}
  }

  	
}

void checkSystemState()
{
  // Read the state of the push button
  onButton = digitalRead(turnSystemOnButton);
  // If the push button is pressed, turn off the LED, piezo buzzer, and servo motor
  if (onButton == LOW) 
  { 
    if (systemOn==false)
    {
   	 	systemOn=true;
      lcd.clear();
     lcd.print("Motion System On");
      Serial.println("FindBurglers system is on");
      delay(5000);
    }
    else
    {
      systemOn=false;
      lcd.clear();
      lcd.print("Motion System Off");
      Serial.println("FindBurglers system is off");
      digitalWrite(led, LOW);
      delay(5000);
    }
  }
}

void checkButtonState()
{
  // Read the state of the push button
  buttonState = digitalRead(resetAlarmButton);
  // If the push button is pressed, turn off the LED, piezo, and servo motor
  if (buttonState == LOW && alarmActive)
  {
    pushButton=true;
  }
}

void turnOffAlarm()
{
  digitalWrite(led, LOW);
  noTone(buzzer);
  alarmActive = false;
  ComputerLocks = false; 
  pushButton=true;
  lcd.setCursor(0, 1);
  lcd.print("No Movement       ");
  Serial.println("Turn off the alarm");
  cancelLockPC();
}

void checkUltraSonicSensor() {
  // If the PIR sensor detects motion and the alarm is not already active, activate the alarm and servo motor
 digitalWrite(trigPin,LOW);
 delayMicroseconds(2);
 digitalWrite(trigPin,HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPin,LOW);
 duration = pulseIn(echoPin,HIGH);
 distance = duration*0.034/2;
  if (distance<10 && !alarmActive && pushButton==false)
  {
    activateAlarm();
  }
}

void activateAlarm()
{
  // Turn on the LED
  digitalWrite(led, HIGH);

  // Print "Motion Detected" on the LCD screen
  lcd.setCursor(0, 1);// להדפיס בשורה השנייה
  Serial.println("Active the alarm"); // הדפסה שנראה
  lcd.print("Motion Detected");// תראה על האלסידי מושן דיטקטד
  // Activate the piezo buzzer
  tone(buzzer, 1000, 5000); // variable //5000 קח את הבאזר עם התדירות 1000 והמהירות
  // Move the servo motor to simulate the closing of the blinds
  alarmActive = true; //האזעקה פועלת
  activateLockPC();//נעילת מחשבים
}

void keepAlarmActive()
{
  // If the alarm is active, keep the piezo buzzer on
  if (alarmActive)
  {
    ComputerLocks = true; //נעילת מחשבים
    tone(buzzer, 1000, 500);// תרעיש בתדירות 1000 ומהירות 500, 5000?
  }
}

void activateLockPC()
{
   speed=180;
   systemServo.write(speed);
   delay(3000);
   speed = 90;
   systemServo.write(speed);
}
void cancelLockPC()
{
   speed = 0;  
   systemServo.write(speed);
   delay(3000);
   speed = 90;
   systemServo.write(speed);
   pushButton=false;
}