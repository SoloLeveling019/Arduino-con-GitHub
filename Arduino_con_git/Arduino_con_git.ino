int led = 9;              // Pin conectado al LED
float brillo = 0;         // Nivel de brillo (como número decimal para más suavidad)
float paso = 0.5;         // Incremento pequeño para una transición suave
bool subiendo = true;     // Dirección del cambio

unsigned long tiempoAnterior = 0;
unsigned int intervalo = 10; // Tiempo entre pasos

void setup() {
  pinMode(led, OUTPUT);
}

void loop() {
  unsigned long tiempoActual = millis();

  // Solo actualiza si ha pasado el intervalo
  if (tiempoActual - tiempoAnterior >= intervalo) {
    tiempoAnterior = tiempoActual;

    // Aplicamos curva cuadrática para un efecto más natural de "respiración"
    float brilloCurvado = pow(brillo / 255.0, 2.2) * 255.0;
    analogWrite(led, (int)brilloCurvado);

    // Cambia el brillo
    if (subiendo) {
      brillo += paso;
      if (brillo >= 255) {
        brillo = 255;
        subiendo = false;
        delay(500); // Pausa en brillo máximo
      }
    } else {
      brillo -= paso;
      if (brillo <= 0) {
        brillo = 0;
        subiendo = true;
        delay(500); // Pausa en brillo mínimo
      }
    }
  }
}
