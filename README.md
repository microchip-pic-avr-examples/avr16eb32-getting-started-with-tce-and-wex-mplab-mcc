[![MCHP](images/microchip.png)](https://www.microchip.com)

# Getting Started with Timer/Counter Type E (TCE) and WEX MCC Melody

This repository contains examples of MPLAB® Code Configurator (MCC) Melody source code for the new Timer/Counter Type E (TCE) and Waveform Extension (WEX) peripherals of the AVR<sup>®</sup> EB family of devices. There are three applications described in this document. Each application's functionality is explained.

* [<strong>Generate PWM Signals Using TCE:</strong>](TCE_DS_4PWM_Signals) In this use case, the TCE timer is initialized in Dual Slope Mode to generate four Pulse-Width Modulation (PWM) signals with different duty cycles, scaling and high resolution option.
* [<strong>Generate Patterns Using WEX:</strong>](WEX_PGM_8Channels_Patterns) This example shows how to use WEX to generate different patterns, and take control of the TCE pins during run time, without stopping the timer. This is extremely useful for applications like trapezoidal motor control for example, where some PWM signals must be forced to low '0' logic depending on the commutation sector.
* [<strong>Generate Eight Complementary Pulse-Width Modulation Signals Using TCE and WEX modules:</strong>](TCE_AND_WEX_8_Complementary_PWM) In this example the TCE timer is initialized in Single Slope mode and generates four PWM signals. WEX is configured to split the four PWM signals into eight complementary PWM signals with dead time. The PWM signals have different duty cycles, that get incremented in 0-100% range minus dead time. Duty cycles increment happens in ISR routines during each compare register interrupt. A fault is triggered at every 250 μs, driving all the outputs to low ‘0’ logic. Then the fault is cleared and normal operation is restored. After that, the process repeats itself over and over again.

## Related Documentation

More details and code examples on the AVR16EB32 can be found at the following links:

- [AVR<sup>®</sup> EB Product Page](https://www.microchip.com/en-us/product/AVR16EB32)
- [AVR<sup>®</sup> EB Code Examples on GitHub](https://github.com/microchip-pic-avr-examples?q=AVR16EB32)

## Software Used

- [MPLAB® X IDE v6.15 or newer](https://www.microchip.com/en-us/tools-resources/develop/mplab-x-ide)
- [AVR-Ex DFP-2.8.189 or newer Device Pack](https://packs.download.microchip.com/)
- [MPLAB® XC8 compiler v2.45](https://www.microchip.com/en-us/tools-resources/develop/mplab-xc-compilers/downloads-documentation#XC8)
- [MPLAB® Code Configurator (MCC) v 5.3.7](https://www.microchip.com/en-us/tools-resources/configure/mplab-code-configurator)
- [MPLAB® Code Configurator (MCC) Melody Core v 2.6.2 or newer](https://www.microchip.com/en-us/tools-resources/configure/mplab-code-configurator)

## Hardware Used

- [AVR<sup>®</sup> EB Curiosity Nano](https://www.microchip.com/en-us/product/AVR16EB32)

## Setup

The AVR16EB32 Curiosity Nano Development Board is used as test platform.

<br><img src="images/AVR16EB32_Cnano_Board.png">