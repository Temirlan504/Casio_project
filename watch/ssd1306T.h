#define OLED_ADDRESS 0x3C
#define SCREEN_WIDTH 64
#define SCREEN_HEIGHT 32

byte screenBuffer[SCREEN_WIDTH * SCREEN_HEIGHT / 8];

void sendCommand(byte command) {
  Wire.beginTransmission(OLED_ADDRESS);
  Wire.write(0x00); // Control byte indicating command
  Wire.write(command);
  Wire.endTransmission();
}
void sendData(byte data) {
  Wire.beginTransmission(OLED_ADDRESS);
  Wire.write(0x40); // Control byte indicating data
  Wire.write(data);
  Wire.endTransmission();
}
void display_init() {
  sendCommand(0xAE); // Display off
  sendCommand(0x20); // Set memory addressing mode
  sendCommand(0x10); // Horizontal addressing mode
  sendCommand(0xB0); // Set page start address
  sendCommand(0);    // Page 0
  sendCommand(0xC8); // Set COM output scan direction
  sendCommand(0x00); // Set lower column start address
  sendCommand(0x10); // Set higher column start address
  sendCommand(0x40); // Set display start line
  sendCommand(0x81); // Set contrast control
  sendCommand(0xFF); // Maximum contrast
  sendCommand(0xA1); // Set segment remap
  sendCommand(0xA6); // Set normal display
  sendCommand(0xA8); // Set multiplex ratio
  sendCommand(0x1F); // 1/32 duty cycle
  sendCommand(0xA4); // Set entire display on/off
  sendCommand(0xD3); // Set display offset
  sendCommand(0x00);
  sendCommand(0xDA); // Set COM pins hardware configuration
  sendCommand(0x12);
  sendCommand(0xD5); // Set display clock divide ratio/oscillator frequency
  sendCommand(0x80);
  sendCommand(0x8D); // Enable charge pump regulator
  sendCommand(0x14);
  sendCommand(0xAF); // Display on
}
void clearScreen() {
  memset(screenBuffer, 0, sizeof(screenBuffer));
}
void updateScreen() {
  for (int page = 0; page < SCREEN_HEIGHT / 8; page++) {
    sendCommand(0xB0 + page); // Set page address
    sendCommand(0x00);        // Set lower column start address
    sendCommand(0x12);        // Set higher column start address

    for (int column = 0; column < SCREEN_WIDTH; column++) {
      sendData(screenBuffer[column + page * SCREEN_WIDTH]);
    }
  }
}

// ==================
// Drawing objects
// ==================

void drawPixel(uint8_t x, uint8_t y) {
  if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT) {
    int bufferIndex = x + (y / 8) * SCREEN_WIDTH;
    screenBuffer[bufferIndex] |= (1 << (y % 8));
  }
}
void drawImage(uint8_t x, uint8_t y, const byte* image, uint8_t imageWidth, uint8_t imageHeight) {
  // Ensure the image fits within the screen dimensions
  if (x >= 0 && x + imageWidth <= SCREEN_WIDTH && y >= 0 && y + imageHeight <= SCREEN_HEIGHT) {
    for (int j = 0; j < imageHeight; j++) {
      for (int i = 0; i < imageWidth; i++) {
        // Get the byte containing the pixel data from the image
        byte imageData = pgm_read_byte(&image[i + (j / 8) * imageWidth]);

        // Calculate the screen buffer coordinates
        int screenX = x + i;
        int screenY = y + j;

        // Calculate the bit position within the byte
        int bitPosition = j % 8;

        // Check if the bit at the specified position is set
        bool pixelOn = (imageData & (1 << bitPosition)) != 0;

        // Draw the pixel on the screen buffer
        if (pixelOn) {
          drawPixel(screenX, screenY); // Set pixel to ON
        }
      }
    }
  }
}
