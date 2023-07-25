#ifndef TETRIS_RANKLIST_H
#define TETRIS_RANKLIST_H

#include "common.h"

using namespace std;


extern void readRankList();

extern void writeRankList();

extern void updateRankList();

extern void drawRankList(int, int, int);


struct rankElement {
    string name;
    long long score;
};

extern rankElement rankList[20];

bool placeJudge(int, int, int);

void endGame(bool);

#endif //TETRIS_RANKLIST_H
