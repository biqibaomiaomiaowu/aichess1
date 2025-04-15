#pragma once
#include"Chess.h"
#include"Man.h"
#include"Ai.h"
class Chessgame
{public:
	Chessgame(Chess *chess,Man *man,Ai *ai);
	void play();
	bool checkOver();
	bool checkWin();
private:
	Chess *chess;
	Man* man;
	Ai* ai;
};

