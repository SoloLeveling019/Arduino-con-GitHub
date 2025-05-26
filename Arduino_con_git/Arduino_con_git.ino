const int LED_PIN = 9;
float brillo = 0, paso = 0.5;
bool sube = true, pausa = false;
unsigned long t0 = 0, pausaT0 = 0;
const float gamma = 2.2;

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  unsigned long t = millis();
  if (pausa && t - pausaT0 >= 500) pausa = false;

  if (!pausa && t - t0 >= 10) {
    t0 = t;
    analogWrite(LED_PIN, pow(brillo / 255.0, gamma) * 255);
    brillo += sube ? paso : -paso;
    if (brillo >= 255 || brillo <= 0) {
      brillo = constrain(brillo, 0, 255);
      sube = !sube;
      pausa = true;
      pausaT0 = t;
    }
  }
}
