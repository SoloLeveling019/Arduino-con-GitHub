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

// --- CÓDIGO AÑADIDO PARA MANEJO DE VERSIÓN ---
const String CURRENT_VERSION = "0.01";
String inputString = "";
bool stringComplete = false;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
  Serial.println("Sistema iniciado - Versión: " + CURRENT_VERSION);
  Serial.println("Introduce 'check' para verificar la versión o escribe la versión remota para comparar (ej: 0.02)");
}

void loop() {
  // --- Manejo de versión (nuevo) ---
  if (stringComplete) {
    if (inputString == "check") {
      Serial.println("Versión actual: " + CURRENT_VERSION);
      Serial.println("Visita https://github.com/SoloLeveling019/Arduino-con-GitHub para verificar actualizaciones");
    } else {
      Serial.println("Versión local:  " + CURRENT_VERSION);
      Serial.println("Versión ingresada: " + inputString);
      if (inputString != CURRENT_VERSION) {
        Serial.println("¡Hay una nueva versión disponible!");
        Serial.println("Descarga la actualización desde el repositorio GitHub");
      } else {
        Serial.println("Estás usando la versión más reciente");
      }
    }
    inputString = "";
    stringComplete = false;
  }

  // --- Código original del LED ---
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
}

// --- Función para recibir datos por Serial (nuevo) ---
void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    if (inChar == '\n') {
      stringComplete = true;
    } else {
      inputString += inChar;
    }
  }
}
