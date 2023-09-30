#include <Wire.h>
#include "images.h"
#include "ssd1306T.h"

uint8_t selected_item = 0;
uint8_t next_item = selected_item + 1;

const uint8_t cycle_button = 2;
const uint8_t select_button = 3;

void setup() {
  pinMode(cycle_button, INPUT_PULLUP);
  pinMode(select_button, INPUT_PULLUP);

  Wire.begin();

  display_init();
}

void loop() {
  // Check if the button is pressed (LOW)
  if (digitalRead(cycle_button) == LOW) {
    selected_item++;
    delay(150);
  }

  if (selected_item == 0) {
    clearScreen();

    drawImage(1, 0, img_select, 60, 15);
    drawImage(3, 2, img_clock, 35, 11);
    drawImage(3, 21, img_games, 45, 8);

    updateScreen();
  }
  else if (selected_item == 1) {
    clearScreen();

    drawImage(1, 0, img_select, 60, 15);
    drawImage(3, 3, img_games, 45, 8);
    drawImage(3, 21, img_omnitrix, 54, 11);

    updateScreen();
  }
  else if (selected_item == 2) {
    clearScreen();

    drawImage(1, 0, img_select, 60, 15);
    drawImage(3, 2, img_omnitrix, 54, 11);
    drawImage(3, 19, img_weather, 54, 11);

    updateScreen();
  }
  else if (selected_item == 3) {
    clearScreen();

    drawImage(3, 2, img_omnitrix, 54, 11);
    drawImage(1, 17, img_select, 60, 15);
    drawImage(3, 19, img_weather, 54, 11);

    updateScreen();
  }
  else {selected_item = 0;}
}
