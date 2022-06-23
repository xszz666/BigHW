/* 2054100 信04 林志桓 */
#include <Windows.h>
#include <cmath>
#include "../include/cmd_hdc_tools.h"
#include "hdc_student_works.h"

/* Common Colors */
static const int CCOLOR_BLACK = RGB(0, 0, 0);
static const int CCOLOR_TEETH = RGB(215, 224, 219);
static const int CCOLOR_ORAL_CAVITY = RGB(98, 52, 52);
static const int CCOLOR_TONGUE = RGB(222, 135, 143);

/* Background Colors/Parameters */
static const int Draw_Width = 800;
static const int Draw_Height = 450;
static const int BCOLOR_BACKGROUND = RGB(103,182, 106);

/* IceBear Colors */
static const int ICOLOR_SKIN = RGB(243, 243, 231);
static const int ICOLOR_INNER_CLAW = RGB(181, 176, 157);
static const int ICOLOR_OUT_CLAW = RGB(163, 162, 142);
static const int ICOLOR_SHADOW = RGB(214, 221, 213);

/* Panda Colors */
static const int PCOLOR_BLACK = RGB(80, 80, 80);
static const int PCOLOR_WHITE = RGB(238, 236, 237);

/* Grizzly Colors */
static const int GCOLOR_SKIN = RGB(158, 108, 75);

static void draw_Background(const int base_x, const int base_y)
{
	hdc_rectangle(base_x, base_y, Draw_Width, Draw_Height, 0, true, 1, BCOLOR_BACKGROUND);
	//hdc_rectangle(base_x, base_y, Draw_Width, Draw_Height, 0, true, 1, GCOLOR_SKIN);
}

static void draw_IceBear(const int base_x, const int base_y)
{
	int x = 0, y1 = 0, y2 = 0;
	//脸颊
	hdc_ellipse(base_x + 435, base_y + 133, 50, 43, 65, true, 4, CCOLOR_BLACK);
	hdc_ellipse(base_x + 435, base_y + 133, 47, 40, 65, true, 4, ICOLOR_SKIN);    //填充

	//左耳
	hdc_ellipse(base_x + 520, base_y + 35, 20, 10, -50, true, 4, CCOLOR_BLACK);
	hdc_ellipse(base_x + 520, base_y + 35, 17, 7, -50, true, 4, ICOLOR_SKIN);

	//头顶
	hdc_arc(base_x + 520, base_y + 142, 100, -55, -10, 4, CCOLOR_BLACK);
	hdc_arc(base_x + 520, base_y + 142, 96, -55, -10, 4, ICOLOR_SKIN);     //填充
	hdc_arc(base_x + 520, base_y + 142, 94, -55, -10, 6, ICOLOR_SKIN);     //填充
	hdc_triangle(base_x + 445, base_y + 85, base_x + 480, base_y + 55, base_x + 460, base_y + 150, true, 1, ICOLOR_SKIN);   //提前填充
	//hdc_line(base_x + 445, base_y + 85, base_x + 480, base_y + 55, 4, CCOLOR_BLACK);
	hdc_sector(base_x + 530, base_y + 106, 70, -29, 50, true, 1, CCOLOR_BLACK);
	hdc_sector(base_x + 530, base_y + 106, 66, 0, 360, true, 1, ICOLOR_SKIN);

	//右上身体弧线
	hdc_sector(base_x + 482, base_y + 173, 150, 43, 70, true, 1, CCOLOR_BLACK);
	hdc_sector(base_x + 482, base_y + 173, 146, 43, 120, true, 1, ICOLOR_SKIN);

	//右耳
	hdc_ellipse(base_x + 580, base_y + 51, 20, 10, -50, true, 4, CCOLOR_BLACK);
	hdc_ellipse(base_x + 580, base_y + 51, 17, 7, -50, true, 4, ICOLOR_SKIN);
	hdc_sector(base_x + 540, base_y + 91, 45, 35, 60, 1, CCOLOR_BLACK); //清除多余部分

	//眼睛
	hdc_point(base_x + 458, base_y + 82, 8, CCOLOR_BLACK);
	hdc_point(base_x + 458 + 38, base_y + 82 + 7, 8, CCOLOR_BLACK);

	//鼻子
	hdc_ellipse(base_x + 434, base_y + 104, 13, 7, 16, true, 4, CCOLOR_BLACK);

	//右下身子
	hdc_triangle(base_x + 670, base_y + 300, base_x + 647, base_y + 227, base_x + 620, base_y + 250, true, 1, ICOLOR_SKIN);
	hdc_line(base_x + 670, base_y + 300, base_x + 647, base_y + 227, 4, CCOLOR_BLACK);

	//手
	//手弧
	hdc_ellipse(base_x + 685, base_y + 98, 50, 30, -50, false, 5, CCOLOR_BLACK);
	hdc_ellipse(base_x + 685, base_y + 98, 47, 26, -50, true, 4, ICOLOR_SKIN);
	//填充
	hdc_triangle(base_x + 570, base_y + 180, base_x + 660, base_y + 80, base_x + 630, base_y + 250, true, 1, ICOLOR_SKIN);
	hdc_triangle(base_x + 630, base_y + 250, base_x + 714, base_y + 103, base_x + 660, base_y + 80, true, 1, ICOLOR_SKIN);
	//手左线
	hdc_line(base_x + 570, base_y + 180, base_x + 661, base_y + 79, 4, CCOLOR_BLACK);
	//手右线
	hdc_line(base_x + 630, base_y + 250, base_x + 716, base_y + 103, 4, CCOLOR_BLACK);

	//爪子
	hdc_ellipse(base_x + 686, base_y + 87, 11, 5, -50, true, 4, ICOLOR_OUT_CLAW);
	hdc_ellipse(base_x + 686, base_y + 70, 5, 2, -50, true, 4, ICOLOR_OUT_CLAW);
	hdc_ellipse(base_x + 702, base_y + 67, 6, 3, -50, true, 4, ICOLOR_OUT_CLAW);
	hdc_ellipse(base_x + 708, base_y + 84, 6, 2, -50, true, 4, ICOLOR_OUT_CLAW);
}

