
#include <SPI.h>  

#include "RF24.h"


RF24 myRadio (7, 8);

byte addresses[][6] = {"0"};


struct package

{
  int id=0;
};



typedef struct package Package;

Package data;



const int leftMotorBackward=6;
const int leftMotorForward=5;
const int rightMotorForward=4;
const int rightMotorBackward=3;


void setup() {

  Serial.begin(9600);
  Serial.println("Serial : ");

  delay(1000);

  myRadio.begin();  

  myRadio.setChannel(115);

  myRadio.setPALevel(RF24_PA_MAX);

  myRadio.setDataRate( RF24_250KBPS ) ;

  myRadio.openReadingPipe(1, addresses[0]);
  myRadio.startListening();

  
 pinMode(leftMotorBackward,OUTPUT);
 pinMode(leftMotorForward,OUTPUT);
 pinMode(rightMotorForward,OUTPUT);
 pinMode(rightMotorBackward,OUTPUT);

 Serial.begin(9600);
}


void loop() { 

  if ( myRadio.available())

  {

    while (myRadio.available())

    {

      myRadio.read( &data, sizeof(data) );

    }

    Serial.print("\nPackage:");

    Serial.print(data.id);

    Serial.print("\n");

      if (data.id == 1) forward();
      else if (data.id == 2) backward();
      else if (data.id == 3) left();
      else if (data.id == 4) right(); 
      else if(data.id == 5)freeze(); 
  }

     
}

 void forward()
 {
  digitalWrite(leftMotorForward,HIGH);
  digitalWrite(rightMotorForward,HIGH);
  digitalWrite(leftMotorBackward,LOW);
  digitalWrite(rightMotorBackward,LOW);
 }
 void right()
 {
  digitalWrite(leftMotorForward,HIGH);
  digitalWrite(rightMotorBackward,HIGH);
  digitalWrite(leftMotorBackward,LOW);
  digitalWrite(rightMotorForward,LOW);

 }
 void left()
 {
  digitalWrite(rightMotorForward,HIGH);
  digitalWrite(leftMotorBackward,HIGH);
  digitalWrite(rightMotorBackward,LOW);
  digitalWrite(leftMotorForward,LOW);
 }
  void backward()
 {
  digitalWrite(rightMotorForward,LOW);
  digitalWrite(leftMotorBackward,HIGH);
  digitalWrite(rightMotorBackward,HIGH);
  digitalWrite(leftMotorForward,LOW);
 }
 void freeze()
 {
  digitalWrite(leftMotorForward,LOW);
  digitalWrite(leftMotorBackward,LOW);
  digitalWrite(rightMotorForward,LOW);
  digitalWrite(rightMotorBackward,LOW);
 }
