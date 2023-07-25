#include "src/common.h"

using namespace std;

int main() {
    // 初始化cmd，设置字符编码为UTF-8
    system("chcp 65001");

    // 初始化随机数种子
    srand(time(NULL));

    // 设置命令行窗口大小和位置
    system("mode con cols=170 lines=50");
    system("cls");

    // 隐藏光标
    isCursorDisplay(false);

    // 初始化游戏UI
    idGenerator.init();
    drawUI();
    drawLogo();
    drawWelcome();

    // 循环生成当前方块和下一个方块，直到当前方块不为不规则的值
    do currBlock = idGenerator.getNewID();
    while (currBlock >= 15 && currBlock <= 18);
    nextBlock = idGenerator.getNewID();

    // 绘制下一个方块
    drawTetris(nextBlock, 5, 16, false);

    // 绘制当前方块，并初始化游戏相关参数
    drawTetris(currBlock, nowx, nowy, false);
    drawPrediction(currBlock, false);

    // 初始化计时器和相关参数
    int timer = 0;
    startTime = clock();

    // 是否已清除过下落加速状态
    bool lastDownOptionClear = false;
    // 是否启用了持续下落加速
    bool lastDownOption = false;
    // 固定方块的计数器,用于指数级加分
    int totalFreezeCounter = 2;
    // 玩家能否手动降速
    bool canSlowDown = true;

    // 进入游戏循环
    while (true) {
        // 检查计时器是否到达方块下落时间间隔
        if (timer >= downinterval) lastDownOptionClear = false;

        // 检查计时器是否到达游戏逻辑更新时间间隔
        if (timer >= interval) {
            // 重置计时器和相关参数
            timer = lastDownOptionClear = lastDownOption = 0;

            // 如果计数器cntDown大于2，则根据cntDown的对数增加得分
            if (cntDown > 2) {
                score += (int) log(cntDown);
            }

            // 重置计数器cntDown，并进行方块堆叠和消除处理
            cntDown = 1;
            DROPTEST:
            if (placeJudge(currBlock, nowx + 1, nowy)) {
                // 如果可以向下移动方块，则进行移动操作
                drawTetris(currBlock, nowx++, nowy, true);
                drawTetris(currBlock, nowx, nowy, false);
                if (!placeJudge(currBlock, nowx + 1, nowy)) goto BLOCKFREEZE;

            } else { // 如果不能向下移动方块，则进行冻结处理
                BLOCKFREEZE:
                if (cntDown > 2) {
                    // 根据cntDown的对数增加得分
                    score += (int) log(cntDown);
                }
                cntDown = 1;
                timer = 0;
                lastDownOptionClear = lastDownOption;

                // 在堆叠区域绘制当前方块，并标记已经占用的位置
                int tmpx, tmpy;
                score += (305 - interval) * (int) log(++totalFreezeCounter);
                auto iter = dMap[currBlock].cbegin();
                for (; iter != dMap[currBlock].cend(); ++iter) {
                    tmpx = nowx + iter->first;
                    tmpy = nowy + iter->second;setCursor((tmpy + 1) << 1, tmpx + 1);
                    setColor(0);
                    drawBlock();
                    vis[tmpx][tmpy] = true;
                }
                top = top > nowx ? nowx : top;

                // 判断是否有满行，如果有则进行消除处理
                bool tflag = false, flag;
                int clrCnt = 0;
                for (int i = nowx; i < nowx + height[currBlock]; ++i, flag = true) {
                    for (int j = 0; j != 13; ++j) {
                        if (!vis[i][j]) {
                            flag = clrCnt = 0;
                            break;
                        }
                    }
                    if (flag) { // 有满行
                        clrCnt += (tflag = true);
                        for (int j = i; j >= top; --j) {
                            for (int k = 0; k ^ 13; ++k) {
                                vis[j][k] = vis[j - 1][k];setCursor((k + 1) << 1, j + 1);
                                if (vis[j][k]) drawBlock();
                                else
                                    drawSpace();
                            }
                        }
                    }
                }

                if (tflag) { // 有被消除的行
                    // 更新时间间隔和得分
                    interval = (int) (interval * 0.85);
                    if (interval < 50) canSlowDown = false;
                    drawSpeed();
                    if (clrCnt) {
                        score += ((300 - interval) << clrCnt) * (int) log(totalFreezeCounter);
                    }
                    drawLogo();
                }

                // 生成新的当前方块和下一个方块
                currBlock = nextBlock;
                nextBlock = idGenerator.getNewID();
                drawTetris(currBlock, 5, 16, true);
                drawTetris(nextBlock, 5, 16, false);
                nowx = 0, nowy = 5;
                drawPrediction(currBlock, false);
                drawTetris(currBlock, nowx, nowy, false);

                // 检查当前方块是否可以放置在初始位置，如果不可以则游戏结束
                if (!placeJudge(currBlock, nowx, nowy)) endGame(false);
            }
        }

        // 处理玩家的按键输入
        int key;
        KEYCHECK:
        if (_kbhit()) // 检查键盘输入
            if ((key = _getch()) ^ PRE) {
                // 处理方向键和其他按键的输入
                lastDownOption = lastDownOptionClear = false;
                switch (key) {
                    case 'r':
                        // 交换当前方块和下一个方块
                        if (placeJudge(nextBlock, nowx, nowy) && (currBlock ^ nextBlock)) {
                            drawTetris(currBlock, nowx, nowy, true);
                            drawTetris(nextBlock, 5, 16, true);
                            currBlock ^= nextBlock ^= currBlock ^= nextBlock;
                            drawPrediction(currBlock, true);
                            drawTetris(currBlock, nowx, nowy, false);
                            drawTetris(nextBlock, 5, 16, false);
                            if (cntDown > 2) {
                                score += (int) log(cntDown);
                            }
                            // 减去2的cntDown次幂作为惩罚
                            score -= (chBase << 1);
                            cntDown = 1;

                            // 更新时间间隔
                            interval = (int) (interval * 0.99);
                            if (interval < 50) canSlowDown = false;
                            drawSpeed();

                        }
                        goto KEYCHECK;
                        break;
                    case 'z':
                        // 改变掉落速度
                        if (cntDown > 2) {
                            score += (int) log(cntDown);
                        }
                        cntDown = 1;
                        if (interval > 10) {
                            interval -= 10;

                        }
                        drawSpeed();
                        goto KEYCHECK;
                        break;
                    case 'x':
                        // 改变掉落速度
                        if (cntDown > 2) {
                            score += (int) log(cntDown);
                        }
                        cntDown = 1;
                        if (interval < 300 && canSlowDown) {
                            interval += 10;
                        }
                        drawSpeed();
                        goto KEYCHECK;
                        break;

                    case SP:
                        // 加速方块下落
                        cntDown += (prex - nowx) << 1;
                        drawTetris(currBlock, nowx, nowy, true);
                        nowx = prex;
                        goto BLOCKFREEZE;
                        goto KEYCHECK;
                        break;
                }
            } else {
                key = _getch();
                switch (key) {
                    case UP:
                        // 旋转方块
                        lastDownOption = lastDownOptionClear = false;
                        if (cntDown > 2) {
                            score += (int) log(cntDown);
                        }
                        cntDown = 1;
                        rotate(currBlock);
                        if (placeJudge(rotate(currBlock), nowx, nowy)) {
                            drawTetris(currBlock, nowx, nowy, true);
                            currBlock = rotate(currBlock);
                            drawPrediction(currBlock, true);
                            drawTetris(currBlock, nowx, nowy, false);
                            goto KEYCHECK;
                        } else {
                        }
                        break;
                    case LT:
                        // 向左移动方块
                        lastDownOption = lastDownOptionClear = false;
                        if (cntDown > 2) {
                            score += (int) log(cntDown);
                        }
                        cntDown = 1;
                        if (placeJudge(currBlock, nowx, nowy - 1)) {
                            drawTetris(currBlock, nowx, nowy--, true);
                            drawPrediction(currBlock, true);
                            drawTetris(currBlock, nowx, nowy, false);
                            goto KEYCHECK;
                        } else {
                        }
                        break;
                    case RT:
                        // 向右移动方块
                        lastDownOption = lastDownOptionClear = false;
                        if (cntDown > 2) {
                            score += (int) log(cntDown);
                        }
                        cntDown = 1;
                        if (placeJudge(currBlock, nowx, nowy + 1)) {
                            drawTetris(currBlock, nowx, nowy++, true);
                            drawPrediction(currBlock, true);
                            drawTetris(currBlock, nowx, nowy, false);
                            goto KEYCHECK;
                        } else {
                        }
                        break;
                    case DW:
                        // 快速下落方块
                        if (!lastDownOptionClear) {
                            if (placeJudge(currBlock, nowx + 1, nowy)) {
                                drawTetris(currBlock, nowx++, nowy, true);
                                drawTetris(currBlock, nowx, nowy, false);
                                ++cntDown;
                                lastDownOption = true;
                                goto DROPTEST;
                            }
                            goto BLOCKFREEZE;
                        }
                        break;
                }
            }
        Sleep(1); // 控制游戏的帧率
        ++timer;
        drawScore();

        // 检查游戏是否结束，如果超过规定的运行时间则游戏结束
        if (clock() - startTime >= 9999990) endGame(true);
    }

    // 暂停游戏，并返回0表示正常退出
    system("pause");
    return 0;
}
