//邹良顺 信02 2152611
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<time.h>
#include<conio.h>
#include"90-01-b2-gmw-h.h"

using namespace std;

int main()
{
	cout << "默认5行5列，合成目标为10，请按任意键继续..." << endl;
	_getch();
	cct_cls();

	srand((unsigned int)time(0));

	CONSOLE_GRAPHICS_INFO Mto10_CGI;
	gmw_init(&Mto10_CGI); 
	gmw_set_frame_color(&Mto10_CGI, 7, 0);
	gmw_set_status_line_color(&Mto10_CGI, 0, 0, 7);
	gmw_set_rowno_switch(&Mto10_CGI,1);//
	gmw_set_colno_switch(&Mto10_CGI,1);//
	gmw_set_rowcol(&Mto10_CGI, ROW, COL);
	gmw_set_frame_style(&Mto10_CGI, 10, 5, false);//无分隔线
	gmw_set_font(&Mto10_CGI, "新宋体", 16);
	gmw_set_block_border_switch(&Mto10_CGI, 1);

	const BLOCK_DISPLAY_INFO bdi_normal[] = {  
		{BDI_VALUE_BLANK, -1, -1, NULL},
	{1,  COLOR_BLUE,   COLOR_BLACK,  NULL},	
	{2,  COLOR_GREEN,  COLOR_BLACK,  NULL},
	{3,  COLOR_CYAN,   COLOR_BLACK,  NULL},
	{4,  COLOR_RED,    COLOR_BLACK,  NULL},
	{5,  COLOR_PINK,   COLOR_BLACK,  NULL},
	{6,  COLOR_HBLUE,  COLOR_BLACK,  NULL},
	{7,  COLOR_HGREEN, COLOR_BLACK,  NULL},
	{8,  COLOR_HCYAN,  COLOR_BLACK,  NULL},
	{9,  COLOR_HRED,   COLOR_BLACK,  NULL},
	{10, COLOR_HPINK,  COLOR_BLACK,  NULL}
	};
	const BLOCK_DISPLAY_INFO bdi_related[] = {
		{BDI_VALUE_BLANK, -1, -1, NULL},
		{1,  COLOR_BLUE,   COLOR_WHITE,  NULL},	
		{2,  COLOR_GREEN,  COLOR_WHITE,  NULL},
		{3,  COLOR_CYAN,   COLOR_WHITE,  NULL},
		{4,  COLOR_RED,    COLOR_WHITE,  NULL},
		{5,  COLOR_PINK,   COLOR_WHITE,  NULL},
		{6,  COLOR_HBLUE,  COLOR_WHITE,  NULL},
		{7,  COLOR_HGREEN, COLOR_WHITE,  NULL},
		{8,  COLOR_HCYAN,  COLOR_WHITE,  NULL},
		{9,  COLOR_HRED,   COLOR_WHITE,  NULL},
		{10, COLOR_HPINK,  COLOR_WHITE,  NULL}
	};
	const BLOCK_DISPLAY_INFO bdi_selected[] = {
		{BDI_VALUE_BLANK, -1, -1, NULL},
		{1, COLOR_BLUE,   COLOR_HWHITE, NULL},	
		{2,  COLOR_GREEN, COLOR_HWHITE,  NULL},
		{3, COLOR_CYAN,   COLOR_HWHITE, NULL},
		{4, COLOR_RED,    COLOR_HWHITE, NULL},
		{5, COLOR_PINK,   COLOR_HWHITE, NULL},
		{6, COLOR_HBLUE,  COLOR_HWHITE, NULL},
		{7, COLOR_HGREEN, COLOR_HWHITE, NULL},
		{8, COLOR_HCYAN,  COLOR_HWHITE, NULL},
		{9, COLOR_HRED,   COLOR_HWHITE, NULL},
		{10,COLOR_HPINK,  COLOR_HWHITE, NULL},	
	};

	int i,j;
	char temp[99];
	int mto10[ROW][COL];
	for (i = 0; i < ROW; i++)
		for (j = 0; j < COL; j++)
			mto10[i][j] = rand()%3 + 1;

	gmw_draw_frame(&Mto10_CGI);
	sprintf(temp, "窗口大小：%d行 %d列",Mto10_CGI.lines, Mto10_CGI.cols);
	gmw_status_line(&Mto10_CGI, TOP_STATUS_LINE, temp);
	for (i = 0; i < ROW; i++)
		for (j = 0; j < COL; j++) 			
			gmw_draw_block(&Mto10_CGI, i, j, mto10[i][j], bdi_normal);
		
	int x=0, y=0, action,k1,k2,f_x,f_y,max=0,sim_s,score=0;
	while (1)
	{	

		for (i = 0; i < ROW; i++)
			for (j = 0; j < COL; j++)
				if (mto10[i][j] > max)
					max = mto10[i][j];
		if (max == 10)
			break;
		f_x = x;
		f_y = y;
		int in[ROW][COL] = { 0 };//-1 选中  -2关联
		gmw_read_keyboard_and_mouse(&Mto10_CGI, action, x, y, k1, k2, 1);
	
		if(k1==224)
			switch (k2) {
			case KB_ARROW_UP:
				x == 0 ? x = ROW-1 : x--;
				break;
			case KB_ARROW_DOWN:
				x == ROW-1 ? x = 0 : x++;
				break;
			case KB_ARROW_LEFT:
				y == 0 ? y = COL-1 : y--;
				break;
			case KB_ARROW_RIGHT:
				y == COL-1 ? y = 0 : y++;
				break;
			}
		gmw_draw_block(&Mto10_CGI, x, y, mto10[x][y], bdi_selected);
		gmw_draw_block(&Mto10_CGI, f_x, f_y, mto10[f_x][f_y], bdi_normal);
		if (action == MOUSE_LEFT_BUTTON_CLICK || k1 == 13)
		{
			in[x][y] = -1;
			if (search_identical(in, mto10, bdi_normal, bdi_related, bdi_selected) == 0)
			{
				gmw_status_line(&Mto10_CGI, LOWER_STATUS_LINE,"选中值无效");
				continue;
			}
			in[x][y] = -1;
			draw_identical(Mto10_CGI, in, mto10, bdi_normal, bdi_related, bdi_selected);
			Sleep(SLEEP);
			//消除
			for (i = 0; i < ROW; i++)
				for (j = 0; j < COL; j++)
					if (in[i][j] < 0)
					{
						if (in[i][j] == -1)
							mto10[i][j]++;
						else
							mto10[i][j] = 0;
						gmw_draw_block(&Mto10_CGI, i, j, mto10[i][j], bdi_selected);
					}
			//下落
			for(int i=0;i<COL;i++)
				for (int j = 0; j < ROW; j++)
				{
					if (mto10[j][i] == 0)
					{
						for (int m = j; m > 0; m--)
						{
							mto10[m][i] = mto10[m - 1][i];
							if(mto10[m - 1][i]!=0)
								gmw_move_block(&Mto10_CGI, m - 1, i, mto10[m-1][i], mto10[m-1][i],bdi_normal, 1, 1);
						}
						mto10[0][i] = 0;
					}
				}
			//生成
			for (i = 0; i < ROW; i++)
				for (j = 0; j < COL; j++)
					if (mto10[i][j] == 0)
					{
						mto10[i][j] = rand_num(max);
						gmw_draw_block(&Mto10_CGI, i, j, mto10[i][j], bdi_normal);
					}
			add_score(sim_s, score, mto10, in, x, y);
		}	
	}

	gmw_status_line(&Mto10_CGI, LOWER_STATUS_LINE,"合成成功！！！");
	return 0;
}