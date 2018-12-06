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

String deviceId = String(MY_DEVICE_ID);
String deviceToken = String(MY_DEVICE_TOKEN);
ATTDevice device(deviceId, deviceToken);


int ledPin = 8;

void setup() {
  Serial.begin(115200);
  while(!Serial);
 
  pinMode(ledPin, OUTPUT);
  
  while(status != WL_CONNECTED){
    Serial.print("tentative de connexion au réseau wifi ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
  }
  delay(1000);
  while(!device.connect(&wifi, httpServer)){
    Serial.println("tentative de connexion au serveur distant");
   
  }
  // ajouter un asset au device 
  device.addAsset("led", "led", "light emitting diode", "actuator", "boolean");
  while(!device.subscribe(pubSub)){
    Serial.println("tentative de connexion au broker mqtt");
  }
   

}

void loop() {
  device.process(); // attend les messages entrants
}

void callback(char* topic, byte* payload, unsigned int length){
  Serial.println("Message mqtt recu");
  // définition d'une variable de type chaine de caractère
  String msgString;

  // récupération du nom de l'asset (savoir si c'est bien à nousu qu'on parle)
  String assetName = device.getAssetName(topic, strlen(topic));
  
  // manipulation du message reçu pour le rendre plus facilement traitable
  {
     char message_buff[length+1];
     strncpy(message_buff, (char*)payload, length);
     message_buff[length] = '\0';

     msgString = String(message_buff);
     msgString.toLowerCase();

     Serial.print("Payload: ");
     Serial.println(msgString);
     Serial.print("Topic : ");
     Serial.println(topic);
  }

  // traitement du contenu du message reçu
  if(assetName == "led"){
    if(msgString.indexOf("false") > -1){
      digitalWrite(ledPin, LOW);
      device.send("false", "led");
    }else if(msgString.indexOf("true") > -1){
      digitalWrite(ledPin, HIGH);
      device.send("true", "led");
    }
  }
 
}
