/*
  RELIC: MIDI Touch Controller with MPR121 and MIDIUSB
  
  Description:
  This program uses an Adafruit MPR121 capacitive touch sensor to send MIDI messages over USB.
  Each of the 12 sensor pads is mapped to a specific MIDI note, which is triggered upon touch and released when contact is lost.
  The MIDIUSB library is used for communication with DAWs (Digital Audio Workstations) like Ableton Live.
 
*/

#include <Wire.h>
#include "Adafruit_MPR121.h"
#include <MIDIUSB.h>

#ifndef _BV
#define _BV(bit) (1 << (bit))
#endif

Adafruit_MPR121 cap = Adafruit_MPR121();
uint16_t lasttouched = 0;
uint16_t currtouched = 0;
byte noteMap[12] = {60, 62, 64, 65, 67, 69, 71, 72, 74, 76, 77, 79};
byte midiChannel = 4;
bool rackOn = false;  // Track if the Instrument Rack is On or Off

void setup() {
  Serial.begin(9600);

  while (!cap.begin(0x5A)) {  
    Serial.println("MPR121 not found, retrying in 5 seconds...");
    delay(5000);
  }
  
  Serial.println("            🌙✨ Sensors Ready! The gateway is open... 🪬");
  Serial.println("            🜓🔮 WELCOME TO RELIC 🔮🜓 ");
}

void loop() {
  currtouched = cap.touched();
  bool midiMessageSent = false;

  for (uint8_t i = 0; i < 12; i++) {
    if ((currtouched & _BV(i)) && !(lasttouched & _BV(i))) {

      if (i == 0) {  // Use touchpad 0 to toggle Instrument Rack On/Off
        rackOn = !rackOn;
        controlChange(midiChannel - 1, 1, rackOn ? 127 : 0);  // Sends CC#1 with value 127 (On) or 0 (Off)
        midiMessageSent = true;

        Serial.print("Instrument Rack ");
        Serial.println(rackOn ? "ON" : "OFF");
      }
      else {
        noteOn(midiChannel - 1, noteMap[i], 127);
        midiMessageSent = true;
      }
    }

    if (!(currtouched & _BV(i)) && (lasttouched & _BV(i))) {
      if (i != 0) {  // Only send Note Off messages for musical pads
        noteOff(midiChannel - 1, noteMap[i], 0);
        midiMessageSent = true;
      }
    }
  }

  if (midiMessageSent) {
    MidiUSB.flush();
  }

  lasttouched = currtouched;
  delay(10);
}

void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}

// New function to send Control Change messages
void controlChange(byte channel, byte control, byte value) {
  midiEventPacket_t cc = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(cc);
}
