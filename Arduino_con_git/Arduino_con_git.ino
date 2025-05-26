const int LED_PIN = 9;
float brillo = 0.0;
float paso = 0.5;
bool subiendo = true;
bool enPausa = false;

unsigned long tiempoAnterior = 0;
unsigned long tiempoPausa = 0;

const unsigned int intervalo = 10;
const unsigned int duracionPausa = 500;
const float gamma = 2.2;

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  unsigned long ahora = millis();

  if (enPausa && ahora - tiempoPausa >= duracionPausa) {
    enPausa = false;
  }

  if (!enPausa && ahora - tiempoAnterior >= intervalo) {
    tiempoAnterior = ahora;

    float corregido = pow(brillo / 255.0, gamma) * 255.0;
    analogWrite(LED_PIN, (int)corregido);

    brillo += subiendo ? paso : -paso;

    if (brillo >= 255.0 || brillo <= 0.0) {
      brillo = constrain(brillo, 0.0, 255.0);
      subiendo = !subiendo;
      enPausa = true;
      tiempoPausa = ahora;
    }
  }