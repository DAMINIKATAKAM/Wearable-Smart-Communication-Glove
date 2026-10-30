#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  // LCD I2C address
SoftwareSerial BT(2, 3);             // HC-05 TX -> D2, HC-05 RX -> D3
                                     // Use a voltage divider on HC-05 RX

void setup() {
  Serial.begin(9600);  // PC Serial Monitor
  BT.begin(9600);      // HC-05 Bluetooth communication

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("SIGN LANGUAGE");
}

void loop() {
  int s1 = analogRead(A0);
  int s2 = analogRead(A1);
  int s3 = analogRead(A2);

  Serial.print("Flex 1: ");
  Serial.println(s1);
  Serial.print("Flex 2: ");
  Serial.println(s2);
  Serial.print("Flex 3: ");
  Serial.println(s3);
  Serial.println("----------------------");

  lcd.clear();

  String message = "NOTHING";

  if (s1 > 200) {
    message = "WASHROOM";
  } else if (s2 > 300) {
    message = "DRINK WATER";
  } else if (s3 > 700) {
    message = "FOOD";
  }

  lcd.setCursor(0, 1);
  lcd.print(message);
  BT.println(message);
  Serial.println("Sent via Bluetooth: " + message);

  delay(500);
}
