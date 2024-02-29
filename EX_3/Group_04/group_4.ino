#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

#define TRIG_PIN 6
#define ECHO_PIN 10
#define LED_PIN 7
#define servoPin 9
#define PIEZO_PIN 8

Servo servo;

int angle=0;//זווית התחלתית
bool Direction=true;//הגדרת כיוון (ימין=true)
LiquidCrystal_I2C lcd(0x27, 16, 2);



void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(PIEZO_PIN, OUTPUT);
  lcd.begin(16, 2);
  lcd.backlight();


}

void loop() {
  int distance = measureDistance();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Distance: ");
    lcd.print(distance);
    lcd.print(" cm");

    if (distance <= 40) {
      lcd.setCursor(0, 1);
      lcd.print("attention       ");
      digitalWrite(LED_PIN, HIGH);  // הדלקת הנורה

      if(distance<=30){
       moveServo();

       if (distance<=20){
          lcd.setCursor(0, 1);
          lcd.print("too close!!!       ");
          digitalWrite(PIEZO_PIN, LOW);
       }
       else{
         digitalWrite(PIEZO_PIN, HIGH);
       }
     }
     else  {servo.detach();
     }

    }
  else {
      lcd.setCursor(0, 1);
      lcd.print("                 ");
      servo.detach();
      digitalWrite(PIEZO_PIN, HIGH);
      digitalWrite(LED_PIN, LOW);
      }

}


  // פוקציה שמחזירה את המרחק מהחיישן קרבה
int measureDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  int duration = pulseIn(ECHO_PIN, HIGH);
  int distance = duration * 0.034 / 2;  // מהירות האור היא 34 סמ/מילישנייה

  return distance;
}



void moveServo() {
  servo.attach(servoPin);
  if (Direction){
          angle+=1;
        }
        else{
          angle-=1;
        }
        servo.write(angle);
        if(angle==180)Direction=false;
        if (angle==0)Direction=true;
  
}


