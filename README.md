🚀 dsPIC33CH64MP502 Multi-Core Demo

A dual-core demo project using MPLAB® X IDE v6.25 and MCC Harmony
Harness the power of the dsPIC33 dual-core architecture to explore inter-core communication, peripheral control, and multitasking.

📂 Project Overview

This repository showcases a Master/Slave multi-core architecture running on a dsPIC33CH64MP502 device.

Core	Role	Responsibilities
🧠 Master	Controller	Receives numeric data via MSI protocol, displays Slave status and received data over UART
⚡ Slave	Peripheral Handler	Sends numeric values using MSI protocol and blinks two LEDs on PORTA0 and PORTB11
🔁 Data Flow
Slave ---> (MSI) ---> Master ---> (UART) ---> Serial Terminal
         <--- status/log ---

✨ Features

✔️ Dual-core communication using MSI
✔️ UART output from Master for debugging and monitoring
✔️ LED blinking demo on Slave core
✔️ Clean and minimal starting point for multi-core development

🛠 Requirements

MPLAB® X IDE 6.25

MCC Harmony Configurator

dsPIC33CH64MP502 development hardware

💡 Notes

This demo is ideal for developers learning:

🎯 Inter-core communication
🎯 Real-time embedded coordination
🎯 Hardware abstraction via Harmony
