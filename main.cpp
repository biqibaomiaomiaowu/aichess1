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

/*������־��
2025/4/10��
��ɵ�man->go()����;
2025/4/10:
�����man��>go������������һ������ai*/
