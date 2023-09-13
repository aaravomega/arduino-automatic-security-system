#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x20, 16, 2);

int thresholdValue = 500;

int pirPin = 9;
int motionLedPin = 5;
int buzzerPin = 7;
int tempPin = A0;
int gasPin = A1;
int tempLedPin = 3;

void setup() {
  pinMode(pirPin, INPUT);
  pinMode(motionLedPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(tempPin, INPUT);
  pinMode(gasPin, INPUT);
  pinMode(tempLedPin, OUTPUT);
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.print("Security status:");
  lcd.setCursor(0, 1);
}

void loop() {
  int pirState = digitalRead(pirPin);
  float temperature = readTemperature();
  int gasValue = analogRead(gasPin);

  if (gasValue > thresholdValue || pirState == HIGH) {
    Serial.println("Gas/Smoke detected!");
    lcd.setCursor(0, 1);
    lcd.print("Compromised                     ");
    // Add actions here for gas/smoke detection, e.g., sending alerts, turning on exhaust fans, etc.
  } else if (temperature < 20.0) {
    Serial.println("Heating Room");
    lcd.setCursor(0, 1);
    lcd.print("Heating Room                       ");
    digitalWrite(tempLedPin, HIGH);
  } else {
    lcd.setCursor(0, 1);
    lcd.print("Safe                              ");
    digitalWrite(tempLedPin, LOW);
    delay(10);
  }

  if (pirState == HIGH) {
    digitalWrite(motionLedPin, HIGH);
    digitalWrite(buzzerPin, HIGH);
    Serial.println("Motion detected!");
    delay(1000);
    digitalWrite(buzzerPin, LOW);
  } else {
    digitalWrite(motionLedPin, LOW);
  }
}

float readTemperature() {
  int sensorValue = analogRead(tempPin);
  float voltage = sensorValue * (5.0 / 1023.0);
  float temperatureCelsius = (voltage - 0.5) * 100.0;
  return temperatureCelsius;
}




