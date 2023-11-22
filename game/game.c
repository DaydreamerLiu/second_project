
#define _CRT_SECURE_NO_WARNINGS 1
//函数定义
#include<stdio.h>
#include "game.h"
void InitBoard(char board[ROW][COL], int row, int col)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			board[i][j] = ' ';
		}
	}
}
void DisplayerBoard(char board[ROW][COL], int row, int col)
{
	int i = 0;
	for (i = 0; i < row; i++)
	{
		int j = 0;
		for (j = 0; j < col; j++)
		{
			printf(" %c ", board[i][j]);//打印一行的数据
			if (j < col- 1)
			{
				printf("|");
			}
		}
		printf("\n");
		if (i < row - 1)//打印分割行---|    ---|     ---
		{

			for (j = 0; j < col; j++)
			{
				printf("---");
				if (j < col - 1)
				{
					printf("|");
				}
			}
			
				printf("\n");
		}
	}
	
}
void PlayerMove(char board[ROW][COL], int row, int col)
{
	int x = 0;
	int y = 0;
	printf("玩家1走\n");
	while (1)
	{
		printf("请输入坐标:>");
		scanf("%d%d", &x, &y);//数组中(0,0)对应玩家(1,1)以此类推
		if (x >= 1 && x <= row && y >= 1 && y <= col)
		{
			if (board[x - 1][y - 1] == ' ')//判断坐标是否被占用
			{
				board[x - 1][y - 1] = '*';
				break;
			}
			else
				printf("坐标已被占用\n");
		}
		else
			printf("输入错误，请重新输入");
	}
}
//void ComputerMove(char board[ROW][COL], int row, int col)//双人
//{
//	int x = 0;
//	int y = 0;
//	printf("玩家2走\n");
//	while (1)
//	{
//		printf("请输入坐标:>");
//		scanf("%d%d", &x, &y);
//		if (x >= 1 && x <= row && y >= 1 && y <= col)
//		{
//			if (board[x - 1][y - 1] == ' ')
//			{
//				board[x - 1][y - 1] = '#';
//				break;
//			}
//			else
//				printf("坐标已被占用\n");
//		}
//		else
//			printf("输入错误，请重新输入");
//		
//	}
//
//}
int IsFull(char board[ROW][COL], int row, int col)//返回1表示棋盘满了 返回0表示没满
{
	int i = 0;
	int j = 0;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			if (board[i][j] == ' ')
			{
				return 0;
			}
		}
	}
	return 1;
}
void ComputerMove(char board[ROW][COL], int row, int col)//电脑
{
	int x = 0;
	int y = 0;
	printf("电脑走:>\n");
	while (1)
	{


		x = rand() % row;
		y = rand() % col;
		if (board[x - 1][y - 1] == ' ')
		{
			board[x - 1][y - 1] = '#';
			break;
		}
		
	}

}
char IsWin(char board[ROW][COL], int row, int col)
{
	int i = 0;
	for (i = 0; i < row; i++)//行
	{
		if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][1] != ' ')
			return board[i][1];
	}
	for (i = 0; i < col; i++)//列
	{
		if (board[0][i] == board[1][i] & board[1][i] == board[2][i] && board[1][i] != ' ')
			return board[1][i];
	}
	//两条对角线
	if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[1][1] != ' ')
		return board[1][1];
	if (board[2][0] == board[1][1] && board[1][1] == board[0][2] && board[1][1] != ' ')
		return board[1][1];
	//判断是否平局
	if (1 == IsFull(board, row, col))
	{
		return 'q';
	}
	return 'c';
}