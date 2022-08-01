#define RUNNING 1
#define OTLEN 8
#define BUFFERSNUM 2

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

DISPENV EnvDisp[BUFFERSNUM];
DRAWENV EnvDraw[BUFFERSNUM];
u_long  OrderingTable[BUFFERSNUM][OTLEN];    // Ordering table length

int buffer = 0;

int SwapBuffer () {
  buffer = !buffer;
  return buffer;
}

void ClearOrderingTable () {
  ClearOTagR(OrderingTable[buffer], OTLEN);
}
void AddPrimToOrderingTable(TILE * tile) {
  addPrim(OrderingTable[buffer], tile);
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

int DisplayGraphics (void (*DRAWFUNC)()) {
  DRAWFUNC();

  DrawSync(0);
  VSync(0);

  int buffer = SwapBuffer();

  PutDispEnv(&EnvDisp[buffer]);
  PutDrawEnv(&EnvDraw[buffer]);
  SetDispMask(1);

  DrawOTag(OrderingTable[buffer]+OTLEN-1);

  return buffer;
}
