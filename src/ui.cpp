#include "ui.h"

bool vis[28][16];

void drawDataInt(int num, int y) {
    setCursor(30, y);
    for (int i = 0; i < 16; ++i) putchar(' ');
    int cnt = 0, a = num;
    setColor(3);setCursor(30, y);
    while (a /= 10) ++cnt;
    cnt = (16 - cnt) >> 1;
    while (cnt--) putchar(' ');
    printf("%d", num);
}


void drawScore() {
    static char cMap[5] = {' ', 'K', 'M', 'G', 'T'};
    int cnt = 0, cPos = 0, winFlag = 0;
    long long a = score;
    bool minusFlag = false;
    if (a < 0ll) a = -a, minusFlag = true, ++cnt;

    while (a /= 10ll) ++cnt;
    a = score;
    if (cnt >= 16) winFlag = a > 0 ? 2 : 1;
    while (cnt > 8) { cnt -= 2, a /= 1000, ++cPos; }
    cnt = (16 - cnt) >> 1;setCursor(30, 19);
    printf("                ");
    setColor(3);setCursor(30, 19);
    while (cnt--) putchar(' ');
    printf("%lld", a);
    /*fontColorReset();*/ setColor(1);
    putchar(cMap[cPos]);
    if (winFlag) endGame(winFlag < 1);
}

void drawName() {
    int cnt = (16 - username.length()) / 2;setCursor(30, 13);
    fontColorReset();
    while (cnt--) putchar(' ');
    std::cout << username;
    return;
}

void drawChBase() {
    setCursor(30, 15);
    printf("                ");
    static char cMap[4] = {' ', 'K', 'M', 'G'};
    int cnt = 0, cPos = 0;
    long long a = chBase;
    setColor(3);setCursor(30, 15);
    while (a /= 10ll) ++cnt;
    a = chBase;
    if (cnt >= 16) endGame(false);//drawGameOver();
    while (cnt > 8) {
        cnt -= 2, a /= 1000, ++cPos;
        if (cPos > 3) endGame(false);//drawGameOver();
    }
    cnt = (16 - cnt) >> 1;
    while (cnt--) putchar(' ');
    printf("%lld", a);
    /*fontColorReset();*/ setColor(1);
    putchar(cMap[cPos]);
}

const vector<int> logoMap[5] = {
        {0, 4, 8, 9,  13, 17, 18, 20, 24},
        {1, 2, 5, 11, 14, 17, 19, 21},
        {1, 2, 5, 6,  7,  11, 14, 15, 16, 19, 21, 22, 23, 24},
        {1, 2, 5, 11, 14, 16, 19, 24},
        {0, 0, 1, 3,  4,  8,  9,  10, 12, 13, 15, 16, 18, 20, 24}
};

// 画出logo
void drawLogo() {
    int colorOffset = rand();
    for (int i = 0; i < 5; ++i) {
        auto iter = logoMap[i].begin();
        bool flag = *iter;
        if (!flag) { setCursor(logoStartX, logoStartY + i);
            for (int j = 0; j < 25; ++j) {
                setColor(i + j + colorOffset);
                printf(rand() % 3 ? "□" : "■");
            }
        }

        for (++iter; iter != logoMap[i].end(); ++iter) { setCursor(logoStartX + (*iter * 2), logoStartY + i);
            setColor(i + ((*iter) * 2) + colorOffset);
            printf(flag ? (rand() % 3 ? "□" : "■") : "  ");
        }
    }
}

