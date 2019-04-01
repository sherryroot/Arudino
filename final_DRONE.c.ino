#include <MPU6050.h>
#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"
#include <Servo.h>
MPU6050 accelgyro;
#include <SoftwareSerial.h>
//libraries finish
//
float utrl1_dist;//distance in utrl
float utrl2_dist;

const int utrl1_Echo=3;
const int utrl1_Trig=2;
const int utrl2_Echo=7;
const int utrl2_Trig=6;//utrl set pin
//
int16_t ax,ay,az,gx,gy,gz;//acccel 
//
SoftwareSerial BT(10,11);
struct msg{
  float utrl1;
  float utrl2;
  //float accel;
  
  };//发送包结构
  
  //__________________UTRL_____________________________________
//initialize
  // utrl initial
  void utrl_init(int Echo,int Trig){
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
  }
//execution
  //utrl test distance
  float utrl_dist(int Trig,int Echo){
    float temp;
    float cm;
    //给Trig发送一个低高低的短时间脉冲,触发测距
  digitalWrite(Trig, LOW); //给Trig发送一个低电平
  delayMicroseconds(2);    //等待 2微妙
  digitalWrite(Trig,HIGH); //给Trig发送一个高电平
  delayMicroseconds(10);    //等待 10微妙
  digitalWrite(Trig, LOW); //给Trig发送一个低电平
  
  temp = float(pulseIn(Echo, HIGH)); //存储回波等待时间,
  //pulseIn函数会等待引脚变为HIGH,开始计算时间,再等待变为LOW并停止计时
  //返回脉冲的长度
  
  //声速是:340m/1s 换算成 34000cm / 1000000μs => 34 / 1000
  //因为发送到接收,实际是相同距离走了2回,所以要除以2
  //距离(厘米)  =  (回波时间 * (34 / 1000)) / 2
  //简化后的计算公式为 (回波时间 * 17)/ 1000
  
  cm = (temp * 17 )/1000; //把回波时间换算成cm
  return cm;
  }
  //____________________Bluetooth______________________________________
  //
  void BT_init(){    // 如果是HC-05，請改成38400
 //  Serial.begin(38400);
   BT.begin(9600);
   Serial.println("baud is 9600 ok");
    }
    
   void BT_exe(){

  //    BT.write();
      Serial.write("//receieve msg//");//发送test}
    };
//____________________accelerate______________________________________
void mpu_init(){
  Wire.begin();
 // Serial.begin(9600);
  Serial.println("Initializing I2C devices...");
  accelgyro.initialize();
   // verify connection
    Serial.println("Testing device connections...");
    Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

  }
//____________
int count=0;
int f;
//____________

//********************************************************
void setup(){
  Serial.begin(9600);//start serial,set up bode
  utrl_init(utrl1_Echo,utrl1_Trig);
  utrl_init(utrl2_Echo,utrl2_Trig);
  mpu_init();
  BT_init();
  }

  //

void loop(){
  //超声波测距
  utrl1_dist=utrl_dist(utrl1_Trig,utrl1_Echo);
  utrl2_dist=utrl_dist(utrl2_Trig,utrl2_Echo);


  accelgyro.getMotion6(&ax,&ay,&az,&gx,&gy,&gz);//get mpu6050 value
  // Serial.println(ax);
  // 
//发送data
  // BT_exe();
  Serial.println(ax);
  char t=ax;

  f=count%6;
  Serial.println(f);
  if(f==0){
    BT.write("ultra1:");}
   if(f==1){
    BT.write(t);}
   if(f==2){
    BT.write("ultra2:");}
   if(f==3){
    BT.write(t);}
   if(f==4){
    BT.write("MPU6050:");} 
      if(f==5){
    BT.write(t);}
  count=count+1;
 delay(500);
   
    
    
   
   
    
   
   delay(500);
  }
