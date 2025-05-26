<<<<<<< HEAD
int led = 9;            // Pin conectado al LED
int brillo = 0;         // Nivel inicial de brillo
int paso = 5;           // Cuánto cambia el brillo por ciclo

void setup() {
  pinMode(led, OUTPUT); // Configura el pin como salida
}

void loop() {
  analogWrite(led, brillo);  // Escribe el nivel PWM al LED
  brillo += paso;            // Ajusta el brillo

  // Cambia la dirección del brillo al llegar a los extremos
  if (brillo <= 0 || brillo >= 255) {
    paso = -paso;            // Invierte la dirección del cambio
=======
const int LED_PIN = 9;               // Pin conectado al LED
float brillo = 0;                    // Brillo actual (0 a 255)
float incremento = 0.5;              // Paso de cambio
bool subiendo = true;                // Dirección del cambio (true = subiendo)

unsigned long ultimoTiempo = 0;      // Último tiempo de actualización
const unsigned int intervalo = 10;   // Tiempo entre pasos (ms)
unsigned long pausaInicio = 0;       // Tiempo cuando empieza la pausa
const unsigned int pausaDuracion = 500; // Duración de la pausa (ms)
bool enPausa = false;                // Indicador de pausa

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  unsigned long ahora = millis();

  if (enPausa) {
    // Esperar la pausa antes de continuar
    if (ahora - pausaInicio >= pausaDuracion) {
      enPausa = false;
      ultimoTiempo = ahora;
    }
    return; // No hacer nada más mientras esté en pausa
  }

  if (ahora - ultimoTiempo >= intervalo) {
    ultimoTiempo = ahora;

    // Aplica curva gamma (más natural para el ojo humano)
    float gamma = 2.2;
    float brilloCorregido = pow(brillo / 255.0, gamma) * 255.0;
    analogWrite(LED_PIN, (int)brilloCorregido);

    // Ajusta el brillo
    if (subiendo) {
      brillo += incremento;
      if (brillo >= 255) {
        brillo = 255;
        subiendo = false;
        enPausa = true;
        pausaInicio = ahora;
      }
    } else {
      brillo -= incremento;
      if (brillo <= 0) {
        brillo = 0;
        subiendo = true;
        enPausa = true;
        pausaInicio = ahora;
      }
    }
>>>>>>> e80113481010e613e470812a7123e4e603daf17c
  }

  delay(30); // Controla la velocidad del efecto
}