#include <Servo.h>
#include "Wire.h"
#include "I2Cdev.h"
#include "HMC5883L.h"

Servo servoMotor;
HMC5883L magnetometro;


int pinServo = 9;
//String inString = "";
int16_t mx=0, my=0, mz=0;
//int sumX = 0, sumY = 0, sumZ = 0;
double meanX, meanY, meanZ;   

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  servoMotor.attach(pinServo);

  Serial.println("Inicializando Magnetometro...");
    //Inicializamos la comunicación I2C y el magnetómetro
  Wire.begin();
  magnetometro.initialize();
 
}

void loop() {
  // put your main code here, to run repeatedly:

  for(int i=0;i<=180;i=i+30){
      servoMotor.write(i);
      double sumX = 0, sumY = 0, sumZ = 0;
      //delay(5000);
      // se cambia por un while, example
      for(int j=0;j<5;j++){
        magnetometro.getHeading(&mx, &my, &mz);
        Serial.println(mx);
        //Serial.println(my);
        //Serial.println(mz);
        sumX = sumX + mx; sumY = sumY + my; sumZ = sumZ + mz;      
        delay(500); 
      }
      meanX = sumX/5; meanY = sumY/5; meanZ = sumZ/5;
      Serial.print("Angulo:");
      Serial.println(i);
      Serial.print("meanx:");
      Serial.print(meanX); 
      Serial.print("\tmeany:");
      Serial.print(meanY);
      Serial.print("\tmeanz:");
      Serial.println(meanZ);
      
 }
   for(int i=180;i>=0;i=i-30){
      servoMotor.write(i);
      double sumX = 0, sumY = 0, sumZ = 0;
      //delay(5000);
      // se cambia por un while, example
      for(int j=0;j<5;j++){
        magnetometro.getHeading(&mx, &my, &mz);
        //Serial.println(mx);
        //Serial.println(my);
        //Serial.println(mz);
        sumX = sumX + mx; sumY = sumY + my; sumZ = sumZ + mz;      
        delay(500); 
      }
      meanX = sumX/5; meanY = sumY/5; meanZ = sumZ/5;
      Serial.print("Angulo:");
      Serial.println(i);
      Serial.print("meanx:");
      Serial.print(meanX); 
      Serial.print("\tmeany:");
      Serial.print(meanY);
      Serial.print("\tmeanz:");
      Serial.println(meanZ);
 }  
 delay(5000);
}