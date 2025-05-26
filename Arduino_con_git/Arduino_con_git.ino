#include <DHT.h>

// Definir el pin donde está conectado el sensor DHT22
#define DHTPIN 2     // Cambia este número al pin que estés usando

// Definir el tipo de sensor (DHT22)
#define DHTTYPE DHT22

// Inicializar el sensor DHT
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Iniciar comunicación serial
  Serial.begin(9600);
  Serial.println("Iniciando lectura de DHT22...");
  
  // Iniciar el sensor
  dht.begin();
}

void loop() {
  // Esperar entre lecturas (el DHT22 necesita al menos 2 segundos)
  delay(2000);

  // Leer humedad
  float h = dht.readHumidity();
  // Leer temperatura en Celsius
  float t = dht.readTemperature();
  // Leer temperatura en Fahrenheit (opcional)
  float f = dht.readTemperature(true);

  // Verificar si las lecturas fallaron
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Error al leer el sensor DHT22!");
    return;
  }

  // Calcular índice de calor (sensación térmica) en Celsius
  float hic = dht.computeHeatIndex(t, h, false);
  // Calcular índice de calor en Fahrenheit (opcional)
  float hif = dht.computeHeatIndex(f, h);

  // Mostrar los datos por el monitor serial
  Serial.print("Humedad: ");
  Serial.print(h);
  Serial.print("%\t");
  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.print("°C\t");
  Serial.print(f);
  Serial.print("°F\t");
  Serial.print("Índice de calor: ");
  Serial.print(hic);
  Serial.print("°C\t");
  Serial.print(hif);
  Serial.println("°F");
}