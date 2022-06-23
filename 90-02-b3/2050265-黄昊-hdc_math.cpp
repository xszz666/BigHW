/*2050265 ÐÅ04 »Æê»*/
#include<iostream>
#include<windows.h>
#include<math.h>
#include"../include/cmd_hdc_tools.h"
using namespace std;

int fun(int x)
{
	int y = int(200 * (sqrt(cos(0.005 * x)) * cos(1 * x) + sqrt(fabs(0.005*x)) - 0.7) * pow((4 - 0.005 * 0.005 * x * x), 0.01));
	return y;
}
void hdc_draw_Mathematical_curve_2050265()
{
	hdc_cls();
	int X, Y,X_Next,Y_Next;
	int DeltaX = 1;
	int r, g, b, color;
	r = 85;
	g = 1;
	b = 199;
	color = RGB(r, g, b);
	X = -320;
	Y = fun(X);
	int TotalCount = 640;
	for (int i = 1; i <= TotalCount; i++)
	{
		X++;
		Y = -fun(X);
		X_Next =  X + 1;
		Y_Next = -fun(X_Next);
		hdc_line(X + 400, Y + 400, X_Next + 400, Y_Next + 400, 1, color);
	}
}