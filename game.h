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

//初始化数组
void BoardInit(char board[ROWS][COLS], int rows, int cols, char set);

//埋雷
void SetMine(char board[ROWS][COLS], int row, int col);

//打印雷盘
void BoardPrint(char board[ROWS][COLS], int row, int col);

//排雷
void FindMine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col);