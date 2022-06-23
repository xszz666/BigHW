/* 2053642 ��18 ��� */
#include <iostream>
#include <iomanip>
#include <cmath>
#include <Windows.h>
#include <conio.h>
#include "../include/cmd_hdc_tools.h"
using namespace std;
const static double PI = 3.14159265358979;

/***
* lissajous_curve: ��һ������������
* **********
* ��ѧ��ͨ�õ����������߲������̶���Ϊ��
* ---- x = asin(��)
* ---- y = bsin(n��+��)
* **********
* ���������ܼ�����
* int point_x/y:	������x/y
* int a/b/n:		���̶�����a/b/n/��(nӦ��>1����Ӧ��Ϊ0-90)
* int thickness:	���ߴֶ�
* int RGB_value:	RGBɫ�ţ�gradual=0��ʾ��ɫ��gradual!=0�򲻿��ţ�
* int gradual:		����ɫ���أ�����������ʾʹ��
*/
static void lissajous_curve(int point_x, int point_y, int a, int b, int n, int phi, int thickness, int RGB_value, int gradual = 0) {
	const int r_begin = 255, r_mid1 = 0  , r_mid2 = 0  , r_end = 255;
	const int g_begin = 0  , g_mid1 = 255, g_mid2 = 0  , g_end = 0  ;
	const int b_begin = 0  , b_mid1 = 0  , b_mid2 = 255, b_end = 0  ;
	if (!gradual && RGB_value != INVALID_RGB)
		hdc_set_pencolor(RGB_value);
	n = (n < 1 ? 1 : n);
	phi = (phi < 0 ? 0 : (phi > 90 ? 90 : phi));
	double incre = 1.0 / (double(n) * sqrt(a * a + b * b)); // �Ƕ�����
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
	// �����Ĺ����������lissajous_curve����
	const static int base_x = 480; // ������x
	const static int base_y = 240; // ������y
	const static int a = 400; // ���������ߵĲ�����ʵ����ʾ�п��ƺ�����ʾ���ȣ�ͼ���Ϊ2a��
	const static int b = 200; // ���������ߵĲ�����ʵ����ʾ�п���������ʾ���ȣ�ͼ���Ϊ2b��
	const static int n = 20; // ���������ߵĲ���������ͼ�����״��n=1Ϊ��Բ��n=2Ϊ˫Ŧ�ߣ�����������ӣ�
	const static int phi = 45; // ���������ߵĲ�������ʾ��ʼ��λ
	const static int thickness = 5; // ���ߵĴ�ϸ
	const static int gradual = 1; // �����Ϊ���㣬��չʾ����ɫ������չʾrgb��ʾ����ɫ
	const static int rgb = RGB(0, 140, 140); // ��ɫģʽ�������ɫ����ǰΪMarrs Green

	hdc_set_delay(0); // һ����ʱ�����ܼ�
	lissajous_curve(base_x, base_y, a, b, n, phi, thickness, rgb, gradual);
}