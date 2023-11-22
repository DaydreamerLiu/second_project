#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>
#include <math.h>
#include "game.h"
#include "game.c"
//#define ROW 3//行
//#define COL 3//列
void menu()
{
	printf("**********************************\n");
	printf("******1.开始游戏 2.退出游戏*******\n");
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
		//玩家下棋
		PlayerMove(board, ROW, COL);
		DisplayerBoard(board, ROW, COL);
		ret =IsWin(board, ROW, COL);//判断玩家是否赢
		if (ret != 'c')
		{
			break;
		}
		ComputerMove(board, ROW, COL);//电脑下棋
		DisplayerBoard(board, ROW, COL);
		ret = IsWin(board, ROW, COL);
		if (ret != 'c')
		{
			break;
		}

	}
	if (ret == '*')
	{
		printf("玩家赢\n");
	}
	else if (ret == '#')
	{
		printf("电脑赢\n");
	}
	else
		printf("平局\n");//ret = 'q'




}
void test()
{
	int num = 0;
	srand((unsigned int) time(NULL));
	do
	{
		menu();
		printf("请输入:");
		scanf_s("%d", &num);
		switch (num)
		{
		case 1:
			printf("三子棋\n");
			game();
			break;
		case 2:
			printf("退出游戏\n");
			break;
		default:
			printf("输入错误，请重新输入\n");
			break;


		}
	}
	while (num);
}

int main()
{
	
	
	test();//选项界面
	
	
	return 0;
}