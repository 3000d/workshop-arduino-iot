#define LED_PIN 12
#define BTN_PIN 8

bool prevState = LOW;
bool ledState  = LOW;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BTN_PIN, INPUT);
  Serial.begin(9600);

}

void loop() {
  bool state = digitalRead(BTN_PIN);

  if (state != prevState) {
    if (state == HIGH) {   
      ledState = ! ledState;
      digitalWrite(LED_PIN, ledState);
      Serial.println("on");
    }
    delay(50);
  }
  prevState = state;

}

