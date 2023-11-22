#pragma once
//函数声明
#include <stdio.h>
#include <stdlib.h>//srand
#include <time.h>
#define ROW 3
#define COL 3
void InitBoard(char board[ROW][COL], int row, int col);
void DisplayerBoard(char borad[ROW][COL], int row, int col);
void PlayerMove(char board[ROW][COL], int roe, int col);
void ComputerMove(char board[ROW][COL], int row, int col);
char IsWin(char board[ROW][COL], int row, int col);//告诉我们四种情况
			//玩家赢'*'
			//电脑赢'#'
			//平局'q'
			//继续游戏'c'
int IsFull(char board[ROW][COL], int row, int col);