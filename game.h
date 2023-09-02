#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#define ROW 9
#define COL 9
#define ROWS ROW + 2
#define COLS COL + 2
#define MINE_COUNT 10

//��ʼ������
void BoardInit(char board[ROWS][COLS], int rows, int cols, char set);

//����
void SetMine(char board[ROWS][COLS], int row, int col);

//��ӡ����
void BoardPrint(char board[ROWS][COLS], int row, int col);

//����
void FindMine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col);