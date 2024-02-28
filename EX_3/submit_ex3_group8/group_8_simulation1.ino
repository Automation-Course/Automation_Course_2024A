// C++ code
//
#include <Adafruit_LiquidCrystal.h>
#include <Servo.h>

#define TempSensor A0
#define servoPin 3
#define Temp_Indicator_Light 10
#define buttonDayWork A1

Adafruit_LiquidCrystal lcd_screen(0);
Servo ACisOn;
int TempLightBrightness;
double temp;
int Temp1_input ;
int angle = 90; 
int buttonState;
bool heat;

void setup()
{
lcd_screen.begin(16, 2);
pinMode(TempSensor, INPUT);
pinMode(Temp_Indicator_Light,OUTPUT);
pinMode(buttonDayWork, INPUT);
ACisOn.attach(servoPin);
ACisOn.write(0);
Serial.begin(9600);


}

void loop(void)
{ 
 buttonState = analogRead(buttonDayWork);
    Serial.print("Button state: ");
    Serial.println(buttonState);

if (buttonState != 0) {
  
  	    //Temp1_input = rand() % 120; // (120=~ 60/0.488.to set 60 as the upper bound of  random temoeratures)
       //temp=Temp1_input*0.4882;// convert the analog volt to its temperature equivalent


        //**if you want to check how the AC is 
        //moving between random temps, 
        //put the following 2 sentenses in //
        //and remove the // from this 2 upper sentenses**
  
      	Temp1_input = analogRead(TempSensor)*0.4882;
       	temp = map(Temp1_input, 0, 1023, -10, 60);
       	Serial.print("Temperature read: ");
        Serial.println(temp);
        TempCheck(temp);
    } 
  else{
    ACisOn.write(90);
    printScreen("bye bye! AC is OFF ");
  } 
delay(4000);
 
}
  
void TempCheck(double temp)
{
    if (temp >= 23 and temp <= 25) {
        printScreen("The AC Is Off ");
        TempLightBrightness = 0;    // Set no brightness
        digitalWrite(Temp_Indicator_Light, TempLightBrightness);// Turn off the light
        ACisOn.write(90);
      delay(4000);
    } 
  else if (temp < 23) {
        printScreen("AC on: HEATING mode");
        heat =true;
        TurnOnAC(temp);
        TempLightBrightness = 255;  // full brightness
        digitalWrite(Temp_Indicator_Light, TempLightBrightness);
    } else if (temp > 25) {
        printScreen("AC on: COOLING mode");
        heat =false;
        TurnOnAC(temp);
        TempLightBrightness = 255;  // full brightness
        digitalWrite(Temp_Indicator_Light, TempLightBrightness);
    }
  
    ACisOn.write(angle); 
    Serial.print("Brightness: ");
    Serial.println(TempLightBrightness);
}

void TurnOnAC(double temp) {
 
      if (heat) {
        angle += 10;
       // ACisOn.write(angle);
        Serial.println("HEATING - TURN right");
        Serial.print("Angle: ");
        Serial.println(angle);
        //delay(8000); 
        //angle = 0;
        //ACisOn.write(angle);

    } else {
        angle -= 10;
      //  ACisOn.write(angle);
        Serial.println(" COOLING- TURN left");
        Serial.print("Angle: ");
        Serial.println(angle);
        //delay(8000); 
        //angle = 0;
    }
    ACisOn.write(angle);
    delay(4000);
 	if(angle==180)heat=false;
 	if(angle==0)heat=true;
  
}

void printScreen (String print){
lcd_screen.setCursor(0, 1);
lcd_screen.print(print);
lcd_screen.setBacklight(1);

}
