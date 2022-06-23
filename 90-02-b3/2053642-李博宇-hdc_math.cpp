/* 2053642 信18 李博宇 */
#include <iostream>
#include <iomanip>
#include <cmath>
#include <Windows.h>
#include <conio.h>
#include "../include/cmd_hdc_tools.h"
using namespace std;
const static double PI = 3.14159265358979;

/***
* lissajous_curve: 画一个李萨如曲线
* **********
* 数学上通用的李萨如曲线参数方程定义为：
* ---- x = asin(θ)
* ---- y = bsin(nθ+φ)
* **********
* 参数及功能简述：
* int point_x/y:	基坐标x/y
* int a/b/n:		方程定参数a/b/n/φ(n应当>1，φ应当为0-90)
* int thickness:	曲线粗度
* int RGB_value:	RGB色号（gradual=0表示单色，gradual!=0则不可信）
* int gradual:		渐变色开关，如果非零则表示使用
*/
static void lissajous_curve(int point_x, int point_y, int a, int b, int n, int phi, int thickness, int RGB_value, int gradual = 0) {
	const int r_begin = 255, r_mid1 = 0  , r_mid2 = 0  , r_end = 255;
	const int g_begin = 0  , g_mid1 = 255, g_mid2 = 0  , g_end = 0  ;
	const int b_begin = 0  , b_mid1 = 0  , b_mid2 = 255, b_end = 0  ;
	if (!gradual && RGB_value != INVALID_RGB)
		hdc_set_pencolor(RGB_value);
	n = (n < 1 ? 1 : n);
	phi = (phi < 0 ? 0 : (phi > 90 ? 90 : phi));
	double incre = 1.0 / (double(n) * sqrt(a * a + b * b)); // 角度增量
	double _phi = double(phi) * PI / 180.0;
	int x, y;
	int rgb_r = r_begin;
	int rgb_g = g_begin;
	int rgb_b = b_begin;
	if (!gradual)
		rgb_r = GetRValue(RGB_value), rgb_g = GetGValue(RGB_value), rgb_b = GetBValue(RGB_value);
	for (double rad = 0.0; rad <= 2.0 * PI + incre; rad += incre) {
		x = point_x + (int)(double(a) * sin(rad));
		y = point_y + (int)(double(b) * sin(double(n) * rad + _phi));
		hdc_point(x, y, thickness, RGB(rgb_r, rgb_g, rgb_b));
		if (gradual) {
			if (rad <= 2.0 * PI / 3.0) {
				rgb_r = (int)(double(r_begin) * (1.0 - 1.5 * rad / PI) + double(r_mid1) * (1.5 * rad / PI));
				rgb_g = (int)(double(g_begin) * (1.0 - 1.5 * rad / PI) + double(g_mid1) * (1.5 * rad / PI));
				rgb_b = (int)(double(b_begin) * (1.0 - 1.5 * rad / PI) + double(b_mid1) * (1.5 * rad / PI));
			}
			else if (rad <= 4.0 * PI / 3.0) {
				rgb_r = (int)(double(r_mid1) * (2.0 - 1.5 * rad / PI) + double(r_mid2) * (1.5 * rad / PI - 1.0));
				rgb_g = (int)(double(g_mid1) * (2.0 - 1.5 * rad / PI) + double(g_mid2) * (1.5 * rad / PI - 1.0));
				rgb_b = (int)(double(b_mid1) * (2.0 - 1.5 * rad / PI) + double(b_mid2) * (1.5 * rad / PI - 1.0));
			}
			else {
				rgb_r = (int)(double(r_mid2) * (3.0 - 1.5 * rad / PI) + double(r_end) * (1.5 * rad / PI - 2.0));
				rgb_g = (int)(double(g_mid2) * (3.0 - 1.5 * rad / PI) + double(g_end) * (1.5 * rad / PI - 2.0));
				rgb_b = (int)(double(b_mid2) * (3.0 - 1.5 * rad / PI) + double(b_end) * (1.5 * rad / PI - 2.0));
			}
		}
	}
}

void hdc_draw_Mathematical_curve_2053642() {
	hdc_cls();
	//const int rgb_marrs_green = RGB(0, 140, 140);
	// 参数的功能描述详见lissajous_curve函数
	const static int base_x = 480; // 基坐标x
	const static int base_y = 240; // 基坐标y
	const static int a = 400; // 李萨如曲线的参数，实际显示中控制横向显示长度（图像宽为2a）
	const static int b = 200; // 李萨如曲线的参数，实际显示中控制纵向显示长度（图像高为2b）
	const static int n = 20; // 李萨如曲线的参数，控制图像的形状（n=1为椭圆，n=2为双纽线，更大则更复杂）
	const static int phi = 45; // 李萨如曲线的参数，表示初始相位
	const static int thickness = 5; // 曲线的粗细
	const static int gradual = 1; // 如此项为非零，则展示渐变色，否则展示rgb表示的颜色
	const static int rgb = RGB(0, 140, 140); // 单色模式的输出颜色，当前为Marrs Green

	hdc_set_delay(0); // 一秒延时都不能加
	lissajous_curve(base_x, base_y, a, b, n, phi, thickness, rgb, gradual);
}