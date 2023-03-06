// Setup: Two LEDs on launchpad. One builtin button (assumed to have external pullup) 
/         and one external button (using internal pullup)
// Tests digitalWrite, digitalRead using INPUT and INPUT_PULLUP mode


#define LED1      2
#define BTN1      5           // Uses INPUT (button builtin to launchpad)
#define LED2      14
#define BTN2      6           // Uses INPUT_PULLUP (button external to launchpad)

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(BTN1, INPUT);
  pinMode(BTN2, INPUT_PULLUP);
}

void loop() {
  digitalWrite(LED1, !digitalRead(BTN1));
  digitalWrite(LED2, !digitalRead(BTN2));
}
