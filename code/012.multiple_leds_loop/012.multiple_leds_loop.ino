/**
 * Utiliser les tableaux (array) et les boucles 
 * pour controler plusieurs leds connectées à des bnroches diffiérentes de la carte 
 */
 // instruction au compilateur
#define NBR_LEDS 6
// définir un tableau (array) de références aux broches sur lesquelles 
int leds_pins[] = {0,1,2,3,4,5};
void setup() {

  /* initialiser les broches en sortie */
  // mauvaise méthode : 
  // pinMode(0, OUTPUT);
  // pinMode(1, OUTPUT);
  // pinMode(2, OUTPUT);
  // pinMode(3, OUTPUT);
  // pinMode(4, OUTPUT);
  // pinMode(5, OUTPUT);

  // méthode correcte
  for(int i = 0; i < NBR_LEDS; i++){
    pinMode(leds_pins[i], OUTPUT);
  }

}

void loop() {
  for(int i = 0; i < NBR_LEDS; i++){
    digitalWrite(leds_pins[i], HIGH);
    delay(30);
  }
  for(int i = NBR_LEDS-1; i >= 0; i--){
    digitalWrite(leds_pins[i], LOW);
    delay(30);
  }

}
