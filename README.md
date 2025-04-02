# RELIC: MIDI Touch Controller with MPR121 and MIDIUSB

RELIC is a USB MIDI touch controller built with an Adafruit MPR121 capacitive touch sensor and the MIDIUSB library. It allows you to trigger MIDI notes, control Ableton Live instruments, and create mysterious and expressive performances.

## 🔮 Features
- **12 touch-sensitive pads** mapped to MIDI notes.
- **Control Change (CC) messages** to toggle Instrument Racks in Ableton Live.
- **Mystical aesthetic**, with symbols and messages enhancing the atmosphere.
- Easy integration with Ableton Live or other DAWs via USB.

---

## 📁 Contents
- `main.ino` - The Arduino code for RELIC.
- `README.md` - This documentation file.

---

## 📦 Requirements
- **Hardware:**
  - Arduino board compatible with USB MIDI (e.g., Arduino Leonardo, Arduino Micro, Arduino Due, etc.)
  - Adafruit MPR121 capacitive touch sensor.
  - USB connection to a computer running Ableton Live or any DAW.

- **Libraries:**
  - [Adafruit_MPR121](https://github.com/adafruit/Adafruit_MPR121)
  - [MIDIUSB](https://github.com/arduino-libraries/MIDIUSB)

---

## 🔧 Setup & Installation

1. **Install Libraries:**  
   Install the required libraries via Arduino IDE’s Library Manager or download them from their respective GitHub repositories.

2. **Wiring:**  
   Connect the MPR121 sensor to your Arduino board:
   - `SCL` → `SCL` (A5 on most Arduino boards)
   - `SDA` → `SDA` (A4 on most Arduino boards)
   - `VCC` → `3.3V` or `5V` (depending on your board)
   - `GND` → `GND`

3. **Upload Code:**  
   Upload the `main.ino` file to your Arduino board via Arduino IDE.

---

## 🎹 Usage with Ableton Live

1. **Connect Device:**  
   Plug your Arduino board into your computer via USB.

2. **Enable MIDI in Ableton Live:**  
   - Go to `Preferences > Link/MIDI`.
   - Enable `Track` and `Remote` for your Arduino device.

3. **MIDI Mapping:**  
   - Enter MIDI Map Mode (`Cmd+M` or `Ctrl+M`).
   - Click on the **On/Off switch** of an Instrument Rack.
   - Touch Pad `0` of RELIC to map it to the switch (it sends a MIDI CC message).

4. **Play Music:**  
   - The other pads (`1 - 11`) send MIDI note messages.
   - Map them to instruments or effects in Ableton Live as you wish.

---

## 🌌 Troubleshooting

- **Device Not Recognized:**  
  Make sure your board supports USB MIDI (e.g., Leonardo, Micro, Due).
- **No Sound in Ableton Live:**  
  Ensure `Track` and `Remote` are enabled for your device in `Preferences > Link/MIDI`.
- **MPR121 Not Found:**  
  Ensure the sensor is properly connected to the I2C pins. Check for loose wires or incorrect wiring.
- **Instrument Rack Toggle Not Working:**  
  Ensure you have mapped Pad `0` correctly to the On/Off switch.

---

## ✨ Future Improvements

- Add more Control Change (CC) messages for advanced Ableton Live control.
- Implement LED feedback for a more interactive experience.
- Customize MIDI messages per pad for different functionalities.

---

## 📜 License

This project is open-source and available under the [MIT License](LICENSE).

---

