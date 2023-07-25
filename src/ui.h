#ifndef TETRIS_UI_H
#define TETRIS_UI_H

#define logoStartX (28 * 2)
#define logoStartY 3

#include "common.h"


#define fontColorReset() SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7)
#define setCursor(x, y); {COORD tmpSC;tmpSC.X=x,tmpSC.Y=y;SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),tmpSC);}


using namespace std;


extern void drawDataInt(int, int);

extern void drawScore();

extern void drawChBase();

extern void drawLogo();

extern void drawName();


#define drawBlock() printf("■")
#define drawSpace() printf("  ")

extern void drawWelcome();

extern void drawUI();

extern void drawSpeed();

extern void drawTetris(int, int, int, bool);

extern void drawPrediction(int, bool);

extern const vector<int> logoMap[5];


#endif //TETRIS_UI_H
