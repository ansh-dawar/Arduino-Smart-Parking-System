# 🚗 Arduino-Based Smart Parking System

An automated smart parking system built using **Arduino UNO** that detects incoming vehicles via IR sensors, controls entry via a servo-motor gate, and displays real-time available slot count on a 16x2 LCD — all without any manual intervention.

> Built as a hardware prototype simulating a real-world parking lot with 4 slots.

---

## 📽️ Demo Video

<--  -->

---

## ⚙️ How It Works

**Entry Flow:**
1. Vehicle approaches the entry gate
2. IR sensor detects the vehicle's presence
3. System checks if slots are available
4. If slots available → servo motor opens gate + LCD updates slot count
5. Gate closes automatically after vehicle passes

**Parking Full Flow:**
6. When all 4 slots are filled, any new vehicle trying to enter sees **"Sorry! Parking Full"** on the LCD
7. Gate stays closed — no entry allowed

**Exit Flow:**
8. Vehicle exits through the exit sensor
9. System recalculates and increments the slot count
10. LCD updates back — **"Slots Left: 1"** → **"Slots Left: 2"** → and so on
11. Parking accepts new vehicles again once a slot is free

---

## 🖼️ Project Preview

| State | LCD Display | Gate |
|-------|------------|------|
| Initial / Empty | `WELCOME! Slots Left: 4` | Opens on detection |
| 2 cars parked | `WELCOME! Slots Left: 2` | Opens on detection |
| 3 cars parked | `WELCOME! Slots Left: 1` | Opens on detection |
| Parking Full | `Sorry! Parking Full` | Stays CLOSED ❌ |
| 1 car exits | `WELCOME! Slots Left: 1` | Opens again ✅ |
| 2 cars exit | `WELCOME! Slots Left: 2` | Opens again ✅ |

---

## 🛠️ Components Used

| Component | Quantity | Purpose |
|-----------|----------|---------|
| Arduino UNO | 1 | Main microcontroller |
| IR Sensor | 2 | Entry & exit vehicle detection |
| Servo Motor (SG90) | 1 | Automated gate control |
| 16x2 LCD Display | 1 | Real-time slot status display |
| Breadboard | 1 | Circuit connections |
| Jumper Wires | Multiple | Wiring |
| USB Cable | 1 | Power & programming |

---

## 🔌 Circuit Connections

```
IR Sensor (Entry)   → Arduino Digital Pin 2
IR Sensor (Exit)    → Arduino Digital Pin 3
Servo Motor         → Arduino Digital Pin 9
LCD (RS)            → Arduino Digital Pin 12
LCD (EN)            → Arduino Digital Pin 11
LCD (D4-D7)         → Arduino Digital Pins 7, 6, 5, 4
VCC                 → 5V
GND                 → GND
```

---

## 💻 Code Overview

The system is programmed in **Embedded C** using Arduino IDE.

**Key logic:**

```cpp
// Slot counter logic
int totalSlots = 4;
int availableSlots = totalSlots;

// When entry IR sensor detects vehicle
if (entrySensorTriggered) {
    if (availableSlots > 0) {
        openGate();           // Servo rotates to open
        availableSlots--;     // Decrease slot count
        updateLCD();          // Show updated slots on LCD
        delay(2000);
        closeGate();          // Servo returns to closed position
    } else {
        parkingFull();        // Show "Sorry! Parking Full" — gate stays closed
    }
}

// When exit IR sensor detects vehicle leaving
if (exitSensorTriggered) {
    if (availableSlots < totalSlots) {
        availableSlots++;     // Recalculate and increment slot count
        updateLCD();          // Show updated: Slots Left: 1 → 2 → 3...
    }
}

// Display available slots on LCD
void updateLCD() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("WELCOME!");
    lcd.setCursor(0, 1);
    lcd.print("Slots Left: ");
    lcd.print(availableSlots);
}

// Display when parking is completely full
void parkingFull() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Sorry!");
    lcd.setCursor(0, 1);
    lcd.print("Parking Full");
    // Gate does NOT open
}
```

---

## 🚀 How to Run

1. **Clone this repository**
   ```bash
   git clone https://github.com/your-username/smart-parking-system.git
   ```

2. **Open in Arduino IDE**
   - Open `smart_parking.ino` in Arduino IDE

3. **Install required libraries**
   - `LiquidCrystal.h` (built-in with Arduino IDE)
   - `Servo.h` (built-in with Arduino IDE)

4. **Connect the hardware**
   - Follow the circuit connections table above

5. **Upload the code**
   - Select board: `Arduino UNO`
   - Select correct COM port
   - Click **Upload**

---

## ✨ Features

- ✅ Real-time vehicle detection using IR sensors
- ✅ Automatic gate open/close via servo motor
- ✅ Live available slot count on 16x2 LCD
- ✅ **"Sorry! Parking Full"** message when all slots occupied — gate stays closed
- ✅ Automatic slot recalculation when a vehicle exits (Slots Left: 1 → 2 → 3...)
- ✅ Handles both entry and exit of vehicles seamlessly
- ✅ Zero manual intervention required
- ✅ Instant sensor-to-actuator response with no delay
- ✅ Fully working physical prototype

---

## 📁 Project Structure

```
smart-parking-system/
│
├── smart_parking.ino       # Main Arduino code
├── circuit_diagram.png     # Circuit connection diagram
├── demo_video.mp4          # Working demo
└── README.md               # Project documentation
```

---

## 🔮 Future Improvements

- Add IoT integration to monitor slots remotely via mobile app
- Implement RFID-based entry for registered vehicles
- Add LED indicators (Green/Red) per slot
- Web dashboard for real-time slot monitoring

---

## 👨‍💻 Author

**Shivansh Dawar**  
B.Tech CSE (IoT) — Raj Kumar Goel Institute of Technology, Ghaziabad  
📧 anshdawar1506@gmail.com  
🔗 [LinkedIn](https://linkedin.com/in/shivansh-dawar)  
🐙 [GitHub](https://github.com/your-username)

---

## 📄 License

This project is open source and available under the [MIT License](LICENSE).
