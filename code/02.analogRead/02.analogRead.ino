void setup() {
  Serial.begin(9600);
  // modifie la résolution de l'ADC
  // analogReadResolution(12);
}

void loop() {
  int val = analogRead(A6);
  Serial.println(val);
  delay(500);

}
