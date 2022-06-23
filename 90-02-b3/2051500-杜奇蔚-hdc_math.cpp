/* 2051500 信15 杜奇蔚 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>  
#include <math.h>
#include "../include/cmd_hdc_tools.h"
using namespace std;

//系数
static const int a = 8;
static const double PI = 3.14159;
static const int color[] = { 0x00FF0000, 0x0000FF00, 0x000000FF }; //R G B

//费马螺旋线
void hdc_draw_Mathematical_curve_2051500()
{
	hdc_cls();
	for (int angle = 0; angle < 360 * 7; ++angle)
	{
		hdc_point(400 + int(a * sqrt(angle) * cos(angle * PI / 180)), 400 + int(a * sqrt(angle) * sin(angle * PI / 180)), 10, color[angle % 3]);
		hdc_point(400 - int(a * sqrt(angle) * cos(angle * PI / 180)), 400 - int(a * sqrt(angle) * sin(angle * PI / 180)), 10, color[angle % 3]);
	}
}