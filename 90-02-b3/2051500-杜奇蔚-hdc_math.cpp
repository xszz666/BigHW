/* 2051500 ��15 ����ε */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>  
#include <math.h>
#include "../include/cmd_hdc_tools.h"
using namespace std;

//ϵ��
static const int a = 8;
static const double PI = 3.14159;
static const int color[] = { 0x00FF0000, 0x0000FF00, 0x000000FF }; //R G B

//����������
void hdc_draw_Mathematical_curve_2051500()
{
	hdc_cls();
	for (int angle = 0; angle < 360 * 7; ++angle)
	{
		hdc_point(400 + int(a * sqrt(angle) * cos(angle * PI / 180)), 400 + int(a * sqrt(angle) * sin(angle * PI / 180)), 10, color[angle % 3]);
		hdc_point(400 - int(a * sqrt(angle) * cos(angle * PI / 180)), 400 - int(a * sqrt(angle) * sin(angle * PI / 180)), 10, color[angle % 3]);
	}
}