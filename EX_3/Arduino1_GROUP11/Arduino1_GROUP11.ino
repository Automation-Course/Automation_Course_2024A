#include <IRremote.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>
	
const int greenLedPin = 12; 
const int redLedPin = 13;
const int trigPin = 7;
const int echoPin = 8;
const int servoPin = 9;
const int piezoPin = 6;
LiquidCrystal_I2C lcd(0x27,20,4);
Servo servo;

int index;
long duration;
int max_dist;
int trigger_dist; 
int sensor_dist = 0;
bool sensor_triggered = false; 

int paper_length = 0;
int paper_needed = 0;
int roll_len_left;//45cm 15s 
const double roll_len_total = 1000;
int roll_percentage;
bool length_reached = false;

bool activated = false;
int timeout;

void setup(){
  pinMode(greenLedPin,OUTPUT);
  pinMode(redLedPin,OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(piezoPin, OUTPUT);
  
  calibrate(); //calculate max-distance and trigger-distance
  servo.attach(servoPin);

  roll_len_total; //total roll length on new roll
  roll_len_left = roll_len_total;//paper left on roll

  Serial.begin(9600);
}
	
void loop(){
  delay(100);

  index++; //timer for different actions at specific timing
  if(index == 10) //reset at 10
    index = 0;
  
  if(index%5 == 0) //check distance every 1/2 seconds
    sensor_dist = get_dist();

  if(sensor_triggered || sensor_dist < trigger_dist) //sensor_triggered helps prevent temporary noise by checking for two consecutive trigger states
    { 
      if(index < 5) //blinking green light while working
        digitalWrite(greenLedPin , LOW);
      else
        digitalWrite(greenLedPin , HIGH);
      dispance_paper(); //activate motor and calculate how much paper to release
      activated = true; //set state to active
    }
  else 
    {
      servo.write(90); 
      digitalWrite(greenLedPin , HIGH);
      if(timeout > 20 || !activated) { //this allows the system a few seconds timeout before resetting back to idle state
        digitalWrite(greenLedPin , HIGH);
        activated = false; //set system to not active
        idle_display(); //call for idle lcd display mode
        timeout = 0;
      }
      else timeout++;
    }

  if(sensor_dist < trigger_dist) //eliminates sensor noise by remembering previous trigger status 
    sensor_triggered = true;
  else 
    sensor_triggered = false;
}

int get_dist() {
  digitalWrite(trigPin, LOW); //clear trig
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  return duration * 0.034 / 2;
}
  
void dispance_paper(){
  if(!activated) { //prepare to start working
    Serial.print("Sensor triggered at ");
    Serial.print(sensor_dist);
    Serial.print("/");
    Serial.print(max_dist);
    Serial.println(" : DISPENCING");

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Dispencing!");
    tone(piezoPin,500,100); //buzz once at start of work
    paper_length = 0; //reset previous paper length dispenced
  } 

  if(paper_length <= sensor_dist) {  //check if current length is less then length required 
    servo.write(0);
    if(index%5==0){
      lcd.setCursor(0,1);
      lcd.print(paper_length);
      lcd.print(" out of ");
      lcd.print(sensor_dist);
      lcd.print(" cm");
      paper_length += 1; //count length dispenced
      roll_len_left -= 1; //subtract from total roll length
      length_reached = false; 
    }
  } 
  else {
      servo.write(90);
      if(!length_reached) { //buzz once when reached required length
        tone(piezoPin,1000,50);
        length_reached = true;
      }
  }
}

void idle_display()
{
  if(index%10==0)
  {
    roll_percentage = roll_len_left/roll_len_total*100; //calculate roll remainder percentage
    lcd.clear();
    lcd.setCursor(0,0);
    if(roll_percentage < 10) { //check if paper in low 
      lcd.print("Paper Low!");
    } else {
      lcd.print("Waiting..");
    }
    lcd.setCursor(0,1);
    lcd.print(roll_len_left);
    lcd.print(" cm (");

    lcd.print(roll_percentage);
    lcd.print("%)"); 

    Serial.print("Sensor detects ");
    Serial.print(sensor_dist);
    Serial.print("/");
    Serial.print(max_dist);
    Serial.println(" : IDLE");
  }
}

void calibrate()
{
    Serial.print("Calibrating ");
    Serial.print(trigger_dist);
    Serial.print("/");
    Serial.print(max_dist);
    Serial.println(" : SETUP");

    lcd.init();
    lcd.backlight();
    digitalWrite(redLedPin, HIGH);
  
    sensor_dist = get_dist();
    max_dist = sensor_dist;
    trigger_dist = max_dist * 0.8; //take 80% of maximum distance at calibration as trigger
    lcd.clear();
    lcd.print("Calibrating: ");
    lcd.setCursor(0, 1);
    lcd.print(max_dist);
    lcd.print(" cm");
    delay(1000);
    digitalWrite(redLedPin, LOW);
}
