#include <DHT.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ThingSpeak.h>

DHT dht(D0,DHT11); 
WiFiClient Client; 


long channel_number= ; //Enter your channel number for thingspeak here'
const char WriteAPIkey[]= ; //Enter your Write API key for thingspeak here'

LED=D1; //LED
LDR=A0; //Light Dependent Resistor 
IR=D2; //Infrared Sensor
Buzzer=D3; //Buzzer
PIR=D4; //Passive IR sensor
SM=D5; //Soil Moisture Sensor
FS=D6; //Flow Sensor


void setup() 
{
  WiFi.begin("Wifi_SSID","PASSWORD"); //replace the wifi_ssid and password with your own network details'
  while(WiFi.status()!=WL_CONNECTED);
  {
    delay(300);
  }
  else
  {
    Serial.println("Succesfully Connected\n");
  }


  pinMode(LED,OUTPUT);
  pinMode(Buzzer,OUTPUT);
  pinMode(IR,INPUT);
  pinMode(LDR,INPUT);
  pinMode(PIR,INPUT);
  pinMode(FS,INPUT);
  pinMode(SM,OUTPUT);
  dht.begin();
  ThingSpeak.begin(client);
  Serial.begin(9600);
}

void loop() 
{
  int value=analogRead(LDR);
  if(LDR<200)
  {
    digitalWrite(LED,HIGH);

    int PIR_response=digitalRead(PIR);
    if(PIR_response=>1)
    {
      digitalWrite(Buzzer,HIGH);
    }
  }

  int FS_response=digitalRead(FS);
  int SM_response=digitalRead(SM);
  
  float t=dht.readTemperature();
  float h=dht.readHumidity();


  Serial.println("Humidity:"+(String)t);

  ThingSpeak.writeField(channel_number,1,t,WriteAPIkey);
  ThingSpeak.writeField(channel_number,2,h,WriteAPIkey);
  ThingSpeak.writeField(channel_number,3,FS_response,WriteAPIkey);
  ThingSpeak.writeField(channel_number,4,SM_response,WriteAPIkey);

}