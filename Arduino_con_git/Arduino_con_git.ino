const int LED_PIN = 9;
float brillo = 0.0;
float incremento = 0.5;
bool subiendo = true;

unsigned long ultimoTiempo = 0;
const unsigned int intervalo = 10;

unsigned long pausaInicio = 0;
const unsigned int pausaDuracion = 500;
bool enPausa = false;

const float gamma = 2.2;  // Se define una vez

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  unsigned long ahora = millis();

  if (enPausa) {
    if (ahora - pausaInicio >= pausaDuracion) {
      enPausa = false;
      ultimoTiempo = ahora;
    }
    return;
  }

  if (ahora - ultimoTiempo >= intervalo) {
    ultimoTiempo = ahora;

    // Corrige el brillo con curva gamma
    float brilloNormalizado = brillo / 255.0;
    float brilloCorregido = pow(brilloNormalizado, gamma) * 255.0;
    analogWrite(LED_PIN, static_cast<int>(brilloCorregido));

    // Cambiar dirección si llega al máximo o mínimo
    brillo += subiendo ? incremento : -incremento;
    brillo = constrain(brillo, 0.0, 255.0);

    if (brillo == 255.0 || brillo == 0.0) {
      subiendo = !subiendo;
      enPausa = true;
      pausaInicio = ahora;
    }
  }
}
