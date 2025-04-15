#include "Man.h"
void Man::init(Chess* chess)
{
	this->chess = chess;
}

void Man::go()
{
	MOUSEMSG msg;
	while (1) {
		msg = GetMouseMsg();
		ChessPos pos;
		if (msg.uMsg == WM_LBUTTONDOWN && chess->clickdown(msg.x, msg.y,&pos))
		{
			chess->chessdown(&pos,Chess_Black);
			break;
		}
	}



}
