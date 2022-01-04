This is a firmware for AVR devices that reads from Wiegand interface and outputs results to a character LCD display.

# Usage

This is intended for an ATmega8515L chip, but other AVR devices can be used as long as there is a full 8-bit port available for communication with a HD44780-compatible LCD. See port definitions in `lcd.h` for more details.

* `PortA[7:0]' goes to `D7` to `D0` on the LCD
* `PortE[2:0]` goes to `EN`, `RW`, `RS` on the LCD
* `Data0` (green) and `Data1` (white) on the Wiegand-interface goes to `INT0` and `INT1`

# Supported Formats

* 26-bit HID Proximity (standard)
* 35-bit HID Corporate 1000

Other card formats can still be read but will not have their site and card numbers decoded.
