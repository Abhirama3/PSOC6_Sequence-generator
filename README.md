# PSoC 6 Keypad Input Sequence Generator
A bare-metal embedded application for the Infineon PSoC 6 microcontroller that reads input from a 4x4 matrix keypad, validates it against a predefined sequence, and predicts the next three values of the sequence over UART when a correct match is detected.

---

## Hardware
| Component | Details |
|---|---|
| Primary Board | CYSBSYSKIT-DEV-01 |
| Compatible Board | CY8CPROTO-062-4343W |
| Keypad | 4x4 Matrix Keypad |
| Communication | UART (via KitProg3 USB-to-UART bridge) |

---

## Program Flow
1. The application continuously scans the 4x4 matrix keypad for key presses.
2. Each key press is appended to an input buffer.
3. The buffer is compared against a predefined sequence.
4. When the correct sequence is detected, the next **three predicted values** of the sequence are printed over UART.
5. The buffer resets and the application waits for the next input.

---

## Getting Started

### Prerequisites
- [ModusToolbox™ 3.x](https://www.infineon.com/cms/en/design-support/tools/sdk/modustoolbox-software/)
- A serial terminal (e.g., PuTTY, Tera Term, or the ModusToolbox Terminal)
- CYSBSYSKIT-DEV-01 or CY8CPROTO-062-4343W board
- 4x4 Matrix Keypad

### Build & Flash
```bash
# 1. Clone the repository
git clone https://github.com/Abhirama3/PSOC6_Sequence-generator.git
cd PSOC6_Sequence-generator

# 2. Restore library dependencies
make getlibs

# 3. Build the project
make build

# 4. Flash to the board
make program
```

### UART Configuration
Open your serial terminal with the following settings:

| Setting | Value |
|---|---|
| Baud Rate | 115200 |
| Data Bits | 8 |
| Stop Bits | 1 |
| Parity | None |
| Flow Control | None |

Connect to the KitProg3 COM port that appears when the board is plugged in via USB.

---

## Built With
- **Infineon PSoC 6** — ARM Cortex-M4/M0+ dual-core MCU
- **ModusToolbox™** — Infineon's Eclipse-based IDE and toolchain

---

## Authors
- **Abhirama**
- **Adarsh Shivadas**

---

## License
This project is open for personal reference and learning.
