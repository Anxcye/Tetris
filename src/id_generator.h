#ifndef TETRIS_ID_GENERATOR_H
#define TETRIS_ID_GENERATOR_H
#define MP(x, y) make_pair(x,y)

#include "common.h"

using namespace std;

class ID_generator {
private:
    const pair<int, int> ptnMap[8] = {
            MP(0, 2), MP(2, 1), MP(3, 4), MP(7, 4), MP(11, 4),
            MP(15, 2), MP(17, 2), MP(19, 9)
    };

    queue<int> idQue;

    struct node {
        int data, index;

        bool operator<(const node &b) const {
            return index < b.index;
        }
    } workQue[8];

    void addNewElement();

public:

    void init();

    int getNewID();

};


extern ID_generator idGenerator;


#endif //TETRIS_ID_GENERATOR_H
