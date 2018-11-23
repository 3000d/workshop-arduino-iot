void setup() {
  Serial.begin(9600);
  analogReadResolution(12);
}

void loop() {
  int pot_val = analogRead(A0);

  Serial.println(pot_val);

  delay(100);


}
