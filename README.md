# ⏱️ RTC × Stopwatch × Timer — PIC18F4620 Embedded Project

A complete embedded system project that combines a **Real-Time Clock (RTC)**, **Stopwatch**, and **Countdown Timer** using the **PIC18F4620** microcontroller. This project demonstrates modular embedded development using layered architecture and external peripheral integration.

---

## 📌 Features

- **🕒 Digital Clock**  
  Displays real-time time and date using the **DS1307 RTC** via I2C.

- **⏱️ Stopwatch Mode**  
  High-precision stopwatch with Start, Stop, and Reset functionality.

- **⏳ Countdown Timer**  
  User-configurable timer using keypad input. Triggers buzzer when time is up.

- **📟 Multiplexed 7-Segment Display**  
  Displays clock, stopwatch, and timer states efficiently using limited I/O.

- **🧠 Layered Architecture**
  - **MCAL:** Hardware abstraction for I2C, GPIO, etc.
  - **ECUAL:** Display, keypad, buzzer, and RTC control modules.
  - **APP:** Manages logic for mode switching and behavior execution.

---

## 🧰 Hardware Components

| Component           | Description                        |
|--------------------|------------------------------------|
| **PIC18F4620**      | 8-bit Microcontroller              |
| **DS1307**          | Real-Time Clock via I2C            |
| **7-Segment Display** | 4-Digit Multiplexed Display       |
| **Keypad**          | 4x4 Matrix Keypad                  |
| **Buzzer**          | Audio alarm for timer              |
| **CR2032 Battery**  | RTC backup battery                 |
| **Pull-up Resistors** | I2C communication lines          |

---

## 🧪 How It Works

1. On startup, system initializes RTC and enters default **Clock Mode**.
2. Use keypad buttons to switch between:
   - **Clock**
   - **Stopwatch**
   - **Timer**
3. Each mode has dedicated logic for input handling and display.
4. Display is updated every second using TMR0 and software multiplexing.

---



### 📂 File Structure


