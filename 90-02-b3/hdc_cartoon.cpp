//����˳ 2152611 ��02
#include<iostream>
#include <cmath>

using namespace std;

#include "../include/cmd_hdc_tools.h"

#define pi 3.1415926525

static const int high = 800;
static const int width = 800;
//b g r
static const int background_1 = 0xa0d6b3;
static const int background_2 = 0xffffff;
static const int lines = 0x242f43;
static const int in = 0x000000;
static const int eye = 0xd6fbff;
static const int mouse = 0x9d9042;
static const int ear = 0xa0d6b1;

//����
static void set_background(const int base_x = 400, const int base_y = 400)
{
	hdc_square(base_x - width / 2, base_y - high / 2, high, 0, 1, 1, background_1);
	hdc_circle(base_x, base_y, high * 3 / 8, 1,1 ,background_2);
}
//��
static void draw_eye(int x,int y)
{
	//����
	hdc_ellipse(x, y,  high * 13 / 64/2,high * 25 / 128 * 5/ 8,0,1,5,eye );
	hdc_ellipse(x, y, high * 13 / 64 / 2, high * 25 / 128 * 5 / 8, 0, 0, 5, lines);
	//С��
	hdc_ellipse(x, y, high * 13 / 64 / 2*2/3, high * 25 / 128 * 5 / 8*3/4, 0, 1, 5, in);
	hdc_ellipse(x, y, high * 13 / 64 / 2*2/3, high * 25 / 128 * 5 / 8*3/4, 0, 0, 5, lines);
}
//����
void draw_ear(const int base_x = 400, const int base_y = 400)
{
	int face_half_width = high * 13 / 64;
	int face_half_high = high * 25 / 128;
	//��
	
	hdc_ellipse(base_x + face_half_width * 5/8, base_y - face_half_high + face_half_high *2/25, face_half_width * 3 / 4/2, face_half_high / 3/2, -5, 1, 5, in);
	hdc_ellipse(base_x + face_half_width * 5/8, base_y - face_half_high + face_half_high * 2 / 25, face_half_width * 3 / 4/2, face_half_high / 3/2, -5, 0, 5, lines);

	hdc_ellipse(base_x - face_half_width * 5/8, base_y - face_half_high + face_half_high * 2 / 25, face_half_width * 3 / 4/2, face_half_high / 3/2, 5, 1, 5, in);
	hdc_ellipse(base_x -face_half_width * 5/8, base_y - face_half_high + face_half_high * 2 / 25, face_half_width * 3 / 4/2, face_half_high / 3/2, 5, 0, 5, lines);

	//б
	hdc_ellipse(base_x - face_half_width * 10/16, base_y - face_half_high* 3/8, face_half_high/3, high * 25 / 128 * 3 / 4, - 30 , 1, 5, ear);
	hdc_ellipse(base_x - face_half_width * 10 / 16, base_y - face_half_high * 3 / 8,  face_half_high / 3, high * 25 / 128 * 3 / 4, -30 , 0, 5, lines);

	hdc_ellipse(base_x + face_half_width * 10 / 16, base_y - face_half_high * 3 / 8,  face_half_high / 3, high * 25 / 128 * 3 / 4, 30 , 1, 5, ear);
	hdc_ellipse(base_x + face_half_width * 10 / 16, base_y - face_half_high * 3 / 8,  face_half_high / 3, high * 25 / 128 * 3 / 4, 30 , 0, 5, lines);
}
//��
static void draw_face(const int base_x = 400, const int base_y = 400)
{
	int face_half_width = high * 13 / 64;
	int face_half_high = high * 25 / 128;
	//����
	draw_ear(base_x, base_y);
	//��������
	hdc_ellipse(base_x, base_y, face_half_width, face_half_high, 0, 1, 5, in);
	hdc_ellipse(base_x, base_y, face_half_width, face_half_high, 0, 0, 5, lines);
	//��
	draw_eye(base_x - face_half_width / 2, base_y);
	draw_eye(base_x + face_half_width / 2, base_y);
	//��
	hdc_triangle(base_x, base_y + face_half_high * 10 / 11, base_x - face_half_width / 6, base_y + face_half_high * 2 / 3, base_x + face_half_width / 6, base_y + face_half_high * 2 / 3, 1, 5, mouse);
	hdc_triangle(base_x, base_y + face_half_high * 10 / 11, base_x - face_half_width / 6, base_y + face_half_high * 2 / 3, base_x + face_half_width / 6, base_y + face_half_high * 2 / 3, 0, 5, lines);
}
//����
static void heixiu(const int base_x = 400, const int base_y = 400)
{
	int face_half_width = high * 13 / 64;
	int face_half_high = high * 25 / 128;

	int heixiu_half_width = face_half_width / 3;
	int heixiu_half_high = face_half_high / 4;
	//ͷ
	hdc_ellipse(base_x, base_y-face_half_high, face_half_high/3, face_half_width / 4, 0, 1, 5, in);
	hdc_ellipse(base_x , base_y-face_half_high,  face_half_high / 3, face_half_width / 4, 0, 0, 5, lines);
	//����
	hdc_point(base_x + face_half_high / 3 * 4 / 5, base_y - face_half_high - face_half_high/4 * 2 / 3, 15, lines);
	hdc_point(base_x - face_half_high / 3 * 4 / 5, base_y - face_half_high - face_half_high/4 * 2 / 3, 15, lines);
	//����
	hdc_ellipse(base_x- heixiu_half_width/2, base_y - face_half_high, heixiu_half_width *9/ 25, heixiu_half_high*11/16, 0, 1, 5, eye);
	hdc_ellipse(base_x - heixiu_half_width/2, base_y - face_half_high, heixiu_half_width *9/ 25, heixiu_half_high *11/16, 0, 0, 5, lines);

	hdc_ellipse(base_x +heixiu_half_width / 2, base_y - face_half_high, heixiu_half_width * 9 / 25, heixiu_half_high * 11 / 16, 0, 1, 5, eye);
	hdc_ellipse(base_x + heixiu_half_width / 2, base_y - face_half_high, heixiu_half_width * 9 / 25, heixiu_half_high * 11 / 16, 0, 0, 5, lines);
	//С��
	hdc_ellipse(base_x - heixiu_half_width / 2, base_y - face_half_high, heixiu_half_width * 9 / 25*2/3, heixiu_half_high * 11 / 16/2, 0, 1, 5, in);
	hdc_ellipse(base_x - heixiu_half_width / 2, base_y - face_half_high, heixiu_half_width * 9 / 25*2/3, heixiu_half_high * 11 / 16/2, 0, 0, 5, lines);

	hdc_ellipse(base_x + heixiu_half_width / 2, base_y - face_half_high, heixiu_half_width * 9 / 25*2/3, heixiu_half_high * 11 / 16/2, 0, 1, 5, in);
	hdc_ellipse(base_x + heixiu_half_width / 2, base_y - face_half_high, heixiu_half_width * 9 / 25*2/3, heixiu_half_high * 11 / 16/2, 0, 0, 5, lines);
}
//����
static void body(const int base_x = 400, const int base_y = 400)
{
	int face_half_width = high * 13 / 64;
	int face_half_high = high * 25 / 128;
	hdc_ellipse(base_x, base_y + face_half_high, face_half_width * 6 / 5, face_half_high*2/3, 0, 1, 5, background_1);	
}
void hand(const int base_x = 400, const int base_y = 400)
{
	int face_half_width = high * 13 / 64;
	int face_half_high = high * 25 / 128;
	//��
	hdc_circle(base_x - face_half_width / 2, base_y + face_half_high * 9 / 10, high * 13 / 64 / 2/2 , 1, 5, in);
	hdc_circle(base_x + face_half_width / 2, base_y + face_half_high * 9 / 10, high * 13 / 64 / 2/2 , 1, 5, in);
	hdc_circle(base_x - face_half_width / 2, base_y + face_half_high * 9 / 10, high * 13 / 64 / 2 / 2, 0, 5, lines);
	hdc_circle(base_x + face_half_width / 2, base_y + face_half_high * 9 / 10, high * 13 / 64 / 2 / 2, 0, 5, lines);
}
//�ҽ���С�ڣ�Ҳ������Ŷ
void hdc_draw_cartoon_2152611(const int base_x=400, const int base_y=400)
{
	hdc_cls();
	
	set_background(base_x, base_y);
	body(base_x, base_y);
	draw_face(base_x, base_y);
	heixiu(base_x, base_y);
	hand(base_x, base_y);

	return;
}