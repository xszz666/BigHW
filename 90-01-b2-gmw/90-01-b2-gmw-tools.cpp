//邹良顺 信02 2152611
#include"90-01-b2-gmw-h.h"
#include"../include/cmd_gmw_tools.h"
bool search_identical(int in[ROW][COL],int mto10[ROW][COL], const BLOCK_DISPLAY_INFO bdi_normal[], const BLOCK_DISPLAY_INFO bdi_related[],const BLOCK_DISPLAY_INFO bdi_selected[])
{
	bool loop = 1;
	int time = -1;
	while (loop)
	{
		time++;
		loop = 0;
		for(int x=0;x<ROW;x++)
			for(int y=0;y<COL;y++)
				if (in[x][y] < 0)
				{
					for (int i = x + 1; i < ROW; i++)
						if (mto10[x][y] == mto10[i][y]&& in[i][y]==0)
						{
							loop = 1;
							in[i][y] = -2;
						}
						else
							break;
					for (int i = x - 1; i > -1; i--)
						if (mto10[x][y] == mto10[i][y]&& in[i][y]==0)
						{
							loop = 1;
							in[i][y] = -2;
						}
						else
							break;
					for (int i = y + 1; i < COL; i++)
						if (mto10[x][y] == mto10[x][i]&& in[x][i]==0)
						{
							loop = 1;
							in[x][i] = -2;
						}
						else
							break;
					for (int i = y - 1; i > -1; i--)
						if (mto10[x][y] == mto10[x][i] && in[x][i]==0)
						{
							loop = 1;
							in[x][i] = -2;
						}
						else
							break;
				}
	}
	return time;
}
void draw_identical(CONSOLE_GRAPHICS_INFO Mto10_CGI,int in[ROW][COL], int mto10[ROW][COL], const BLOCK_DISPLAY_INFO bdi_normal[], const BLOCK_DISPLAY_INFO bdi_related[], const BLOCK_DISPLAY_INFO bdi_selected[])
{
	for (int x = 0; x < ROW; x++)
		for (int y = 0; y < COL; y++)
			if (in[x][y]==-1)
				gmw_draw_block(&Mto10_CGI, x, y, mto10[x][y], bdi_selected);
			else if(in[x][y] == -2)
				gmw_draw_block(&Mto10_CGI, x, y, mto10[x][y], bdi_related);
}
int simple_score(int a[ROW][COL], int in[ROW][COL], int x, int y)
{
	int s = 0;
	for (int i = 0; i < ROW; i++)
		for (int j = 0; j < COL; j++)
			if (in[i][j]<0)
				++s;
	s = s * 3 * (a[x][y]-1);
	return s;
}

void add_score(int& sim_s, int& score, int a[ROW][COL], int in[ROW][COL], int x, int y)
{
	sim_s = simple_score(a, in,x,y);
	score += sim_s;
	cct_gotoxy(2, 0);
	cout << "本次得分：" << sim_s << " 总得分：" << score << " 合成目标：10"<< endl;
}
int rand_num(int max)
{
	int a = rand() % 100 + 1, b = rand() % 3 + 1, c = rand() % 4 + 1;
	if (max == 3)
		return b;
	else if (max == 4)
	{
		if (a <= 90)
			return b;
		else
			return 4;
	}
	else if (max == 5)
	{
		if (a <= 75)
			return b;
		else if (a > 75 && a <= 90)
			return 4;
		else
			return 5;
	}
	else if (max == 6)
	{
		if (a <= 80)
			return c;
		else if (a > 80 && a <= 95)
			return 5;
		else
			return 6;
	}
	else
	{
		if (a <= 80)
			return rand() % (max - 3) + 1;
		else if (a > 80 && a <= 90)
			return max - 2;
		else if (a > 90 && a <= 95)
			return max - 1;
		else
			return max;
	}
}