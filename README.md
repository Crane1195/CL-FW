# Crane's Lab Firmware

This firmware is for all-digital fightsticks, with an emphasis on:

* Modifiers for digital to analog functionality
* Ease of adding/modifying games and modes
* Ease of porting to different hardware

## Current Features
#### Modes
* GameCube Mode
* N64 Mode
* PC Dinput Gamepad Mode
* PC Keyboard Mode
* PC Input Viewer Compatibility
* Automatic switching between console and USB modes (GameCube and PC Dinput by default)

#### Games
* Melee
* Ultimate
* Project M/+
* Rivals of Aether
* D-pad mode for traditional fighters and platformers

#### SOCD Resolution Methods
* Neutral
* Second Input Priority (2IP)
* Second Input Priority Without Reactivation (2IP No Reactivation)
* Option to prioritize Up for Keyboard and D-pad mode, using any of the above SOCD resolution methods
* Each game can have all four axes' SOCD method changed independently (Left/Right stick X/Y Axis)

## Hardware Info
#### Currently Supported Hardware
* Arduino AVR family (Leonardo, Micro, Pro Micro, Mega2560, Nano, Uno)
* Crane's Lab Model S v2.X
* Crane's Lab GCCMX
* Crane's Lab GCCPCB v2.0
* Crane's Lab GCCPCB v1.0
* HTangl v1
* HTangl Prototype
* 20XX B0XX r1 (18 Buttons)
* 20XX B0XX r2 (20 Buttons)
* HitBox Smash Box
* JFA LBX

#### Hardware To Eventually Support
* Raspberry Pi Pico (and other RP2040 solutions)
* Frame1 Heavy/Light

## Installation and Setup Guide
[Here you can find a comprehensive Installation and Setup Guide for CL-FW](https://github.com/Crane1195/CL-FW/blob/main/setup/README.md).

## Credits
[@JonnyHaystack](https://github.com/JonnyHaystack) - Creator of [HayB0XX](https://github.com/JonnyHaystack/HayB0XX), providing the pinout of the B0XX r2, the most up to date coordinates for Melee mode, and an example to follow for how to use PlatformIO.

[@Nicohood](https://github.com/NicoHood/Nintendo) - Creator of the [Nintendo Library](https://github.com/NicoHood/Nintendo) used for AVR boards.

[@MHeironimus](https://github.com/MHeironimus) - Creator of the [PC Dinput Gamepad Library](https://github.com/MHeironimus/ArduinoJoystickLibrary) used for AVR boards.

[@Arduino](https://github.com/Arduino) - Creators of open source hardware and libraries used for AVR boards, including the [Keyboard library used in this firmware](https://github.com/arduino-libraries/Keyboard)

## Contact
Let me know if you have any issues with the firmware in my Discord Server:
https://craneslab.xyz/discord

## License
CL-FW is licenced under the GNU GPL Version 3. [See the included LICENSE file for details](https://github.com/Crane1195/CL-FW/blob/main/LICENSE).

## Support my work
I set up a donation link for people who appreciate my work and wish to donate. Donations are greatly appreciated, but are far from necessary:

https://www.paypal.com/donate/?hosted_button_id=NFDEML5FKR8N8
