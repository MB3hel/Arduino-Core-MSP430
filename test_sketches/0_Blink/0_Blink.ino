// Setup: LED onboard launchpad
// Tests digitalWrite, digitalRead, delay, and delayMicroseconds


#define LED     2

void setup() {
  pinMode(LED, OUTPUT);
}

void loop() {
  digitalWrite(LED, HIGH);
  delay(500);
  digitalWrite(LED, LOW);
  for(unsigned int i = 0; i < 100; ++i)
    delayMicroseconds(5000);
}
