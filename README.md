# PSoC 6 Keypad Input Sequence Generator

A bare-metal embedded application for the Infineon PSoC 6 microcontroller that reads input from a 4x4 matrix keypad, validates it against a predefined sequence, and predicts the next three values of the sequence over UART when a correct match is detected.

---

## Hardware

| Component | Details |
|---|---|
| Primary Board | CYBSYSKIT-DEV-01 |
| Compatible Board | CY8CPROTO-062-4343W |
| Keypad | 4x4 Matrix Keypad |
| Communication | UART (via KitProg3 USB-to-UART bridge) |

---

## Program flow

1. The application continuously scans the 4x4 matrix keypad for key presses.
2. Each key press is appended to an input buffer.
3. The buffer is compared against a predefined sequence.
4. When the correct sequence is detected, the next **three predicted values** of the sequence are printed over UART.
5. The buffer resets and the application waits for the next input.

---




## Prerequisites

- [ModusToolbox™ 3.x](https://www.infineon.com/cms/en/design-support/tools/sdk/modustoolbox-software/)
- A serial terminal
- CYBSYSKIT-DEV-01 or CY8CPROTO-062-4343W board
- 4x4 Matrix Keypad



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

This project is open for personal reference and learning
