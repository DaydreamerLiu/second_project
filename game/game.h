#pragma once
//��������
#include <stdio.h>
#include <stdlib.h>//srand
#include <time.h>
#define ROW 3
#define COL 3
void InitBoard(char board[ROW][COL], int row, int col);
void DisplayerBoard(char borad[ROW][COL], int row, int col);
void PlayerMove(char board[ROW][COL], int roe, int col);
void ComputerMove(char board[ROW][COL], int row, int col);
char IsWin(char board[ROW][COL], int row, int col);//���������������
			//���Ӯ'*'
			//����Ӯ'#'
			//ƽ��'q'
			//������Ϸ'c'
int IsFull(char board[ROW][COL], int row, int col);