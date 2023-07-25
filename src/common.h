#ifndef COMMON_H
#define COMMON_H

#pragma GCC optimize ("Ofast", 3)
#pragma GCC target ("sse3", "sse2", "sse")
#pragma GCC target ("avx", "sse4", "sse4.1", "sse4.2", "ssse3")
#pragma GCC target ("f16c")

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <string>
#include <queue>
#include <ctime>
#include <fstream>
#include <algorithm>
#include <windows.h>
#include <conio.h>
#include "dmap.h"
#include "id_generator.h"
#include "cursor.h"
#include "ui.h"
#include "ranklist.h"


using namespace std;


#define a1 0
#define a2 1

#define b1 2

#define c1 3
#define c2 4
#define c3 5
#define c4 6

#define n1 7
#define n2 8
#define n3 9
#define n4 10

#define d1 11
#define d2 12
#define d3 13
#define d4 14

#define e1 15
#define e2 16

#define f1 17
#define f2 18

#define g1 19

#define h1 20
#define h2 21
#define h3 22
#define h4 23

#define k1 24
#define k2 25

#define m1 26
#define m2 27

#define PRE 224
#define UP  72
#define LT  75
#define RT  77
#define DW  80
#define SP  32


#define maxl 24
#define maxh 26

#define downinterval 50

#define placeLegal() ((~tmpx) && (tmpx<25) && (~tmpy) && (tmpy<13) && !vis[tmpx][tmpy])



extern bool vis[28][16];


#define logStartX (27<<1)
#define logStartY 9

struct node {
    string str;
    int color;
};

extern clock_t startTime;
extern const string empStr;
extern string username;

extern long long score, chBase;
extern int preName, prex, prey;


extern int top, nowx, nowy, currBlock, nextBlock, interval, cntDown;


#endif // COMMON_H
