/*
 Based on WebClient
 Exemple implementation of PubSubClient for Mkr1000
 created 13 July 2010
 by dlf (Metodo2 srl)
 modified 31 May 2012
 by Tom Igoe
 */

#include <PubSubClient.h>
#include <SPI.h>
#include <WiFi101.h>
#include "arduino_secrets.h" 
///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)


int status = WL_IDLE_STATUS;


WiFiClient wifiClient;
PubSubClient client(wifiClient);
// insérer l'adresse IP du serveur
IPAddress server(xxx,xxx,xxx,xxx);

bool prevState = HIGH;

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);

  // configuration du client avec l'adesse et le port du serveur (broker) mqtt
  client.setServer(server, 1883);
  pinMode(1, INPUT_PULLUP);
  
  // attempt to connect to WiFi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(5000);
  }
  Serial.println("Connected to wifi");
  printWiFiStatus();

  
}

void loop() {
  if(!client.connected()){
    reconnect();
  }
  
  client.loop();
  bool state = digitalRead(1);
  if(state != prevState){

    if(state == LOW){
      client.publish("/topic/commande", "1");
      delay(100);
    }
  }
  prevState = state;
  
}

void reconnect(){
  // boucle tant que le client n'est pas connecté
  while(!client.connected()){
    Serial.println("tentative de connexion au serveur mqtt");
    if(client.connect("gbe_mkr1000")){
      Serial.println("connecté");
      
    }else{
      Serial.print("echec, rc=");
      Serial.print(client.state());
      Serial.print(" nouvelle tentative dans 5 secondes");
      delay(5000);
    }
  }
}

void printWiFiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
