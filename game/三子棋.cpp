#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>
#include <math.h>
#include "game.h"
#include "game.c"
//#define ROW 3//��
//#define COL 3//��
void menu()
{
	printf("**********************************\n");
	printf("******1.��ʼ��Ϸ 2.�˳���Ϸ*******\n");
	printf("**********************************\n");
}
void game()
{
	char ret = 0;
	char board[ROW][COL] = { 0 };
	InitBoard(board, ROW, COL);
	DisplayerBoard(board, ROW, COL);
	while (1)
	{
		//�������
		PlayerMove(board, ROW, COL);
		DisplayerBoard(board, ROW, COL);
		ret =IsWin(board, ROW, COL);//�ж�����Ƿ�Ӯ
		if (ret != 'c')
		{
			break;
		}
		ComputerMove(board, ROW, COL);//��������
		DisplayerBoard(board, ROW, COL);
		ret = IsWin(board, ROW, COL);
		if (ret != 'c')
		{
			break;
		}

	}
	if (ret == '*')
	{
		printf("���Ӯ\n");
	}
	else if (ret == '#')
	{
		printf("����Ӯ\n");
	}
	else
		printf("ƽ��\n");//ret = 'q'




}
void test()
{
	int num = 0;
	srand((unsigned int) time(NULL));
	do
	{
		menu();
		printf("������:");
		scanf_s("%d", &num);
		switch (num)
		{
		case 1:
			printf("������\n");
			game();
			break;
		case 2:
			printf("�˳���Ϸ\n");
			break;
		default:
			printf("�����������������\n");
			break;


		}
	}
	while (num);
}

int main()
{
	
	
	test();//ѡ�����
	
	
	return 0;
}