static void draw_Panda(const int base_x, const int base_y)
{
	int x = 0, y1 = 0, y2 = 0;

	//右手
	hdc_ellipse(base_x + 100, base_y + 140, 35, 27, 55, true, 4, CCOLOR_BLACK);
	hdc_ellipse(base_x + 100, base_y + 140, 31, 23, 55, true, 4, PCOLOR_BLACK);
	hdc_triangle(base_x + 198, base_y + 200, base_x + 121, base_y + 126, base_x + 190, base_y + 350, true, 1, PCOLOR_BLACK);
	hdc_triangle(base_x + 121, base_y + 126, base_x + 75, base_y + 150, base_x + 190, base_y + 350, true, 1, PCOLOR_BLACK);
	hdc_line(base_x + 198, base_y + 200, base_x + 121, base_y + 126, 4, CCOLOR_BLACK);
	hdc_line(base_x + 190, base_y + 350, base_x + 75, base_y + 150, 4, CCOLOR_BLACK);
	hdc_circle(base_x + 200, base_y + 265, 45, true, 4, PCOLOR_BLACK);

	//身体
	hdc_arc(base_x + 590, base_y + 380, 400, -100, -70, 6, CCOLOR_BLACK);   //左边的线
	hdc_arc(base_x + 590, base_y + 380, 396, -100, -70, 6, PCOLOR_BLACK);   //填充
	hdc_arc(base_x + 590, base_y + 380, 392, -100, -70, 6, PCOLOR_BLACK);   //填充
	hdc_arc(base_x + 590, base_y + 380, 388, -100, -70, 6, PCOLOR_BLACK);   //填充
	hdc_rectangle(base_x + 205, base_y + 270, 200, Draw_Height - 270, 0, true, 3, PCOLOR_BLACK);   //填充

	//耳朵
	hdc_ellipse(base_x + 352, base_y + 130, 15, 12, -30, true, 4, CCOLOR_BLACK);
	hdc_ellipse(base_x + 352, base_y + 130, 11, 8, -30, true, 4, PCOLOR_BLACK);

	//左手
	hdc_arc(base_x + 276, base_y + 380, 30, -130, 30, 4, CCOLOR_BLACK);
	hdc_line(base_x + 250, base_y + 395, base_x + 287, base_y + 435, 4, CCOLOR_BLACK);
	hdc_line(base_x + 289, base_y + 352, base_x + 334, base_y + 378, 4, CCOLOR_BLACK);
	hdc_line(base_x + 325, base_y + 370, base_x + 335, base_y + 354, 4, CCOLOR_BLACK);
	hdc_line(base_x + 264, base_y + 353, base_x + 294, base_y + 372, 4, CCOLOR_BLACK);
	hdc_line(base_x + 250, base_y + 365, base_x + 280, base_y + 384, 4, CCOLOR_BLACK);

	//左下白斑
	hdc_triangle(base_x + 200, base_y + Draw_Height, base_x + 220, base_y + Draw_Height, base_x + 195, base_y + Draw_Height - 15, true, 1, PCOLOR_WHITE);

	//头左弧
	hdc_ellipse(base_x + 260, base_y + 238, 80, 60, 65, true, 4, CCOLOR_BLACK);
	hdc_ellipse(base_x + 260, base_y + 238, 77, 57, 65, true, 4, PCOLOR_WHITE);

	//头右上弧
	//hdc_sector(base_x + 273, base_y + 148, 20, 0, 360, true, 1, PCOLOR_BLACK);
	hdc_sector(base_x + 320, base_y + 224, 100, -50, 60, true, 4, CCOLOR_BLACK);
	hdc_sector(base_x + 320, base_y + 224, 96, 0, 360, true, 4, PCOLOR_WHITE);
	//hdc_sector(base_x + 320, base_y + 224, 108, -50, 60, false, 4, BCOLOR_BACKGROUND);
	//hdc_sector(base_x + 320, base_y + 224, 104, -50, 60, false, 4, BCOLOR_BACKGROUND);

	//头下弧
	hdc_sector(base_x + 320, base_y + 152, 170, 150, 210, true, 4, CCOLOR_BLACK);
	hdc_sector(base_x + 320, base_y + 152, 166, 150, 210, true, 4, PCOLOR_WHITE);

	//脸部
	//鼻子
	hdc_ellipse(base_x + 244, base_y + 175, 13, 6, 16, true, 4, CCOLOR_BLACK);

	//左眼
	//hdc_sector(base_x + 273, base_y + 148, 20, 0, 360, true, 1, PCOLOR_BLACK);  //轮廓曲线
	for (x = base_x + 253; x <= base_x + 284; x++)
	{
		y1 = base_y + 224 - (int)sqrt(100 * 100 - (x - base_x - 320) * (x - base_x -320));
		y2 = base_y + 148 + (int)sqrt(20 * 20 - (x - base_x - 273) * (x - base_x - 273));
		hdc_line(x, y1 - 1, x, y2, 1, PCOLOR_BLACK);
	}
	hdc_sector(base_x + 273, base_y + 148, 20, 34, 180, true, 1, PCOLOR_BLACK);  //补右边曲线
	hdc_point(base_x + 274, base_y + 150, 8, CCOLOR_BLACK);


	//右眼
	hdc_sector(base_x + 320, base_y + 175, 20, 0, 360, true, 1, PCOLOR_BLACK);
	hdc_point(base_x + 315, base_y + 170, 8, CCOLOR_BLACK);

	//嘴
	hdc_sector(base_x + 266, base_y + 220, 38, 90, 270, true, 2, CCOLOR_BLACK);
	hdc_sector(base_x + 266, base_y + 223, 33, 90, 270, true, 2, CCOLOR_ORAL_CAVITY);


	//舌头
	//hdc_arc(base_x + 295, base_y + 275, 40, 0, -360, 1, CCOLOR_TONGUE);    画轮廓时的曲线
	for (x = base_x + 260; x <= base_x + 297; x++)          //这些数据是用图形计算器计算得到的
	{
		y1 = base_y + 223 + (int)sqrt(33 * 33 - (x - base_x - 266) * (x - base_x - 266));
		y2 = base_y + 275 - (int)sqrt(40 * 40 - (x - base_x - 295) * (x - base_x - 295));
		hdc_line(x, y1 - 1, x, y2 - 2, 1, CCOLOR_TONGUE);
	}

	//牙齿
	//hdc_arc(base_x + 285, base_y + 226, 8, 90, 270, 1, CCOLOR_BLACK);  画轮廓时的曲线
	//hdc_arc(base_x + 270, base_y + 226, 8, 90, 270, 1, CCOLOR_BLACK);
	//hdc_arc(base_x + 255, base_y + 226, 8, 90, 270, 1, CCOLOR_BLACK);
	y1 = base_y + 223;
	for (x = base_x + 281; x <= base_x + 297; x++)          //这些数据是用图形计算器计算得到的
	{
		y2 = base_y + 223 + (int)sqrt(8 * 8 - (x - base_x - 289) * (x - base_x - 289));
		hdc_line(x, y1, x, y2, 1, CCOLOR_TEETH);
	}

	for (x = base_x + 266; x <= base_x + 282; x++)          //这些数据是用图形计算器计算得到的
	{
		y2 = base_y + 223 + (int)sqrt(8 * 8 - (x - base_x - 274) * (x - base_x - 274));
		hdc_line(x, y1, x, y2, 1, CCOLOR_TEETH);
	}

	for (x = base_x + 251; x <= base_x + 267; x++)          //这些数据是用图形计算器计算得到的
	{
		y2 = base_y + 223 + (int)sqrt(8 * 8 - (x - base_x - 259) * (x - base_x - 259));
		hdc_line(x, y1, x, y2, 1, CCOLOR_TEETH);
	}
	

}

