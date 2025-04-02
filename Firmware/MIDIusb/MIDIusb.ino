#include <Wire.h>
#include "Adafruit_MPR121.h"
#include <MIDIUSB.h>

#ifndef _BV
#define _BV(bit) (1 << (bit)) 
#endif

// Instancia para el MPR121 (sensor táctil)
Adafruit_MPR121 cap = Adafruit_MPR121();

// Variables para hacer seguimiento del estado de los pines táctiles
uint16_t lasttouched = 0;
uint16_t currtouched = 0;

// Arreglo con las notas que serán enviadas cuando se toque cada pin
byte noteMap[12] = {60, 62, 64, 65, 67, 69, 71, 72, 74, 76, 77, 79};  // C3, D3, E3, F3, G3, A3, B3, C4, etc.

// Variable global para definir el canal MIDI (por defecto canal 1)
byte midiChannel = 4;  // Los canales MIDI van de 1 a 16, pero internamente se usa de 0 a 15

void setup() {
  Serial.begin(9600);

  // Ya no necesitamos esperar a que el Serial esté disponible

  // Opcional: solo imprimir si el puerto Serial está disponible
  if (Serial) {
    Serial.println("Adafruit MPR121 Capacitive Touch sensor test"); 
  }
  
  // Inicializa el sensor MPR121 en la dirección por defecto 0x5A
  if (!cap.begin(0x5A)) {
    if (Serial) {
      Serial.println("MPR121 no encontrado, verifica la conexión.");
    }
    while (1);  // Detener la ejecución si no se encuentra el sensor
  }
  if (Serial) {
    Serial.println("MPR121 detectado!");
  }
}

void loop() {
  // Obtiene el estado actual de los pads táctiles
  currtouched = cap.touched();
  
  for (uint8_t i = 0; i < 12; i++) {
    // Si el pin está tocado y no estaba tocado antes
    if ((currtouched & _BV(i)) && !(lasttouched & _BV(i))) {
      if (Serial) {
        Serial.print(i); 
        Serial.println(" tocado");
      }
      // Envía una nota MIDI "Note On" cuando se toca
      noteOn(midiChannel - 1, noteMap[i], 127);  // Canal ajustable, nota asignada, velocidad 127
      MidiUSB.flush();  // Envía el mensaje MIDI
    }
    // Si el pin estaba tocado y ya no lo está
    if (!(currtouched & _BV(i)) && (lasttouched & _BV(i))) {
      if (Serial) {
        Serial.print(i); 
        Serial.println(" soltado");
      }
      // Envía una nota MIDI "Note Off" cuando se suelta
      noteOff(midiChannel - 1, noteMap[i], 0);  // Canal ajustable, nota asignada, velocidad 0 (Note Off)
      MidiUSB.flush();  // Envía el mensaje MIDI
    }
  }

  // Actualiza el estado táctil anterior para la próxima iteración
  lasttouched = currtouched;

  // Agrega un pequeño delay para evitar sobrecargar el bucle
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
