int led = 9;
int brillo = 128;

void setup() {
  pinMode(led, OUTPUT);
}

void loop() {
  analogWrite(led, brillo);
  delay(1000);
}