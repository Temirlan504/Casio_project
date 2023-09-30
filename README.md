# Digital Watch with an Arduino and I2C OLED Display

This project demonstrates how to create a digital watch using Arduino and an I2C OLED display with a resolution of 64x32 pixels.
The project utilizes the `Wire.h` library for communication between Arduino and the display. 
The digital watch not only displays the current time but also offers additional functionalities including video games, an Omnitrix app, and potentially weather information (pending due to size limitations).
There are also plans to incorporate Wi-Fi capabilities into the watch.

## Features

1. **Digital Time Display:** The watch accurately displays the current time in a digital format on the OLED display.

2. **Video Games:** Some super small video games (depends on the controllers memory).

3. **Omnitrix App:** Just some fun

4. **Weather Information (Pending):** Depending on case size limitations, weather information might be included

5. **Wi-Fi Capabilities (Planned):** Future plans include integrating Wi-Fi capabilities, enabling the watch to connect to the internet for additional functionalities and data retrieval.

## Hardware Requirements

- Arduino board (Arduino Nano)
- I2C OLED display with 64x32 resolution
- Additional components as per specific game or app requirements like buttons

## Software Requirements

- `Wire.h` library for I2C communication
