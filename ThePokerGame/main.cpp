#include <cstdlib>
#include <stdio.h>
#include <time.h>

#include "funclib.h"
#include "oldLib.h"
#include "testLib.h"


void gameInit();

Card* handCard[4];
int changeWithWhom[4], playerCount;
Card deck[52];
const char* face[] = {
	"Deuce", "Three",
	"Four", "Five",
	"Six", "Seven", "Eight",
	"Nine", "Ten",
	"Jack", "Queen", "King", "Ace"
};

const char* suit[] = {"Clubs", "Diamonds", "Hearts", "Spades"};

const char* cardType[] = {"散牌", "對子", "二對", "三條", "順子", "同花", "葫蘆", "四條", "同花順"};


int main()
{
	////////////////////

	srand(time(NULL));
	int i, j;


	printf("歡迎來到神奇的撲克遊戲!!\n");


	
	gameInit();


	int operation = 0;
	fillDeckFaceFirst(deck, face, suit);

	int score[4] = {0};

	system("cls");
	while (1)
	{
		printf("目前分數:");
		for (i = 0; i < playerCount; i++)
		{
			printf("P%d:%d  ", i + 1, score[i]);
		}
		printf("\n動作選項:\n\t(1)重新開始(重設開始積分)\n\t(2) 繼續下一回\n\t(3) 不玩了\n");
		printf("Input your operation(1~3):");
		scanf_s("%d", &operation, 10);
		if (operation == 1)
		{
			system("cls");
			for (i = 0; i < 4; i++)
			{
				score[i] = 0;
			}
			printf("遊戲重制\n");
			gameInit();
			system("cls");
			printf("遊戲已重制\n");
			system("pause");
			system("cls");
		}
		else if (operation == 2)
		{
			shuffle(deck);
			dealManyPlayer(playerCount, deck);
			system("pause");

			int changeCardIndexBuffer[4][3]; //暫存要換的牌是哪些

			int scoreThisRoundTemp[4][3]; //暫存分數 4個玩家 前中後3個墩

			int currentPlayer;


			//選要換的牌
			for (currentPlayer = 0; currentPlayer < playerCount; currentPlayer++)
			{
				system("cls");
				printf("\t現在輪到第%d位玩家\n\t你要跟第%d位玩家換牌\n", currentPlayer + 1, changeWithWhom[currentPlayer] + 1);
				printf("\n以下是您的牌\n");
				//system("pause");
				sort(handCard[currentPlayer], 13);
				deal(handCard[currentPlayer], 13);
				printf("\n請選擇三張你要換的牌:");
				for (i = 0; i < 3; i++)
				{
					scanf_s("%d", &changeCardIndexBuffer[currentPlayer][i]);
					changeCardIndexBuffer[currentPlayer][i]--;
				}
			}
			system("cls");


			//開始換牌
			for (currentPlayer = 0; currentPlayer < playerCount; currentPlayer++)
			{
				for (i = 0; i < 3; i++)
				{
					Card temp = handCard[currentPlayer][changeCardIndexBuffer[currentPlayer][i]];
					Card toBeChanged = handCard[changeWithWhom[currentPlayer]][changeCardIndexBuffer[changeWithWhom[
						currentPlayer]][i]];
					handCard[currentPlayer][changeCardIndexBuffer[currentPlayer][i]] = toBeChanged;
					handCard[changeWithWhom[currentPlayer]][changeCardIndexBuffer[changeWithWhom[currentPlayer]][i]] =
						temp;
				}
				if (changeWithWhom[0] == 1) //如果是1 2 互換
				{
					if (currentPlayer == 0)
					{
						currentPlayer++;
					}
					if (currentPlayer == 2)
					{
						break;
					}
				}
				else
				{
					if (currentPlayer == 1)
					{
						break;
					}
				}
			}


			//排列牌組，順便計算手牌分數
			for (currentPlayer = 0; currentPlayer < playerCount; currentPlayer++)
			{
				Card handCardTemp[13];
				int indexTemp; //暫存排好的牌
				printf("\t現在輪到第%d位玩家\n", currentPlayer + 1);
				printf("\n以下是您的牌\n");
				//system("pause");
				sort(handCard[currentPlayer], 13);
				deal(handCard[currentPlayer], 13);
				i = 0;
				//前墩三張
				printf("請輸入前墩三張:");
				for (i = 0; i < 3; i++)
				{
					scanf_s("%d", &indexTemp, 10);
					handCardTemp[i] = handCard[currentPlayer][indexTemp - 1];
				}

				//中墩五張
				printf("請輸入中墩五張:");
				for (; i < 8; i++)
				{
					scanf_s("%d", &indexTemp, 10);
					handCardTemp[i] = handCard[currentPlayer][indexTemp - 1];
				}
				//後墩五張
				printf("請輸入後墩五張:");
				for (; i < 13; i++)
				{
					scanf_s("%d", &indexTemp, 10);
					handCardTemp[i] = handCard[currentPlayer][indexTemp - 1];
				}

				for (i = 0; i < 13; i++)
				{
					handCard[currentPlayer][i] = handCardTemp[i];
				}

				sort(handCard[currentPlayer], 3);
				sort(handCard[currentPlayer] + 3, 5);
				sort(handCard[currentPlayer] + 8, 5);

				printf("\n換牌後:\n");
				deal(handCard[currentPlayer], 13);

				//計算手牌的分數
				if (isStraight(handCard[currentPlayer], 13) == 1) //如果是一條龍就讓她贏了
				{
					printf("你的牌是一條龍!!");
					for (i = 0; i < 3; i++)
					{
						scoreThisRoundTemp[currentPlayer][i] = 100000;
					}
				}
				else //存入分數
				{
					printf("\n前墩: %s  分數:%d\n", cardType[determine(handCard[currentPlayer], 3)],
					       giveScore(handCard[currentPlayer], 3));
					printf("中墩: %s 分數:%d\n", cardType[determine(handCard[currentPlayer] + 3, 5)],
					       giveScore(handCard[currentPlayer] + 3, 5));
					printf("後墩: %s 分數:%d\n", cardType[determine(handCard[currentPlayer] + 8, 5)],
					       giveScore(handCard[currentPlayer] + 8, 5));

					scoreThisRoundTemp[currentPlayer][0] = giveScore(handCard[currentPlayer], 3);
					scoreThisRoundTemp[currentPlayer][1] = giveScore(handCard[currentPlayer] + 3, 5);
					scoreThisRoundTemp[currentPlayer][2] = giveScore(handCard[currentPlayer] + 8, 5);

					if (scoreThisRoundTemp[currentPlayer][0] >= scoreThisRoundTemp[currentPlayer][1] ||
						scoreThisRoundTemp[currentPlayer][1] >= scoreThisRoundTemp[currentPlayer][2])
					{
						printf("\n但你違反了規則要你的排序方式,所以全部零分");
						printf("(後墩必須大於等於中墩，中墩必須大於等於前墩，否則視為三墩全輸)\n\n");
						for (i = 0; i < 3; i++)
						{
							scoreThisRoundTemp[currentPlayer][i] = 0;
						}
					}
				}


				system("pause");
				system("cls");
			}


			system("cls");
			//計算比較各墩後的最終分數
			for (currentPlayer = 0; currentPlayer < playerCount; currentPlayer++)
			{
				printf("現在結算 第%d位玩家這輪的分數:\n", currentPlayer + 1);
				printf("\n\t前墩\t中墩\t後墩\n");
				printf("我自己\t%d\t%d\t%d\n", scoreThisRoundTemp[currentPlayer][0], scoreThisRoundTemp[currentPlayer][1],
				       scoreThisRoundTemp[currentPlayer][2]);
				printf("\n");
				int homerunCount = 0;
				for (i = 0; i < playerCount; i++)
				{
					if (i != currentPlayer)
					{
						printf("第%d位\t%d\t%d\t%d\n", i + 1, scoreThisRoundTemp[i][0], scoreThisRoundTemp[i][1],
						       scoreThisRoundTemp[i][2]);
					}
				}
				printf("\n\n\n");

				for (i = 0; i < playerCount; i++)
				{
					int winTimesWithOtherPlayer = 0;
					int tieTimesWithOtherPlayer = 0;
					if (i != currentPlayer)
					{
						for (j = 0; j < 3; j++)
						{
							if (scoreThisRoundTemp[currentPlayer][j] > scoreThisRoundTemp[i][j])
							{
								winTimesWithOtherPlayer++;
							}
							if (scoreThisRoundTemp[currentPlayer][j] == scoreThisRoundTemp[i][j])
							{
								tieTimesWithOtherPlayer++;
							}
						}
						int totalPlus = 0;
						if (tieTimesWithOtherPlayer == 3)
						{
							totalPlus = 0;
						}
						else if (winTimesWithOtherPlayer == 3)
						{
							score[currentPlayer] = score[currentPlayer] + 6;
							totalPlus = 6;
							homerunCount++;
						}
						else if (winTimesWithOtherPlayer == 2)
						{
							score[currentPlayer] = score[currentPlayer] + 2;
							totalPlus = 2;
						}
						else if (winTimesWithOtherPlayer == 1)
						{
							score[currentPlayer] = score[currentPlayer] - 1;
							totalPlus = -1;
						}
						else if (winTimesWithOtherPlayer == 0)
						{
							score[currentPlayer] = score[currentPlayer] - 6;
							totalPlus = -6;
						}


						printf("第%d位玩家 對第%d位玩家 總分加%d\n", currentPlayer + 1, i + 1, totalPlus);
					}
				}
				if (homerunCount >= 3 && playerCount == 4)
				{
					printf("恭喜你紅不讓了!!! 總分再加18分\n");
					score[currentPlayer] = score[currentPlayer] + 18;
				}

				printf("結果: 第%d位玩家總分:%d\n\n\n", currentPlayer + 1, score[currentPlayer]);
			}

			system("pause");
			system("cls");
		}
		else if (operation == 3)
		{
			break;
		}
	}

	system("cls"); // 洗牌
	printf("感謝遊玩");

	system("pause");
	return 0;
}


void gameInit()
{
	int i;
	printf("請選擇遊戲人數:");
	scanf_s("%d", &playerCount, 10);


	for (i = 0; i < 4; i++)
	{
		handCard[i] = deck + 13 * i;
	}
	if (playerCount == 4)
	{
		int buffer[4]; //暫存
		printf("制定換牌規則(輸入四個玩家代號 第一二互換 三四戶換):");
		for (i = 0; i < 4; i++)
		{
			scanf_s("%d", &buffer[i], 10);
		}
		changeWithWhom[buffer[0] - 1] = buffer[1] - 1;
		changeWithWhom[buffer[1] - 1] = buffer[0] - 1;
		changeWithWhom[buffer[2] - 1] = buffer[3] - 1;
		changeWithWhom[buffer[3] - 1] = buffer[2] - 1;
	}
	else
	{
		changeWithWhom[0] = 1;
		changeWithWhom[1] = 0;
	}
}
