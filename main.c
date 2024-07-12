#include "font.h"
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// TODO produce turi code as output (this is a code editor after hoes)
// TODO take turi code as imput and play it
// TODO ability to swap the alphabet like int bool or anything

const int sw = 1920;
const int sh = 1080;

const int cellSize = 100;
const int cellPadding = 20;
const int numCells = 1001; // TODO dynamic memory allocation

typedef struct {
  int *tape;
  /* bool *tape; */
  int headPosition;
  float targetX;
  float currentX;
} TuringMachine;

TuringMachine tm = {0};


void initTuringMachine() {
  tm.tape = (int *)malloc(numCells * sizeof(int));
  /* tm.tape = (bool *)malloc(numCells * sizeof(bool)); */

  for (int i = 0; i < numCells; i++) {
    tm.tape[i] = 0;
  }

  tm.headPosition = numCells / 2; // Start at the center
  tm.currentX = tm.targetX =
      -((numCells / 2 + 8) * (cellSize + cellPadding) - sw / 2); // no idea why + 8 is needed

  // or start from the beginning
  /* tm.headPosition = 0;  */
  /* tm.currentX = tm.targetX = 0; */

}


int headThickness = 10;

void drawHead() {
  int headX = (sw / 2.0) - (cellSize / 2.0);
  int headY = (sh / 2.0) - (cellSize / 2.0);
  DrawRectangleLinesEx(
      (Rectangle){headX - cellPadding / 2.0, headY - cellPadding / 2.0,
                  cellSize + cellPadding, cellSize + cellPadding},
      headThickness, RED);
}

void drawTuringMachine() {
  for (int i = 0; i < numCells; i++) {
    int x = (sw / 2.0) - (cellSize / 2.0) + (i * (cellSize + cellPadding)) +
            tm.currentX;
    int y = (sh / 2) - (cellSize / 2);

    DrawRectangle(x, y, cellSize, cellSize, WHITE);

    char cellValueStr[12];
    sprintf(cellValueStr, "%d", tm.tape[i]);
    Vector2 textSize =
        MeasureTextEx(CURRENT_FONT, cellValueStr, cellSize / 2.0, 1);
    DrawTextEx(CURRENT_FONT, cellValueStr,
               (Vector2){x + cellSize / 2.0 - textSize.x / 2.0,
                         y + cellSize / 2.0 - textSize.y / 2.0},
               cellSize / 2.0, 1, BLACK);
  }

  drawHead();
}

void updateTuringMachine() {
  tm.currentX += (tm.targetX - tm.currentX) * 0.03f;
}

void handleKeys() {
  if (IsKeyPressed(KEY_L) && tm.headPosition < numCells - 1) {
    tm.headPosition++;
    tm.targetX -= (cellSize + cellPadding);
  }
  if (IsKeyPressed(KEY_H) && tm.headPosition > 0) {
    tm.headPosition--;
    tm.targetX += (cellSize + cellPadding);
  }

  if (IsKeyPressed(KEY_J))
      tm.tape[tm.headPosition]++;
      /* tm.tape[tm.headPosition] = !tm.tape[tm.headPosition]; */
  if (IsKeyPressed(KEY_K))
      tm.tape[tm.headPosition]--;

  if (IsKeyPressed(KEY_EQUAL) && IsKeyDown(KEY_LEFT_ALT)) {
    nextFont();
  }
  if (IsKeyPressed(KEY_MINUS) && IsKeyDown(KEY_LEFT_ALT)) {
    previousFont();
  }
}

int main() {
  InitWindow(sw, sh, "Interactive Turing Machine");
  SetTargetFPS(144);

  initTuringMachine();
  loadFonts();

  while (!WindowShouldClose()) {
    updateTuringMachine();
    handleKeys();

    BeginDrawing();

    ClearBackground(BLACK);
    drawTuringMachine();

    EndDrawing();
  }

  free(tm.tape);
  CloseWindow();
  return 0;
}

