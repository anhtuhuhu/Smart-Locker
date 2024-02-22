# DO AN 2
## Project: Smart Locker
### Overview
- Use `Esp32` connect to modules include: `Esp32-CAM` through UART, `SIMCOM A7680c` through UART, `Keypad`.
- Make the options to open cabinet.
- Save data such as: `password`, `face` in `HTML_interface`.
### Detail
`MCU` : ESP32 DevKit V1 (ESP-WROOM-32)

`Peripheral` : 

`Development` : Arduino IDE, EasyEDA

`Feature` : 
- Unlock with password.
- Unlock with face recognition.
- Send message to the owner when cannot recognite face more than 3 times or enter password incorrect more than 3 times
