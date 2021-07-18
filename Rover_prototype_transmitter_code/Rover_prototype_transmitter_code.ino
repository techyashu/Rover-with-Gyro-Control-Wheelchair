
#include <SPI.h>  

#include "RF24.h"

#include <Wire.h>
#include <I2Cdev.h>
#include <MPU6050.h>


RF24 myRadio (7, 8);

struct package

{

  int id=0;

  //float temperature = 0.0;

 // char  text[100] ="empty";

};


byte addresses[][6] = {"0"};




typedef struct package Package;

Package data;

MPU6050 mpu;
int16_t ax, ay, az, gx, gy, gz;
int vx, vy;


void setup()

{

  Serial.begin(9600);
 pinMode(A0, INPUT);
  Wire.begin();
  mpu.initialize();
  
        if (!mpu.testConnection()) 
        {
          while (1);
        }

  delay(1000);


  myRadio.begin();

  myRadio.setChannel(115);

  myRadio.setPALevel(RF24_PA_MAX);

  myRadio.setDataRate( RF24_250KBPS ) ;

 myRadio.openWritingPipe( addresses[0]);
 
 delay(1000);


}



void loop()  

{
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  vx = (gx - 200) / 200; // "-400" because the x axis of gyroscope give values about -350 while it's not moving. Change this value if you get something different using the TEST code, chacking if there are values far from zero.
  vy = -(gz - 200) / 200; // same here about "-200"

  int buttonState1 = analogRead(A0);

  if(vy<-30)
  {
    data.id=1;
    Serial.println("FORWARD");
  }
  
  if(vy>30)
  {
     data.id=2;
     Serial.println("BACKWARD");
  }

  
  if(vx<-30)
  {
    data.id=3;
    Serial.println("LEFT");
  }
  if(vx>30)
  {
     data.id=4;
    Serial.println("RIGHT");
  }

 if (buttonState1 >= 500) {
  data.id=5;
  Serial.println("STOP");
  
 } 

  myRadio.write(&data, sizeof(data));

  delay(10);

}
