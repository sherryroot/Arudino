#include <MPU6050.h>

#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"
#include <Servo.h>
MPU6050 accelgyro;

int16_t ax, ay, az;
int16_t gx, gy, gz;
int16_t h;
int16_t m;
int16_t n;
int16_t p;

Servo myservo;  // create servo object to control a servo
int potpin = 0;  // analog pin used to connect the potentiometer
int pos = 0; 

#define LED_PIN 13
bool blinkState = false;


#include "SR04.h"
#define TRIG_PIN 2
#define ECHO_PIN 3
#include "LedControl.h"
SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);
long a;
LedControl lc=LedControl(10,9,8,1);
int bai=0;
int shi=0;
int ge=0;
void displaynumber(void)
{
 // lc.setChar(0,0,0,false);
 // lc.setChar(0,1,1,false);
 // lc.setChar(0,2,2,false);
 
  lc.setChar(0,3,ge,false);
  lc.setChar(0,4,shi,false);
  lc.setChar(0,5,bai,false);
  Serial.println("@@@@@@@@");
  Serial.println(bai);
  Serial.println(shi);
  Serial.println(ge);
 // lc.setChar(0,6,6,false);
//  lc.setChar(0,7,7,false);
}

void setup() {
  lc.shutdown(0,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,15);
  /* and clear the display */
  lc.clearDisplay(0);
   //sherry Serial.begin(34800);
   Serial.begin(9600);
   Serial.println("Example written by Coloz From Arduin.CN");
   delay(1000);
  
    // join I2C bus (I2Cdev library doesn't do this automatically)
    Wire.begin();
 myservo.attach(7);
    // initialize serial communication
    // (38400 chosen because it works as well at 8MHz as it does at 16MHz, but
    // it's really up to you depending on your project)
  // sherry_ Serial.begin(115200);

    // initialize device
    Serial.print("sherry______************************___________");
    Serial.println("Initializing I2C devices...");
    accelgyro.initialize();

    // verify connection
    Serial.println("Testing device connections...");

    Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

    // configure Arduino LED for
    pinMode(LED_PIN, OUTPUT);
}

void loop() {
    // read raw accel/gyro measurements from device
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    // these methods (and a few others) are also available
    //accelgyro.getAcceleration(&ax, &ay, &az);
    //accelgyro.getRotation(&gx, &gy, &gz);
    // display tab-separated accel/gyro x/y/z values

    blinkState = !blinkState;
    digitalWrite(LED_PIN, blinkState);

   a=sr04.Distance();
   bai=a/100;
   shi=a/10%10;
   ge=a%10;
     // delay(50);
   displaynumber();
      
    m=ax/16382;
    n=ay/16382;
    p=az/16382;
    h=sqrt(m^2+n^2+p^2);
  Serial.print("###########");

  Serial.println(a);
  Serial.print(h); Serial.print("**********");
  Serial.print("\n");
  
     if(bai<1){ if (h>0)
    {
      loo();
     
      
     }}else{   displaynumber();}
   
}
void loo() {
  for (pos = 0; pos <= 180; pos -= 10)
  { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    
   // myservo.write(pos);  
        myservo.write(pos); 
      Serial.print("pos is");// tell servo to go to position in variable 'pos'
        Serial.print(pos);
  // delay(300);                       // waits 15ms for the servo to reach the position
  }
}
