#include <DHT.h>

#define DHTPIN 5      // Pin donde está conectado el sensor
#define DHTTYPE DHT22 // Tipo de sensor

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println("Lectura de humedad con DHT22");
  dht.begin();
}

void loop() {
  delay(2000); // Espera entre lecturas
  
  float humedad = dht.readHumidity();

  if (isnan(humedad)) {
    Serial.println("Error al leer la humedad!");
    return;
  }

  Serial.print("Humedad: ");
  Serial.print(humedad);
  Serial.println("%");
}
