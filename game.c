#define _CRT_SECURE_NO_WARNINGS 1
#include "game.h"
//数组初始化
void BoardInit(char board[ROWS][COLS], int rows, int cols, char set)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
			board[i][j] = set; //set表示要初始化的字符
	}
}

//埋雷
void SetMine(char board[ROWS][COLS], int row, int col)
{
	int count = MINE_COUNT;
	while (count)
	{
		int x = rand() % row + 1; //随机生成0-row的其中一个数
		int y = rand() % col + 1;
		if (board[x][y] == '0')  //检查该位置是否已经有雷
		{
			board[x][y] = '1';
			count--;
		}
	}
}

//打印雷盘
void BoardPrint(char board[ROWS][COLS], int row, int col)
{
	int i = 0;
	int j = 0;
	for (i = 0; i <= row; i++) //打印行号
	{
		printf("%d ", i);
	}
	printf("\n");
	for (i = 1; i <= row; i++)
	{
		printf("%d ", i); //打印列号
		for (j = 1; j <= col; j++)
		{
			printf("%c ", board[i][j]);
		}
		printf("\n");
	}
	printf("----扫雷游戏----\n");
}


//标记雷的位置
void MarkMine(char board[ROWS][COLS], int row, int col)
{
	int x = 0; 
	int y = 0;
	while (1)
	{
		printf("请输入你想要标记的坐标->");
		scanf("%d %d", &x, &y);
		if (x >= 1 && x <= row && y >= 1 && y <= col)  //判断该坐标是否合法
		{
			if (board[x][y] == '*')  //判断该坐标是否被排查
			{
				board[x][y] = '!';
				break;
			}
			else
			{
				printf("该坐标不能被标记，请重新输入！\n");
			}
		}
		else
		{
			printf("输入错误，请重新输入");
		}
	}
}


//获取坐标周围雷的个数
int GetMineCount(char board[ROWS][COLS], int x, int y)
{
	int i = 0; 
	int j = 0;
	int count = 0;
	for (i = x - 1; i <= x + 1; i++)
	{
		for (j = y - 1; j < y + 1; j++)
		{
			if (board[i][j] == '1')
			{
				count++;
			}
		}
	}
	return count;
}



//递归爆炸式展开
void ExplosionSpread(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col, int x, int y, int* pw)
{
	if (x >= 1 && x <= row && y >= 1 && y <= col)  //判断坐标是否为排查范围
	{
		int num = GetMineCount(mine, x, y);  //获取坐标周围雷的个数
		if (num == 0)
		{
			(*pw)++;
			show[x][y] = ' ';  //如果该坐标周围没有雷，就把该坐标设置成空格，并向周围8个坐标展开
			int i = 0;
			int j = 0;
			for (i = x - 1; i <= x + 1; i++)
			{
				for (j = y - 1; j <= y + 1; j++)
				{
					if (show[i][j] == '*') //递归限制条件，防止已经排查过的坐标再次递归,造成死递归
						ExplosionSpread(mine, show, row, col, i, j, pw);
				}
			}
		}
		else
		{
			(*pw)++;
			show[x][y] = num + '0';
		}
	}
}


//排雷
void FindMine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col)
{
	int x = 0;
	int y = 0;
	int win = 0;  //用来标记是否取得胜利
	int* pw = &win;
	char ch = 0;  //用来接受是否需要标记雷
	while (win < row * col - MINE_COUNT) //格子总数减去雷的总数，得到没有雷的格子总数
	{
		printf("请输入你想排查的坐标->");
		scanf("%d %d", &x, &y);
		if (x >= 1 && x <= row && y >= 1 && y <= col)  //判断坐标合法性
		{
			if (mine[x][y] == '1')
			{
				system("cls");
				printf("很遗憾，你被炸死了！\n");
				BoardPrint(mine, row, col);  //炸死了就打印mine数组，让用户知道
				break;
			}
			else
			{
				if (show[x][y] != '*')  //判断是否重复排查
				{
					printf("改坐标已被排查，请重新输入！\n");
					continue;  //直接进入下一次循环
				}
				else
				{
					ExplosionSpread(mine, show, row, col, x, y, pw);  //爆炸展开一片
					system("cls");  //清空屏幕
					BoardPrint(show, row, col);  //打印棋盘
					printf("需要标记雷的位置请输入y/Y,否则请按任意键->");
					while ((ch = getchar()) != '\n');  //清理缓冲区。意思是一直循环。等到用户输入回车为止，结束循环。
					scanf("%c", &ch);
					if (ch == 'Y' || ch == 'y')
					{
						MarkMine(show, row, col);  //标记雷
						system("cls");
						BoardPrint(show, row, col);
					}
					else
					{
						continue;
					}
				}
			}
		}
		else
		{
			printf("非法坐标，请重新输入->");
		}
	}
	if (win == row * col - MINE_COUNT)
	{
		system("cls");
		printf("恭喜你，排雷成功\n");
		BoardPrint(show, row, col);
		return;
	}
}