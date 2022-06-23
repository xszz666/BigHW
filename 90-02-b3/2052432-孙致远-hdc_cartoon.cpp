/*2052432 信12 孙致远*/
#include <iostream>
#include <Windows.h>
#include <stdio.h>  
#include <stdlib.h>  
#include <conio.h>  
#include <math.h>
#include <time.h>
#include "../include/cmd_hdc_tools.h"
#define COLOR_HEAD RGB(243, 180, 145)
#define COLOR_HEAD_ARC RGB(124, 53, 14)
#define COLOR_EAR RGB(124, 53, 14)
#define COLOR_YELLOW_HEAD RGB(243, 208, 129)
#define COLOR_MOUSE RGB(250,122,177)
#define COLOR_BACKGROUND_UP RGB(140, 141, 135)
void background()
{
	hdc_rectangle(0,0, 800, 600, 0, true, 4, COLOR_BACKGROUND_UP);
}
void head(const int base_x, const int base_y)
{
	hdc_circle(base_x, base_y - 50,180,true,3,COLOR_HEAD);//最大的圆
	hdc_circle(base_x - 120, base_y - 180,45, true, 3, COLOR_HEAD);//左边耳朵
	hdc_arc(base_x, base_y - 50, 180, 245, 150, 8, COLOR_HEAD_ARC);//整个头的上半部分的黑边
	hdc_circle(base_x + 120, base_y - 180, 40, true, 3, COLOR_HEAD);//右边的耳朵
	hdc_arc(base_x - 120, base_y - 180, 45, 220, 54, 8, COLOR_HEAD_ARC);//左边耳朵上的黑边
	hdc_arc(base_x + 120, base_y - 180, 40, -65, 170, 10, COLOR_HEAD_ARC);//右边耳朵上的黑边
	hdc_sector(base_x - 120, base_y - 180, 25, 220, 45, true, 3, COLOR_EAR);//左边的小耳朵
	hdc_sector(base_x + 110, base_y - 170, 27, -40, 140, true, 3, COLOR_EAR);//右边的小耳朵
	hdc_circle(base_x - 145, base_y + 55, 45, true, 3, COLOR_HEAD);//左边腮帮子的第一个小圆
	hdc_circle(base_x - 130, base_y + 60, 45, true, 3, COLOR_HEAD);//左边腮帮子的第二个小圆
	hdc_circle(base_x - 115, base_y + 60, 50, true, 3, COLOR_HEAD);//左边腮帮子的第三个小圆
	hdc_circle(base_x - 150, base_y + 55, 40, true, 3, COLOR_YELLOW_HEAD);//左边腮帮子的黄色小圆
	hdc_circle(base_x + 70, base_y + 55, 40, true, 3, COLOR_YELLOW_HEAD);//右边腮帮子的黄色小圆
	hdc_arc(base_x - 145, base_y + 55,45,190, 345, 8, COLOR_HEAD_ARC);//左边腮帮子的第一个黑边
	hdc_arc(base_x - 125, base_y + 50, 60, 150, 220, 8, COLOR_HEAD_ARC);//左边腮帮子的第二个黑边
	hdc_circle(base_x - 90, base_y-15, 20, true, 3, COLOR_HEAD_ARC);//左边眼睛
	hdc_circle(base_x + 50, base_y - 10, 20, true, 3, COLOR_HEAD_ARC);//右边眼睛
	hdc_ellipse(base_x - 18, base_y + 15, 10, 20, 0, true, 2, COLOR_MOUSE);//舌头
	hdc_ellipse(base_x - 18, base_y + 15, 10, 20, 0, false, 4, COLOR_HEAD_ARC);//舌头的黑边
	hdc_arc(base_x -30, base_y - 15, 15, 130, 260, 6, COLOR_HEAD_ARC);//左边嘴巴
	hdc_arc(base_x -8, base_y - 15, 15, 130, 260, 6, COLOR_HEAD_ARC);//左边嘴巴
}
void body(int base_x,int base_y)
{
	hdc_rectangle(base_x - 90, base_y + 110, 180, 150, 0, true, 4, COLOR_HEAD);//身体的主体部分
	hdc_sector(base_x-5, base_y + 190, 120,225,315,true, 4, COLOR_HEAD);//身体的左填充部分
	hdc_sector(base_x - 5, base_y + 190, 120, 45, 135, true, 4, COLOR_HEAD);//身体的右填充部分
	hdc_rectangle(base_x-25, base_y + 260, 20, 10, 0, true, 4, COLOR_HEAD);//身体下边的填充部分
	hdc_ellipse(base_x - 55, base_y + 265, 40, 20, 5, true, 2, COLOR_HEAD);//左边的脚
	hdc_ellipse(base_x+40, base_y + 270, 40, 20, 5, true, 2, COLOR_HEAD);//右边的脚
	hdc_ellipse(base_x - 55, base_y + 265, 40, 20, 5, false, 8, COLOR_HEAD_ARC);//左边的脚的轮廓
	hdc_ellipse(base_x + 40, base_y + 270, 40, 20, 5, false, 8, COLOR_HEAD_ARC);//右边的脚的轮廓
	hdc_arc(base_x - 5, base_y + 190, 120, 225, 315, 8, COLOR_HEAD_ARC);//身体左边的黑边
	hdc_arc(base_x - 5, base_y + 190, 120, 45, 135, 8, COLOR_HEAD_ARC);//身体右边的黑边
	hdc_line(base_x - 25, base_y + 270, base_x+10, base_y + 273, 10, COLOR_HEAD_ARC);//下方的横线
	hdc_rectangle(base_x - 98, base_y + 230, 60, 25, 0, true, 4, COLOR_HEAD);//下方消除部分椭圆轮廓(左边)
	hdc_rectangle(base_x+30, base_y + 230, 50, 40, 0, true, 4, COLOR_HEAD);//下方消除部分椭圆轮廓(右边)
	hdc_ellipse(base_x - 70, base_y + 190, 40, 30, 60, false, 8, COLOR_HEAD_ARC);//左边的手
	hdc_rectangle(base_x - 107, base_y + 140, 60, 30, 0, true, 4, COLOR_HEAD);//左边的手的消除部分
	hdc_ellipse(base_x + 50, base_y + 200, 40, 30, 150, false, 8, COLOR_HEAD_ARC);//右边的手
	hdc_rectangle(base_x + 65, base_y + 135, 90, 30, 60, true, 4, COLOR_HEAD);//左边的手的消除部分
}

/* 老师点评：分函数、加注释，好评 */
void hdc_draw_cartoon_2052432(const int base_x, const int base_y)
{
	hdc_cls();
	background();
	head(base_x, base_y);
	body(base_x, base_y);
}