


#include "ranklist.h"

rankElement rankList[20];
fstream file;


// 读取排行榜
void readRankList() {
    for (int i = 0; i < 10; ++i)
        rankList[i] = (rankElement) {"", 0};

    file.open("tetrisRanking.dat", ios::in);
    for (int i = 0; i < 10; ++i) {
        if (file >> rankList[i].name)
            file >> rankList[i].score;
        else
            break;
    }
    file.close();
}

void writeRankList() {

    file.open("tetrisRanking.dat", ios::out | ios::trunc);
    for (int i = 0; i < 10; ++i) {
        if (rankList[i].name == "") break;
        file << rankList[i].name << " " << rankList[i].score << endl;
    }
    file.close();


}

bool cmp(rankElement a, rankElement b) {
    return (a.score ^ b.score) ? (a.score > b.score) : (a.name > b.name);
}

// 更新排行榜
void updateRankList() {
    int listLen = 0, pos = -1;
    while (true) {
        if (rankList[listLen].name == username) pos = listLen;
        if (rankList[listLen].name == "") break;
        ++listLen;
    }
    if (pos == -1) pos = listLen; else --listLen;
    rankList[pos] = (rankElement) {username, max(rankList[pos].score, score)};
    std::sort(rankList + 0, rankList + listLen + 1, cmp);
}

void drawRankList(int X, int Y, int num) {
    fontColorReset();
    for (int i = 0; i < num; ++i) {
        if (rankList[i].name == "") break;
        if (rankList[i].name == username) setColor(3);
        else
            fontColorReset();setCursor(X, Y + i);
        printf("#%02d ", i + 1);
        std::cout << rankList[i].name;setCursor(X + 11, Y + i);
        printf("%23lld", rankList[i].score);
    }
}

bool placeJudge(int name, int x, int y) {
    int tmpx, tmpy;
    auto iter = dMap[name].begin();
    for (; iter != dMap[name].end(); ++iter) {
        tmpx = x + iter->first;
        tmpy = y + iter->second;
        if (!placeLegal()) return false;
    }
    return true;
}


void endGame(bool isWin) {
    updateRankList();
    writeRankList();

    for (int i = 0; i < 17; ++i) { setCursor(logStartX, logStartY + i);
        std::cout << empStr;
    }

    fontColorReset();setCursor(logStartX, logStartY);
    printf(isWin ? "获胜" : "游戏结束");setCursor(logStartX, logStartY + 2);
    printf("得分是: ");
    setColor(3);
    printf("%lld", score);
    fontColorReset();setCursor(logStartX, logStartY + 4);
    printf("成绩排行: ");
    drawRankList(logStartX + 9, logStartY + 5, 10);
    fontColorReset();

    setCursor(logStartX, logStartY + 16)
    printf("按[Q]退出");
    drawUI();
    while (!_kbhit() || (_getch() ^ 'q')) Sleep(100);
    fontColorReset();
    system("cls");
    exit(0);
}

