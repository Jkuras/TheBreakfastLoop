#include <Arduino.h>
// MIDI clock, start and stop byte definitions - based on MIDI 1.0 Standards.
#define MIDI_CLOCK 0xF8
#define MIDI_START 0xFA
#define MIDI_STOP  0xFC

unsigned long lastPotRead = 0;
const int readInterval = 50; // ms

// The callback function called by Clock each Pulse of 24PPQN clock resolution.
void onSync24Callback(uint32_t tick) {
  // Send MIDI_CLOCK to external gears
  Serial.write(MIDI_CLOCK);
}

// The callback function called when clock starts by using Clock.start() method.
void onClockStart() {
  Serial.write(MIDI_START);
}

// The callback function called when clock stops by using Clock.stop() method.
void onClockStop() {
  Serial.write(MIDI_STOP);
}

void setup() {

  // Initialize serial communication at 31250 bits per second, the default MIDI serial speed communication:
  Serial.begin(31250);

  
}

void loop() {

  if (millis() - lastPotRead >= readInterval) {
      lastPotRead = millis();
      // Place the analogRead and setTempo logic here
      int lastPotValue = 0;
      int currentPotValue = analogRead(A0);
      // Detect if the pot has actually moved enough to warrant a change
      if (abs(currentPotValue - lastPotValue) > 4) { // '4' filters out micro-jitter 
        lastPotValue = currentPotValue;
        
        // Map the 0-1023 ADC range to your desired BPM (e.g., 60 to 200 BPM)
        int newBpm = map(currentPotValue, 0, 1023, 60, 200); 
        
      }
  }

  

}