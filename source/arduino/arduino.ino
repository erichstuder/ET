#define DATA_READY_PIN 0

void setup() {
  pinMode(DATA_READY_PIN, OUTPUT);
}

void loop() {
  digitalWrite(DATA_READY_PIN, HIGH);
  delay(1000);
  digitalWrite(DATA_READY_PIN, LOW);
  delay(1000);
}
