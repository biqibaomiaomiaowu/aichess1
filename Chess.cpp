#include "Chess.h"
void Chess::init()
{
	initgraph(897,895,WM_SHOWWINDOW);
	loadimage(0, "res/����2.jpg");
	mciSendString("play res/��ʼ��Ϸ(startGame)_������_aigei_com.mp3", 0, 0, 0);
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

void Chess::putimagePNG(int x, int y, IMAGE* picture) //xΪ����ͼƬ��X���꣬yΪY����
{
	// ������ʼ��
	DWORD* dst = GetImageBuffer();    // GetImageBuffer()���������ڻ�ȡ��ͼ�豸���Դ�ָ�룬EASYX�Դ�
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(picture); //��ȡpicture���Դ�ָ��
	int picture_width = picture->getwidth(); //��ȡpicture�Ŀ�ȣ�EASYX�Դ�
	int picture_height = picture->getheight(); //��ȡpicture�ĸ߶ȣ�EASYX�Դ�
	int graphWidth = getwidth();       //��ȡ��ͼ���Ŀ�ȣ�EASYX�Դ�
	int graphHeight = getheight();     //��ȡ��ͼ���ĸ߶ȣ�EASYX�Դ�
	int dstX = 0;    //���Դ������صĽǱ�

	// ʵ��͸����ͼ ��ʽ�� Cp=��p*FP+(1-��p)*BP �� ��Ҷ˹���������е���ɫ�ĸ��ʼ���
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width; //���Դ������صĽǱ�
			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA��͸����
			int sr = ((src[srcX] & 0xff0000) >> 16); //��ȡRGB���R
			int sg = ((src[srcX] & 0xff00) >> 8);   //G
			int sb = src[srcX] & 0xff;              //B
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				dstX = (ix + x) + (iy + y) * graphWidth; //���Դ������صĽǱ�
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //��ʽ�� Cp=��p*FP+(1-��p)*BP  �� ��p=sa/255 , FP=sr , BP=dr
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //��p=sa/255 , FP=sg , BP=dg
					| (sb * sa / 255 + db * (255 - sa) / 255);              //��p=sa/255 , FP=sb , BP=db
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
	}//���Ͻ�
	if (abs((lefttopx+1) * 67 + 45 - x) < 67 * 0.4 && abs(lefttopy * 67 + 45 - y) < 67 * 0.4) {
		pos->row = lefttopx+1;
		pos->col = lefttopy;
		if (chessmap[pos->row][pos->col] == 0) {
			return true;
		}
		else {
			return false;
		}
	}//���Ͻ�
	if (abs(lefttopx * 67 + 45 - x) < 67 * 0.4 && abs((lefttopy+1) * 67 + 45 - y) < 67 * 0.4) {
		pos->row = lefttopx;
		pos->col = lefttopy+1;
		if (chessmap[pos->row][pos->col] == 0) {
			return true;
		}
		else {
			return false;
		}

	}//���½�
	if (abs((lefttopx+1) * 67 + 45 - x) < 67 * 0.4 && abs((lefttopy+1) * 67 + 45 - y) < 67 * 0.4) {
		pos->row = lefttopx+1;
		pos->col = lefttopy+1;

		if (chessmap[pos->row][pos->col] == 0) {
			return true;
		}
		else {
			return false;
		}
	}//���½�
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
