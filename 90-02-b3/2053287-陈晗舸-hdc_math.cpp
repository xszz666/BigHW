/* 2053287 陈晗舸 信15 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <stdio.h>  
#include <stdlib.h>  
#include <conio.h>  
#include <math.h>
#include <time.h>
using namespace std;
#include "../include/cmd_hdc_tools.h"
static const double PI = 3.14159;
static const int KCOLOR[4] = { RGB(81, 151, 211),RGB(253, 118, 115),RGB(170, 133, 29),RGB(240, 20, 240) };
static int pingfang_2(int shuzi)
{
	int i = 1;
	if (shuzi == 1)
		return i;
	else
	{
		for (int k = 1; k < shuzi; k++)
			i *= 2;
	}
	return i;
}
static void Helical_curve(const int point_x, const int point_y, const int a, const int thickness, const int RGB_value,bool fangxiang)
{
	int banjing = a;
	int jiaodu = 0;
	int x1 = point_x;
	int y1 = point_y;
	int th = thickness;
	for (; banjing <= 160;)
	{
		if (fangxiang)
			hdc_arc(x1, y1, banjing, (180 - 180 * jiaodu), (-180 * jiaodu), th, RGB_value);
		else
			hdc_arc(x1, y1, banjing, (-180 * jiaodu),(-180 - 180 * jiaodu), th, RGB_value);
		jiaodu++;
		banjing *= 2;
		if (jiaodu % 2 == 1)//圆心向下移动
		{
			for (int k = 0; k < pingfang_2(jiaodu); k++)
				y1 += a;
		}
		else//圆心向上移动
		{
			for (int k = 0; k < pingfang_2(jiaodu); k++)
				y1 -= a;
		}
	}
	th++;
	if (fangxiang)
		hdc_line(x1, y1 - banjing, x1 + 210, y1 - banjing, th, RGB_value);
	else
		hdc_line(x1, y1 - banjing, x1 - 210, y1 - banjing, th, RGB_value);
}
static void hdc_draw_Cartesian_lobar(const int point_x, const int point_y, const int radium, const int thickness, const int RGB_value,int pianzhuan)
{
	double t = -50;
	double old_x, old_y, new_x, new_y;
	for (; t < 50;)
	{
		if (t == -1)
			t += 0.01;
		if (pianzhuan==1)
		{
			new_x = -((double)((double)3 * (double)radium) * t) / (1 + t * t * t) + (double)point_x;
			new_y = ((double)((double)3 * (double)radium) * t * t) / (1 + t * t * t) + (double)point_y;
		}
		else 
		{
			if (pianzhuan == 0) 
			{
				new_x = ((double)((double)3 * (double)radium) * t) / (1 + t * t * t) + (double)point_x;
				new_y = ((double)((double)3 * (double)radium) * t * t) / (1 + t * t * t) + (double)point_y;
			}
			else
			{
				if (pianzhuan == 2)
				{
					new_x = ((double)((double)3 * (double)radium) * t) / (1 + t * t * t) + (double)point_x;
					new_y = -((double)((double)3 * (double)radium) * t * t) / (1 + t * t * t) + (double)point_y;
				}
				else
				{
					new_x = -((double)((double)3 * (double)radium) * t) / (1 + t * t * t) + (double)point_x;
					new_y = -((double)((double)3 * (double)radium) * t * t) / (1 + t * t * t) + (double)point_y;
				}
			}
		}
		if (t != -50)
		{
				hdc_line((int)old_x, (int)old_y, (int)new_x, (int)new_y, thickness, RGB_value);
		}
		old_x = new_x;
		old_y = new_y;
		t += 0.01;
	}

}
void hdc_draw_Mathematical_curve_2053287()
{
	int point_x = 400, point_y = 400;
	int a = 40;
	hdc_cls();
	/*Helical_curve(point_x, point_y, a, 3, ,1);
	Helical_curve(point_x + 420, point_y, a, 3, RGB(75, 220, 250),0);
	Helical_curve(point_x + 210, point_y + 350, a, 3, RGB(250, 245, 5), 0);*/
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 2; j++)
			hdc_draw_Cartesian_lobar(point_x, point_y, a + j * 30, 3, KCOLOR[i], i);
	cct_gotoxy(0, 0);
	cct_setcolor(7, 0);
	//cout << "#这是3条柱坐标螺旋曲线,尾部为直线拓展" << endl;
	cout << "#这是4条笛卡尔叶形曲线扩大生成的组合图形" << endl;
}

