#include <sys/types.h>
#include <libgte.h>
#include <libetc.h>
#include <libgpu.h>
#include <stdio.h>

#include "utils/utils.h"


void draw();

int main () {
  InitGraphics();
  // Load the internal font texture
  FntLoad(960, 0);
  // Create the text stream
  FntOpen(0, 8, 320, 224, 0, 100);

  while (RUNNING) {
    draw();
    DisplayGraphics(&draw);
  }
  return 0;
}

void draw() {
  FntPrint("HELLO WORLD!");

  FntFlush(-1);
}
