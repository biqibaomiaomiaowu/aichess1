#include "Chess.h"
void Chess::init()
{
	initgraph(897,895,WM_SHOWWINDOW);
	loadimage(0, "res/棋盘2.jpg");
	mciSendString("play res/开始游戏(startGame)_爱给网_aigei_com.mp3", 0, 0, 0);
	loadimage(&Chess_white, "res/white.png");
	loadimage(&Chess_black, "res/black.png");
}
//void Chess::chessdown(ChessPos* pos, Chess_kind_t kind)
//{
//	if (kind == Chess_Black) {
//		int x= pos->row * 67 + 45 - 67 / 2;
//		int y= pos->col * 67 + 45 - 67 / 2;
//		putimagePNG(x,y,&Chess_black);
//		mciSendString("play res/down7.wav", 0, 0, 0);
//		updatechessdate(pos);
//	}
//	if (kind == Chess_White) {
//		int x = pos->row * 67 + 45 - 67 / 2;
//		int y = pos->col * 67 + 45 - 67 / 2;
//		putimagePNG(x, y, &Chess_white);
//		mciSendString("play res/down7.wav", 0, 0, 0); 
//	updatechessdate(pos);
//}
//
//
//}
void Chess::chessdown(ChessPos* pos, Chess_kind_t kind)
{
	int x = pos->row * 67 + 45 - 67 / 2;
	int y = pos->col * 67 + 45 - 67 / 2;

	if (kind == Chess_Black) {
		putimagePNG(x, y, &Chess_black);
	}
	else if (kind == Chess_White) {
		putimagePNG(x, y,& Chess_white);
	}
	else {
		// Handle invalid kind
		return;
	}

	mciSendString("play res/down7.wav", 0, 0, 0);
	updatechessdate(pos);
}

//void Chess::chessdown(ChessPos* pos, Chess_kind_t kind)
//{
//	mciSendString("play res/down7.WAV", 0, 0, 0);
//
//	int x = margin_x + pos->col * 67.083 - 0.5 * 67.083;
//	int y = margin_y + pos->row * 67.083 - 0.5 * 67.083;
//
//	if (kind == Chess_White) {
//		putimagePNG(x, y, &Chess_white);
//	}
//	else {
//		putimagePNG(x, y, &Chess_black);
//	}
//
//}

void Chess::putimagePNG(int x, int y, IMAGE* picture) //x为载入图片的X坐标，y为Y坐标
{
	// 变量初始化
	DWORD* dst = GetImageBuffer();    // GetImageBuffer()函数，用于获取绘图设备的显存指针，EASYX自带
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(picture); //获取picture的显存指针
	int picture_width = picture->getwidth(); //获取picture的宽度，EASYX自带
	int picture_height = picture->getheight(); //获取picture的高度，EASYX自带
	int graphWidth = getwidth();       //获取绘图区的宽度，EASYX自带
	int graphHeight = getheight();     //获取绘图区的高度，EASYX自带
	int dstX = 0;    //在显存里像素的角标

	// 实现透明贴图 公式： Cp=αp*FP+(1-αp)*BP ， 贝叶斯定理来进行点颜色的概率计算
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width; //在显存里像素的角标
			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA是透明度
			int sr = ((src[srcX] & 0xff0000) >> 16); //获取RGB里的R
			int sg = ((src[srcX] & 0xff00) >> 8);   //G
			int sb = src[srcX] & 0xff;              //B
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				dstX = (ix + x) + (iy + y) * graphWidth; //在显存里像素的角标
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //公式： Cp=αp*FP+(1-αp)*BP  ； αp=sa/255 , FP=sr , BP=dr
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //αp=sa/255 , FP=sg , BP=dg
					| (sb * sa / 255 + db * (255 - sa) / 255);              //αp=sa/255 , FP=sb , BP=db
			}
		}
	}
}
void Chess::transparentimage(int x, int y, IMAGE img) {
	IMAGE img1;
	DWORD* d1;
	img1 = img;
	d1 = GetImageBuffer(&img1);
	float h, s, l;
	for (int i = 0; i < img1.getheight() * img1.getwidth(); i++) {
		RGBtoHSL(BGR(d1[i]), &h, &s, &l);
		if (l < 0.03) {
			d1[i] = BGR(WHITE);
		}
		if (d1[i] != BGR(WHITE)) {
			d1[i] = 0;
		}
	}
	putimage(x, y, &img1, SRCAND);
	putimage(x, y, &img, SRCPAINT);
	//	putimage(x+100,y,&img1);
	//	putimage(x+200,y,&img);
}
bool Chess::clickdown(int x, int y, ChessPos* pos)
{
	int lefttopx = (x - 45) / 67;
	int lefttopy = (y - 45) / 67;
	if (abs(lefttopx * 67 + 45 - x) < 67 * 0.4 && abs(lefttopy * 67 + 45 - y) < 67 * 0.4) {
		pos->row = lefttopx;
		pos->col = lefttopy;
		if (chessmap[pos->row][pos->col] == 0) {
			return true;
		}
		else {
			return false;
		}
	}//左上角
	if (abs((lefttopx+1) * 67 + 45 - x) < 67 * 0.4 && abs(lefttopy * 67 + 45 - y) < 67 * 0.4) {
		pos->row = lefttopx+1;
		pos->col = lefttopy;
		if (chessmap[pos->row][pos->col] == 0) {
			return true;
		}
		else {
			return false;
		}
	}//右上角
	if (abs(lefttopx * 67 + 45 - x) < 67 * 0.4 && abs((lefttopy+1) * 67 + 45 - y) < 67 * 0.4) {
		pos->row = lefttopx;
		pos->col = lefttopy+1;
		if (chessmap[pos->row][pos->col] == 0) {
			return true;
		}
		else {
			return false;
		}

	}//左下角
	if (abs((lefttopx+1) * 67 + 45 - x) < 67 * 0.4 && abs((lefttopy+1) * 67 + 45 - y) < 67 * 0.4) {
		pos->row = lefttopx+1;
		pos->col = lefttopy+1;

		if (chessmap[pos->row][pos->col] == 0) {
			return true;
		}
		else {
			return false;
		}
	}//右下角
	return false;
}

int Chess::getgradesize()
{
	return 0;
}


int Chess::getchessdate(ChessPos* pos)
{
	
	return 0;
}

int Chess::getchessdate(int row, int col)
{
	return chessmap[row][col];
}

int Chess::getplayercolor()
{
	return playerflag;
}
void Chess::updatechessdate(ChessPos* pos) {
	lastPos = *pos;
	chessmap[pos->row][pos->col] = playerflag;
	playerflag = -playerflag;
}

ChessPos Chess::getlastpos() {
	return lastPos;
}
int* Chess::getchessmap() {
	return &chessmap[0][0];
}
Chess::Chess(int margin_x, int margin_y, double chesssize, int gradesize, int playerflag)
{
	this->margin_x = margin_x;
	this->margin_y = margin_y;
	this->chesssize = chesssize;
	this->gradesize = gradesize;
	this->playerflag = playerflag;
}
