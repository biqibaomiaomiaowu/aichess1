#pragma once
#include<graphics.h>
#include<easyx.h>
#include<windows.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")
#include<iostream>
struct ChessPos
{
	int row;
	int col;
	ChessPos(int r = 0, int c = 0) :row(r), col(c) {}
};
typedef enum
{
	Chess_White = -1,
	Chess_None = 0,
	Chess_Black = 1,
}Chess_kind_t;

class Chess
{
public:
	void transparentimage(int x, int y, IMAGE img);
	void init();//�����̳�ʼ��
	void chessdown(ChessPos * pos, Chess_kind_t kind);//����
	bool clickdown(int x, int y, ChessPos* pos);//�ж��Ƿ�Ϊ��Ч���
	int getgradesize();//�õ����̴�С��12��15��19��
	int getchessdate(ChessPos *pos);//�õ���λ�õ�����
	int getchessdate(int row, int col);
	int getplayercolor();//�õ���ǰ��ʲô��ɫ
	void putimagePNG(int x, int y, IMAGE* picture);
	ChessPos getlastpos();
	int* getchessmap();
	Chess(int margin_x, int margin_y, double chesssize, int gradesize, int playerflag = Chess_Black);
private:
	int margin_x;
	int margin_y;
	double chesssize;
	int gradesize;
	int playerflag=1;
	int chessmap[12][12] = { 0 };
	IMAGE Chess_white;
	IMAGE Chess_black;
	void updatechessdate(ChessPos* pos);
	ChessPos lastPos; //�������λ��, Chess��private���ݳ�Ա
};

