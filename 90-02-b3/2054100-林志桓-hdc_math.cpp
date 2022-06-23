/* 2054100 ��04 ��־�� */
#include <cmath>
#include <iostream>
#include "../include/cmd_hdc_tools.h"
#include "hdc_student_works.h"
using namespace std;

#define DEFAULT_A 1
#define DEFAULT_B 1
#define DEFAULT_C 1
#define CONTINUE 0
#define FIRST_OVER 1
#define SECOND_OVER 2

/***************************************************************************
  �������ƣ�
  ��    �ܣ�����������
  ���������const int point_x	��ԭ���x����
			const int point_y	��ԭ���y����
			const int a 		������a��x^2��y^2��ϵ������ȱʡֵ��
			const int b 		������c���������ȱʡֵ��
			const int c 		������d��x^3ϵ������ȱʡֵ��
			const int thickness ���ߵĴ�ϸ����ȱʡֵ��
			const int RGB_value ����ɫ����ȱʡֵ��
  �� �� ֵ��
  ˵    ����ԭ������(x^2+y^2-1)^2=x^3�����ò���(ax^2+ay^2-b)^2 = cx^3��x��y��
            ��������ȵ�ʱ��źÿ�
***************************************************************************/
void moon_craft(const int point_x, const int point_y, const int a = DEFAULT_A, const int b = DEFAULT_B, const int c = DEFAULT_C, const int thickness = 2, const int RGB_value = INVALID_RGB)
{
	if (RGB_value != INVALID_RGB)
		hdc_set_pencolor(RGB_value);
	int ra = a, rb = b, rc = c;
	if (ra <= 0)
		ra = DEFAULT_A;
	if (rb <= 0)
		rb = DEFAULT_B;
	if (rc <= 0)
		rc = DEFAULT_C;

	int Y1 = 0, Y2 = 0, y1 = 0, y2 = 0, y3 = 0, y4 = 0;
	int old_Y1 = 0, old_Y2 = 0, old_y1 = 0, old_y2 = 0, old_y3 = 0, old_y4 = 0;
	int x = 0;
	int rx = point_x + x;
	double rc3 = 0;
	int flag = CONTINUE;
	while (1)
	{
		rc3 = double(rc) / 1000000 * x * x * x ;
		Y1 = (int)(rb - ra * x * x + sqrt(rc3) * 1000) / ra;  //��ֹsqrtԽ��
		Y2 = (int)(rb - ra * x * x - sqrt(rc3) * 1000) / ra;

		if (old_Y1 >= 0 && Y1 < 0)
			hdc_line(rx, point_y + y1, rx, point_y + y2, thickness, RGB_value);
		if (old_Y2 >= 0 && Y2 < 0)
			hdc_line(rx, point_y + y3, rx, point_y + y4, thickness, RGB_value);

		old_Y1 = Y1;
		old_Y2 = Y2;

		if (Y1 < 0 && Y2 < 0)
			break;

		if (Y1 >= 0 && Y2 >= 0)
		{
			y1 = (int)sqrt(Y1);
			y2 = (int)-sqrt(Y1);
			y3 = (int)sqrt(Y2);
			y4 = (int)-sqrt(Y2);
			if (x == 0)
			{
				old_y1 = y1;
				old_y2 = y2;
				old_y3 = y3;
				old_y4 = y4;
			}
			rx = point_x + x;
			hdc_point(rx, point_y + y1, thickness, RGB_value);
			hdc_point(rx, point_y + y2, thickness, RGB_value);
			hdc_point(rx, point_y + y3, thickness, RGB_value);
			hdc_point(rx, point_y + y4, thickness, RGB_value);
			if (abs(y1 - old_y1) > 3 )
				hdc_line(rx - 1, point_y + old_y1, rx, point_y + y1, thickness, RGB_value);
			if (abs(y2 - old_y2) > 3)
				hdc_line(rx - 1, point_y + old_y2, rx, point_y + y2, thickness, RGB_value);
			if (abs(y3 - old_y3) > 3)
				hdc_line(rx - 1, point_y + old_y3, rx, point_y + y3, thickness, RGB_value);
			if (abs(y4 - old_y4) > 3)
				hdc_line(rx - 1, point_y + old_y4, rx, point_y + y4, thickness, RGB_value);
			old_y1 = y1;
			old_y2 = y2;
			old_y3 = y3;
			old_y4 = y4;
		}

		if (Y1 >= 0 && Y2 < 0)
		{
			y1 = (int)sqrt(Y1);
			y2 = (int)-sqrt(Y1);
			rx = point_x + x;
			hdc_point(rx, point_y + y1, thickness, RGB_value);
			hdc_point(rx, point_y + y2, thickness, RGB_value);
			if (abs(y1 - old_y1) > 3)
				hdc_line(rx - 1, point_y + old_y1, rx, point_y + y1, thickness, RGB_value);
			if (abs(y2 - old_y2) > 3)
				hdc_line(rx - 1, point_y + old_y2, rx, point_y + y2, thickness, RGB_value);
			old_y1 = y1;
			old_y2 = y2;
		}

		x++;
	}


}


void hdc_draw_Mathematical_curve_2054100()
{
	hdc_cls();
	cout << "�������ߣ�����Ϊ(ax^2+ay^2-b)^2 = cx^3";

	hdc_set_pencolor(rand() % 256, rand() % 256, rand() % 256);
	moon_craft(400, 400, 100, 4000000, 200000, 5);

	hdc_set_pencolor(rand() % 256, rand() % 256, rand() % 256);
	moon_craft(400, 400, 100, 400000, 400000, 5);

	hdc_set_pencolor(rand() % 256, rand() % 256, rand() % 256);
	moon_craft(450, 400, 100, 8000000, 400000, 5);
}