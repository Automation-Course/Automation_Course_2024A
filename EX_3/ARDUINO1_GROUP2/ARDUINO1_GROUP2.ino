//stay hydrate code
int counterWaterCups = 0;
#define buttonDrankWater 4
#define ledDrinkWater 13
unsigned long previousMillis = 0;
const long interval = 5000;  // Interval in milliseconds (1 minute)
int currentState;

//LCD
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16,2); //Set the LCD address to display

// fill water
#include <Servo.h>
Servo servo;
#define trigPin 11
#define echoPin 10
long distance,duration; 
#define fillingWaterLed 12
#define servoPin 9
int angle= 0;
bool direction= true;
int speed = 90;

void setup()
{
  lcd.begin(16, 2);
  
  //stay hydrate code
  pinMode(buttonDrankWater, INPUT);
  pinMode(ledDrinkWater, OUTPUT);
  Serial.begin(9600);

    //real code-LCD
  lcd.init(); //initialize LCD real code
  lcd.backlight();
  lcd.display();

  //filling water
   servo.attach(servoPin);
   Serial.begin(9600);
   pinMode(fillingWaterLed,OUTPUT);
   pinMode(trigPin,OUTPUT);
   pinMode(echoPin,INPUT);
   pinMode(servoPin,OUTPUT);
}

void loop()
{ 
  //stay hydrate code- Remind drinking every 5 seconds
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) 
  {
    previousMillis = currentMillis; // Save the last time the LED was turned on
    
  	if(digitalRead(ledDrinkWater) == LOW)
  	{
      digitalWrite(ledDrinkWater, HIGH);
      Serial.println("The system alerts the employee to drink water");
    }
  }
    currentState= digitalRead(buttonDrankWater);

  //if the employee noticed and drank --> the red light will turn off and the LCD will display the total cups of water the employee drank
  if (currentState == HIGH && digitalRead(ledDrinkWater)==HIGH)
  {
    digitalWrite(ledDrinkWater, LOW);
    counterWaterCups++; 
        //turn on the backlight and print
	  lcd.setCursor(0, 1);  // Set the cursor to the beginning of the first line
    lcd.setBacklight(1);
    lcd.print("My total cups:");
  	lcd.print(counterWaterCups); 
    Serial.print("The employee pressed the button and informed that he drank water, total cups: ");
    Serial.println(counterWaterCups);
  }

  //Filling Water
  UltraSonic();
  Distance_Calculation();
  
  //If the employee placed a cup in the appropriate place --> the bottle will pour water into the cup with the help of the servo motor
  if (distance <= 10)
   {
   
    digitalWrite(fillingWaterLed,HIGH); //Alerts the employee about pouring water into the cup
    lcd.setCursor(0, 0);
    lcd.print("Filling Water");
    ServoFillWater();
    servo.write(speed);
    delay(2000); 
    }
   //The bottle returns to its place after pouring the water
  else 
  {
    digitalWrite(fillingWaterLed,LOW);
    lcd.setCursor(0, 0);
    lcd.print("Ready To Fill");
    returnBottle();
    servo.write(speed);
  }
}

void UltraSonic()
{
// Clears the trigPin condition
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin HIGH (ACTIVE) for 10 microseconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
}
void Distance_Calculation()
{
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
}

//The bottle will pour water into the cup with the help of the servo motor
void ServoFillWater()
{
  if (direction)
  {
    angle +=1;
    speed = 98;
    if (angle >= 2)
    {
      direction = false;
      speed = 90;
      angle = 2;
       Serial.println("The employee placed the cup in the appropriate place, the system poured water into the cup");
    }
  }
}

//The bottle returns to its place after pouring the water
void returnBottle()
{
  if (angle <= 2) 
  { // Checks if the water has been poured
    if (!direction)
    {
      angle -=1;
      speed = 5;
      if (angle <= -17)
      {
        direction = true;
        speed = 90;
        angle = 0;
        Serial.println("The employee took the cup, the bottle returned to its place");
      }
    }
  }
}

  
  
  
