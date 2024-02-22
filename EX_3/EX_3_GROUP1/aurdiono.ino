// C++ code
//
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);
#define led4 4
#define led7 7
int Piezo = 8;
#include <Servo.h>
int position = 0;
Servo servo_12;
int servo = 12;
bool Direction = true;


void setup()
{
    pinMode(servo, INPUT);
     servo_12.attach(12);
    pinMode(Piezo, OUTPUT);
   pinMode(led4, OUTPUT);
  pinMode(led7, OUTPUT);
    pinMode(2, INPUT);
    Serial.begin(9600); 
  lcd.init();
   lcd.begin(16, 2);
    lcd.setBacklight(1);
}

void loop()
{
  position = 0;
  int pir = 0;
  pir = digitalRead(2);
    if (pir == 1) {
       Serial.println("Motion detected!");
       servo_12.write(0);
       digitalWrite(led4, LOW);
       digitalWrite(led7, HIGH);
       lcd_emergency();
       tone(Piezo,1000);
     delay(10000);
    }else{
      Serial.println("Steady");
       lcd_normal();
        servo_move();
       digitalWrite(led7, LOW);
      digitalWrite(led4, HIGH);
       noTone(Piezo);
        
    }
}

void lcd_normal(){
lcd.setCursor(0, 0);
    lcd.print("Together We Will");
    lcd.setCursor(7, 1);
    lcd.print("Win");
}
void lcd_emergency(){
lcd.setCursor(0, 0);
    lcd.print("Wakef Wakef !!!!");
    lcd.setCursor(7, 1);
    lcd.print("                      ");
}

void servo_move(){
      Serial.println("Servo start moving");
    servo_12.write(90);
    delay(15);
