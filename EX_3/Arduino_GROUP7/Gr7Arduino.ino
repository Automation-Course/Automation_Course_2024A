#include <SPI.h>
#include <IRremote.h>
#include <MFRC522.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include "pitches.h"
LiquidCrystal_I2C lcd(0x27, 16, 2); // Format -> (Address, Width, Height)


#define SS_PIN 10
#define RST_PIN 9
#define LED_G 6 // Green LED pin
#define LED_R 7 // Red LED pin
#define servoPin 4
#define BUZZER_PIN 8
Servo myServo;
MFRC522 mfrc522(SS_PIN, RST_PIN); // Declare the MFRC522 object globally

int melody[] = {
  REST, REST, REST, NOTE_DS4, 
  NOTE_E4, REST, NOTE_FS4, NOTE_G4, REST, NOTE_DS4,
  NOTE_E4, NOTE_FS4,  NOTE_G4, NOTE_C5, NOTE_B4, NOTE_E4, NOTE_G4, NOTE_B4,   
  NOTE_AS4, NOTE_A4, NOTE_G4, NOTE_E4, NOTE_D4, 
  NOTE_E4, REST, REST, NOTE_DS4,
  
  NOTE_E4, REST, NOTE_FS4, NOTE_G4, REST, NOTE_DS4,
  NOTE_E4, NOTE_FS4,  NOTE_G4, NOTE_C5, NOTE_B4, NOTE_G4, NOTE_B4, NOTE_E5,
  NOTE_DS5   
};

int durations[] = {
  2, 4, 8, 8, 
  4, 8, 8, 4, 8, 8,
  8, 8,  8, 8, 8, 8, 8, 8,   
  2, 16, 16, 16, 16, 
  2, 4, 8, 4,
  
  4, 8, 8, 4, 8, 8,
  8, 8,  8, 8, 8, 8, 8, 8,
  1 
};

void setup() {
  Serial.begin(9600);
  SPI.begin();
  myServo.attach(servoPin);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_R, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  mfrc522.PCD_Init(); // Initialize MFRC522 here
  Serial.println("Put your card to the reader...");
  Serial.println();
  lcd.init();
  lcd.backlight();
}

void playMelody() {
  int size = sizeof(durations) / sizeof(int);
  for (int note = 0; note < size; note++) {
    int duration = 1000 / durations[note];
    tone(BUZZER_PIN, melody[note], duration);
    int pauseBetweenNotes = duration * 1.70;
    delay(pauseBetweenNotes);
    noTone(BUZZER_PIN);
  }
}


void loop() {
  lcd.clear();
  lcd.setCursor(0, 0);// Set cursor (Column, Row)
  lcd.print("Hello"); // print "Hello" at (0, 0) 
  lcd.setCursor(0,1);// Set cursor (Column, Row)
  lcd.print("Place Your card");// print "Place Your card" at (0, 1)
  delay(1000);
  lcd.clear();
  // Look for new cards
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  // Show UID on the serial monitor
  Serial.print("UID tag: ");
  String content = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message: ");
  content.toUpperCase();
  
  if (content.substring(1) == "D5 0A 9A 8A") { // Login is approved
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Authorized Access");
    delay(1000);
    lcd.clear();
    Serial.println("Authorized access");
    digitalWrite(LED_G, HIGH);
    myServo.write(180); // Rotate in one direction
    delay(3000); // Wait for 3 seconds
    myServo.write(0); // Stop rotation
    delay(500);
    myServo.write(90); // Stop servo for denied access

    digitalWrite(LED_G, LOW);
    } 
    else { // Entry denied
    Serial.println("Access denied");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Access Denied");
    digitalWrite(LED_R, HIGH);
    playMelody();
    delay(1000);
    digitalWrite(LED_R, LOW);
    myServo.write(90); // Stop servo for denied access
    delay(500);
  }
}
