#ifndef FONT_H
#define FONT_H

#include <raylib.h>

extern Font jetb;
extern Font fonts[];
extern int currentFontIndex;
#define CURRENT_FONT (fonts[currentFontIndex])

void loadFonts();
void unloadFonts();
void nextFont();
void previousFont();

#endif // FONT_H
