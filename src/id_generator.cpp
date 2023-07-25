#include "id_generator.h"

void ID_generator::addNewElement() {
    for (int i = 0; i < 8; ++i)
        workQue[i] = (node) {i, rand()};
    sort(workQue, workQue + 8);
    for (int i = 0; i < 8; ++i)
        idQue.push(workQue[i].data);
}

void ID_generator::init() {
    while (!idQue.empty()) idQue.pop();
    srand(time(NULL));
    addNewElement();
}

int ID_generator::getNewID() {
    int id = idQue.front();
    idQue.pop();
    if (idQue.size() <= 8) addNewElement();
    return ptnMap[id].first + (rand() % ptnMap[id].second + ptnMap[id].second) % ptnMap[id].second;
}

 ID_generator idGenerator;