static void draw_Grizzly(const int base_x, const int base_y)
{
	int x = 0, y1 = 0, y2 = 0;

	//左下弧
	hdc_arc(base_x, base_y + 397, 400, 75, 98, 4, CCOLOR_BLACK);
	hdc_arc(base_x, base_y + 397, 403, 75, 98, 4, GCOLOR_SKIN);  //填充

	//脸颊
	hdc_ellipse(base_x + 400, base_y + 280, 60, 45, 50, true, 4, CCOLOR_BLACK);
	hdc_ellipse(base_x + 400, base_y + 280, 56, 41, 50, true, 4, GCOLOR_SKIN);  //填充
	
	//左耳
	hdc_ellipse(base_x + 455, base_y + 140, 10, 9, -10, true, 4, CCOLOR_BLACK);
	hdc_ellipse(base_x + 455, base_y + 140, 6, 6, -10, true, 4, GCOLOR_SKIN);

	//头顶弧
	hdc_arc(base_x + 481, base_y + 249, 110, -80, 25, 5, CCOLOR_BLACK);
	hdc_arc(base_x + 481, base_y + 249, 107, -80, 25, 4, CCOLOR_BLACK); //填充

	//右下弧
	hdc_arc(base_x + 10, base_y + 752, 800, 42, 68, 6, CCOLOR_BLACK);
	hdc_arc(base_x + 10, base_y + 752, 797, 42, 68, 5, GCOLOR_SKIN);     //填充

	//右耳
	hdc_ellipse(base_x + 535, base_y + 149, 10, 9, 25, true, 4, CCOLOR_BLACK);
	hdc_ellipse(base_x + 535, base_y + 149, 6, 6, 25, true, 4, GCOLOR_SKIN);

	//填充颜色
	hdc_rectangle(base_x + 400, base_y + 180, 170, 271, 0, true, 1, GCOLOR_SKIN);
	hdc_sector(base_x + 429, base_y + 226, 51, -110, 0, true, 1, GCOLOR_SKIN);
	hdc_sector(base_x + 481, base_y + 249, 108, -80, 55, true, 1, GCOLOR_SKIN);     //填充左上
	hdc_sector(base_x + 415, base_y + 324, 20, -150, -90, true, 1, GCOLOR_SKIN);     //左下
	hdc_sector(base_x + 570, base_y + 324, 92, 0, 180, true, 1, GCOLOR_SKIN);
	hdc_sector(base_x + 530, base_y + 260, 82, 30, 80, true, 1, GCOLOR_SKIN);
	hdc_sector(base_x + 570, base_y + 275, 63, 20, 80, true, 1, GCOLOR_SKIN);
	hdc_sector(base_x + 680, base_y + Draw_Height, 64, -90, 91, true, 1, GCOLOR_SKIN);
	hdc_rectangle(base_x + 570, base_y + 350, 100, 101, 0, true, 1, GCOLOR_SKIN);
	hdc_sector(base_x + 619, base_y + 337, 62, 0, 90, true, 1, GCOLOR_SKIN);
	hdc_sector(base_x + 627, base_y + 383, 79, 0, 100, true, 1, GCOLOR_SKIN);
	hdc_sector(base_x + 654, base_y + 415, 72, 5, 100, true, 1, GCOLOR_SKIN);
	hdc_sector(base_x + 736, base_y + Draw_Height, 10, 20, 91, true, 1, GCOLOR_SKIN);

	//手
	hdc_arc(base_x + 70, base_y + 580, 600, 65, 78, 4, CCOLOR_BLACK);
	hdc_arc(base_x + 17, base_y + 657, 600, 60, 70, 4, CCOLOR_BLACK);

	//眼睛
	hdc_point(base_x + 400, base_y + 215, 8, CCOLOR_BLACK);
	hdc_point(base_x + 400 + 55, base_y + 215 + 4, 8, CCOLOR_BLACK);

	//鼻子
	hdc_ellipse(base_x + 400, base_y + 245, 16, 8, 8, true, 4, CCOLOR_BLACK);

	//嘴
	hdc_sector(base_x + 440, base_y + 275, 40, 60, 240, true, 1, CCOLOR_BLACK);
	hdc_sector(base_x + 442, base_y + 277, 35, 60, 240, true, 1, CCOLOR_ORAL_CAVITY);

	//牙齿
	//hdc_arc(base_x + 463, base_y + 264, 10, 80, 220, 1, CCOLOR_BLACK);  画轮廓时的曲线
	//hdc_arc(base_x + 447, base_y + 273, 10, 80, 220, 1, CCOLOR_BLACK);
	//hdc_arc(base_x + 431, base_y + 282, 10, 80, 220, 1, CCOLOR_BLACK);
	for (x = base_x + 422; x <= base_x + 438; x++)          //这些数据是用图形计算器计算得到的
	{
		y1 = -(int)(double(x - base_x - 442) / 1.732) + base_y + 277;
		y2 = base_y + 282 + (int)sqrt(10 * 10 - (x - base_x - 431) * (x - base_x - 431));
		hdc_line(x, y1, x, y2, 1, CCOLOR_TEETH);
	}

	for (x = base_x + 438; x <= base_x + 456; x++)          //这些数据是用图形计算器计算得到的
	{
		y1 = -(int)(double(x - base_x - 442) / 1.732) + base_y + 277;
		y2 = base_y + 273 + (int)sqrt(10 * 10 - (x - base_x - 447) * (x - base_x - 447));
		hdc_line(x, y1-1, x, y2, 1, CCOLOR_TEETH);
	}

	for (x = base_x + 454; x <= base_x + 471; x++)          //这些数据是用图形计算器计算得到的
	{
		y1 = -(int)(double(x - base_x - 442) / 1.732) + base_y + 277;
		y2 = base_y + 264 + (int)sqrt(10 * 10 - (x - base_x - 463) * (x - base_x - 463));
		hdc_line(x, y1-1, x, y2, 1, CCOLOR_TEETH);
	}

	//舌头
	//hdc_arc(base_x + 492, base_y + 317, 40, -80, -20, 1, CCOLOR_TONGUE);    画轮廓时的曲线
	for (x = base_x + 453; x <= base_x + 476; x++)          //这些数据是用图形计算器计算得到的
	{
		y1 = base_y + 277 + (int)sqrt(35 * 35 - (x - base_x - 442) * (x - base_x - 442));
		y2 = base_y + 317 - (int)sqrt(40 * 40 - (x - base_x - 492) * (x - base_x - 492));
		hdc_line(x, y1-1, x, y2-2, 1, CCOLOR_TONGUE);
	}
}

/* 老师点评：分函数、加注释，好评 */
void hdc_draw_cartoon_2054100(const int base_x, const int base_y)
{
	hdc_cls();

	draw_Background(base_x, base_y);
	draw_Panda(base_x, base_y);
	draw_IceBear(base_x, base_y);
	draw_Grizzly(base_x, base_y);
}