 
#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
String UID = "24 CE 75 A3"; // Fixed UID
byte lock = 0;

Servo servo;
LiquidCrystal_I2C lcd(0x27, 16, 2); // Confirmed address
MFRC522 rfid(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  pinMode(3, OUTPUT);
  digitalWrite(3, LOW);
  servo.attach(3);
  servo.write(70);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(4, 0);
  lcd.print("Welcome!");
  lcd.setCursor(1, 1);
  lcd.print("Put your card");
  SPI.begin();
  rfid.PCD_Init();
  Serial.println("Setup complete. RFID Ready.");
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent()) {
    Serial.println("No card detected");
    return;
  }
  if (!rfid.PICC_ReadCardSerial()) {
    Serial.println("Failed to read card");
    return;
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Scanning");
  Serial.print("Card UID: ");
  String ID = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    lcd.print(".");
    ID.concat(String(rfid.uid.uidByte[i] < 0x10 ? " 0" : " "));
    ID.concat(String(rfid.uid.uidByte[i], HEX));
    Serial.print(rfid.uid.uidByte[i] < 0x10 ? "0" : "");
    Serial.print(rfid.uid.uidByte[i], HEX);
    delay(300);
  }
  Serial.println();
  ID.toUpperCase();

  if (ID.substring(1) == UID && lock == 0) {
    servo.write(80);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Door is locked");
    delay(1500);
    lock = 1;
  } else if (ID.substring(1) == UID && lock == 1) {
    servo.write(170);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Door is open");
    delay(1500);
    lock = 0;
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Wrong card!");
    delay(1500);
  }
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("Welcome!");
  lcd.setCursor(1, 1);
  lcd.print("Put your card");
}
