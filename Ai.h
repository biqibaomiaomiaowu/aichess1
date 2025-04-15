#pragma once
#include"Chess.h"
#include<vector>
class Ai
{public:
	void init(Chess* chess);
	void go();
	void pointsscore();
private:
	Chess* chess;
	ChessPos down;
	int scoremap[12][12] = { 0 };
	ChessPos think();
};

