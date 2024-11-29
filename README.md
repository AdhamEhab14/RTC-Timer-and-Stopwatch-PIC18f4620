# RTC, Timer, and Stopwatch using PIC18F4620

## Overview
This project implements a **Real-Time Clock (RTC)**, **Timer**, and **Stopwatch** using the PIC18F4620 microcontroller. The RTC is powered by the **DS1307 module**, communicating via I2C, while a **keypad** is used to set the Timer, and a **buzzer** signals the alarm. The Stopwatch includes a **reset button** and a **pause/resume button**. All functionalities are displayed on a **multiplexed 7-segment display**.

## Features
- **Real-Time Clock (RTC)**:
  - Uses DS1307 for accurate timekeeping.
  - Communicates via I2C protocol.
- **Timer**:
  - Adjustable countdown using a keypad.
  - Buzzer alert upon timer completion.
- **Stopwatch**:
  - Reset button to restart.
  - Pause/Resume button for control.
- **Display**:
  - Multiplexed 7-segment display for all modes.

