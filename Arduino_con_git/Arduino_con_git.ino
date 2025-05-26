#include <math.h>

enum FadeState { RISING, FALLING, PAUSED };

const byte LED_PIN = 9;
const unsigned long FADE_DURATION = 5100; // 255*10ms*2 (ida y vuelta)
const unsigned long PAUSE_TIME = 500;
const float GAMMA = 2.2;

FadeState state = RISING;
unsigned long stateStartTime;
unsigned long cycleStartTime;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  stateStartTime = millis();
  cycleStartTime = millis();
}

void loop() {
  unsigned long currentTime = millis();
  unsigned long elapsed = currentTime - stateStartTime;
  
  switch(state) {
    case RISING:
      updateBrightness(elapsed, true);
      if (currentTime - cycleStartTime >= FADE_DURATION/2) {
        state = PAUSED;
        stateStartTime = currentTime;
      }
      break;
      
    case FALLING:
      updateBrightness(elapsed, false);
      if (currentTime - cycleStartTime >= FADE_DURATION) {
        state = PAUSED;
        stateStartTime = currentTime;
        cycleStartTime = currentTime;
      }
      break;
      
    case PAUSED:
      if (elapsed >= PAUSE_TIME) {
        state = (state == RISING) ? FALLING : RISING;
        stateStartTime = currentTime;
      }
      break;
  }
}

void updateBrightness(unsigned long elapsed, bool rising) {
  float progress = (float)elapsed / (FADE_DURATION/2);
  progress = constrain(progress, 0.0, 1.0);
  
  float brightness = rising ? progress * 255 : (1.0 - progress) * 255;
  float corrected = pow(brightness/255.0, GAMMA) * 255;
  
  analogWrite(LED_PIN, (int)corrected);
}
