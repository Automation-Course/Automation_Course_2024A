// controlling led with LDR
#define LdrPin  A0 // the cell and 10K pulldown are connected to a0
int LdrValue=0; // the analog reading from the sensor divider
#define LedPin  11 // connect Red LED to pin 11 (PWM pin)
int LedBrightness; 
//#include <Adafruit_LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>
int seconds = 0;
//Adafruit_LiquidCrystal lcd_1(0);
LiquidCrystal_I2C lcd(0x27,16,2);
#include <Servo.h>
#define servoPin 9
Servo my_servo;
int angle = 0;
bool Direction = true;
#define gasSensorPin A1
const int threshold = 500;

//For piezo (Buzzer):
int buzzer = 2;
//for ultraSonic
int trigPin =6;
int echoPin =5;
//for distance
long duration,distance;
int gasValue ;
 

void setup()
{
  Serial.begin(9600); 
 	pinMode(LdrPin,INPUT);
	pinMode(LedPin,OUTPUT);
 	pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  pinMode(servoPin, OUTPUT);
  my_servo.attach(servoPin);
  pinMode(gasSensorPin,INPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  int gasValue = analogRead(gasSensorPin);
  UltraSonic();
  Distance_Calculation();
  GasSensor(gasValue,200);
  if (distance < 200){    
     lcd1();
     lightSensor();
     servo1();
  } else {
  	return_normal();
  }
}  	
  
void return_normal(){
	my_servo.write(90); // Servo back to place
	digitalWrite(LedPin, LOW); // turn the LED off
  lcd.clear();
  noTone(buzzer);
}

void lightSensor(){
	LdrValue = analogRead(LdrPin); 
	Serial.print("LDR reading = ");
	Serial.println(LdrValue);    // the raw analog reading
	if (LdrValue > 300)
    digitalWrite(LedPin, LOW);
  else
    digitalWrite(LedPin, HIGH);
	delay(100);
}

void lcd1(){
    lcd.begin(16, 2);
    lcd.init();
    lcd.setBacklight(1);
    lcd.print("have a nice day!");
  	delay(1000);
  	lcd.clear();
  	lcd.setBacklight(0);
  	delay(1000);
}

//servo movement
void servo1() {
  	if (Direction){ 
    angle = angle + 180;
    }else{
    angle = angle - 180;
    }
    my_servo.write(angle);
    delay(15);
    if(angle == 180)Direction = false; 
    if(angle == 0)Direction = true;
}

void UltraSonic() {
	// Clears the trigPin condition
	digitalWrite(trigPin, LOW);
	delayMicroseconds(2);
	// Sets the trigPin HIGH (ACTIVE) for 10 microseconds
	digitalWrite(trigPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigPin, LOW);
}

void Distance_Calculation(){
	// Reads the echoPin, returns the sound wave travel time in microseconds
	duration = pulseIn(echoPin, HIGH);
	// Calculating the distance
	distance = duration * 0.034 / 2 ;// Speed of sound wave divided by 2 (go and back
}

void GasSensor(int gasValue,int threshold ){
  if (gasValue < threshold) {
    Serial.println("(low)Gas Value: ");
    Serial.println(gasValue);
    noTone(buzzer);
	}
  if (gasValue > threshold){
    Serial.println("Gas Value: ");
    Serial.println(gasValue);
    tone(buzzer,1000);
  }
}

