# INO_Arduino_Vault

An arduino project that simulates an electronical lock (w/ keypad + 7 segment display).

## Table of contents

- [Table of contents](#table-of-contents)
- [Detailled description](#detailled-description)
- [Components and supplies](#components-and-supplies)
- [Breadboard view](#breadboard-view)
- [Schematic view](#schematic-view)

## Detailled description

Using a keypad and a 7-seg display, I wanted to make a kind of vault that is locked until the correct password is entered.
The user can interact with the keypad and the button. An audible sound can be heard when:

- Entering any number
- Pressing the "C" button
- Entering the right password
- Entering the wrong password
- Resetting the password.

When the correct password is found, nothing happens except an audio cue.
You could add, later down the road, something that will be triggered with this cue (like a led, a motor or an electronical lock).

The letters and symbols aren't used, except for "**C**", who will clear the user's input.

Misc: It uses E²PROM to store the correct password. The latter can be changed if the button is held for 3 seconds.

## Components and supplies

- 4-Pin button
- 5V Active buzzer
- 10K Resistor
- Adafruit 0.56" 4-Digit 7-Segment Display w/I2C Backpack
- Arduino Mega 2560 Rev 3
- Breadboard
- Jumper wires
- Keypad 4x4

## Breadboard view

![image](https://user-images.githubusercontent.com/56207146/196478829-52e3ca05-d96d-4309-8e82-a4ba5c4ceeae.png)

## Schematic view

![image](https://user-images.githubusercontent.com/56207146/196470456-f2446f37-cc52-4c66-b142-ee55d017a498.png)
