#include "Ai.h"
#include<vector>
using namespace std;
void Ai::init(Chess* chess)
{
	this->chess = chess;
}

void Ai::go()
{
	ChessPos hah;
	hah = think();
	chess->chessdown(&hah,Chess_White);
    cout << "aa";
}
//void Ai::pointsscore()
//{
//	for (int i = 0; i < 12; i++) {
//		for (int j = 0; j < 12; j++) {
//			scoremap[i][j] = 0;
//		}
//	}
//	for (int i = 0; i < 12; i++) {
//		for (int j = 0; j < 12; j++) {
//			if (chess->getchessdate(i, j) != 0) {
//				continue;
//			}
//
//			for (int y = -1; y <= 0; y++) {
//				for (int x = -1; x <= 1; x++) {
//					int personnub = 0;
//					int emptynub = 0;
//					int Ainub = 0;
//					if (y == 0 && x == 0) {
//						continue;
//					}
//					if (y == 0 && x != 1) {
//						continue;
//					}
//					//对白棋评分
//					//正向
//					for (int p = 1; p <= 4; p++) {
//						if (!(0 <= i - x * p && i - x * p <= 12 && 0 <= j - y * p && j - y * p <= 12)) {
//							continue;
//						}
//						if (chess->getchessdate(i - x * p, j - y * p) == -1) {
//							Ainub++;
//						}
//						if (chess->getchessdate(i - x * p, j - y * p) == 0) {
//							emptynub++;
//							break;
//						}
//						if (chess->getchessdate(i - x * p, j - y * p) == 1) {
//							break;
//						}
//						//反向
//						for (int p = 1; p <= 4; p++) {
//							if (!(0 <= i + x * p && i + x * p <= 12 && 0 <= j + y * p && j + y * p <= 12)) {
//								continue;
//							}
//							if (chess->getchessdate(i + x * p, j + y * p) == -1) {
//								Ainub++;
//							}
//							if (chess->getchessdate(i + x * p, j + y * p) == 0) {
//								emptynub++;
//								break;
//							}
//							if (chess->getchessdate(i + x * p, j + y * p) == 1) {
//								break;
//							}
//						}
//						if (Ainub == 0) {
//							scoremap[i][j] += 5;
//						}
//						if (Ainub == 1) {
//							scoremap[i][j] += 10;
//						}
//						if (Ainub == 2) {
//							if (emptynub == 1) {
//								scoremap[i][j] += 25;
//							}
//							if (emptynub == 2) {
//								scoremap[i][j] += 50;
//							}
//						}
//						if (Ainub == 3) {
//							if (emptynub == 1) {
//								scoremap[i][j] += 5;
//							}
//							if (emptynub == 2) {
//								scoremap[i][j] += 1000;
//							}
//						}
//						if (Ainub == 4) {
//							scoremap[i][j] += 20000;
//						}
//
//
//						//对黑棋评分
//
//						emptynub = 0;
//						for (int p = 1; p <= 4; p++) {
//							if (!(0 <= i - x * p && i - x * p <= 12 && 0 <= j - y * p && j - y * p <= 12)) {
//								continue;
//							}
//							if (chess->getchessdate(i - x * p, j - y * p) == -1) {
//								break;
//							}
//							if (chess->getchessdate(i - x * p, j - y * p) == 0) {
//								emptynub++;
//								break;
//							}
//							if (chess->getchessdate(i - x * p, j - y * p) == 1) {
//								personnub++;
//							}
//						}
//						//反向
//						for (int p = 1; p <= 4; p++) {
//							if (!(0 <= i + x * p && i + x * p <= 12 && 0 <= j + y * p && j + y * p <= 12)) {
//								continue;
//							}
//							if (chess->getchessdate(i + x * p, j + y * p) == -1) {
//								break;
//							}
//							if (chess->getchessdate(i + x * p, j + y * p) == 0) {
//								emptynub++;
//								break;
//							}
//							if (chess->getchessdate(i + x * p, j + y * p) == 1) {
//								personnub++;
//								break;
//							}
//						}
//						if (personnub == 1) {
//							scoremap[i][j] += 10;
//						}
//
//						if (personnub == 2) {
//							if (emptynub == 1) {
//								scoremap[i][j] += 30;
//							}
//							if (emptynub == 2) {
//								scoremap[i][j] += 40;
//							}
//						}
//						if (personnub == 3) {
//							if (emptynub == 1) {
//								scoremap[i][j] += 60;
//							}
//							if (emptynub == 2) {
//								scoremap[i][j] += 200;
//							}
//						}
//						if (personnub == 4) {
//							scoremap[i][j] += 20000;
//						}
//
//
//					}
//				}
//
//
//
//
//
//
//
//
//			}
//		}
//	}
//}
 void Ai::pointsscore()
{
	int personNum = 0; //棋手方（黑棋）多少个连续的棋子
	int aiNum = 0; //AI方（白棋）连续有多少个连续的棋子
	int emptyNum = 0; // 该方向上空白位的个数

	// 评分向量数组清零
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 12; j++) {
			scoremap[i][j] = 0;
		}
	}

	int size = 12;
	for (int row = 0; row < size; row++) {
		for (int col = 0; col < size; col++) {
			//对每个点进行计算
			if (chess->getchessdate(row, col)) continue;

			for (int y = -1; y <= 0; y++) {        //Y的范围还是-1， 0
				for (int x = -1; x <= 1; x++) {    //X的范围是 -1,0,1
					if (y == 0 && x == 0) continue;
					if (y == 0 && x != 1) continue; //当y=0时，仅允许x=1

					personNum = 0;
					aiNum = 0;
					emptyNum = 0;

					// 假设黑棋在该位置落子，会构成什么棋型
					for (int i = 1; i <= 4; i++) {
						int curRow = row + i * y;
						int curCol = col + i * x;

						if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getchessdate(curRow, curCol) == 1) {
							personNum++;
						}
						else if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getchessdate(curRow, curCol) == 0) {
							emptyNum++;
							break;
						}
						else {
							break;
						}
					}

					// 反向继续计算
					for (int i = 1; i <= 4; i++) {
						int curRow = row - i * y;
						int curCol = col - i * x;

						if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getchessdate(curRow, curCol) == 1) {
							personNum++;
						}
						else if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getchessdate(curRow, curCol) == 0) {
							emptyNum++;
							break;
						}
						else {
							break;
						}
					}

					if (personNum == 1) { //连2
						//CSDN  程序员Rock
						scoremap[row][col] += 10;
					}
					else if (personNum == 2) {
						if (emptyNum == 1) {
							scoremap[row][col] += 30;
						}
						else if (emptyNum == 2) {
							scoremap[row][col] += 40;
						}
					}
					else if (personNum == 3) {
						if (emptyNum == 1) {
							scoremap[row][col] = 60;
						}
						else if (emptyNum == 2) {
							scoremap[row][col] = 5000; //200
						}
					}
					else if (personNum == 4) {
						scoremap[row][col] = 20000;
					}

					// 假设白棋在该位置落子，会构成什么棋型
					emptyNum = 0;

					for (int i = 1; i <= 4; i++) {
						int curRow = row + i * y;
						int curCol = col + i * x;

						if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getchessdate(curRow, curCol) == -1) {
							aiNum++;
						}
						else if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getchessdate(curRow, curCol) == 0) {
							emptyNum++;
							break;
						}
						else {
							break;
						}
					}

					for (int i = 1; i <= 4; i++) {
						int curRow = row - i * y;
						int curCol = col - i * x;

						if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getchessdate(curRow, curCol) == -1) {
							aiNum++;
						}
						else if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getchessdate(curRow, curCol) == 0) {
							emptyNum++;
							break;
						}
						else {
							break;
						}
					}

					if (aiNum == 0) {
						scoremap[row][col] += 5;
					}
					else if (aiNum == 1) {
						scoremap[row][col] += 10;
					}
					else if (aiNum == 2) {
						if (emptyNum == 1) {
							scoremap[row][col] += 25;
						}
						else if (emptyNum == 2) {
							scoremap[row][col] += 50;
						}
					}
					else if (aiNum == 3) {
						if (emptyNum == 1) {
							scoremap[row][col] += 55;
						}
						else if (emptyNum == 2) {
							scoremap[row][col] += 10000;
						}
					}
					else if (aiNum >= 4) {
						scoremap[row][col] += 30000;
					}
				}
			}
		}
	}
}
//ChessPos Ai::think() 
//{
//	pointsscore();
//	down.row = 0;
//	down.col = 0;
//	for (int i = 0; i < 12; i++) {
//		for (int j = 0; j < 12; j++) {
//			if (scoremap[i][j] > scoremap[down.row][down.col]) {
//				down.row = i;
//				down.col = j;
//			}
//		}
//	}
//	return down;
//}
//void Ai::pointsscore()
//{
//    // 统计玩家或者电脑连成的子
//    int personNum = 0;  // 玩家连成子的个数
//    int botNum = 0;     // AI连成子的个数
//    int emptyNum = 0;   // 各方向空白位的个数
//
//    // 清空评分数组
//    for (int i = 0; i < 12; i++) {
//        for (int j = 0; j < 12; j++) {
//            scoremap[i][j] = 0;
//        }
//    }
//
//    int size = 12;
//    for (int row = 0; row < size; row++)
//        for (int col = 0; col < size; col++)
//        {
//            // 空白点就算
//            if (chess->getchessdate(row, col) == 0) {
//                // 遍历周围八个方向
//                for (int y = -1; y <= 1; y++) {
//                    for (int x = -1; x <= 1; x++)
//                    {
//                        // 重置
//                        personNum = 0;
//                        botNum = 0;
//                        emptyNum = 0;
//
//                        // 原坐标不算
//                        if (!(y == 0 && x == 0))
//                        {
//                            // 每个方向延伸4个子
//                            // 对黑棋评分（正反两个方向）
//                            for (int i = 1; i <= 4; i++)
//                            {
//                                int curRow = row + i * y;
//                                int curCol = col + i * x;
//                                if (curRow >= 0 && curRow < size &&
//                                    curCol >= 0 && curCol < size &&
//                                    chess->getchessdate(curRow, curCol) == 1) // 真人玩家的子
//                                {
//                                    personNum++;
//                                }
//                                else if (curRow >= 0 && curRow < size &&
//                                    curCol >= 0 && curCol < size &&
//                                    chess->getchessdate(curRow, curCol) == 0) // 空白位
//                                {
//                                    emptyNum++;
//                                    break;
//                                }
//                                else            // 出边界
//                                    break;
//                            }
//
//                            for (int i = 1; i <= 4; i++)
//                            {
//                                int curRow = row - i * y;
//                                int curCol = col - i * x;
//                                if (curRow >= 0 && curRow < size &&
//                                    curCol >= 0 && curCol < size &&
//                                    chess->getchessdate(curRow, curCol) == 1) // 真人玩家的子
//                                {
//                                    personNum++;
//                                }
//                                else if (curRow >= 0 && curRow < size &&
//                                    curCol >= 0 && curCol < size &&
//                                    chess->getchessdate(curRow, curCol) == 0) // 空白位
//                                {
//                                    emptyNum++;
//                                    break;
//                                }
//                                else            // 出边界
//                                    break;
//                            }
//
//                            if (personNum == 1)                      // 杀二
//                                scoremap[row][col] += 10;
//                            else if (personNum == 2)                 // 杀三
//                            {
//                                if (emptyNum == 1)
//                                    scoremap[row][col] += 30;
//                                else if (emptyNum == 2)
//                                    scoremap[row][col] += 40;
//                            }
//                            else if (personNum == 3)                 // 杀四
//                            {
//                                // 量变空位不一样，优先级不一样
//                                if (emptyNum == 1)
//                                    scoremap[row][col] += 60;
//                                else if (emptyNum == 2)
//                                    scoremap[row][col] += 200;
//                            }
//                            else if (personNum == 4)                 // 杀五
//                                scoremap[row][col] += 20000;
//
//                            // 进行一次清空
//                            emptyNum = 0;
//
//                            // 对白棋评分
//                            for (int i = 1; i <= 4; i++)
//                            {
//                                int curRow = row + i * y;
//                                int curCol = col + i * x;
//                                if (curRow > 0 && curRow < size &&
//                                    curCol > 0 && curCol < size &&
//                                    chess->getchessdate(curRow, curCol) == -1) // 玩家的子
//                                {
//                                    botNum++;
//                                }
//                                else if (curRow > 0 && curRow < size &&
//                                    curCol > 0 && curCol < size &&
//                                    chess->getchessdate(curRow, curCol) == 0) // 空白位
//                                {
//                                    emptyNum++;
//                                    break;
//                                }
//                                else            // 出边界
//                                    break;
//                            }
//
//                            for (int i = 1; i <= 4; i++)
//                            {
//                                int curRow = row - i * y;
//                                int curCol = col - i * x;
//                                if (curRow > 0 && curRow < size &&
//                                    curCol > 0 && curCol < size &&
//                                    chess->getchessdate(curRow, curCol) == -1) // 玩家的子
//                                {
//                                    botNum++;
//                                }
//                                else if (curRow > 0 && curRow < size &&
//                                    curCol > 0 && curCol < size &&
//                                    chess->getchessdate(curRow, curCol) == 0) // 空白位
//                                {
//                                    emptyNum++;
//                                    break;
//                                }
//                                else            // 出边界
//                                    break;
//                            }
//
//                            if (botNum == 0)                      // 普通下子
//                                scoremap[row][col] += 5;
//                            else if (botNum == 1)                 // 活二
//                                scoremap[row][col] += 10;
//                            else if (botNum == 2)
//                            {
//                                if (emptyNum == 1)                // 死三
//                                    scoremap[row][col] += 25;
//                                else if (emptyNum == 2)
//                                    scoremap[row][col] += 50;  // 活三
//                            }
//                            else if (botNum == 3)
//                            {
//                                if (emptyNum == 1)                // 死四
//                                    scoremap[row][col] += 55;
//                                else if (emptyNum == 2)
//                                    scoremap[row][col] += 10000; // 活四
//                            }
//                            else if (botNum >= 4)
//                                scoremap[row][col] += 30000;   // 活五，应该具有最高优先级
//                        }
//                    }
//                }
//            }
//        }
//}
ChessPos Ai::think()
{
	// 计算评分
	pointsscore();

	// 从评分中找出最大分数的位置
	int maxScore = 0;
	//std::vector<std::pair<int, int>> maxPoints;
	vector<ChessPos> maxPoints;
	int k = 0;

	int size = 12;
	for (int row = 0; row < size; row++) {
		for (int col = 0; col < size; col++)
		{
			// 前提是这个坐标是空的
			if (chess->getchessdate(row, col) == 0) {
				if (scoremap[row][col] > maxScore)          // 找最大的数和坐标
				{
					maxScore = scoremap[row][col];
					maxPoints.clear();
					maxPoints.push_back(ChessPos(row, col));
				}
				else if (scoremap[row][col] == maxScore) {   // 如果有多个最大的数，都存起来
					maxPoints.push_back(ChessPos(row, col));
				}
			}
		}
	}

	// 随机落子，如果有多个点的话
	int index = rand() % maxPoints.size();
	return maxPoints[index];
}