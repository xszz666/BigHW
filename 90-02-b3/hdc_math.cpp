//邹良顺 2152611 信02
#include<iostream>
#include"../include/cmd_hdc_tools.h"
#define pi 3.141592653589793
using namespace std;
#define a 0.5
#define b 0.2 
#define start_x 350
#define start_y 350 

void hdc_draw_Mathematical_curve_2152611()
{
	hdc_cls();
	cct_setconsoleborder(100, 50);
	hdc_set_pencolor(143,220, 20);
	//画阿基米德螺线
	for (int angle = 255 * 6; angle >0; angle--)
	{
		hdc_set_pencolor(angle>=255*2?255:angle/2%255, angle-255*4>=0? 255:(angle - 255 * 2>=0?(angle - 255 * 2)/2%255:0), angle - 255 * 4 >= 0 ? (angle - 255 * 4) / 2 % 255 : 0);
		double x, y;
		x = (a + b * angle) * cos(angle * pi / 180);
		y = (a + b * angle) * sin(angle * pi / 180);
		hdc_point(int(x)+start_x,int(y)+start_y,8);
	}
	return;
}