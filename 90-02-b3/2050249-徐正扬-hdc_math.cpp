/* 2050249 ÐÅ14 ÐìÕýÑï */
#include <iostream>
#include <cmath>
#include <time.h>
#include "../include/cmd_hdc_tools.h"
#define pi 3.141592653589793
using namespace std;

void flowers(double point_x, double point_y, double radius, double angles, int thickness, double(*p)(double), int a, double(*q)(double), int b)
{
	hdc_set_pencolor(rand() % 256, rand() % 256, rand() % 256);

	for (double i = angles; i < angles + 360; i += 0.01)
	{
		double sin_i = sin(i * pi / 180);
		double cos_i = cos(i * pi / 180);
		double sin_angles = sin(angles * pi / 180);
		double cos_angles = cos(angles * pi / 180);
		double fun_theta = p(a * i * pi / 180) * q(b * i * pi / 180);
		double x0 = radius * fun_theta * cos_i;
		double y0 = radius * fun_theta * sin_i;
		double x = x0 * cos_angles - y0 * sin_angles + point_x;
		double y = x0 * sin_angles + y0 * cos_angles + point_y;
		hdc_point((int)x, (int)y, thickness);
	}
	return;
}

void hdc_draw_Mathematical_curve_2050249()
{
	cct_setconsoleborder(80, 120);
	hdc_cls();
	srand((unsigned)time(NULL));
	flowers(400, 320, 300, 0, 3, sin, 2, cos, 4);
	flowers(400, 320, 300, 45, 3, sin, 2, cos, 4);
	flowers(400, 320, 50, 0, 2, cos, 2, sin, 4);
	return;
}