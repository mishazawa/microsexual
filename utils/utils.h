#define RUNNING 1

DISPENV EnvDisp[2];
DRAWENV EnvDraw[2];

int buffer = 0;

int SwapBuffer () {
  buffer = !buffer;
  return buffer;
}

void InitGraphics () {
  ResetGraph(0);
  SetDefDispEnv(&EnvDisp[0], 0, 0, 320, 240);
  SetDefDispEnv(&EnvDisp[1], 0, 240, 320, 240);

  SetDefDrawEnv(&EnvDraw[0], 0, 240, 320, 240);
  SetDefDrawEnv(&EnvDraw[1], 0, 0, 320, 240);

  // Specifies the clear color of the DRAWENV
  setRGB0(&EnvDraw[0], 63, 0, 127);
  setRGB0(&EnvDraw[1], 63, 0, 127);
  // Enable background clear
  EnvDraw[0].isbg = 1;
  EnvDraw[1].isbg = 1;

  PutDispEnv(&EnvDisp[0]);
  PutDrawEnv(&EnvDraw[0]);

}

void DisplayGraphics (void (*f)()) {
  DrawSync(0);
  VSync(0);

  int buffer = SwapBuffer();

  PutDispEnv(&EnvDisp[buffer]);
  PutDrawEnv(&EnvDraw[buffer]);

  SetDispMask(1);
}
