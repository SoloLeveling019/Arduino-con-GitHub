#include <DHT.h>

#define DHTPIN 5      // Pin donde está conectado el sensor
#define DHTTYPE DHT22 // Tipo de sensor

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println("Lectura de temperatura con DHT22");
  dht.begin();
}

void loop() {
  delay(2000); // Espera entre lecturas
  
  float temperaturaC = dht.readTemperature(); // Lectura en Celsius
  // float temperaturaF = dht.readTemperature(true); // Para Fahrenheit

  if (isnan(temperaturaC)) {
    Serial.println("Error al leer la temperatura!");
    return;
  }

  Serial.print("Temperatura: ");
  Serial.print(temperaturaC);
  Serial.println("°C");
  
  // Si quieres mostrar Fahrenheit también:
  // Serial.print(" | ");
  // Serial.print(temperaturaF);
  // Serial.println("°F");
}
