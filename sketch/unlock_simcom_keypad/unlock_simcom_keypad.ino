#include <Keypad.h>
#include <HardwareSerial.h>
#include <Tone32.h>

#define BUZZER_PIN 14
#define BUZZER_CHANNEL 0

HardwareSerial SerialPort(2);  // use UART0
HardwareSerial SerialAT(0);

const byte ROWS = 4;
const byte COLS = 4;
char password[4];
char correctPassword[] = "123";
int passwordLength = 0;
bool doorUnlocked = false;
unsigned long unlockTime = 0;  // Thêm biến thời gian

const int unlockRelay = 27;  // Relay kết nối với cửa mở

char MatrixKey[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};
byte rowPins[ROWS] = { 19, 18, 5, 17 };  // R1, R2, R3, R4
byte colPins[COLS] = { 16, 4, 0, 2 };    // C1, C2, C3, C4

Keypad Mykeys = Keypad(makeKeymap(MatrixKey), rowPins, colPins, ROWS, COLS);
char number = ' ';
int wrongAttempts = 0;
#define MAX_WRONG_ATTEMPTS 3
void setup() {
  Serial.begin(115200);

  SerialPort.begin(115200, SERIAL_8N1, 3, 1);

  SerialAT.begin(115200, SERIAL_8N1, 23, 25);
  delay(6000);
  pinMode(unlockRelay, OUTPUT);
  digitalWrite(unlockRelay, LOW);
  Serial.println("Enter Password:");
}

void loop() {
   

  char EnterKey = Mykeys.getKey();


  if (EnterKey && !doorUnlocked) {
    if (passwordLength < 3) {
      password[passwordLength] = EnterKey;
      passwordLength++;
      Serial.print("*");
    }

    if (passwordLength == 3) {
      if (strcmp(password, correctPassword) == 0) {
        // Mật khẩu đúng, mở relay
        digitalWrite(unlockRelay, HIGH);
        Serial.println("\nDoor Unlocked");
        doorUnlocked = true;
        Serial.print("doorUnlocked: ");
        Serial.println(doorUnlocked);
        wrongAttempts = 0;
      } else {
        // Mật khẩu sai, khóa lại relay và in cảnh báo
        digitalWrite(unlockRelay, LOW);
        tone(BUZZER_PIN, NOTE_D4, 500, BUZZER_CHANNEL);
        noTone(BUZZER_PIN, BUZZER_CHANNEL);
        Serial.println("\nIncorrect Password! Door Remains Locked");
        wrongAttempts++;

        Serial.println(wrongAttempts);
        if (wrongAttempts >= MAX_WRONG_ATTEMPTS) {
          wrongAttempts = 0;
          SerialAT.println("AT+CMGF=1");
          SerialAT.print("AT+CMGS=\"");
          SerialAT.print("+84961425842");
          SerialAT.println("\"");
          delay(1000);
          // updateSerial();

          SerialAT.print("Nhap sai pass 3 lan");
          delay(1000);

          // Send Ctrl+Z to indicate the end of the message
          SerialAT.write(26);

          delay(1000);
          Serial.println("\nDa gui tin nhan canh bao");
          tone(BUZZER_PIN, NOTE_D4, 2000, BUZZER_CHANNEL);
          noTone(BUZZER_PIN, BUZZER_CHANNEL);
          delay(2000);
        }
      }
      passwordLength = 0;
      memset(password, 0, sizeof(password));
      Serial.println("Enter Password:");
    }
  }
  if (EnterKey == '#') {
    if (doorUnlocked) {
      // Nếu cửa đã mở, đóng lại ngay lập tức
      digitalWrite(unlockRelay, LOW);
      doorUnlocked = false;
      Serial.println("Door Locked");
      Serial.print("doorUnlocked: ");
      Serial.println(doorUnlocked);
    }
  }
  if (SerialPort.available()) {
    char number = SerialPort.read();
    if (number == 'M') {
      digitalWrite(unlockRelay, HIGH);
      Serial.println("\nDoor Unlocked");
      doorUnlocked = true;
      Serial.print("doorUnlocked: ");
      Serial.println(doorUnlocked);
    }
    if (number == '0') {
      digitalWrite(unlockRelay, LOW);
      doorUnlocked = false;
      Serial.println("Door Locked");
      Serial.print("doorUnlocked: ");
      Serial.println(doorUnlocked);
    }
    if (number == 'Z') {
        SerialAT.println("AT+CMGF=1");
          SerialAT.print("AT+CMGS=\"");
          SerialAT.print("+84961425842");
          SerialAT.println("\"");
          delay(1000);
          // updateSerial();

          SerialAT.print("Khong nhan dien duoc khuon mat");
          delay(1000);

          // Send Ctrl+Z to indicate the end of the message
          SerialAT.write(26);

          delay(1000);
          Serial.println("\nDa gui tin nhan canh bao");
          tone(BUZZER_PIN, NOTE_D4, 2000, BUZZER_CHANNEL);
          noTone(BUZZER_PIN, BUZZER_CHANNEL);
          delay(2000);
      
    }
  }
}


