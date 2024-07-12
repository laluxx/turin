#include "font.h"
#include <stdio.h>

Font jetb;
int currentFontIndex = 1;
Font fonts[2];


void loadFonts() {
  fonts[0] = jetb = LoadFontEx("./assets/fonts/JetBrainsMono-Bold.ttf", 50, 0, 0);
  fonts[1] = jetb = LoadFontEx("./assets/fonts/IosevkaNerdFont-Regular.ttf", 50, 0, 0);

  for (int i = 0; i < 3; i++) {
    if (fonts[i].texture.id == 0) {
      printf("Failed to load font at index %d.\n", i);
    }
  }

  int asciiRange[95]; // for characters from 32 to 126
  for (int i = 0; i < 95; i++) {
    asciiRange[i] = 32 + i;
  }

}

void unloadFonts() {
  for (int i = 0; i < 3; i++) {
    UnloadFont(fonts[i]);
  }
}

void nextFont() {
  currentFontIndex++;
  if (currentFontIndex >= sizeof(fonts) / sizeof(Font)) {
    currentFontIndex = 0;
  }
}

void previousFont() {
  currentFontIndex--;
  if (currentFontIndex < 0) {
    currentFontIndex = sizeof(fonts) / sizeof(Font) - 1;
  }
}
