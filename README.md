# GPS Campus Navigator on TM4C123GH6PM

[![C Language](https://img.shields.io/badge/Language-C-blue.svg)](#)
[![ARM Assembly](https://img.shields.io/badge/Architecture-ARM%20ASM-lightgrey.svg)](#)
[![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)

> **Navigate your campus with ease**  
> An embedded GPS‑tracking demo running on a TI Tiva C Series TM4C123GH6PM, displaying real‑time proximity to key campus locations on an LCD.

---

## 🚀 Features

- **Real‐time GPS parsing**  
  Continuously reads NMEA sentences from a GPS module via UART.
- **Closest‐point algorithm**  
  Calculates which predefined campus landmark is nearest.
- **On‐board LCD display**  
  Shows your current coordinates and the name/distance of the closest location.
- **Modular C & ARM codebase**  
  Clear separation of GPS, display, and navigation logic.
- **Low‐power friendly**  
  Utilizes sleep modes when idle to minimize power use.

---

## 🛠️ Hardware

- **Microcontroller**: TI Tiva C Series TM4C123GH6PM  
- **GPS Module**: e.g. u‑blox NEO‑6M (UART interface)  
- **LCD Display**: 16×2 Character LCD (HD44780‑compatible)  
- **Wiring**:  
  - GPS TX → UART1 RX (PD2)  
  - GPS RX → UART1 TX (PD3)  
  - LCD data pins → GPIO Port B (PB0–PB7)  
  - LCD RS/E/RW → GPIO Port A (PA6, PA7, PA5)  
- **Power**: 3.3 V regulated supply

> _See [`hardware/`](./hardware/) for detailed schematics & wiring diagrams._

---

## 💻 Software

- **Languages**: C (Keil MDK), ARM Assembly  
- **IDE**: Keil µVision5  
- **Compiler**: ARMCC  
- **Libraries**:  
  - TivaWare™ (GPIO, UART, SysTick)  
  - Custom GPS parser & LCD driver

---

## 📦 Installation & Build

1. **Clone the repo**  
   ```bash
   git clone https://github.com/your‑username/gps-campus-navigator.git
   cd gps-campus-navigator
