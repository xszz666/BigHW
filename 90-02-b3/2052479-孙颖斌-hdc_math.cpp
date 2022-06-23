/*2052479 –≈10 ÀÔ”±±Û*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include <stdio.h>  
#include <stdlib.h>  
#include <conio.h>  
#include <math.h>
#include <time.h>
#include "../include/cmd_hdc_tools.h"
using namespace std;
static const double PI = 3.14159;
void hdc_draw_Mathematical_curve_2052479()
{
	hdc_cls();
	int x0, y0;
	x0 = 400 + int((80.0 * fabs(sin(2 * 0)) + 100.0 * fabs(sin(4 * 0))) * cos(0));
	y0 = 400 - int((80.0 * fabs(sin(2 * 0)) + 100.0 * fabs(sin(4 * 0))) * sin(0));
	for (int i = 0; i < 360; i++)
	{
		double angle = ((double)i / 180.0 * PI);
		int x = 400 + int((100.0 * fabs(sin(2 * angle)) + 50.0 * fabs(sin(4 * angle))) * cos(angle));
		int y = 400 - int((100.0 * fabs(sin(2 * angle)) + 50.0 * fabs(sin(4 * angle))) * sin(angle));
		hdc_line(x0, y0, x, y, 3, RGB(188, 37, 235));
		x0 = x, y0 = y;
	}
	x0 = 400 + int((80.0 * fabs(sin(2 * 0)) + 100.0 * fabs(sin(4 * 0))) * cos(0));
	y0 = 400 - int((80.0 * fabs(sin(2 * 0)) + 100.0 * fabs(sin(4 * 0))) * sin(0));
	for (int i = 0; i < 360; i++)
	{
		double angle = ((double)i / 180.0 * PI);
		int x = 400 + int((160.0 * fabs(sin(2 * angle)) + 80.0 * fabs(sin(4 * angle))) * cos(angle));
		int y = 400 - int((160.0 * fabs(sin(2 * angle)) + 80.0 * fabs(sin(4 * angle))) * sin(angle));
		hdc_line(x0, y0, x, y, 5, RGB(226, 236, 36));
		x0 = x, y0 = y;
	}
	x0 = 400 + int((80.0 * fabs(sin(2 * 0)) + 100.0 * fabs(sin(4 * 0))) * cos(0));
	y0 = 400 - int((80.0 * fabs(sin(2 * 0)) + 100.0 * fabs(sin(4 * 0))) * sin(0));
	for (int i = 0; i < 360; i++)
	{
		double angle = ((double)i / 180.0 * PI);
		int x = 400 + int((220.0 * fabs(sin(2 * angle)) + 110.0 * fabs(sin(4 * angle))) * cos(angle));
		int y = 400 - int((220.0 * fabs(sin(2 * angle)) + 110.0 * fabs(sin(4 * angle))) * sin(angle));
		hdc_line(x0, y0, x, y, 8, RGB(251, 65, 21));
		x0 = x, y0 = y;
	}
}