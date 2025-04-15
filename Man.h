#pragma once
#include"Chess.h"
#include<graphics.h>
#include<iostream>
class Man
{public:
	void init(Chess* chess);
	void go();
private:
	Chess* chess;
};

