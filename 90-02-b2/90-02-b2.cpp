//2152611 邹良顺 信02
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include"./90-02-b2-h.h"
#include<Windows.h>
#include<time.h>
using namespace std;

int main()
{
	cout << "默认5行5列，目标为合成2048" << endl;
	Sleep(1000);

	srand((unsigned int)time(0));
	CONSOLE_GRAPHICS_INFO G2048_CGI;
	int G2048[ROW][COL] = { 0 },x,y;
	const BLOCK_DISPLAY_INFO bdi_normal[] = {
		{BDI_VALUE_BLANK, -1, -1, NULL}, 
		{2, COLOR_HYELLOW, COLOR_BLACK, NULL},
		{4, COLOR_HRED, COLOR_BLACK, NULL},
		{8, COLOR_GREEN, COLOR_BLACK, NULL},
		{16, COLOR_RED, COLOR_BLACK, NULL},
		{32, COLOR_HGREEN, COLOR_BLACK, NULL},
		{64, COLOR_HYELLOW, COLOR_BLACK, NULL},
		{128, COLOR_HRED, COLOR_BLACK, NULL},
		{256, COLOR_HWHITE, COLOR_BLACK, NULL},
		{512, COLOR_HBLACK, COLOR_BLACK, NULL},
		{1024, COLOR_HPINK, COLOR_BLACK, NULL},
		{2048, COLOR_WHITE, COLOR_BLACK, NULL}		 
	};

	gmw_init(&G2048_CGI);
	gmw_set_block_border_switch(&G2048_CGI, 1);
	gmw_set_delay(&G2048_CGI, 1, 0);
	gmw_set_delay(&G2048_CGI, 2, 0);
	gmw_set_rowcol(&G2048_CGI, ROW, COL);
	gmw_set_frame_style(&G2048_CGI, 10, 5, 1);
	gmw_set_frame_color(&G2048_CGI, 7, 0);
	gmw_set_status_line_switch(&G2048_CGI, 0, 1);
	gmw_set_status_line_switch(&G2048_CGI, 1, 0);
	for (int i = 0; i < 2; i++)
	{
		x = rand() % ROW;
		y = rand() % COL;
		G2048[x][y] == 0 ? G2048[x][y] = 2 : i--;
	}
	gmw_draw_frame(&G2048_CGI);
	for (int i = 0; i < ROW; i++)
		for (int j = 0; j < COL; j++)
			gmw_draw_block(&G2048_CGI, i, j, G2048[i][j], bdi_normal);
	gmw_status_line(&G2048_CGI, 0, "Created by xszz666");
	while (1)
	{
		int x, y, a, k1, k2, distance = 0,ret,max=0,loop=0;
		ret=gmw_read_keyboard_and_mouse(&G2048_CGI, a, x, y, k1, k2);
		if (ret == CCT_KEYBOARD_EVENT)
		{
			loop = 0;
			if (k1 == 224)
				switch (k2)
				{
				case  KB_ARROW_UP:
					for (int j = 0; j < COL; j++)
					{
						distance = 0;
						for (int i = 0; i < ROW; i++)
						{
							if (G2048[i][j] == 0)
								distance++;
							else 
							{
								gmw_move_block(&G2048_CGI, i, j, G2048[i][j], G2048[i][j], bdi_normal, DOWN_TO_UP, distance);
								G2048[i - distance][j] = G2048[i][j];
								distance>0?G2048[i][j] = 0: G2048[i][j]= G2048[i][j];
								if (i - distance > 0 && G2048[i - distance][j] == G2048[i - distance - 1][j])
								{
									//gmw_move_block(&G2048_CGI, i, j, G2048[i - distance - 1][j], G2048[i - distance - 1][j], bdi_normal, DOWN_TO_UP, 1);
									G2048[i - distance - 1][j] *= 2;
									G2048[i - distance][j] = 0;
									gmw_draw_block(&G2048_CGI, i - distance, j, G2048[i - distance][j], bdi_normal);
									gmw_draw_block(&G2048_CGI, i - distance - 1, j, G2048[i - distance - 1][j], bdi_normal);
									distance++;
								}
								loop = distance > 0 ? 1 : loop;
							}
						}
					}
					break;
				case KB_ARROW_DOWN:
					for (int j = 0; j < COL; j++)
					{
						distance = 0;
						for (int i = ROW - 1; i > -1; i--)
						{
							if (G2048[i][j] == 0)
								distance++;
							else
							{
								gmw_move_block(&G2048_CGI, i, j, G2048[i][j], G2048[i][j], bdi_normal, UP_TO_DOWN, distance);
								G2048[i + distance][j] = G2048[i][j];
								distance > 0 ? G2048[i][j] = 0 : G2048[i][j] = G2048[i][j];
								if (i + distance < ROW - 1 && G2048[i + distance][j] == G2048[i + distance + 1][j])
								{
									//gmw_move_block(&G2048_CGI, i, j, G2048[i + distance + 1][j], G2048[i + distance + 1][j], bdi_normal, UP_TO_DOWN, 1);
									G2048[i + distance + 1][j] *= 2;
									G2048[i + distance][j] = 0;
									gmw_draw_block(&G2048_CGI, i + distance, j, G2048[i + distance][j], bdi_normal);
									gmw_draw_block(&G2048_CGI, i + distance + 1, j, G2048[i + distance + 1][j], bdi_normal);
									distance++;
								}
								loop = distance > 0 ? 1 : loop;
							}
						}
					}
					break;
				case KB_ARROW_RIGHT:
					for (int i = 0; i < ROW; i++)
					{
						distance = 0;
						for (int j = COL - 1; j > -1; j--)
						{
							if (G2048[i][j] == 0)
								distance++;
							else
							{
								gmw_move_block(&G2048_CGI, i, j, G2048[i][j], G2048[i][j], bdi_normal, LEFT_TO_RIGHT, distance);
								G2048[i][j + distance] = G2048[i][j];
								distance > 0 ? G2048[i][j] = 0 : G2048[i][j] = G2048[i][j];
								if (j + distance < COL - 1 && G2048[i][j + distance] == G2048[i][j + distance + 1])
								{
									//gmw_move_block(&G2048_CGI, i, j, G2048[i][j + distance + 1], G2048[i][j + distance + 1], bdi_normal, LEFT_TO_RIGHT, 1);
									G2048[i][j + distance + 1] *= 2;
									G2048[i][j + distance] = 0;
									gmw_draw_block(&G2048_CGI, i, j + distance + 1, G2048[i][j + distance + 1], bdi_normal);
									gmw_draw_block(&G2048_CGI, i, j + distance, G2048[i][j + distance], bdi_normal);
									distance++;
								}
								loop = distance > 0 ? 1 : loop;
							}
						}
					}
					break;
				case KB_ARROW_LEFT:
					for (int i = 0; i < ROW; i++)
					{
						distance = 0;
						for (int j = 0; j < COL; j++)
						{
							if (G2048[i][j] == 0)
								distance++;
							else
							{
								gmw_move_block(&G2048_CGI, i, j, G2048[i][j], G2048[i][j], bdi_normal, RIGHT_TO_LEFT, distance);
								G2048[i][j - distance] = G2048[i][j];
								distance > 0 ? G2048[i][j] = 0 : G2048[i][j] = G2048[i][j];
								if (j - distance > 0 && G2048[i][j - distance] == G2048[i][j - distance - 1])
								{
									//gmw_move_block(&G2048_CGI, i, j, G2048[i][j - distance - 1], G2048[i][j - distance - 1], bdi_normal, RIGHT_TO_LEFT, 1);
									G2048[i][j - distance - 1] *= 2;
									G2048[i][j - distance] = 0;
									gmw_draw_block(&G2048_CGI, i, j - distance - 1, G2048[i][j - distance - 1], bdi_normal);
									gmw_draw_block(&G2048_CGI, i, j - distance, G2048[i][j - distance], bdi_normal);
									distance++;
								}
								loop = distance > 0 ? 1 : loop;
							}
						}
					}
					break;
				}

			if (loop)
			{
				while(1)
				{
					x = rand() % ROW;
					y = rand() % COL;
					if (G2048[x][y] == 0)
					{
						gmw_set_status_line_switch(&G2048_CGI, 1, 1);
						char temp[30];
						sprintf(temp, "随机值位置：行=%d 列=%d", x+1,y+1);
						gmw_status_line(&G2048_CGI, 1, temp);
						G2048[x][y] = 2 * (rand() % 2 + 1);
						gmw_draw_block(&G2048_CGI, x, y, G2048[x][y], bdi_normal);
						break;
					}
				}
			}
			for (int i = 0; i < ROW; i++)
				for (int j = 0; j < COL; j++)
					max = G2048[i][j] > max ? G2048[i][j] : max;

			char temp[30];
			sprintf(temp,"目前最大值：%d 目标值：2048", max);
			gmw_status_line(&G2048_CGI, 0, temp);
			if (max == 2048)
				break;
		}
	}
	gmw_set_status_line_switch(&G2048_CGI, 1, 1);
	gmw_status_line(&G2048_CGI, 1,"合成成功，你赢了！！！！");
	return 0;
}