#include <dht11.h>        //引用dht11库文件，使得下面可以调用相关参数
#define DHT11PIN 2      //定义温湿度针脚号为2号引脚
dht11 DHT11;        //实例化一个对象



int red=4;//RGB灯的3个引脚口
int green=5;
int blue=6;
//设置成绿灯
void setcolorgreen(){
  analogWrite(red,255);     
  analogWrite(green,0);   //可以随意设置开启关闭哪些灯，搭配出不同组合有不同颜色
  analogWrite(blue,255); 
}
//设置成红灯
void setcolorred(){
  analogWrite(red,0);     
  analogWrite(green,255); 
  analogWrite(blue,255); 
}


void setup(){
Serial.begin(9600);
pinMode(DHT11PIN,OUTPUT);                   //定义输出口
pinMode(red,OUTPUT);
pinMode(green,OUTPUT);
pinMode(blue,OUTPUT);

     }

void loop(){

int chk = DHT11.read(DHT11PIN);                 //将读取到的值赋给chk
int tem=(float)DHT11.temperature;               //将温度值赋值给tem
int hum=(float)DHT11.humidity;                   //将湿度值赋给hum
int value=50;    //你设定的值，超过什么时候可以改
Serial.println(hum);
delay(100);
 if(hum<value)
 {
  setcolorgreen();
  Serial.println("湿度正常，目前是");
  Serial.println(hum);

  delay(100);
  }

else{
  setcolorred();
  Serial.println("湿度不正常，目前是");
  Serial.println(hum);
  delay(100);
  }

     



}
