const byte LED_PIN = 9;
const unsigned int FADE_INTERVAL = 10;
const unsigned int PAUSE_DURATION = 500;
const float GAMMA_VALUE = 2.2;
const float FADE_STEP = 0.5;

float brightness = 0.0;
bool isIncreasing = true;
bool isPaused = false;

unsigned long previousTime = 0;
unsigned long pauseStartTime = 0;

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  unsigned long currentTime = millis();

  handlePause(currentTime);
  
  if (!isPaused && (currentTime - previousTime >= FADE_INTERVAL)) {
    updateBrightness(currentTime);
  }
}

void handlePause(unsigned long now) {
  if (isPaused && (now - pauseStartTime >= PAUSE_DURATION)) {
    isPaused = false;
  }
}

void updateBrightness(unsigned long now) {
  previousTime = now;
  
  // Aplicar corrección gamma
  float gammaCorrected = pow(brightness / 255.0, GAMMA_VALUE) * 255.0;
  analogWrite(LED_PIN, (int)gammaCorrected);

  // Actualizar brillo
  brightness += isIncreasing ? FADE_STEP : -FADE_STEP;

  // Comprobar límites y cambiar dirección
  if (brightness >= 255.0 || brightness <= 0.0) {
    brightness = constrain(brightness, 0.0, 255.0);
    isIncreasing = !isIncreasing;
    isPaused = true;
    pauseStartTime = now;
  }
}
