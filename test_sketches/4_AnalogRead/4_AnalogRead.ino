// Setup: Potentiometer connected between VCC and GND. Signal to an analog pin. Two LEDs on launchpad
// Tests: analogRead

#define POT       A0
#define LED1      2
#define LED2      14
#define ADC_MAX   1024



void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
}

void loop() {
  int val = analogRead(POT);
  if(val >= (ADC_MAX / 2)){
    digitalWrite(LED1, HIGH);
  }else{
    digitalWrite(LED1, LOW);
  }
  /*if(val >= (2 * ADC_MAX / 3)){
    digitalWrite(LED2, HIGH);
  }else{
    digitalWrite(LED2, LOW);
  }*/
}