// 显示欢迎界面
void drawWelcome() {
    fontColorReset();
    setCursor(logStartX, logStartY + 1);    printf("Welcome to Tetris!");
    setCursor(logStartX, logStartY + 3);    printf("[↑] 旋转方块");
    setCursor(logStartX, logStartY + 4);    printf("[←] [→] 移动方块");
    setCursor(logStartX, logStartY + 5);    printf("[↓] 加速下落");
    setCursor(logStartX, logStartY + 6);    printf("[空格] 直接落地");
    setCursor(logStartX, logStartY + 7);    printf("[R] 交换当前与下一个方块");
    setCursor(logStartX, logStartY + 8);    printf("[Z] [X] 加减速度");
    setCursor(logStartX, logStartY + 9);    printf("输入玩家名: ");
    isCursorDisplay(true);
    std::cin >> username;

    setCursor(logStartX, logStartY + 11);
    printf("分数排行: ");
    readRankList();
    updateRankList();
    drawRankList(logStartX + 9, logStartY + 11, 5);
    fontColorReset();

    setCursor(logStartX, logStartY + 16);
    printf("按[E]开始游戏        Tetris, 启动！");setCursor(logStartX, logStartY + 17);


    isCursorDisplay(false);
    drawName();

    while (!_kbhit() || (_getch() != 'e')) Sleep(100);

    setCursor(logStartX, logStartY + 16);
    cout << empStr;
}

void drawUI() {
    setColor(3);
    // 游戏上下两侧
    for (int i = 0; i < 15; ++i) { setCursor(i * 2, 0);
        printf("##"); //drawBlock();
        setCursor(i * 2, maxh);
        printf("##"); //drawBlock();
    }
    // 信息上中下
    for (int i = 15; i < 23; ++i) { setCursor(i * 2, 0);
        printf("=");setCursor(i * 2, 10);
        printf("=");setCursor(i * 2, maxh);
        printf("=");
    }
    // 纵向三条界线
    for (int i = 0; i < maxh; ++i) { setCursor(0, i);
        printf("##");setCursor(maxl + 4, i);
        printf("##");

        setCursor(maxl + 22, i);
        printf("||");
    }
    // 顶点
//    setCursor(0, 0);
//    printf("□");
//    setCursor(0, maxh);
//    printf("□");
    setCursor(14 * 2, 0);
    printf("〇=");setCursor(14 * 2, maxh);
    printf("〇=");setCursor((23 * 2) - 2, 0);
    putchar('=');setCursor((23 * 2) - 2, 10);
    putchar('=');setCursor((23 * 2) - 2, maxh);
    putchar('=');setCursor(23 * 2, 0);
    printf("〇");setCursor(23 * 2, 10);
    printf("〇");setCursor(23 * 2, maxh);
    printf("〇");

    // 信息显示
    fontColorReset();setCursor(36, 2);
    printf("NEXT");
//    setCursor(36, 13);
//    printf("Base");
    setCursor(35, 17);
    printf("SCORE");setCursor(35, 21);
    printf("SPEED");
    drawSpeed();

    setCursor(0, 27);
    printf("TEAM 18");setCursor(0, 28);
    printf("XMU 2023");
}

void drawTetris(int name, int x, int y, bool re) {
    int tmpx, tmpy, cnt = 0;
    auto iter = dMap[name].begin();
    for (; iter != dMap[name].end(); ++iter, ++cnt) {
        tmpx = x + iter->first;
        tmpy = y + iter->second;setCursor((tmpy + 1) * 2, tmpx + 1);
        if (re) drawSpace();
        else {
            setColor(cnt + 1);
            drawBlock();
        }
    }
}

void drawPrediction(int name, bool isClr) {
    int tmpx, tmpy;
    auto iter = dMap[preName].begin();
    if (isClr)
        for (; iter != dMap[preName].end(); ++iter) {
            tmpx = prex + iter->first;
            tmpy = prey + iter->second;setCursor((tmpy + 1) << 1, tmpx + 1);
            drawSpace();
        }

    int x = nowx - 1, y = nowy, cnt = 0;
    while (placeJudge(name, ++x, y));
    x--;

    iter = dMap[name].begin();
    for (; iter != dMap[name].end(); ++iter, ++cnt) {
        tmpx = x + iter->first;
        tmpy = y + iter->second;setCursor((tmpy + 1) << 1, tmpx + 1);
        setColor(cnt + 1);
        printf("□");
    }
    prex = x, prey = y, preName = name;
}

extern void drawSpeed() {
    fontColorReset();setCursor(36, 23);
    printf("%03d", 310 - interval);
}



