#define LED_PIN 12
#define BTN_PIN 8

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BTN_PIN, INPUT);
}

void loop() {
  bool btn_state = digitalRead(BTN_PIN);
  if(btn_state == HIGH){
    digitalWrite(LED_PIN, HIGH);
  }else{
    digitalWrite(LED_PIN, LOW);
  }
}
