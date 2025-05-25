int led = 9;
int brillo = 0;  // Comenzamos apagado
bool estado = false; // Estado del LED, false = apagado, true = encendido

void setup() {
  pinMode(led, OUTPUT);
}

void loop() {
  if (estado) {
    brillo = 255;  // Encender LED al máximo brillo
  } else {
    brillo = 0;    // Apagar LED
  }

  analogWrite(led, brillo);
  estado = !estado;  // Cambiar estado para el próximo ciclo
  delay(1000);       // Esperar 1 segundo
}
WAZAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
sale o nada 
