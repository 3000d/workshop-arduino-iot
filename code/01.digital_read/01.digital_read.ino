void setup() {
  pinMode(1, INPUT_PULLUP);
  
}

void loop() {
  bool etatBouton = digitalRead(1);

  digitalWrite(6, etatBouton);

}
