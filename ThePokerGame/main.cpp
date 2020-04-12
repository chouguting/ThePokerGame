#include <cstdlib>
#include <stdio.h>
#include <time.h>

#include "funclib.h"

void gameInit(); //�C����l��(��ܤH�ơA��w���P�W�h)
Card* handCard[4]; //�|�Ƥ�P
int changeWithWhom[4]; //�U�Ӫ��a�n��ִ��P
int playerCount; //�x�s���X�Ӫ��a(�䴩2��4�H)
Card deck[52]; //�P��

//�P��(�Ʀr)
const char* face[] = {
	"Deuce", "Three",
	"Four", "Five",
	"Six", "Seven", "Eight",
	"Nine", "Ten",
	"Jack", "Queen", "King", "Ace"
};

//�P��(���)
const char* suit[] = {"Clubs", "Diamonds", "Hearts", "Spades"};

//�o�Ӱ}�C�O�P��(���ǰt�XDetermine)
const char* cardType[] = {"���P", "��l", "�G��", "�T��", "���l", "�P��", "��Ī", "�|��", "�P�ᶶ"};


int main()
{
	////////////////////

	srand(time(nullptr));
	int i, j;


	printf("�w��Ө쯫�_�����J�C��!!\n");


	gameInit(); //��l��


	int operation = 0; //�s���a���ާ@
	fillDeckFaceFirst(deck, face, suit); //��J�P

	int score[4] = {0}; //�C�ӤH�����ƥ��k�s

	system("cls");
	while (true)
	{
		printf("�ثe����:");
		for (i = 0; i < playerCount; i++)
		{
			printf("P%d:%d  ", i + 1, score[i]);
		}
		printf("\n�ʧ@�ﶵ:\n\t(1)���s�}�l(���]�}�l�n��)\n\t(2) �~��U�@�^\n\t(3) �����F\n");
		printf("Input your operation(1~3):");
		scanf_s("%d", &operation, 10);

		if (operation == 1) //�C�����m
		{
			system("cls");
			for (i = 0; i < 4; i++)
			{
				score[i] = 0; //�k�s�C�ӤH������
			}
			printf("�C������\n");
			gameInit(); //���s��l��
			system("cls");
			printf("�C���w����\n");
			system("pause");
			system("cls");
		}
		else if (operation == 2) //�~��C��
		{
			shuffle(deck); //�~�P


			int changeCardIndexBuffer[4][3]; //�Ȧs�n�����P�O����

			int scoreThisRoundTemp[4][3]; //�Ȧs���� 4�Ӫ��a �e����3�Ӽ[

			int currentPlayer; //�{�b���ʧ@�O�w����쪱�a


			//��n�����P
			for (currentPlayer = 0; currentPlayer < playerCount; currentPlayer++)
			{
				system("cls");
				printf("\t�{�b�����%d�쪱�a\n\t�A�n���%d�쪱�a���P\n", currentPlayer + 1, changeWithWhom[currentPlayer] + 1);
				printf("\n�H�U�O�z���P\n");
				sort(handCard[currentPlayer], 13); //����z
				deal(handCard[currentPlayer], 13); //�A�L�X�P
				printf("\n�п�ܤT�i�A�n�����P:");
				for (i = 0; i < 3; i++)
				{
					scanf_s("%d", &changeCardIndexBuffer[currentPlayer][i]); //��J�n�����P�O���X�i
					changeCardIndexBuffer[currentPlayer][i]--; //�P���s���O�q1�}�l,�����Pindex�O�q0�}�l
				}
			}
			system("cls");


			//�}�l���P
			for (currentPlayer = 0; currentPlayer < playerCount; currentPlayer++)
			{
				for (i = 0; i < 3; i++)
				{
					//SWAP���P

					//���Ȧs��currentPlayer�쪱�a��P����"currentPlayer�n�����P"�i�P;
					//²��ӻ��N�O�n���X���P
					Card temp = handCard[currentPlayer][changeCardIndexBuffer[currentPlayer][i]];

					//���P�ؼ�:"�n��currentPlayer���P�����a" ����P����"(�n��currentPlayer���P�����a)�n�����P" �i�P
					//²��ӻ��N�O�n���J���P
					Card toBeChanged = handCard[changeWithWhom[currentPlayer]][changeCardIndexBuffer[changeWithWhom[
						currentPlayer]][i]];

					//��i�P�洫
					handCard[currentPlayer][changeCardIndexBuffer[currentPlayer][i]] = toBeChanged;
					handCard[changeWithWhom[currentPlayer]][changeCardIndexBuffer[changeWithWhom[currentPlayer]][i]] =
						temp;
				}

				//��������H���έ��ƴ�(���p�W�h�O13����,����������b�Ĥ@�Ӫ��a�ɲĤT��]���n�F)
				if (changeWithWhom[0] == 1) //�p�G�O1 2 �����A���������ʧ@�u�ݭn�@�Φb��1��M��3��N�n
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
				else //�p�G�O 13�� �άO 14���A�����u�n�����ĤG��N���������F
				{
					if (currentPlayer == 1)
					{
						break;
					}
				}
			}


			//�ƦC�P�աA���K�p���P����
			for (currentPlayer = 0; currentPlayer < playerCount; currentPlayer++)
			{
				Card handCardTemp[13]; //�Ȧs��P
				int indexTemp; //�Ȧs���a��J���P���s��
				printf("\t�{�b�����%d�쪱�a\n", currentPlayer + 1);
				printf("\n�H�U�O�z���P\n");
				sort(handCard[currentPlayer], 13);
				deal(handCard[currentPlayer], 13);

				//���⪱�a��J���ƧǦs��handCardTemp��,�A�ƻs�^handCard				
				//�Ȧs�e�[�T�i
				printf("�п�J�e�[�T�i:");
				for (i = 0; i < 3; i++)
				{
					scanf_s("%d", &indexTemp, 10);
					handCardTemp[i] = handCard[currentPlayer][indexTemp - 1];
				}

				//�Ȧs���[���i
				printf("�п�J���[���i:");
				for (; i < 8; i++)
				{
					scanf_s("%d", &indexTemp, 10);
					handCardTemp[i] = handCard[currentPlayer][indexTemp - 1];
				}
				//�Ȧs��[���i
				printf("�п�J��[���i:");
				for (; i < 13; i++)
				{
					scanf_s("%d", &indexTemp, 10);
					handCardTemp[i] = handCard[currentPlayer][indexTemp - 1];
				}

				//��handCardTemp�A�ƻs�^handCard
				for (i = 0; i < 13; i++)
				{
					handCard[currentPlayer][i] = handCardTemp[i];
				}

				sort(handCard[currentPlayer], 3); //�Ƨǫe�[
				sort(handCard[currentPlayer] + 3, 5); //�ƧǤ��[
				sort(handCard[currentPlayer] + 8, 5); //�Ƨǫ�[

				printf("\n���P��:\n");
				deal(handCard[currentPlayer], 13);

				//�p���P������
				if (isStraight(handCard[currentPlayer], 13) == 1) //�S��:�p�G�O�@���s�N���oĹ�F
				{
					printf("�A���P�O�@���s!!");
					for (i = 0; i < 3; i++)
					{
						scoreThisRoundTemp[currentPlayer][i] = 100000;
					}
				}
				else //���`���p�U�s�J����
				{
					//�Q��determine�L�X�P��,�Q��giveScore��P������
					printf("\n�e�[: %s  ����:%d\n", cardType[determine(handCard[currentPlayer], 3)],
					       giveScore(handCard[currentPlayer], 3));
					printf("���[: %s ����:%d\n", cardType[determine(handCard[currentPlayer] + 3, 5)],
					       giveScore(handCard[currentPlayer] + 3, 5));
					printf("��[: %s ����:%d\n", cardType[determine(handCard[currentPlayer] + 8, 5)],
					       giveScore(handCard[currentPlayer] + 8, 5));


					//��U���a���T�[���ƼȦs�_��
					scoreThisRoundTemp[currentPlayer][0] = giveScore(handCard[currentPlayer], 3);
					scoreThisRoundTemp[currentPlayer][1] = giveScore(handCard[currentPlayer] + 3, 5);
					scoreThisRoundTemp[currentPlayer][2] = giveScore(handCard[currentPlayer] + 8, 5);


					//�W�h�P�_: ��[�����j�󵥩󤤼[�A���[�����j�󵥩�e�[�A�_�h�����T�[����
					if (scoreThisRoundTemp[currentPlayer][0] >= scoreThisRoundTemp[currentPlayer][1] ||
						scoreThisRoundTemp[currentPlayer][1] >= scoreThisRoundTemp[currentPlayer][2])
					{
						printf("\n���A�H�ϤF�W�h�n�A���ƧǤ覡,�ҥH�����s��");
						printf("(��[�����j�󵥩󤤼[�A���[�����j�󵥩�e�[�A�_�h�����T�[����)\n\n");
						for (i = 0; i < 3; i++)
						{
							scoreThisRoundTemp[currentPlayer][i] = 0; //���ƭ��k�s
						}
					}
				}


				system("pause");
				system("cls");
			}


			system("cls");

			//�p�����U�[�᪺�̲פ���
			for (currentPlayer = 0; currentPlayer < playerCount; currentPlayer++)
			{
				printf("�{�b���� ��%d�쪱�a�o��������:\n", currentPlayer + 1);
				printf("\n\t�e�[\t���[\t��[\n");
				printf("�ڦۤv\t%d\t%d\t%d\n", scoreThisRoundTemp[currentPlayer][0], scoreThisRoundTemp[currentPlayer][1],
				       scoreThisRoundTemp[currentPlayer][2]);
				printf("\n");
				int homerunCount = 0; //�p���Ĺ������
				for (i = 0; i < playerCount; i++)
				{
					if (i != currentPlayer)
					{
						printf("��%d��\t%d\t%d\t%d\n", i + 1, scoreThisRoundTemp[i][0], scoreThisRoundTemp[i][1],
						       scoreThisRoundTemp[i][2]);
					}
				}
				printf("\n\n\n"); //�L�X�M��L���a�����

				for (i = 0; i < playerCount; i++)
				{
					int winTimesWithOtherPlayer = 0; //�x�s�M�t�@�Ӫ��a��� Ĺ������
					int tieTimesWithOtherPlayer = 0; //�x�s�M�t�@�Ӫ��a��� ���⪺����
					if (i != currentPlayer) //���ΩM�ۤv��
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
						int totalPlus = 0; //�Ȧs�`���n�[����

						if (tieTimesWithOtherPlayer == 3) //�������� �[0��
						{
							totalPlus = 0;
						}
						else if (winTimesWithOtherPlayer == 3) //��Ĺ �[6��
						{
							score[currentPlayer] = score[currentPlayer] + 6;
							totalPlus = 6;
							homerunCount++;
						}
						else if (winTimesWithOtherPlayer == 2) //��@�� �[2��
						{
							score[currentPlayer] = score[currentPlayer] + 2;
							totalPlus = 2;
						}
						else if (winTimesWithOtherPlayer == 1) //Ĺ�@�� ��1��
						{
							score[currentPlayer] = score[currentPlayer] - 1;
							totalPlus = -1;
						}
						else if (winTimesWithOtherPlayer == 0) //���� ��6��
						{
							score[currentPlayer] = score[currentPlayer] - 6;
							totalPlus = -6;
						}


						printf("��%d�쪱�a ���%d�쪱�a �`���[%d\n", currentPlayer + 1, i + 1, totalPlus);
					}
				}
				if (homerunCount >= 3 && playerCount == 4) //�p�G���L���a���O��Ĺ,�NHOMERUN(�ȭ�4�H��)
				{
					printf("���ߧA�������F!!! �`���A�[18��\n");
					score[currentPlayer] = score[currentPlayer] + 18;
				}

				printf("���G: ��%d�쪱�a�`��:%d\n\n\n", currentPlayer + 1, score[currentPlayer]);
			}

			system("pause");
			system("cls");
		}
		else if (operation == 3) //�����C��
		{
			break;
		}
	}

	system("cls"); // �~�P
	printf("�P�¹C��");

	system("pause");
	return 0;
}


void gameInit()
{
	int i;
	printf("�п�ܹC���H��:");
	scanf_s("%d", &playerCount, 10);


	for (i = 0; i < 4; i++)
	{
		handCard[i] = deck + 13 * i;
	}
	if (playerCount == 4)
	{
		int buffer[4]; //�Ȧs��J���Ʀr
		printf("��w���P�W�h(��J�|�Ӫ��a�N�� �Ĥ@�G���� �T�|�ᴫ):");
		for (i = 0; i < 4; i++)
		{
			scanf_s("%d", &buffer[i], 10);
		}

		//�s�J�n��ִ�(index�O�q0�}�l�A���a�s���O�q 1�}�l)
		changeWithWhom[buffer[0] - 1] = buffer[1] - 1;
		changeWithWhom[buffer[1] - 1] = buffer[0] - 1; //��J��1,2�줬��
		changeWithWhom[buffer[2] - 1] = buffer[3] - 1;
		changeWithWhom[buffer[3] - 1] = buffer[2] - 1; //��J��3,4�줬��
	}
	else
	{
		changeWithWhom[0] = 1;
		changeWithWhom[1] = 0;
	}
}
