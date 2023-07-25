


#include "cursor.h"

int rotate(int name) {

    int nameRet;

    switch (name) {
        case a1:
            nameRet = a2;
            break;
        case a2:
            nameRet = a1;
            break;

        case b1:
            nameRet = b1;
            break;

        case c1:
            nameRet = c2;
            break;
        case c2:
            nameRet = c3;
            break;
        case c3:
            nameRet = c4;
            break;
        case c4:
            nameRet = c1;
            break;

        case n1:
            nameRet = n2;
            break;
        case n2:
            nameRet = n3;
            break;
        case n3:
            nameRet = n4;
            break;
        case n4:
            nameRet = n1;
            break;

        case d1:
            nameRet = d2;
            break;
        case d2:
            nameRet = d3;
            break;
        case d3:
            nameRet = d4;
            break;
        case d4:
            nameRet = d1;
            break;

        case e1:
            nameRet = e2;
            break;
        case e2:
            nameRet = e1;
            break;

        case f1:
            nameRet = f2;
            break;
        case f2:
            nameRet = f1;
            break;

        case g1:
            nameRet = g1;
            break;

        case h1:
            nameRet = h2;
            break;
        case h2:
            nameRet = h3;
            break;
        case h3:
            nameRet = h4;
            break;
        case h4:
            nameRet = h1;
            break;

        case k1:
            nameRet = k2;
            break;
        case k2:
            nameRet = k1;
            break;

        case m1:
            nameRet = m2;
            break;
        case m2:
            nameRet = m1;
            break;
    }

    static const pair<int, int> ddp[8] = {MP(0, 1), MP(0, -1), MP(-1, 0), \
        MP(-1, 1), MP(-1, -1), MP(0, -2), MP(0, -3), MP(0, -4)};

    int tmpx, tmpy;

    if (!placeJudge(nameRet, nowx, nowy)) {
        for (int i = 0; i ^ 7; ++i) {
            tmpx = nowx + ddp[i].first, \
            tmpy = nowy + ddp[i].second;
            if (placeJudge(nameRet, tmpx, tmpy)) {
                drawTetris(currBlock, nowx, nowy, true);
                nowx = tmpx, nowy = tmpy;
                break;
            }
        }
    }
    return nameRet;
}

// 是否显示光标
void isCursorDisplay(bool flag) {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO CursorInfo;
    GetConsoleCursorInfo(handle, &CursorInfo);
    CursorInfo.bVisible = flag;
    SetConsoleCursorInfo(handle, &CursorInfo);
}

// 设置字符颜色
void setColor(int color) {
    switch (color % 5) {
        case 0:
            color = 0x08; // 0x08 黑色
            break;
        case 1:
            color = 0x0C; // 0x0C 红色
            break;
        case 2:
            color = 0x0D; // 0x0D 紫色
            break;
        case 3:
            color = 0x0E; // 0x0E 黄色
            break;
        case 4:
            color = 0x0A; // 0x0A 绿色
            break;
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}