#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN

struct joyReceaved{
  byte X;
  byte Y;
};
joyReceaved joystick;

int Xaxis = 124;
int x = 0;
int stepsX= 11;
int dirX = 10;
int EnableX = 12;

int Yaxis = 124;
int y = 0;
int stepsY = 4;
int dirY = 3;
int EnableY = 5;

const byte address[6] = "00001";

void setup() {

  pinMode(stepsX, OUTPUT);
  pinMode(dirX, OUTPUT);
  pinMode(EnableX, OUTPUT);
  digitalWrite(EnableX, HIGH);
  pinMode(26, INPUT_PULLUP);
  pinMode(27, INPUT_PULLUP);

  pinMode(stepsY, OUTPUT);
  pinMode(dirY, OUTPUT);
  pinMode(EnableY, OUTPUT);
  digitalWrite(EnableY, HIGH);
  pinMode(28, INPUT);
  pinMode(29, INPUT);
  
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}


unsigned long receaveTime = 0;
void data_receaving(){
  while(radio.available()){
    radio.read(&joystick, sizeof(joyReceaved));
    receaveTime = millis();
  }
}

void loop() {

  data_receaving();

  unsigned long Time = millis();
  if(Time - receaveTime > 1000){
    digitalWrite(EnableX, HIGH);
    digitalWrite(EnableY, HIGH);
  }

  Xaxis = joystick.X;  
  Yaxis = joystick.Y;

  if(Xaxis < 100){
    if(!digitalRead(30)){}
    else{
    x = map(Xaxis, 0, 100, 0, 10);
    digitalWrite(EnableX, LOW);
    digitalWrite(dirX, HIGH);
    digitalWrite(stepsX, HIGH);   
    delay(x);                      
    digitalWrite(stepsX, LOW);    
    delay(x);
    }
  }

  if(Xaxis > 150){
    if(!digitalRead(28)){}
    else{
    x = map(Xaxis, 150, 255, 10, 0);
    digitalWrite(EnableX, LOW);
    digitalWrite(dirX, LOW);
    digitalWrite(stepsX, HIGH);   
    delay(x);                      
    digitalWrite(stepsX, LOW);    
    delay(x);
    }
  }

 if(Xaxis > 100 && Xaxis < 150){
    digitalWrite(EnableX, HIGH);
  }

  if(Yaxis < 100){
    if(!digitalRead(27)){}
    else{
    y = map(Yaxis, 0, 100, 0, 10);
    digitalWrite(EnableY, LOW);
    digitalWrite(dirY, HIGH);
    digitalWrite(stepsY, HIGH);   
    delay(y);                      
    digitalWrite(stepsY, LOW);    
    delay(y);
    }
  }

  if(Yaxis > 150){
    if(!digitalRead(26)){}
    else{
    y = map(Yaxis, 150, 255, 10, 0);
    digitalWrite(EnableY, LOW);
    digitalWrite(dirY, LOW);
    digitalWrite(stepsY, HIGH);   
    delay(y);                      
    digitalWrite(stepsY, LOW);    
    delay(y);
    }
  }

  if(Yaxis > 100 && Yaxis < 150){
    digitalWrite(EnableY, HIGH);
  }

  Serial.println(Xaxis);
  Serial.println(Yaxis);
}
