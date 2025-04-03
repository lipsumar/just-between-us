# Just Between Us

Just Between Us is a eurorack clock module heavily inspired by Pam's New Workout.

I made this module for 2 main reasons:

1. I like modular but my wallet likes it much less
2. I want to learn more about electronics and C++

This is my second large Arduino project and still consider myself a C++ and electronics noob. Keep in mind information in this repo may be inexact. I would absolutely love to be corrected on any mistake made in this project, please do get in touch! piremmanuel at gmail dot com

## Features

- 2 analog outputs (more can be added very easily)
- MIDI clock (USB)
- Play/pause button
- Rotary encoder
- OLED display (128x64)
- User interface
  - Set BPM
  - Set modifier for each output (x1, x2, x3, /2, /3, /4, ...)
  - Parameters for each output:
    - Wave (square, triangle, sine) ([in progress](https://github.com/lipsumar/just-between-us/discussions/2))
    - Width (duty cycle)
    - Phase

This is the very first version of this module, the prototype stage really. Analog outputs are currently limited to gates and only 2 parameters are implemented (width & phase).

## User interface

Again, borrowing heavily from Pam's New Workout.

![UI - bpm](./docs/assets/UI-bpm.png)
![UI - modifier](./docs/assets/UI-modifier.png)
![UI - modifier edit](./docs/assets/UI-modifier-edit.png)
![UI - parameter](./docs/assets/UI-parameter.png)

## Schematic

The full schematics can be found in the `docs/` folder:

- [PDF](./docs/schematic.pdf)
- [KiCad](./docs/JustBetweenUs.kicad_sch)

![Full Schematic](./docs/assets/schematic.png)

There is no PCB yet, as this is still on breadboard at the moment.

## Details and comments

### Teensy

This module is based on a Teensy 4.1. A Teensy may be oversized for such a project, but I had one lying around and wanted to get to know the Teensy.

The experience was great, the documentation too. I never regretted this choice. I particularly enjoyed details such as being able to rename the MIDI device easily.

### Output stage

I'm currently working on getting proper analog outputs: https://github.com/lipsumar/just-between-us/discussions/2

### Power

#### USB and external power

Do not plug USB with the Teensy powerd through eurorack. I'm currently using a cable with the + cable cut out. Eventually a second USB port will allow to connect safely to a USB host but without the +5v connection.

Here is an excellent page about this very topic: https://www.pjrc.com/teensy/external_power.html
