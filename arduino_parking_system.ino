/*
Arduino Smart Parking System
Stable Version - No Servo Jitter
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

/* ------------------- LCD ------------------- */
LiquidCrystal_I2C lcd(0x27, 16, 2);

/* ------------------- SERVO ----------------- */
Servo gateServo;
const int SERVO_PIN = 4;
const int GATE_OPEN = 0;
const int GATE_CLOSE = 100;

/* ------------------- IR SENSORS ------------ */
const int IR_ENTRY = 2;
const int IR_EXIT  = 3;

/* ------------------- PARKING --------------- */
const int TOTAL_SLOTS = 4;
int slotsAvailable = TOTAL_SLOTS;

/* ------------------- SETUP ----------------- */
void setup() {

  Serial.begin(9600);

  pinMode(IR_ENTRY, INPUT);
  pinMode(IR_EXIT, INPUT);

  // Attach servo with stable pulse range
  gateServo.attach(SERVO_PIN, 500, 2400);
  gateServo.write(GATE_CLOSE);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("ARDUINO PARKING");
  lcd.setCursor(0, 1);
  lcd.print("SYSTEM");
  delay(2000);
  lcd.clear();
}

/* ------------------- LOOP ------------------ */
void loop() {

  /* ---------- ENTRY SENSOR ---------- */
  if (digitalRead(IR_ENTRY) == LOW) {

    if (slotsAvailable > 0) {

      openGateSmooth();
      slotsAvailable--;

      // Wait until vehicle passes completely
      while (digitalRead(IR_ENTRY) == LOW);
      delay(500);

      closeGateSmooth();
    }
    else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("SORRY :(");
      lcd.setCursor(0, 1);
      lcd.print("Parking Full");
      delay(2000);
      lcd.clear();
    }
  }

  /* ---------- EXIT SENSOR ---------- */
  if (digitalRead(IR_EXIT) == LOW) {

    if (slotsAvailable < TOTAL_SLOTS) {

      openGateSmooth();
      slotsAvailable++;

      // Wait until vehicle passes completely
      while (digitalRead(IR_EXIT) == LOW);
      delay(500);

      closeGateSmooth();
    }
  }

  /* ---------- LCD DISPLAY ---------- */
  lcd.setCursor(0, 0);
  lcd.print("WELCOME!      ");

  lcd.setCursor(0, 1);
  lcd.print("Slots Left: ");
  lcd.print(slotsAvailable);
  lcd.print("   ");

  delay(200);
}

/* ----------- FUNCTIONS ----------- */

void openGateSmooth() {
  for (int pos = GATE_CLOSE; pos >= GATE_OPEN; pos--) {
    gateServo.write(pos);
    delay(10);
  }
}

void closeGateSmooth() {
  for (int pos = GATE_OPEN; pos <= GATE_CLOSE; pos++) {
    gateServo.write(pos);
    delay(10);
  }
}
