#include "Chessgame.h"
#include<iostream>
Chessgame::Chessgame(Chess* chess, Man* man, Ai* ai)
{
    this->chess = chess;
    this->man = man;
    this->ai = ai;
    man->init(chess);
    ai->init(chess);
}

void Chessgame::play()
{
	chess->init();
	while (1) {
		man->go();
	if (checkOver()) {
			chess->init();
			continue;
		}

		ai->go();
	if (checkOver()) {
			chess->init();
			continue;
		}
	}
}
bool Chessgame::checkWin()
{
	// 横竖斜四种大情况，每种情况都根据当前落子往后遍历5个棋子，有一种符合就算赢
	// 水平方向
	ChessPos hh = chess->getlastpos();
	int row = hh.row;
	int col = hh.col;
	int chessMap[12][12];
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 12; j++) {
			chessMap[i][j] = chess->getchessdate(i, j);
		}
	}

	for (int i = 0; i < 5; i++)
	{
		// 往左5个，往右匹配4个子，20种情况
		if (col - i >= 0 &&
			col - i + 4 < 12 &&
			chessMap[row][col - i] == chessMap[row][col - i + 1] &&
			chessMap[row][col - i] == chessMap[row][col - i + 2] &&
			chessMap[row][col - i] == chessMap[row][col - i + 3] &&
			chessMap[row][col - i] == chessMap[row][col - i + 4])
			return true;
	}

	// 竖直方向(上下延伸4个)
	for (int i = 0; i < 5; i++)
	{
		if (row - i >= 0 &&
			row - i + 4 < 12 &&
			chessMap[row - i][col] == chessMap[row - i + 1][col] &&
			chessMap[row - i][col] == chessMap[row - i + 2][col] &&
			chessMap[row - i][col] == chessMap[row - i + 3][col] &&
			chessMap[row - i][col] == chessMap[row - i + 4][col])
			return true;
	}

	// “/"方向
	for (int i = 0; i < 5; i++)
	{
		if (row + i < 12 &&
			row + i - 4 >= 0 &&
			col - i >= 0 &&
			col - i + 4 < 12 &&
			// 第[row+i]行，第[col-i]的棋子，与右上方连续4个棋子都相同
			chessMap[row + i][col - i] == chessMap[row + i - 1][col - i + 1] &&
			chessMap[row + i][col - i] == chessMap[row + i - 2][col - i + 2] &&
			chessMap[row + i][col - i] == chessMap[row + i - 3][col - i + 3] &&
			chessMap[row + i][col - i] == chessMap[row + i - 4][col - i + 4])
			return true;
	}

	// “\“ 方向
	for (int i = 0; i < 5; i++)
	{
		// 第[row+i]行，第[col-i]的棋子，与右下方连续4个棋子都相同
		if (row - i >= 0 &&
			row - i + 4 < 12 &&
			col - i >= 0 &&
			col - i + 4 < 12 &&
			chessMap[row - i][col - i] == chessMap[row - i + 1][col - i + 1] &&
			chessMap[row - i][col - i] == chessMap[row - i + 2][col - i + 2] &&
			chessMap[row - i][col - i] == chessMap[row - i + 3][col - i + 3] &&
			chessMap[row - i][col - i] == chessMap[row - i + 4][col - i + 4])
			return true;
	}

	return false;
}
bool Chessgame::checkOver()
{
	if (checkWin()) {
		Sleep(1500);
		if (chess->getplayercolor () == false) {  //黑棋赢（玩家赢）,此时标记已经反转，轮到白棋落子
			mciSendString("play res/不错.mp3", 0, 0, 0);
			loadimage(0, "res/胜利.jpg");
		}
		else {
			mciSendString("play res/失败.mp3", 0, 0, 0);
			loadimage(0, "res/失败.jpg");
		}

		getchar(); // 补充头文件 #include <conio.h>
		return true;
	}

	return false;
}
