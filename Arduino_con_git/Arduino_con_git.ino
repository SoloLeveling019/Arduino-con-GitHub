int ledPin = 9;      // Pin PWM

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Incrementa el brillo
  for (int brightness = 0; brightness <= 255; brightness++) {
    analogWrite(ledPin, brightness);  // Escribe valor PWM (0-255)
    delay(10);                        // Pequeña pausa para ver el cambio
  }

  // Disminuye el brillo
  for (int brightness = 255; brightness >= 0; brightness--) {
    analogWrite(ledPin, brightness);
    delay(10);
  }
}
