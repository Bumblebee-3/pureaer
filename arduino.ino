#include "MQ7.h"
#include "MQ2.h"
#include "CO2Sensor.h"
#include <SoftwareSerial.h>
SoftwareSerial espSerial(5, 6);

#define mgP A0
#define mq7p A1
#define mq2p A2
#define mq135p A3
#define fanP 7

const String secretKey = "";


CO2Sensor co2Sensor(mgP, 0.99, 100);
MQ7 mq7(mq7p,3.7);
MQ2 mq2(mq2p);
  

void setup() {
  Serial.begin(9600);
  pinMode(fanP,OUTPUT);
  //Serial.println("=== Initialized ===");
  co2Sensor.calibrate();
  mq2.begin();
  Serial.begin(115200);
  espSerial.begin(115200);
}

float getCO2(){
  float val = co2Sensor.read();
  return val;
}
float getCO(){
  float val = mq7.getPPM();
  return val;
}

float getLPG(){
  float val = mq2.readLPG();
  return val;
}

float getSmoke(){
  float val = mq2.readSmoke();
  return val;
}

float getAQI(){
  float val = analogRead(mq135p);
  return val;
}


void loop() {
  float co2,co,lpg,smoke,aqi;
  co2=getCO2();
  co=getCO();
  lpg=getLPG();
  smoke=getSmoke();
  aqi=getAQI();
  Serial.flush();
  Serial.print("/api/setAll/"+String(co2)+"/"+String(co)+"/"+String(lpg)+"/"+String(smoke)+"/"+String(aqi)+"/");
  Serial.flush();
  Serial.end();   /*end serial communication*/
  Serial.begin(115200);  /*clear serial buffer*/


  if(co2>=500.00||co>=5.00||lpg>=0.02||smoke>=0.02||aqi>=70.00){
    digitalWrite(fanP,HIGH);
  }else{
    digitalWrite(fanP,HIGH);
  }
  delay(5000); //5000
}
