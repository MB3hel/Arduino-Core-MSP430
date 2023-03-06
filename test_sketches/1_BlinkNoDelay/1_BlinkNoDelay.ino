// Setup: Two LEDs onboard launchpad
// Tests digitalWrite, digitalRead, millis, micros


#define LED1      2
#define LED2      14
#define RATE1     (500)
#define RATE2     (250 * 1000L)

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
}

void loop() {
  static unsigned long last1 = 0;
  static unsigned long last2 = 0;

  if(millis() - last1 >= RATE1){
    digitalWrite(LED1, !digitalRead(LED1));
    last1 = millis();
  }

  if(micros() - last2 >= RATE2){
    digitalWrite(LED2, !digitalRead(LED2));
    last2 = micros();
  }
}
