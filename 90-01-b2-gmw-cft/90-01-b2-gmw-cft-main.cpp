/*邹良顺 2152611 信02*/
#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include<conio.h>
#include"../90-01-b2-gmw-cft/90-01-b2-gmw-cft-tools.h"


int main(int argv, char** argc)
{
	int MAX = 10;
	
	CONSOLE_GRAPHICS_INFO Mto10_CGI;
	
	gmw_init(&Mto10_CGI);
	gmw_set_frame_color(&Mto10_CGI, 7, 0);
	gmw_set_status_line_color(&Mto10_CGI, 0, 0, 7);
	gmw_set_rowno_switch(&Mto10_CGI, 1);//
	gmw_set_colno_switch(&Mto10_CGI, 1);//
	gmw_set_rowcol(&Mto10_CGI, 5, 5);
	gmw_set_frame_style(&Mto10_CGI, 10, 5, false);//无分隔线
	gmw_set_font(&Mto10_CGI, "新宋体", 16);
	gmw_set_block_border_switch(&Mto10_CGI, 1);



	int f_n[11] = { 0 }, b_n[11] = { 1,2,3,4,5,9,10,11,12,13 }, d_f = -1, d_b = -1, s_f = 15, s_b = -1, f_b = -1, f_f = 7;
	/*设置参数*/
	if (argv == 3&&strcmp(argc[1],"--cfgfile") == 0)
	{
		//只读方式打开
		cft file((const char*)argc[2]);
		if (!file.is_open())
		{
			cout << "文件打开失败" << endl;
			return 0;
		}		
		set_by_cft(Mto10_CGI,file,MAX,f_n,b_n,d_f,d_b,s_f,s_b,f_b,f_f);		
		file.close();
		system("pause");
	}
	else
	{
		cout << "默认5行5列，合成目标为10，请按任意键继续..." << endl;
		_getch();
		cct_cls();		
	}

	BLOCK_DISPLAY_INFO bdi_normal[] = {
		{BDI_VALUE_BLANK, -1, -1, NULL},
	{1,  b_n[0],   f_n[0],  NULL},
	{2,  b_n[1],  f_n[1],  NULL},
	{3,  b_n[2],   f_n[2],  NULL},
	{4,  b_n[3],    f_n[3],  NULL},
	{5,  b_n[4],   f_n[4],  NULL},
	{6,  b_n[5],  f_n[5],  NULL},
	{7,  b_n[6], f_n[6],  NULL},
	{8,  b_n[7],  f_n[7],  NULL},
	{9,  b_n[8],   f_n[8],  NULL},
	{10, b_n[9],  f_n[9],  NULL}
	};
	BLOCK_DISPLAY_INFO bdi_related[] = {
		{BDI_VALUE_BLANK, -1, -1, NULL},
		{1,  f_f,   f_b,  NULL},
	{2,  f_f,   f_b,  NULL}, 
	{3,  f_f,   f_b,  NULL}, 
	{4,  f_f,   f_b,  NULL}, 
	{5,  f_f,   f_b,  NULL}, 
	{6,  f_f,   f_b,  NULL}, 
	{7,  f_f,   f_b,  NULL}, 
	{8,  f_f,   f_b,  NULL}, 
	{9,  f_f,   f_b,  NULL}, 
	{10,  f_f,   f_b,  NULL} };
	BLOCK_DISPLAY_INFO bdi_selected[] = {
		{BDI_VALUE_BLANK, -1, -1, NULL},
		{1, s_f, s_b, NULL},
		{2, s_f, s_b, NULL},
		{3, s_f, s_b, NULL},
		{4, s_f, s_b, NULL},
		{5, s_f, s_b, NULL},
		{6, s_f, s_b, NULL},
		{7, s_f, s_b, NULL},
		{8, s_f, s_b, NULL},
		{9, s_f, s_b, NULL},
		{10, s_f, s_b, NULL}
	};

	/*运行*/
	srand((unsigned int)time(0));
	int i, j;

	char temp[99];
	int mto10[8][10]={0};
	for (i = 0; i < Mto10_CGI.row_num; i++)
		for (j = 0; j < Mto10_CGI.col_num; j++)
			mto10[i][j] = rand() % 3 + 1;

	gmw_draw_frame(&Mto10_CGI);
	sprintf(temp, "窗口大小：%d行 %d列", Mto10_CGI.lines, Mto10_CGI.cols);
	gmw_status_line(&Mto10_CGI, TOP_STATUS_LINE, temp);
	for (i = 0; i < Mto10_CGI.row_num; i++)
		for (j = 0; j < Mto10_CGI.col_num; j++)
			gmw_draw_block(&Mto10_CGI, i, j, mto10[i][j], bdi_normal);

	int x = 0, y = 0, action, k1, k2, f_x, f_y, max = 0, sim_s, score = 0;
	while (1)
	{
		for (i = 0; i < Mto10_CGI.row_num; i++)
			for (j = 0; j < Mto10_CGI.col_num; j++)
				if (mto10[i][j] > max)
					max = mto10[i][j];
		if (max == MAX)
			break;
		f_x = x;
		f_y = y;
		int in[8][10] = { 0 };//-1 选中  -2关联
		gmw_read_keyboard_and_mouse(&Mto10_CGI, action, x, y, k1, k2, 1);

		if (k1 == 224)
			switch (k2) {
				case KB_ARROW_UP:
					x == 0 ? x = Mto10_CGI.row_num - 1 : x--;
					break;
				case KB_ARROW_DOWN:
					x == Mto10_CGI.row_num - 1 ? x = 0 : x++;
					break;
				case KB_ARROW_LEFT:
					y == 0 ? y = Mto10_CGI.col_num - 1 : y--;
					break;
				case KB_ARROW_RIGHT:
					y == Mto10_CGI.col_num - 1 ? y = 0 : y++;
					break;
			}
		gmw_draw_block(&Mto10_CGI, x, y, mto10[x][y], bdi_selected);
		gmw_draw_block(&Mto10_CGI, f_x, f_y, mto10[f_x][f_y], bdi_normal);
		if (action == MOUSE_LEFT_BUTTON_CLICK || k1 == 13)
		{
			in[x][y] = -1;
			if (search_identical(in, mto10, bdi_normal, bdi_related, bdi_selected) == 0)
			{
				gmw_status_line(&Mto10_CGI, LOWER_STATUS_LINE, "选中值无效");
				continue;
			}
			in[x][y] = -1;
			draw_identical(Mto10_CGI, in, mto10, bdi_normal, bdi_related, bdi_selected);
			Sleep(SLEEP);
			//消除
			for (i = 0; i < Mto10_CGI.row_num; i++)
				for (j = 0; j < Mto10_CGI.col_num; j++)
					if (in[i][j] < 0)
					{
						if (in[i][j] == -1)
							mto10[i][j]++;
						else
							mto10[i][j] = 0;
						gmw_draw_block(&Mto10_CGI, i, j, mto10[i][j], bdi_selected);
					}
			//下落
			for (int i = 0; i < Mto10_CGI.col_num; i++)
				for (int j = 0; j < Mto10_CGI.row_num; j++)
				{
					if (mto10[j][i] == 0)
					{
						for (int m = j; m > 0; m--)
						{
							mto10[m][i] = mto10[m - 1][i];
							if (mto10[m - 1][i] != 0)
								gmw_move_block(&Mto10_CGI, m - 1, i, mto10[m - 1][i], mto10[m - 1][i], bdi_normal, 1, 1);
						}
						mto10[0][i] = 0;
					}
				}
			//生成
			for (i = 0; i < Mto10_CGI.row_num; i++)
				for (j = 0; j < Mto10_CGI.col_num; j++)
					if (mto10[i][j] == 0)
					{
						mto10[i][j] = rand_num(max);
						gmw_draw_block(&Mto10_CGI, i, j, mto10[i][j], bdi_normal);
					}
			add_score(sim_s, score, mto10, in, x, y);
		}
	}

	gmw_status_line(&Mto10_CGI, LOWER_STATUS_LINE, "合成成功！！！");

	return 0;
}