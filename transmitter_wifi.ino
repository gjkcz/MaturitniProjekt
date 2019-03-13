/*
* Arduino Wireless Communication Tutorial
*     Example 1 - Transmitter Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10); // CE, CSN

struct joyRead {
  byte X;
  byte Y;
};

joyRead Joystick;

const byte address[6] = "00001";

void setup() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();

  Serial.begin(9600);
}

void loop() {

  Joystick.X = map(analogRead(A0), 0, 1023, 0, 255);
  Joystick.Y = map(analogRead(A1), 0, 1023, 0, 255);

  radio.write(&Joystick, sizeof(joyRead));

  Serial.println(Joystick.X);
  Serial.println(Joystick.Y);
    
  delay(10);
}
