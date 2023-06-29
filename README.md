# Center-Aligned PWM Controller on Teensy 4.1 Board (Arduino IDE)

This repository contains the source code for controlling a center-aligned Pulse Width Modulation (PWM) signal on a Teensy 4.1 board using the Arduino IDE. This project is unique as it focuses on enabling center-aligned PWM, a feature not directly supported by the Arduino's built-in functions. The project is currently in the development and testing phase, with continuous enhancements being made for optimization.

## About the Project

Center-aligned PWM, also known as symmetrical PWM, is a method where the PWM pulses are centered around the middle of the period rather than aligned at the start of the period. This can be especially useful in power electronics and motor control applications where harmonic distortion needs to be minimized.

The Teensy 4.1 board, equipped with an ARM Cortex-M7 processor at 600 MHz, 8 MB of RAM, 2 MB of Flash Memory, and 55 digital I/O pins, is the cornerstone of this PWM controller.

The code includes several functions that enable center-aligned PWM control:

- `setup()`: Sets up the FlexPWM modules and configures the multiplexer to use FlexPWM.
- `start_gate()`: Enables PWM channels A and B of submodules 3-0 of Module 4, 2, and 1.
- `stop_car()`: Disables PWM channels A and B of submodules 3-0 of Module 4, 2, and 1.
- `duty_update()`: Allows dynamic updating of the PWM signal's duty cycle.

## Project Status

This project is in the development phase. Initial tests have been conducted but further tests are needed to optimize the code and fix any potential issues. The goal is to develop a robust and efficient method for controlling center-aligned PWM using the Teensy 4.1 board in the Arduino environment.

## Contributing

Contributions and suggestions for improvements to this project are most welcome. Please feel free to fork this repository, make your changes, and submit pull requests.

