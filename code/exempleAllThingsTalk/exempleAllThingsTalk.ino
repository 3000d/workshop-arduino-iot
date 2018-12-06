#include <WiFi101.h>
#include <PubSubClient.h>
#include <ATT_IOT.h>
#include "arduino_secrets.h"


#define httpServer "api.allthingstalk.io"
#define mqttServer "api.allthingstalk.io"
int port = 1883;

char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;

WiFiClient wifi;

void callback(char* topic, byte* payload, unsigned int length);
PubSubClient pubSub(mqttServer, 1883, callback, wifi);
int status = WL_IDLE_STATUS;


ATTDevice device;


void setup() {
  Serial.begin(115200);
  while(!Serial);

  while(status != WL_CONNECTED){
    Serial.print("tentative de connexion au réseau wifi ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
  }
  delay(1000);
  while(!device.connect(&wifi, httpServer)){
    Serial.println("tentative de connexion au serveur distant");
   
  }
  device.addAsset("MonPotar", "Potentiometer", "Pot value", "sensor", "integer");
  while(!device.subscribe(pubSub)){
    Serial.println("tentative de connexion au broker mqtt");
  }
   

}

void loop() {
  
  int val = analogRead(A6);

  device.send(String(val), "MonPotar");

  device.process();

  delay(5000);
  
}

void callback(char* topic, byte* payload, unsigned int length){
  Serial.println("Message mqtt recu");
  Serial.println(topic);
  Serial.println((char*)payload);
}
