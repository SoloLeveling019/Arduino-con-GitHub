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
  }

  delay(30); // Controla la velocidad del efecto
}