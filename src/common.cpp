
#include "common.h"

long long score, chBase = 1ll;

int preName = -1, prex, prey;


int top = 25, nowx, nowy = 5, currBlock, nextBlock, interval = 300, cntDown = 1;

const string empStr = "                                                               ";


int height[28] = {4, 1, 2, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 1, 2, 2, 2, 2, 1, 3, 2, 1};


#define logStartX (27<<1)
#define logStartY 9


clock_t startTime;

string username;

// char buff[1001];
