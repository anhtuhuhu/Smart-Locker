# DO AN 2
## Project: Smart Locker
### Overview
- Use `Esp32` connect to modules include: `Esp32-CAM` through UART, `SIMCOM A7680c` through UART, `Keypad`.
- Make the options to open cabinet.
- Save data such as: `password`, `face` in `HTML_interface`.
### Detail
`MCU` : ESP32 DevKit V1 (ESP-WROOM-32)

`Peripheral` : 
- `ESP32-CAM`.
- `A7680c : Module SIMCOM 4G`.
- `Keypad 4x4`.

`Development` : Arduino IDE, EasyEDA

`Feature` : 
- Unlock with password.
- Unlock with facial recognition.
- Send message to the owner when cannot recognite face more than 3 times or enter password incorrect more than 3 times.

### Schematic

<picture>
  <img alt="schematic" height="70%" width="70%" src="https://i.imgur.com/DxodNM5.png">
</picture>

`3D view`

<picture>
  <img alt="3Dview" height="40%" width="40%" src="https://i.imgur.com/5oPIiYm.png">
</picture>

`Note` : 
- File code : In the folder sketch.
- Upload file FaceDoorEntryESP32Cam.ino to ESP32-CAM and file unlock_simcom_keypad.ino to ESP32.
