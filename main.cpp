#include<iostream>
#include"Chessgame.h"
using namespace std;

int main() {
    Chess chess(45, 45, 67.083, 12, Chess_Black);
    Man man{};
    Ai ai;
    Chessgame game(&chess, &man, &ai);
    game.play();

    getchar();
    return 0;
}

/*开发日志：
2025/4/10：
完成到man->go()函数;
2025/4/10:
已完成man—>go（）函数，下一步完善ai*/
