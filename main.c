#include <sys/types.h>
#include <libgte.h>
#include <libetc.h>
#include <libgpu.h>
#include <stdio.h>

#include "utils/utils.h"
#define TILE_SIZE 32

char pribuff[2][32768]; // Primitive buffer
char *nextpri;          // Next primitive pointer

TILE *tile;

int x = 0;
int y = 0;

int dirx = 1;
int diry = 1;

int velx = 1;
int vely = 1;

void draw();
void update();

int main () {
  InitGraphics();
  // Load the internal font texture
  FntLoad(960, 0);
  // Create the text stream
  FntOpen(0, 8, 320, 224, 0, 100);

  nextpri = pribuff[0];

  while (RUNNING) {
    ClearOrderingTable();  // Clear ordering table
    int buffer = DisplayGraphics(&draw);
    nextpri = pribuff[buffer];
    update();
  }
  return 0;
}

void draw() {
  FntPrint("HELLO WORLD!");

  FntFlush(-1);
  tile = (TILE*)nextpri; // Cast next primitive

  setTile(tile);
  setXY0(tile, x, y);
  setWH(tile, TILE_SIZE, TILE_SIZE);
  setRGB0(tile, 255, 255, 255);
  AddPrimToOrderingTable(tile);

  nextpri += sizeof(TILE);    // Advance the next primitive pointer

}

void update() {
  int xnext = x + TILE_SIZE;
  int ynext = y + TILE_SIZE;

  if (x < 0 || xnext > SCREEN_WIDTH) {
    velx *= -1;
  }
  if (y < 0 || ynext > SCREEN_HEIGHT) {
    vely *= -1;
  }

  x += velx;
  y += vely;
}
