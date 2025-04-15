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
	// ����б���ִ������ÿ����������ݵ�ǰ�����������5�����ӣ���һ�ַ��Ͼ���Ӯ
	// ˮƽ����
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
		// ����5��������ƥ��4���ӣ�20�����
		if (col - i >= 0 &&
			col - i + 4 < 12 &&
			chessMap[row][col - i] == chessMap[row][col - i + 1] &&
			chessMap[row][col - i] == chessMap[row][col - i + 2] &&
			chessMap[row][col - i] == chessMap[row][col - i + 3] &&
			chessMap[row][col - i] == chessMap[row][col - i + 4])
			return true;
	}

	// ��ֱ����(��������4��)
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

	// ��/"����
	for (int i = 0; i < 5; i++)
	{
		if (row + i < 12 &&
			row + i - 4 >= 0 &&
			col - i >= 0 &&
			col - i + 4 < 12 &&
			// ��[row+i]�У���[col-i]�����ӣ������Ϸ�����4�����Ӷ���ͬ
			chessMap[row + i][col - i] == chessMap[row + i - 1][col - i + 1] &&
			chessMap[row + i][col - i] == chessMap[row + i - 2][col - i + 2] &&
			chessMap[row + i][col - i] == chessMap[row + i - 3][col - i + 3] &&
			chessMap[row + i][col - i] == chessMap[row + i - 4][col - i + 4])
			return true;
	}

	// ��\�� ����
	for (int i = 0; i < 5; i++)
	{
		// ��[row+i]�У���[col-i]�����ӣ������·�����4�����Ӷ���ͬ
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
		if (chess->getplayercolor () == false) {  //����Ӯ�����Ӯ��,��ʱ����Ѿ���ת���ֵ���������
			mciSendString("play res/����.mp3", 0, 0, 0);
			loadimage(0, "res/ʤ��.jpg");
		}
		else {
			mciSendString("play res/ʧ��.mp3", 0, 0, 0);
			loadimage(0, "res/ʧ��.jpg");
		}

		getchar(); // ����ͷ�ļ� #include <conio.h>
		return true;
	}

	return false;
}
