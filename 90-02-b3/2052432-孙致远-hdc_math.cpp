/*2052432 ��12 ����Զ*/
#include <iostream>
#include <cmath>
#include <Windows.h>
#include <stdio.h>  
#include <stdlib.h>  
#include <conio.h>  
#include <time.h>
#include "../include/cmd_hdc_tools.h"
using namespace std;

/*����Ϊ�����׵����ߣ����ļ����귽��Ϊ r=a+b*�� */

void hdc_draw_Mathematical_curve_2052432()
{
	hdc_cls();

	static double a = 0.05,b=0.1;
	double angle = 0;
	double radius = 0;
	static int base_x = 400;
	static int base_y = 400;

	for (; angle-(360 * 5)<0; angle++)
	{
		radius = a + b * 2.5*angle;
		hdc_arc(base_x, base_y, int(radius), int(angle), int(angle + 1), 4, RGB(100, 180, 200));
	}
}