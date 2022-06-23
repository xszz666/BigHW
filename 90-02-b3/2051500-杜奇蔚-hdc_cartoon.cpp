/* 2051500 信15 杜奇蔚 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>  
#include <Windows.h>
#include <math.h>
#include "../include/cmd_hdc_tools.h"
using namespace std;

static const int beige = RGB(242, 200, 142);//米色
static const int red = RGB(187, 19, 32);
static const int dark_red = RGB(157,13,24);
static const int brown = RGB(120, 26, 26);
static const int black = RGB(25,25,25);
static const int white = RGB(255,255,255);
static const int dark_blue = RGB(18,35,60);


static const int bwidth = 800;
static const int bhigh = 800;
static const int face_center_y = -150;
static const int face_lower_high = 110;
static const int face_upper_high = 60;
static const int face_width = 120;

//背景六边形
static void hdc_hexagon(const int point_x, const int point_y, const int length,  const int RGB_value)
{
	hdc_triangle(point_x, point_y - length, point_x - int(length * sqrt(3) / 2), point_y - length / 2, point_x + int(length * sqrt(3) / 2), point_y - length / 2, true, 2, RGB_value);
	hdc_rectangle(point_x - int(length * sqrt(3) / 2), point_y - length / 2, int(length * sqrt(3)), length, 0, true, 2, RGB_value);
	hdc_triangle(point_x, point_y + length, point_x - int(length * sqrt(3) / 2), point_y + length / 2, point_x + int(length * sqrt(3) / 2), point_y + length / 2, true, 2, RGB_value);
}

//眼睛
static void hdc_eye(const int base_x, const int base_y,const int eye_color)
{
	//左眼
	for (int j = base_y + face_center_y - 3; j < base_y + face_center_y + 20; ++j)
	{
		hdc_line(base_x + 2 - int(sqrt(50 * 50 - (j - (base_y + face_center_y - 10)) * (j - (base_y + face_center_y - 10)))), j, int((j - (base_y + face_center_y + 2)) * 4.0 / 3) + base_x - 40, j, 1, eye_color);
	}
	for (int j = base_y + face_center_y + 20; j < base_y + face_center_y + 30; ++j)
	{
		hdc_line(base_x + 2 - int(sqrt(50 * 50 - (j - (base_y + face_center_y - 10)) * (j - (base_y + face_center_y - 10)))), j,
			base_x - 35 + int(sqrt(20 * 20 - (j - (base_y + face_center_y + 15)) * (j - (base_y + face_center_y + 15)))), j, 1, eye_color);
	}
	hdc_point(base_x - 15, base_y + face_center_y + 23, 5, eye_color);
	hdc_point(base_x - 15, base_y + face_center_y + 25, 5, eye_color);
	hdc_point(base_x - 17, base_y + face_center_y + 27, 5, eye_color);
	hdc_point(base_x - 13, base_y + face_center_y + 24, 5, eye_color);
	//右眼
	for (int j = base_y + face_center_y - 3; j < base_y + face_center_y + 20; ++j)
	{
		hdc_line(base_x - 2 + int(sqrt(50 * 50 - (j - (base_y + face_center_y - 10)) * (j - (base_y + face_center_y - 10)))), j, int((j - (base_y + face_center_y + 2)) * 4.0 / (-3)) + base_x + 40, j, 1, eye_color);
	}
	for (int j = base_y + face_center_y + 20; j < base_y + face_center_y + 30; ++j)
	{
		hdc_line(base_x - 2 + int(sqrt(50 * 50 - (j - (base_y + face_center_y - 10)) * (j - (base_y + face_center_y - 10)))), j,
			base_x + 35 - int(sqrt(20 * 20 - (j - (base_y + face_center_y + 15)) * (j - (base_y + face_center_y + 15)))), j, 1, eye_color);
	}
	hdc_point(base_x + 17, base_y + face_center_y + 23, 5, eye_color);
	hdc_point(base_x + 17, base_y + face_center_y + 25, 5, eye_color);
	hdc_point(base_x + 19, base_y + face_center_y + 27, 5, eye_color);
	hdc_point(base_x + 15, base_y + face_center_y + 24, 5, eye_color);
}

//蜘蛛侠的头
static void hdc_draw_head(const int base_x, const int base_y)
{
	//红色的底
	hdc_ellipse(base_x, base_y + face_center_y, face_lower_high, face_width/2, 90, true, 2,red);
	hdc_ellipse(base_x, base_y + face_center_y, face_lower_high, face_width/2, 90, false, 2,dark_red);
	hdc_rectangle(base_x - face_width/2, base_y + face_center_y - face_lower_high, face_width, face_lower_high, 0, true, 2,brown );
	hdc_circle(base_x, base_y + face_center_y, face_upper_high, true, 2,red);

	//黑色的蜘蛛网
	//一个小圆圈和几根直线
	hdc_circle(base_x, base_y + face_center_y+20, 5, false, 2,black);
	hdc_line(base_x-5, base_y + face_center_y + 20, base_x - face_width / 2, base_y + face_center_y + 20 , 2, black);
	hdc_line(base_x+5, base_y + face_center_y + 20 , base_x + face_width / 2, base_y + face_center_y + 20, 2, black);
	hdc_line(base_x, base_y + face_center_y + 20 - 6, base_x, base_y + face_center_y - face_upper_high, 2, black);
	//上半脸左一竖弧
	hdc_arc(base_x + 200, base_y - 270, 245, 236, 253, 2, black);
	//下半脸右二竖弧
	hdc_arc(base_x + 200, base_y - 270, 245, 219, 234, 2, black);
	//上半脸右一竖弧
	hdc_arc(base_x - 200, base_y - 270, 245, 107,124 , 2, black);
	//下半脸左二竖弧
	hdc_arc(base_x - 200, base_y - 270, 245, 126, 141, 2, black);
	//上半脸左二竖弧
	hdc_arc(base_x + 90, base_y - 330, 220, 205, 222, 2, black);
	//上半脸右二竖弧
	hdc_arc(base_x - 90, base_y - 330, 220, 138, 155, 2, black);
	//下半脸左一竖弧
	hdc_line(base_x-1 , base_y + face_center_y + 20 + 5, base_x - 15, base_y + face_center_y + 105, 2, black);
	//下半脸右一竖弧
	hdc_line(base_x , base_y + face_center_y + 20 + 5, base_x + 15, base_y + face_center_y + 105, 2, black);
	//上半脸横曲弧
	hdc_arc(base_x - 28, base_y - 222, 35, 128, 181, 2, black);
	hdc_arc(base_x + 28, base_y - 222, 35, 179, 232, 2, black);
	hdc_arc(base_x - 20, base_y - 180, 23, 120, 171, 2, black);
	hdc_arc(base_x + 20, base_y - 180, 23, 189, 240, 2, black);
	hdc_arc(base_x - 64, base_y - 190, 33, 98, 150, 2, black);
	hdc_arc(base_x + 64, base_y - 190, 33, 210, 262, 2, black);
	hdc_arc(base_x - 40, base_y - 164, 23, 110, 145, 2, black);
	hdc_arc(base_x + 40, base_y - 164, 23, 215, 250, 2, black);
	hdc_arc(base_x - 81, base_y - 145, 35, 71, 115, 2, black);
	hdc_arc(base_x + 81, base_y - 145, 35, 245, 292, 2, black);
	hdc_arc(base_x - 70, base_y - 101, 35, 40, 109, 2, black);
	hdc_arc(base_x + 70, base_y - 101, 35, -109, -40, 2, black);
	hdc_arc(base_x - 39, base_y - 54, 35, 8, 58, 2, black);
	hdc_arc(base_x + 39, base_y -54, 35, -58, -8, 2, black);
	hdc_arc(base_x - 30, base_y - 74, 35, 21, 44, 2, black);
	hdc_arc(base_x +30, base_y - 74, 35, -44, -21, 2, black);
	hdc_arc(base_x+1, base_y-66, 10, -48, 47, 2, black);
	hdc_arc(base_x+1, base_y-90, 10, -25, 25, 2, black);

	//左眼框
	hdc_line(base_x - 50, base_y + face_center_y-10 , base_x - 10, base_y + face_center_y+20, 8, black);
	hdc_arc(base_x, base_y + face_center_y - 5, 50, 218, 280, 8, black);
	hdc_arc(base_x - 25, base_y + face_center_y + 15, 20, 120, 190, 8, black);
	//右眼框
	hdc_line(base_x + 50, base_y + face_center_y - 10, base_x + 10, base_y + face_center_y + 20, 8, black);
	hdc_arc(base_x, base_y + face_center_y - 5, 50, -270, -218, 8, black);
	hdc_arc(base_x + 25, base_y + face_center_y + 15, 20,-190, -120, 8, black);
	//眼睛
	hdc_eye(base_x, base_y, white);
}

//身子轮廓
static void hdc_body_outline(const int base_x, const int base_y)
{
	//脖子
	hdc_line(base_x - 40, base_y - 65, base_x - 45, base_y - 35, 2, dark_red);
	hdc_line(base_x + 40, base_y - 65, base_x + 45, base_y - 35, 2, dark_red);
	//左肩
	hdc_line(base_x - 45, base_y - 35, base_x - 85, base_y - 25, 2, dark_red);
	hdc_arc(base_x - 70, base_y + 33, 60, -85, -10, 2, dark_red);
	//左臂
	hdc_line(base_x - 131, base_y + 28, base_x - 200, base_y + 235, 2, dark_red);
	hdc_line(base_x - 90, base_y + 140, base_x - 160, base_y + 260, 2, dark_red);
	hdc_line(base_x - 90, base_y + 140, base_x - 85, base_y + 300, 2, dark_red);
	//右肩
	hdc_line(base_x + 45, base_y - 35, base_x + 85, base_y - 25, 2, dark_red);
	hdc_arc(base_x + 70, base_y + 33, 60, 10, 85, 2, dark_red);
	//右臂
	hdc_line(base_x + 130, base_y + 28, base_x + 200, base_y + 235, 2, dark_red);
	hdc_line(base_x + 90, base_y + 140, base_x + 160, base_y + 260, 2, dark_red);
	hdc_line(base_x + 90, base_y + 140, base_x + 85, base_y + 300, 2, dark_red);
}

//身体填红色
static void fill_red(const int base_x, const int base_y)
{
	//填脖子红色
	for (int j = base_y - 65 + 1; j < base_y - 35; ++j)
	{
		hdc_line(2 + base_x - 40 - (j - (base_y - 65)) / 6, j, -2 + base_x + 40 + (j - (base_y - 65)) / 6, j, 1, red);
	}
	//填两肩之间的红色
	for (int j = base_y - 35; j < base_y - 25; ++j)
	{
		hdc_line(2 + base_x - 45 - (j - (base_y - 35)) * 4, j, -2 + base_x + 45 + (j - (base_y - 35)) * 4, j, 1, red);
	}
	for (int j = base_y - 25; j < base_y + 28; ++j)
	{
		hdc_line(2 + base_x - 70 - int(sqrt(60 * 60 - (j - (base_y + 33)) * (j - (base_y + 33)))), j, -1 + base_x + 70 + int(sqrt(60 * 60 - (j - (base_y + 33)) * (j - (base_y + 33)))), j, 1, red);
	}
	//腋下以上区域填红色
	for (int j = base_y + 28; j < base_y + 140; ++j)
	{
		//hdc_line(2 + base_x - 90 - (j - (base_y - 140)) *7/ 12, j, -2 + base_x + 90 + (j - (base_y - 140)) *7/ 12, j, 1, red);
		hdc_line(2 + base_x - 131 - (j - (base_y + 28)) / 3, j, -2 + base_x + 131 + (j - (base_y + 28)) / 3, j, 1, red);
	}
	//腋下以下区域填红色
	for (int j = base_y + 140; j < base_y + 235; ++j)
	{
		hdc_line(2 + base_x - 131 - (j - (base_y + 28)) / 3, j, -2 + base_x - 90 - (j - (base_y + 140)) * 7 / 12, j, 1, red);
		hdc_line(2 + base_x + 90 + (j - (base_y + 140)) * 7 / 12, j, -2 + base_x + 131 + (j - (base_y + 28)) / 3, j, 1, red);
		hdc_line(2 + base_x - 90 + (j - (base_y + 140)) / 32, j, -2 + base_x + 90 - (j - (base_y + 140)) / 32, j, 1, red);
	}
	for (int j = base_y + 235; j < base_y + 260 - 2; ++j)
	{
		hdc_line(2 + base_x + int((j - (base_y + 350)) * sqrt(3)), j, -2 + base_x - 90 - (j - (base_y + 140)) * 7 / 12, j, 1, red);
		hdc_line(2 + base_x + 90 + (j - (base_y + 140)) * 7 / 12, j, -2 + base_x - int((j - (base_y + 350)) * sqrt(3)), j, 1, red);
		hdc_line(2 + base_x - 90 + (j - (base_y + 140)) / 32, j, -2 + base_x + 90 - (j - (base_y + 140)) / 32, j, 1, red);
	}
	for (int j = base_y + 260 - 2; j < base_y + 300; ++j)
	{
		hdc_line(2 + base_x - 90 + (j - (base_y + 140)) / 32, j, -2 + base_x + 90 - (j - (base_y + 140)) / 32, j, 1, red);
	}
	for (int j = base_y + 300; j < base_y + 350; ++j)
	{
		hdc_line(2 + base_x + int((j - (base_y + 350)) * sqrt(3)), j, -2 + base_x - int((j - (base_y + 350)) * sqrt(3)), j, 1, red);
	}
}

//画身上的蛛网
static void spider_net(const int base_x, const int base_y)
{
	//竖线
	//中间
	hdc_line(base_x, base_y + face_center_y + face_lower_high + 1, base_x, base_y + 350 - 2, 2, black);
	//左一
	hdc_line(base_x - 15, base_y + face_center_y + face_lower_high - 5, base_x - 60, base_y + 100, 2, black);
	//右一
	hdc_line(base_x + 15, base_y + face_center_y + face_lower_high - 5, base_x + 60, base_y + 100, 2, black);
	//左二
	hdc_line(base_x - 30, base_y + face_center_y + face_lower_high - 13, base_x - 90, base_y + 90, 2, black);
	//右二
	hdc_line(base_x + 30, base_y + face_center_y + face_lower_high - 13, base_x + 90, base_y + 90, 2, black);
	//左三
	hdc_line(base_x - 60, base_y + face_center_y + face_lower_high + 10, base_x - 190, base_y + 240, 2, black);
	//右三
	hdc_line(base_x + 60, base_y + face_center_y + face_lower_high + 10, base_x + 190, base_y + 240, 2, black);
	//左四
	hdc_line(base_x - 80, base_y + face_center_y + face_lower_high + 15, base_x - 140, base_y + 60, 2, black);
	//右四
	hdc_line(base_x + 80, base_y + face_center_y + face_lower_high + 15, base_x + 140, base_y + 60, 2, black);
	//下左一
	hdc_line(base_x - 45, base_y + 110, base_x - 25, base_y + 330, 2, black);
	//下右一
	hdc_line(base_x + 45, base_y + 110, base_x + 25, base_y + 330, 2, black);
	//横弧
	hdc_arc(base_x - 13, base_y + 10, 20, -40, 40, 2, black);
	hdc_arc(base_x + 13, base_y + 10, 20, -40, 40, 2, black);
	hdc_arc(base_x - 20, base_y + 60, 30, -35, 39, 2, black);
	hdc_arc(base_x + 20, base_y + 60, 30, -39, 35, 2, black);
	hdc_arc(base_x - 40, base_y + 8, 20, -13, 40, 2, black);
	hdc_arc(base_x + 41, base_y + 8, 20, -40, 13, 2, black);
	hdc_arc(base_x - 60, base_y + 5, 20, -12, 43, 2, black);
	hdc_arc(base_x + 62, base_y + 5, 20, -43, 12, 2, black);
	hdc_arc(base_x - 80, base_y + 1, 20, -10, 45, 2, black);
	hdc_arc(base_x + 82, base_y + 1, 20, -45, 10, 2, black);
	hdc_arc(base_x - 60, base_y + 56, 30, -5, 47, 2, black);
	hdc_arc(base_x + 61, base_y + 56, 30, -47, 5, 2, black);
	hdc_arc(base_x - 15, base_y + 250, 25, -39, 37, 2, black);
	hdc_arc(base_x + 17, base_y + 250, 25, -37, 39, 2, black);
	hdc_arc(base_x - 13, base_y + 310, 20, -39, 37, 2, black);
	hdc_arc(base_x + 15, base_y + 310, 20, -37, 39, 2, black);
	hdc_arc(base_x - 46, base_y + 250, 25, -10, 30, 2, black);
	hdc_arc(base_x + 48, base_y + 250, 25, -30, 10, 2, black);
	hdc_arc(base_x - 41, base_y + 310, 20, -19, 37, 2, black);
	hdc_arc(base_x + 43, base_y + 310, 20, -37, 19, 2, black);
	hdc_arc(base_x - 150, base_y + 120, 30, -5, 60, 2, black);
	hdc_arc(base_x + 152, base_y + 120, 30, -60, 5, 2, black);
	hdc_arc(base_x - 170, base_y + 180, 30, -5, 45, 2, black);
	hdc_arc(base_x + 172, base_y + 180, 30, -45, 5, 2, black);
}

//部分区域填深蓝色
static void fill_dark_blue(const int base_x, const int base_y)
{
	//内脚层
	for (int j = base_y - 28; j < base_y - 20; ++j)
	{
		hdc_line(int(((j - (base_y - 35)) * (-4))) + base_x - 45, j, base_x - 40 - int(sqrt(30 * 30 - (j - (base_y - 30)) * (j - (base_y - 30)))), j, 1, dark_blue);
		hdc_line(-int(((j - (base_y - 35)) * (-4))) + base_x + 45, j, base_x + 40 + int(sqrt(30 * 30 - (j - (base_y - 30)) * (j - (base_y - 30)))), j, 1, dark_blue);
	}
	for (int j = base_y - 20; j < base_y - 3; ++j)
	{
		hdc_line(int(((j - (base_y - 3)) * 30.0 / 17)) + base_x - 70, j, base_x - 40 - int(sqrt(30 * 30 - (j - (base_y - 30)) * (j - (base_y - 30)))), j, 1, dark_blue);
		hdc_line(-int(((j - (base_y - 3)) * 30.0 / 17)) + base_x + 70, j, base_x + 40 + int(sqrt(30 * 30 - (j - (base_y - 30)) * (j - (base_y - 30)))), j, 1, dark_blue);
	}
	for (int j = base_y - 3; j < base_y + 55; ++j)
	{
		hdc_line(base_x - 50, j, base_x - 70, j, 1, dark_blue);
		hdc_line(base_x + 50, j, base_x + 70, j, 1, dark_blue);
	}
	for (int j = base_y + 55; j < base_y + 65; ++j)
	{
		hdc_line(base_x - 70, j, int(((j - (base_y + 65)) * 3)) + base_x - 20, j, 1, dark_blue);
		hdc_line(base_x + 70, j, -int(((j - (base_y + 65)) * 3)) + base_x + 20, j, 1, dark_blue);
	}
	for (int j = base_y + 65; j < base_y + 70; ++j)
	{
		hdc_line(base_x - 70, j, base_x - 10, j, 1, dark_blue);
		hdc_line(base_x + 70, j, base_x + 10, j, 1, dark_blue);
	}
	for (int j = base_y + 70; j < base_y + 80; ++j)
	{
		hdc_line(base_x - 10, j, int(((j - (base_y + 80)) * 4)) + base_x - 40, j, 1, dark_blue);
		hdc_line(base_x + 10, j, -int(((j - (base_y + 80)) * 4)) + base_x + 40, j, 1, dark_blue);
	}
	for (int j = base_y + 80; j < base_y + 95; ++j)
	{
		hdc_line(base_x - 40, j, base_x - 10, j, 1, dark_blue);
		hdc_line(base_x + 40, j, base_x + 10, j, 1, dark_blue);
	}
	for (int j = base_y + 95; j < base_y + 115; ++j)
	{
		hdc_line(base_x - 10, j, int(((j - (base_y + 95)) * (-1.5))) + base_x - 40, j, 1, dark_blue);
		hdc_line(base_x + 10, j, -int(((j - (base_y + 95)) * (-1.5))) + base_x + 40, j, 1, dark_blue);
	}
	for (int j = base_y + 115; j < base_y + 122; ++j)
	{
		hdc_line(int(((j - (base_y + 115)) * 10.0 / 7)) + base_x - 40, j, int(((j - (base_y + 95)) * (-1.5))) + base_x - 40, j, 1, dark_blue);
		hdc_line(-int(((j - (base_y + 115)) * 10.0 / 7)) + base_x + 40, j, -int(((j - (base_y + 95)) * (-1.5))) + base_x + 40, j, 1, dark_blue);
	}
	for (int j = base_y + 122; j < base_y + 225; ++j)
	{
		hdc_line(int(((j - (base_y + 110)) * 33.0 / 190)) + base_x - 88, j, base_x - 50, j, 1, dark_blue);
		hdc_line(-int(((j - (base_y + 110)) * 33.0 / 190)) + base_x + 88, j, base_x + 50, j, 1, dark_blue);
	}
	for (int j = base_y + 225; j < base_y + 300; ++j)
	{
		hdc_line(int(((j - (base_y + 110)) * 33.0 / 190)) + base_x - 88, j, int(((j - (base_y + 115)) * 30.0 / 185)) + base_x - 70, j, 1, dark_blue);
		hdc_line(-int(((j - (base_y + 110)) * 33.0 / 190)) + base_x + 88, j, -int(((j - (base_y + 115)) * 30.0 / 185)) + base_x + 70, j, 1, dark_blue);
	}
	for (int j = base_y + 300; j < base_y + 312; ++j)
	{
		hdc_line(int(((j - (base_y + 300)) * (-35.0 / 20))) + base_x - 55, j, int(((j - (base_y + 300)) * (-1))) + base_x - 40, j, 1, dark_blue);
		hdc_line(-int(((j - (base_y + 300)) * (-35.0 / 20))) + base_x + 55, j, -int(((j - (base_y + 300)) * (-1))) + base_x + 40, j, 1, dark_blue);
	}
	for (int j = base_y + 312; j < base_y + 318; ++j)
	{
		hdc_line(base_x + int((j - (base_y + 350)) * sqrt(3)), j, int(((j - (base_y + 300)) * (-1))) + base_x - 40, j, 1, dark_blue);
		hdc_line(base_x - int((j - (base_y + 350)) * sqrt(3)), j, -int(((j - (base_y + 300)) * (-1))) + base_x + 40, j, 1, dark_blue);
	}
	//外脚层
	for (int j = base_y; j < base_y + 10; ++j)
	{
		hdc_line(int(((j - (base_y + 68)) * (20.0 / 68))) + base_x - 80, j, int(((j - (base_y + 10)) * (-25.0 / 10))) + base_x - 125, j, 1, dark_blue);
		hdc_line(-int(((j - (base_y + 68)) * (20.0 / 68))) + base_x + 80, j, -int(((j - (base_y + 10)) * (-25.0 / 10))) + base_x + 125, j, 1, dark_blue);
	}
	for (int j = base_y + 10; j < base_y + 30; ++j)
	{
		hdc_line(int(((j - (base_y + 68)) * (20.0 / 68))) + base_x - 80, j, int(((j - (base_y + 10)) * (-14.0 / 50))) + base_x - 125, j, 1, dark_blue);
		hdc_line(-int(((j - (base_y + 68)) * (20.0 / 68))) + base_x + 80, j, -int(((j - (base_y + 10)) * (-14.0 / 50))) + base_x + 125, j, 1, dark_blue);
	}
	for (int j = base_y + 30; j < base_y + 60; ++j)
	{
		hdc_line(int(((j - (base_y + 60)) * (-24.0 / 30))) + base_x - 139, j, int(((j - (base_y + 10)) * (-14.0 / 50))) + base_x - 125, j, 1, dark_blue);
		hdc_line(-int(((j - (base_y + 60)) * (-24.0 / 30))) + base_x + 139, j, -int(((j - (base_y + 10)) * (-14.0 / 50))) + base_x + 125, j, 1, dark_blue);
	}
	for (int j = base_y + 30; j < base_y + 68; ++j)
	{
		hdc_line(int(((j - (base_y + 68)) * (20.0 / 68))) + base_x - 80, j, int(((j - (base_y + 30)) * (23.0 / 50))) + base_x - 115, j, 1, dark_blue);
		hdc_line(-int(((j - (base_y + 68)) * (20.0 / 68))) + base_x + 80, j, -int(((j - (base_y + 30)) * (23.0 / 50))) + base_x + 115, j, 1, dark_blue);
	}
	for (int j = base_y + 68; j < base_y + 80; ++j)
	{
		hdc_line(int(((j - (base_y + 30)) * (23.0 / 50))) + base_x - 115, j, int(((j - (base_y + 80)) * (40.0 / 12))) + base_x - 40, j, 1, dark_blue);
		hdc_line(-int(((j - (base_y + 30)) * (23.0 / 50))) + base_x + 115, j, -int(((j - (base_y + 80)) * (40.0 / 12))) + base_x + 40, j, 1, dark_blue);
	}
	for (int j = base_y + 80; j < base_y + 85; ++j)
	{
		hdc_line(int(((j - (base_y + 80)) * (32.0 / 5))) + base_x - 92, j, int(((j - (base_y + 80)) * (40.0 / 12))) + base_x - 40, j, 1, dark_blue);
		hdc_line(-int(((j - (base_y + 80)) * (32.0 / 5))) + base_x + 92, j, -int(((j - (base_y + 80)) * (40.0 / 12))) + base_x + 40, j, 1, dark_blue);
	}
	for (int j = base_y + 85; j < base_y + 95; ++j)
	{
		hdc_line(base_x - 40, j, base_x - 60, j, 1, dark_blue);
		hdc_line(base_x + 40, j, base_x + 60, j, 1, dark_blue);
	}
	for (int j = base_y + 95; j < base_y + 110; ++j)
	{
		hdc_line(int(((j - (base_y + 95)) * (-28.0 / 15))) + base_x - 60, j, int(((j - (base_y + 95)) * (30.0 / 20))) + base_x - 40, j, 1, dark_blue);
		hdc_line(-int(((j - (base_y + 95)) * (-28.0 / 15))) + base_x + 60, j, -int(((j - (base_y + 95)) * (-30.0 / 20))) + base_x + 40, j, 1, dark_blue);
	}
	for (int j = base_y + 110; j < base_y + 130; ++j)
	{
		hdc_line(int(((j - (base_y + 110)) * (33.0 / 190))) + base_x - 88, j, base_x - 60, j, 1, dark_blue);
		hdc_line(-int(((j - (base_y + 110)) * (33.0 / 190))) + base_x + 88, j, base_x + 60, j, 1, dark_blue);
	}
	//腰部和手臂
	hdc_triangle(base_x - 40, base_y + 300, base_x + 40, base_y + 300, base_x, base_y + 350, true, 2, dark_blue);
	hdc_triangle(base_x - 40, base_y + 300, base_x - 58, base_y + 318, base_x, base_y + 350, true, 2, dark_blue);
	hdc_triangle(base_x + 58, base_y + 318, base_x + 40, base_y + 300, base_x, base_y + 350, true, 2, dark_blue);
	hdc_triangle(base_x - 88, base_y + 110, base_x - 145, base_y + 235, base_x - 165, base_y + 195, true, 2, dark_blue);
	hdc_triangle(base_x + 88, base_y + 110, base_x + 145, base_y + 235, base_x + 165, base_y + 195, true, 2, dark_blue);
	hdc_triangle(base_x - 88, base_y + 110, base_x - 125, base_y + 60, base_x - 165, base_y + 195, true, 2, dark_blue);
	hdc_triangle(base_x + 88, base_y + 110, base_x + 125, base_y + 60, base_x + 165, base_y + 195, true, 2, dark_blue);
	hdc_triangle(base_x - 88, base_y + 110, base_x - 145, base_y + 235, base_x - 90, base_y + 140, true, 2, dark_blue);
	hdc_triangle(base_x + 88, base_y + 110, base_x + 145, base_y + 235, base_x + 90, base_y + 140, true, 2, dark_blue);
	hdc_triangle(base_x - 88, base_y + 110, base_x - 85, base_y + 300, base_x - 55, base_y + 300, true, 2, dark_blue);
	hdc_triangle(base_x + 88, base_y + 110, base_x + 85, base_y + 300, base_x + 55, base_y + 300, true, 2, dark_blue);
	hdc_triangle(base_x - 73, base_y + 307, base_x - 85, base_y + 300, base_x - 55, base_y + 300, true, 2, dark_blue);
	hdc_triangle(base_x + 73, base_y + 307, base_x + 85, base_y + 300, base_x + 55, base_y + 300, true, 2, dark_blue);
	hdc_triangle(base_x - 200, base_y + 235, base_x - 165, base_y + 255, base_x - 193, base_y + 210, true, 2, dark_blue);
	hdc_triangle(base_x + 200, base_y + 235, base_x + 165, base_y + 255, base_x + 193, base_y + 210, true, 2, dark_blue);
}

//描金边
static void golden_line(const int base_x, const int base_y)
{
	//上内脚线横线
	hdc_line(base_x - 20, base_y + 65, base_x - 50, base_y + 55, 2, beige);
	hdc_line(base_x + 20, base_y + 65, base_x + 50, base_y + 55, 2, beige);
	//上内脚内竖线
	hdc_line(base_x - 50, base_y + 55, base_x - 50, base_y - 3, 2, beige);
	hdc_line(base_x + 50, base_y + 55, base_x + 50, base_y - 3, 2, beige);
	//上内脚内弧
	hdc_arc(base_x - 40, base_y - 30, 30, -160, -95, 2, beige);
	hdc_arc(base_x + 40, base_y - 30, 30, 95, 160, 2, beige);
	//上内脚外竖线
	hdc_line(base_x - 70, base_y + 70, base_x - 70, base_y - 3, 2, beige);
	hdc_line(base_x + 70, base_y + 70, base_x + 70, base_y - 3, 2, beige);
	//上内脚外斜线
	hdc_line(base_x - 70, base_y - 3, base_x - 100, base_y - 20, 2, beige);
	hdc_line(base_x + 70, base_y - 3, base_x + 100, base_y - 20, 2, beige);
	//上内脚中横线
	hdc_line(base_x - 40, base_y + 80, base_x - 80, base_y + 68, 2, beige);
	hdc_line(base_x + 40, base_y + 80, base_x + 80, base_y + 68, 2, beige);
	//上外脚内竖线
	hdc_line(base_x - 80, base_y + 68, base_x - 100, base_y, 2, beige);
	hdc_line(base_x + 80, base_y + 68, base_x + 100, base_y, 2, beige);
	//上外脚外斜线
	hdc_line(base_x - 100, base_y, base_x - 125, base_y + 10, 2, beige);
	hdc_line(base_x + 100, base_y, base_x + 125, base_y + 10, 2, beige);
	//中小竖线
	hdc_line(base_x - 40, base_y + 80, base_x - 40, base_y + 95, 2, beige);
	hdc_line(base_x + 40, base_y + 80, base_x + 40, base_y + 95, 2, beige);
	//中下中斜线
	hdc_line(base_x - 40, base_y + 95, base_x - 70, base_y + 115, 2, beige);
	hdc_line(base_x + 40, base_y + 95, base_x + 70, base_y + 115, 2, beige);
	//中下内斜线
	hdc_line(base_x - 40, base_y + 115, base_x - 50, base_y + 122, 2, beige);
	hdc_line(base_x + 40, base_y + 115, base_x + 50, base_y + 122, 2, beige);
	//下内脚内竖线
	hdc_line(base_x - 50, base_y + 122, base_x - 50, base_y + 225, 2, beige);
	hdc_line(base_x + 50, base_y + 122, base_x + 50, base_y + 225, 2, beige);
	//中竖线
	hdc_line(base_x - 70, base_y + 115, base_x - 40, base_y + 300, 2, beige);
	hdc_line(base_x + 70, base_y + 115, base_x + 40, base_y + 300, 2, beige);
	//下横线
	hdc_line(base_x - 40, base_y + 300, base_x + 40, base_y + 300, 2, beige);
	//下斜线
	hdc_line(base_x - 40, base_y + 300, base_x - 58, base_y + 318, 2, beige);
	hdc_line(base_x + 40, base_y + 300, base_x + 58, base_y + 318, 2, beige);
	//上外脚外沿
	hdc_line(base_x - 125, base_y + 10, base_x - 139, base_y + 60, 2, beige);
	hdc_line(base_x + 125, base_y + 10, base_x + 139, base_y + 60, 2, beige);
	//上外脚内沿
	hdc_line(base_x - 139, base_y + 60, base_x - 115, base_y + 30, 4, beige);
	hdc_line(base_x + 139, base_y + 60, base_x + 115, base_y + 30, 4, beige);
	//上外脚外竖线
	hdc_line(base_x - 115, base_y + 30, base_x - 92, base_y + 80, 2, beige);
	hdc_line(base_x + 115, base_y + 30, base_x + 92, base_y + 80, 2, beige);
	//中上外横线
	hdc_line(base_x - 92, base_y + 80, base_x - 60, base_y + 85, 2, beige);
	hdc_line(base_x + 92, base_y + 80, base_x + 60, base_y + 85, 2, beige);
	//中外小竖线
	hdc_line(base_x - 60, base_y + 85, base_x - 60, base_y + 95, 2, beige);
	hdc_line(base_x + 60, base_y + 85, base_x + 60, base_y + 95, 2, beige);
	//中下外横线
	hdc_line(base_x - 60, base_y + 95, base_x - 88, base_y + 110, 2, beige);
	hdc_line(base_x + 60, base_y + 95, base_x + 88, base_y + 110, 2, beige);
	//下中竖线
	hdc_line(base_x - 88, base_y + 110, base_x - 55, base_y + 300, 2, beige);
	hdc_line(base_x + 88, base_y + 110, base_x + 55, base_y + 300, 2, beige);
	//下方小拐
	hdc_line(base_x - 55, base_y + 300, base_x - 90, base_y + 320, 2, beige);
	hdc_line(base_x + 55, base_y + 300, base_x + 90, base_y + 320, 2, beige);
}

//蜘蛛侠的身子
static void hdc_draw_body(const int base_x, const int base_y)
{
	//身子轮廓
	hdc_body_outline(base_x, base_y);
	//身体填红色
	fill_red(base_x, base_y);
	//身上黑色蜘蛛网
	spider_net(base_x, base_y);
	//中间蓝色的蜘蛛
	fill_dark_blue(base_x, base_y);
	//蜘蛛主体
	hdc_hexagon(base_x, base_y + 75, 23, beige);
	hdc_hexagon(base_x, base_y + 140, 48, beige);
	hdc_rectangle(base_x - 19, base_y + 70, 40, 40, 0, true, 1, beige);
	hdc_hexagon(base_x, base_y + 75, 20, dark_blue);
	hdc_hexagon(base_x, base_y + 140, 45, dark_blue);
	hdc_rectangle(base_x - 17, base_y + 70, 35, 40, 0, true, 1, dark_blue);
	//描金边
	golden_line(base_x, base_y);
}

//眼睛闪烁 Go Crazy!!!
static const int eye_color = red;
static void hdc_wink(const int base_x, const int base_y)
{
	for (int i = 0; i < 3; ++i)
	{
		hdc_eye(base_x, base_y, red);
		Sleep(100);
		hdc_eye(base_x, base_y, white);
		Sleep(100);
		hdc_eye(base_x, base_y, dark_blue);
		Sleep(100);
		hdc_eye(base_x, base_y, white);
		Sleep(100);
		hdc_eye(base_x, base_y, black);
		Sleep(100);
		hdc_eye(base_x, base_y, white);
		Sleep(100);
		//hdc_eye(base_x, base_y, red);
		//hdc_eye(base_x, base_y, dark_blue);
		//(base_x, base_y, black);
	}
}

static void net(const int x, const int y, const int layer, const int space)
{
	for (int i = layer; i >= 1; --i)
	{
		if(i%2==0)
			hdc_hexagon(x, y,i*space, red);
		else
			hdc_hexagon(x, y, i * space,dark_blue);
	}
}

/* 老师点评：分函数、加注释，好评 */
//蜘蛛侠
void hdc_draw_cartoon_2051500(const int base_x, const int base_y)
{
	hdc_cls();
	//大背景
	hdc_rectangle(base_x - bwidth / 2, base_y - bhigh / 2, bwidth, bhigh, 0, true, 2, RGB(10, 26, 42));
	//小背景
	hdc_hexagon(base_x, base_y, 380,beige);
	hdc_hexagon(base_x, base_y, 350, brown);
	//完整的蜘蛛侠
	hdc_draw_body(base_x, base_y);
	hdc_draw_head(base_x, base_y);
	//两个六边形
	net(base_x - 170, base_y - 100, 7, 10);
	net(base_x + 170, base_y - 100, 7, 10);
	//眼睛变色
	hdc_wink(base_x, base_y);
}