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
//					//�԰�������
//					//����
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
//						//����
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
//						//�Ժ�������
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
//						//����
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
	int personNum = 0; //���ַ������壩���ٸ�����������
	int aiNum = 0; //AI�������壩�����ж��ٸ�����������
	int emptyNum = 0; // �÷����Ͽհ�λ�ĸ���

	// ����������������
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 12; j++) {
			scoremap[i][j] = 0;
		}
	}

	int size = 12;
	for (int row = 0; row < size; row++) {
		for (int col = 0; col < size; col++) {
			//��ÿ������м���
			if (chess->getchessdate(row, col)) continue;

			for (int y = -1; y <= 0; y++) {        //Y�ķ�Χ����-1�� 0
				for (int x = -1; x <= 1; x++) {    //X�ķ�Χ�� -1,0,1
					if (y == 0 && x == 0) continue;
					if (y == 0 && x != 1) continue; //��y=0ʱ��������x=1

					personNum = 0;
					aiNum = 0;
					emptyNum = 0;

					// ��������ڸ�λ�����ӣ��ṹ��ʲô����
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

					// �����������
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

					if (personNum == 1) { //��2
						//CSDN  ����ԱRock
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

					// ��������ڸ�λ�����ӣ��ṹ��ʲô����
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
//    // ͳ����һ��ߵ������ɵ���
//    int personNum = 0;  // ��������ӵĸ���
//    int botNum = 0;     // AI�����ӵĸ���
//    int emptyNum = 0;   // ������հ�λ�ĸ���
//
//    // �����������
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
//            // �հ׵����
//            if (chess->getchessdate(row, col) == 0) {
//                // ������Χ�˸�����
//                for (int y = -1; y <= 1; y++) {
//                    for (int x = -1; x <= 1; x++)
//                    {
//                        // ����
//                        personNum = 0;
//                        botNum = 0;
//                        emptyNum = 0;
//
//                        // ԭ���겻��
//                        if (!(y == 0 && x == 0))
//                        {
//                            // ÿ����������4����
//                            // �Ժ������֣�������������
//                            for (int i = 1; i <= 4; i++)
//                            {
//                                int curRow = row + i * y;
//                                int curCol = col + i * x;
//                                if (curRow >= 0 && curRow < size &&
//                                    curCol >= 0 && curCol < size &&
//                                    chess->getchessdate(curRow, curCol) == 1) // ������ҵ���
//                                {
//                                    personNum++;
//                                }
//                                else if (curRow >= 0 && curRow < size &&
//                                    curCol >= 0 && curCol < size &&
//                                    chess->getchessdate(curRow, curCol) == 0) // �հ�λ
//                                {
//                                    emptyNum++;
//                                    break;
//                                }
//                                else            // ���߽�
//                                    break;
//                            }
//
//                            for (int i = 1; i <= 4; i++)
//                            {
//                                int curRow = row - i * y;
//                                int curCol = col - i * x;
//                                if (curRow >= 0 && curRow < size &&
//                                    curCol >= 0 && curCol < size &&
//                                    chess->getchessdate(curRow, curCol) == 1) // ������ҵ���
//                                {
//                                    personNum++;
//                                }
//                                else if (curRow >= 0 && curRow < size &&
//                                    curCol >= 0 && curCol < size &&
//                                    chess->getchessdate(curRow, curCol) == 0) // �հ�λ
//                                {
//                                    emptyNum++;
//                                    break;
//                                }
//                                else            // ���߽�
//                                    break;
//                            }
//
//                            if (personNum == 1)                      // ɱ��
//                                scoremap[row][col] += 10;
//                            else if (personNum == 2)                 // ɱ��
//                            {
//                                if (emptyNum == 1)
//                                    scoremap[row][col] += 30;
//                                else if (emptyNum == 2)
//                                    scoremap[row][col] += 40;
//                            }
//                            else if (personNum == 3)                 // ɱ��
//                            {
//                                // �����λ��һ�������ȼ���һ��
//                                if (emptyNum == 1)
//                                    scoremap[row][col] += 60;
//                                else if (emptyNum == 2)
//                                    scoremap[row][col] += 200;
//                            }
//                            else if (personNum == 4)                 // ɱ��
//                                scoremap[row][col] += 20000;
//
//                            // ����һ�����
//                            emptyNum = 0;
//
//                            // �԰�������
//                            for (int i = 1; i <= 4; i++)
//                            {
//                                int curRow = row + i * y;
//                                int curCol = col + i * x;
//                                if (curRow > 0 && curRow < size &&
//                                    curCol > 0 && curCol < size &&
//                                    chess->getchessdate(curRow, curCol) == -1) // ��ҵ���
//                                {
//                                    botNum++;
//                                }
//                                else if (curRow > 0 && curRow < size &&
//                                    curCol > 0 && curCol < size &&
//                                    chess->getchessdate(curRow, curCol) == 0) // �հ�λ
//                                {
//                                    emptyNum++;
//                                    break;
//                                }
//                                else            // ���߽�
//                                    break;
//                            }
//
//                            for (int i = 1; i <= 4; i++)
//                            {
//                                int curRow = row - i * y;
//                                int curCol = col - i * x;
//                                if (curRow > 0 && curRow < size &&
//                                    curCol > 0 && curCol < size &&
//                                    chess->getchessdate(curRow, curCol) == -1) // ��ҵ���
//                                {
//                                    botNum++;
//                                }
//                                else if (curRow > 0 && curRow < size &&
//                                    curCol > 0 && curCol < size &&
//                                    chess->getchessdate(curRow, curCol) == 0) // �հ�λ
//                                {
//                                    emptyNum++;
//                                    break;
//                                }
//                                else            // ���߽�
//                                    break;
//                            }
//
//                            if (botNum == 0)                      // ��ͨ����
//                                scoremap[row][col] += 5;
//                            else if (botNum == 1)                 // ���
//                                scoremap[row][col] += 10;
//                            else if (botNum == 2)
//                            {
//                                if (emptyNum == 1)                // ����
//                                    scoremap[row][col] += 25;
//                                else if (emptyNum == 2)
//                                    scoremap[row][col] += 50;  // ����
//                            }
//                            else if (botNum == 3)
//                            {
//                                if (emptyNum == 1)                // ����
//                                    scoremap[row][col] += 55;
//                                else if (emptyNum == 2)
//                                    scoremap[row][col] += 10000; // ����
//                            }
//                            else if (botNum >= 4)
//                                scoremap[row][col] += 30000;   // ���壬Ӧ�þ���������ȼ�
//                        }
//                    }
//                }
//            }
//        }
//}
ChessPos Ai::think()
{
	// ��������
	pointsscore();

	// ���������ҳ���������λ��
	int maxScore = 0;
	//std::vector<std::pair<int, int>> maxPoints;
	vector<ChessPos> maxPoints;
	int k = 0;

	int size = 12;
	for (int row = 0; row < size; row++) {
		for (int col = 0; col < size; col++)
		{
			// ǰ������������ǿյ�
			if (chess->getchessdate(row, col) == 0) {
				if (scoremap[row][col] > maxScore)          // ��������������
				{
					maxScore = scoremap[row][col];
					maxPoints.clear();
					maxPoints.push_back(ChessPos(row, col));
				}
				else if (scoremap[row][col] == maxScore) {   // ����ж������������������
					maxPoints.push_back(ChessPos(row, col));
				}
			}
		}
	}

	// ������ӣ�����ж����Ļ�
	int index = rand() % maxPoints.size();
	return maxPoints[index];
}