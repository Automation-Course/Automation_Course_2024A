#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(39,16,2);

Servo myservo; // יצירת אובייקט סרבו לשליטה במנוע סרבו
int photoResistorPin = A0; // פין של חיישן האור מחובר לכניסה אנלוגית A0
int ultrasonicEchoPin = 2; // פין הקלט של חיישן האולטרסוני
int ultrasonicTrigPin = 3; // פין השליחה של חיישן האולטרסוני
int ledPin = 13; // פין הנורה LED
int distanceThreshold = 150; // ערך הסף למרחק בסנטימטר
int diss;
int light;
int direction=0;
int pos=0;

void setup() {
  myservo.attach(9); // מחבר את המנוע סרבו לפין שהוגדר
  pinMode(photoResistorPin, INPUT);
  pinMode(ultrasonicTrigPin, OUTPUT);
  pinMode(ultrasonicEchoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  lcd.begin(16,2);
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  lcd.clear();
 
}
//בקטע הבא אני דואגת לסיבוב הסרבו באמצעות משתנה המיקום שאומר בכמה מעלות הסתובב הסרבו נע מ0 ל180 
//ומשתנה הכיוון שקובע האם אני מסובבת עם או נגד כיוון השעון 

void loop() {
  
   
    delay(15); // ממתין 15 מילישניות עד שהסרבו מגיע למיקום
    diss= DistanceOfMotionDetected();//מבצעת קריאה של מרחק חפץ מחיישן
    light= LightDetected();// מבצעת קיראה עבור ערך האור בחדר
    // הדפסות למטרות מעקב ובדיקות 
    Serial.print("distance: ");
    Serial.print(diss);
    Serial.print(" ");
    Serial.print("Light Value: ");
    Serial.print(light);
    Serial.print(" ");
    Serial.println(" ");
    
  //תחילת מידול ההפעלה של המקרן
    if (diss<50 ||light<250) { //  בודק אם זוהתה תנועה או אור שיפריעו לסרט
      turnOffLED();// לכבות את הסרט אם זוהתה קרבה למסך או הדלקת אור 
      myservo.write(90);//עוצר את הקרנת הסרט
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Movie is Paused");
      
    } else {
      turnOnLED(); // סרט יכול להתחיל
      turnOnServo();//מדליק את הסרט
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Movie is ON");
       // מכבה את ה-LED אם לא זוהתה תנועה ולא אור
    }
}
//פונקציית הקרנת הסרט על ידי סיבוב הסרבו "הפילם" 
void turnOnServo(){
 if (direction==0){
    if (pos<180)
    {
      pos= pos +1;
    }
    else{
      direction=1;
    }
  }
  else
  {
    if (pos>0){
      pos= pos-1;
    }
    else{
      direction=0;
    }
  }
   myservo.write(pos); // אומר לסרבו להגיע למיקום במשתנה 'pos'
}
//פונקצית דגימת המרחק באמצעות החיישן מחזירה את המרחק
int DistanceOfMotionDetected() {
  digitalWrite(ultrasonicTrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(ultrasonicTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(ultrasonicTrigPin, LOW);

  long duration = pulseIn(ultrasonicEchoPin, HIGH);
  int distance = duration * 0.034 / 2;

  return (distance);
}
// פונקצית דגימת ערך האור מהחיישן מחזירה את עוצמת האור
int LightDetected() {
  int lightValue = analogRead(photoResistorPin);
  return (lightValue ); 
}
//פונקציה להדלקת נורת הלד
void turnOnLED() {
  digitalWrite(ledPin, HIGH); // מדליק את ה-LED
}
// פונקציה לכיבוי נורת הלד 
void turnOffLED() {
  digitalWrite(ledPin, LOW); // מכבה את ה-LED
}