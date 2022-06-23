/* 2053287 陈晗舸 信15 */
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
static const int COLOR_BACK2 = RGB(242, 255, 250);
static const int  COLOR_FACE = RGB(255, 211, 198);
static const int COLOR_BACK1 = RGB(255, 227, 225);
static const int FACE_YELLOW = RGB(255, 229, 222);
static const int HAIR_BLACK = RGB(87, 77, 75);
static const int TIE_RED = RGB(255, 43, 61);
static const int EYE_BLACK = RGB(60, 1, 7);
static const int KCOLOR_ANGER = RGB(19, 6, 9);
static const int KCOLOR_GLASS = RGB(3, 0, 7);
static const int KCOLOR_CLOTHES = RGB(81, 151, 211);
static const int KCOLOR_MOUTH = RGB(253, 118, 115);
static const int KCOLOR_BROW = RGB(170, 133, 29);
static const int KCOLOR_LIGHT1 = RGB(220, 220, 80);
static const int KCOLOR_LIGHT2 = RGB(140, 150, 160);
static const int HAIR_GREY = RGB(129, 114, 115);
static void hdc_draw_background(const int base_x, const int base_y)
{
	hdc_square(0, 0, 795, 0, 1, 2, COLOR_BACK1);
	hdc_square(30, 30, 740, 0, 1, 2, COLOR_BACK2);
}
static void hdc_draw_tie(const int base_x, const int base_y)
{
	hdc_rectangle(base_x - 70, base_y + 120, 140, 110, 0, 1, 2, FACE_YELLOW);
	hdc_circle(base_x, base_y + 260, 20, 1, 1, TIE_RED);
	hdc_ellipse(base_x - 46, base_y + 244, 20, 30, -60, 1, 1, TIE_RED);
	hdc_ellipse(base_x - 46, base_y + 276, 20, 30, 60, 1, 1, TIE_RED);
	hdc_ellipse(base_x + 46, base_y + 244, 20, 30, 60, 1, 1, TIE_RED);
	hdc_ellipse(base_x + 46, base_y + 276, 20, 30, -60, 1, 1, TIE_RED);
	hdc_circle(base_x, base_y + 300, 5, 1, 1, KCOLOR_BROW);
}
static void hdc_draw_clothes(const int base_x, const int base_y)
{
	hdc_rectangle(base_x - 70, base_y + 230, 140, 90, 0, 1, 2, KCOLOR_CLOTHES);
	hdc_sector(base_x - 70, base_y + 320, 90, -90, 0, 1, 1, KCOLOR_CLOTHES);
	hdc_sector(base_x + 70, base_y + 320, 90, 0, 90, 1, 1, KCOLOR_CLOTHES);
	hdc_line(base_x - 134, base_y + 256, base_x, base_y + 320, 3, HAIR_BLACK);
	hdc_line(base_x + 134, base_y + 256, base_x, base_y + 320, 3, HAIR_BLACK);
	hdc_rectangle(base_x - 70, base_y + 230, 140, 50, 0, 1, 2, COLOR_BACK2);
	hdc_triangle(base_x - 70, base_y + 280, base_x + 70, base_y + 280, base_x, base_y + 320, 1, 2, COLOR_BACK2);
}
static void hdc_draw_face(const int base_x, const int base_y)
{
	hdc_sector(base_x, base_y - 50, 270, -90, 90, 1, 2, HAIR_BLACK);
	hdc_circle(base_x, base_y, 220, 1, 2, FACE_YELLOW);
	hdc_ellipse(base_x + 61, base_y + 48, 200, 100, 133, true, 1, FACE_YELLOW);
    hdc_ellipse(base_x - 108, base_y, 100, 190, 0, true, 1, FACE_YELLOW);
	hdc_ellipse(base_x + 108, base_y, 100, 190, 0, true, 1, FACE_YELLOW);
}
static void hdc_draw_hair(const int base_x, const int base_y)
{
	//hdc_sector(base_x, base_y - 50, 270, -45, 135, 1, 2, HAIR_BLACK);
	hdc_sector(base_x-30, base_y - 50, 170, -90, 90, 1, 2, HAIR_BLACK);
	hdc_ellipse(base_x + 70, base_y - 153, 189, 154, 30, true, 1, HAIR_BLACK);
	hdc_rectangle(base_x + 155, base_y - 320, 55, 40, 30, 1, 2, HAIR_BLACK);
	hdc_sector(base_x + 155, base_y - 320, 55, 30, 120, 1, 2, HAIR_BLACK);
	hdc_sector(base_x + 155, base_y - 320, 85, 120, 150, 1, 2, HAIR_BLACK);
	hdc_sector(base_x - 120, base_y+30, 120, -45, 45, 1, 2, FACE_YELLOW);
	hdc_ellipse(base_x - 100, base_y -80, 80, 40, -30, true, 1, FACE_YELLOW);
	hdc_circle(base_x + 180, base_y - 280, 40, 1, 2, HAIR_BLACK);
	hdc_ellipse(base_x - 60, base_y - 95, 80, 40, 30, true, 1, HAIR_BLACK);
	hdc_sector(base_x +30, base_y , 80, 0, 95, 1, 2, FACE_YELLOW);
	hdc_ellipse(base_x +30, base_y - 70, 80, 40, 60, true, 1, FACE_YELLOW);
	hdc_ellipse(base_x + 70, base_y + 30, 80, 40, 90, true, 1, FACE_YELLOW);
	hdc_sector(base_x +80, base_y - 70, 120, -90, 90, 1, 2, HAIR_BLACK);
	hdc_ellipse(base_x  +30, base_y - 50, 60, 20, 20, true, 1, HAIR_BLACK);
	hdc_ellipse(base_x + 70, base_y - 40, 33, 18, 35, true, 1, FACE_YELLOW);
	hdc_ellipse(base_x + 100, base_y - 70, 60, 20, 10, true, 1, HAIR_BLACK);
	hdc_ellipse(base_x - 220, base_y - 200, 90, 40, -10, true, 1, HAIR_BLACK);
	//hdc_sector(base_x - 270, base_y - 200, 40, 90, 130, 1, 2, COLOR_BACK2);
	hdc_ellipse(base_x - 245, base_y - 165, 45, 16, -25, true, 2, COLOR_BACK2);
	hdc_ellipse(base_x - 220, base_y - 165, 45, 23, -65, true, 2, HAIR_BLACK);
	hdc_sector(base_x - 330, base_y - 150, 45, 20, 75, 1, 2, HAIR_BLACK);
	hdc_ellipse(base_x + 80, base_y - 40, 80, -30, 10, true, 1, HAIR_BLACK);
	hdc_ellipse(base_x - 205, base_y - 220, 85, 30, 40, 1, 1, HAIR_BLACK);
	//hdc_ellipse(base_x - 255, base_y - 265, 45, 25, 25, 1, 1, HAIR_BLACK);
	//hdc_ellipse(base_x - 240, base_y - 275, 40, 10, 15, 1, 1, COLOR_BACK2);
	hdc_circle(base_x - 160, base_y - 210, 18, 1, 1, HAIR_GREY);
	hdc_circle(base_x - 122, base_y - 155, 8, 1, 1, HAIR_GREY);
}
static void hdc_draw_mouth(const int base_x, const int base_y)
{
	hdc_circle(base_x - 120, base_y + 138, 15, 1, 2, KCOLOR_MOUTH);
	hdc_circle(base_x + 120, base_y + 138, 15, 1, 2, KCOLOR_MOUTH);
	//hdc_ellipse(base_x + 10, base_y + 180, 20, 18, 0, 1, 2, KCOLOR_MOUTH);
	hdc_arc(base_x + 10, base_y + 200, 30, -55, 55, 2, KCOLOR_MOUTH);
	//hdc_line
	/*hdc_line(base_x - 10, base_y + 165, base_x + 10, base_y + 180, 4, KCOLOR_MOUTH);
	hdc_line(base_x + 10, base_y + 165, base_x - 10, base_y + 180, 4, KCOLOR_MOUTH);*/
}
static void hdc_draw_eyes(const int base_x, const int base_y)
{
	hdc_circle(base_x + 125, base_y + 20, 60, 1, 1, FACE_YELLOW);
	hdc_circle(base_x - 125, base_y + 20, 60, 1, 1, FACE_YELLOW);
	hdc_ellipse(base_x + 125, base_y - 70, 80, 40, 60, true, 1, FACE_YELLOW);
	hdc_ellipse(base_x + 85, base_y - 90, 80, 40, -60, true, 1, HAIR_BLACK);
	hdc_ellipse(base_x + 47, base_y - 40, 30, 15, 60, true, 1, FACE_YELLOW);
	hdc_sector(base_x + 125, base_y + 20, 50, 90, 270, 1, 1, COLOR_BACK2);
	hdc_sector(base_x - 125, base_y + 20, 50, 90, 270, 1, 1, COLOR_BACK2);
	hdc_sector(base_x + 125, base_y + 20, 30, 90, 270, 1, 1, EYE_BLACK);
	hdc_sector(base_x - 125, base_y + 20, 30, 90, 270, 1, 1, EYE_BLACK);
	/*hdc_circle(base_x - 125, base_y +20, 50, 1, 1, COLOR_BACK2);
	hdc_circle(base_x-100, base_y + 20, 20, 1, 1, EYE_BLACK);
	hdc_circle(base_x + 125, base_y + 20, 50, 1, 1, COLOR_BACK2);
	hdc_circle(base_x + 100, base_y + 20, 20, 1, 1, EYE_BLACK);*/
}
static void hdc_draw_glasses(const int base_x, const int base_y)
{
	/*hdc_arc(base_x - 165, base_y + 20, 122, -70, 70, 5, KCOLOR_GLASS);
	hdc_arc(base_x + 165, base_y + 20, 122, -70, 70, 5, KCOLOR_GLASS);
	hdc_line(base_x - 279, base_y - 22, base_x - 279, base_y + 60, 5, KCOLOR_GLASS);
	hdc_line(base_x - 48, base_y - 22, base_x - 48, base_y + 60, 5, KCOLOR_GLASS);

	hdc_arc(base_x - 165, base_y + 20, 122, 110, 250, 5, KCOLOR_GLASS);
	hdc_arc(base_x + 165, base_y + 20, 122, 110, 250, 5, KCOLOR_GLASS);
	hdc_line(base_x + 282, base_y - 20, base_x + 282, base_y + 60, 5, KCOLOR_GLASS);
	hdc_line(base_x + 51, base_y - 20, base_x + 51, base_y + 60, 5, KCOLOR_GLASS);
	hdc_line(base_x - 51, base_y + 5, base_x + 51, base_y + 5, 8, KCOLOR_GLASS);*/

	hdc_arc(base_x - 135, base_y + 20, 100, -70, 70, 5, KCOLOR_GLASS);
	hdc_arc(base_x + 135, base_y + 20, 100, -70, 70, 5, KCOLOR_GLASS);
	hdc_line(base_x - 230, base_y - 22, base_x - 230, base_y + 60, 5, KCOLOR_GLASS);
	hdc_line(base_x - 40, base_y - 22, base_x - 40, base_y + 60, 5, KCOLOR_GLASS);

	hdc_arc(base_x - 135, base_y + 20, 100, 110, 250, 5, KCOLOR_GLASS);
	hdc_arc(base_x + 135, base_y + 20, 100, 110, 250, 5, KCOLOR_GLASS);
	hdc_line(base_x + 230, base_y - 20, base_x + 230, base_y + 60, 5, KCOLOR_GLASS);
	hdc_line(base_x + 40, base_y - 20, base_x + 40, base_y + 60, 5, KCOLOR_GLASS);
	hdc_line(base_x - 40, base_y + 5, base_x + 40, base_y + 5, 8, KCOLOR_GLASS);
}
static void hdc_draw_nose(const int base_x, const int base_y)
{
	hdc_circle(base_x, base_y+110, 3, 1, 2, EYE_BLACK);
}
static void hdc_draw_ears(const int base_x, const int base_y)
{
	hdc_ellipse(base_x + 240, base_y - 50, 38, 25, -50, true, 1, HAIR_BLACK);
	hdc_ellipse(base_x + 245, base_y-15, 40, 20, -75, true, 1, HAIR_BLACK);
	hdc_ellipse(base_x + 235, base_y - 15, 25, 10, 40, true, 1, HAIR_BLACK);
	hdc_ellipse(base_x + 240, base_y + 20, 40, 20, -75, true, 1, FACE_YELLOW);
	hdc_ellipse(base_x + 240, base_y + 20, 10, 5, -75, true, 1, HAIR_BLACK);
	hdc_ellipse(base_x - 240, base_y - 50, 38, 25, 50, true, 1, HAIR_BLACK);
	hdc_ellipse(base_x - 245, base_y - 15, 40, 20, 75, true, 1, HAIR_BLACK);
	hdc_ellipse(base_x - 235, base_y - 15, 25, 10, -40, true, 1, HAIR_BLACK);
	hdc_ellipse(base_x - 230, base_y + 20, 40, 20, 85, true, 1, FACE_YELLOW);
	hdc_ellipse(base_x - 230, base_y + 20, 10, 5, 75, true, 1, HAIR_BLACK);
}
static void hdc_draw_brows(const int base_x, const int base_y)
{
	hdc_arc(base_x - 125, base_y + 60, 95, -35, 25, 2, KCOLOR_BROW);
	hdc_arc(base_x + 125, base_y + 60, 95, -35, 25, 2, KCOLOR_BROW);
}
static void hdc_draw_details(const int base_x, const int base_y)
{
	hdc_sector(base_x - 250, base_y - 350, 40, -145, 95, true, 1, KCOLOR_LIGHT1);
	hdc_ellipse(base_x - 250, base_y - 345, 40, 25, 65, true, 1, KCOLOR_LIGHT1);
	hdc_ellipse(base_x - 230, base_y - 325, 15, 16, -65, true, 1, KCOLOR_LIGHT1);
	hdc_ellipse(base_x - 230, base_y - 345, 15, 16, 0, true, 1, KCOLOR_LIGHT1);
	hdc_ellipse(base_x - 270, base_y - 325, 15, 6, 65, true, 1, KCOLOR_LIGHT1);
	hdc_rectangle(base_x - 240, base_y - 305, 30, 25, -35, true, 1, KCOLOR_LIGHT2);
	for (int i = 3; i > 0; i--)
		hdc_arc(base_x - 245, base_y - 340, 10 * i, -70, 30, 2, HAIR_BLACK);
	hdc_arc(base_x - 350, base_y - 320, 60, 32, 55, 2, KCOLOR_LIGHT1);
	hdc_arc(base_x - 350, base_y - 320, 105, 32, 48, 2, KCOLOR_LIGHT1);
	//hdc_arc(base_x - 350, base_y - 320, 90, 32, 55, 2, KCOLOR_LIGHT1);
	hdc_arc(base_x - 150, base_y - 320, 60, -55, -32, 2, KCOLOR_LIGHT1);
	hdc_arc(base_x - 150, base_y - 320, 105, -48, -32, 2, KCOLOR_LIGHT1);
	hdc_arc(base_x + 90, base_y - 300, 50, -60, 0, 2, KCOLOR_MOUTH);
	hdc_arc(base_x + 90, base_y - 300, 70, -50, -10, 2, KCOLOR_MOUTH);
	hdc_arc(base_x + 90, base_y - 300, 90, -40, -20, 2, KCOLOR_MOUTH);
	hdc_arc(base_x + 90, base_y - 300, 110, -35, -25, 2, KCOLOR_MOUTH);
	hdc_arc(base_x - 196, base_y - 63, 14, 90, 180, 3, KCOLOR_ANGER);
	hdc_arc(base_x - 157, base_y - 63, 14, -180, -90, 3, KCOLOR_ANGER);
	hdc_arc(base_x - 196, base_y - 27, 14, 0, 90, 3, KCOLOR_ANGER);
	hdc_arc(base_x - 157, base_y - 27, 14, -90, 0, 3, KCOLOR_ANGER);
	hdc_arc(base_x + 205, base_y + 220, 45, 120, 160, 3, HAIR_BLACK);
	hdc_line(base_x + 250, base_y + 245, base_x + 255, base_y + 270, 3, HAIR_BLACK);
	hdc_line(base_x + 280, base_y + 245, base_x + 315, base_y + 250, 3, HAIR_BLACK);
	hdc_arc(base_x + 280, base_y + 245, 39, 100, 160, 3, HAIR_BLACK);
	hdc_arc(base_x + 265, base_y + 230, 39, 100, 180, 3, HAIR_BLACK);
}

/* 老师点评：分函数、加注释，好评 */
void hdc_draw_cartoon_2053287(const int base_x, const int base_y)
{
	hdc_cls();
	//背景
	hdc_draw_background(base_x, base_y);
	//脸
	hdc_draw_face(base_x, base_y);
	//头发
	hdc_draw_hair(base_x, base_y);
	//衣服
	hdc_draw_clothes(base_x, base_y);
	//领结
	hdc_draw_tie(base_x, base_y);
	//嘴巴
	hdc_draw_mouth(base_x, base_y);
	//眼睛
	hdc_draw_eyes(base_x, base_y);
	hdc_draw_brows(base_x, base_y);
	//鼻子
	hdc_draw_nose(base_x, base_y);
	//耳朵
	hdc_draw_ears(base_x, base_y);
	////眼镜
	hdc_draw_glasses(base_x, base_y);
	//细节
	hdc_draw_details(base_x, base_y);
}