Components Used:
Arduino board (UNO or similar)
PIR (Passive Infrared) sensor
LEDs (Green and Red)
Servo motor
Piezo buzzer
LCD display with I2C interface

Installation and Setup:
Connect the components as per the provided pin configurations in the code:
Green LED to pin 4
Red LED to pin 7
Piezo buzzer to pin 8
PIR sensor to pin 2
Servo motor to pin 12
LCD display using I2C communication (Address: 0x27, Rows: 16, Columns: 2)
Upload the provided Arduino sketch to your Arduino board using the Arduino IDE or any compatible software.
Once uploaded, power up the Arduino board and ensure that all components are functioning correctly.

Operation:
Upon startup, the system initializes and displays "Start Operation" on the LCD screen.
In normal operation (no motion detected):
Green LED is turned on.
LCD screen displays "Together We Will Win".
Servo motor continuously rotates.
When motion is detected by the PIR sensor:
Servo motor stops moving.
Green LED turns off, and the Red LED turns on to indicate an emergency situation.
LCD screen displays "Wakef Wakef !!!!" to alert the user.
Piezo buzzer emits a sound for 10 seconds to draw attention to the detected motion.
After 10 seconds of the emergency state, the system returns to normal operation, waiting for the next motion detection.