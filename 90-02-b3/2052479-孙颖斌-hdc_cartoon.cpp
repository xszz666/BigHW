/*2052479 ÐÅ10 ËïÓ±±ó*/
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
#define BLUE RGB(0,160,232)
#define RED RGB(225,0,42)
#define WHITE RGB(225,225,225)
#define YELLOW RGB(253,229,59)
#define ORANGE RGB(238,124,28)
#define GREY RGB(119,102,94)
#define BLACK RGB(0,0,0)
#define R 300

static void hdc_head(const int base_x, const int base_y)
{
	//ÏîÈ¦
	hdc_ellipse(base_x - 30, base_y - 110, 160, 140, 0, true, 3, RED);
	hdc_ellipse(base_x - 30, base_y - 110, 162, 142, 0, false, 5, BLACK);
	//Í·
	hdc_ellipse(base_x - 30, base_y - 150, 180, 160, 0, true, 3, BLUE);
	hdc_ellipse(base_x - 30, base_y - 150, 182, 162, 0, false, 5, BLACK);
	//Á³
	hdc_ellipse(base_x - 15, base_y - 135, 160, 136, 0, true, 3, WHITE);
	hdc_ellipse(base_x - 15, base_y - 135, 162, 138, 0, false, 5, BLACK);
	//ÑÛ¿ô
	hdc_ellipse(base_x - 60, base_y - 250, 47, 38, 95, true, 3, WHITE);
	hdc_ellipse(base_x + 20, base_y - 250, 47, 38, 80, true, 3, WHITE);
	hdc_ellipse(base_x - 60, base_y - 250, 50, 40, 95, false, 3, BLACK);
	hdc_ellipse(base_x + 20, base_y - 250, 50, 40, 80, false, 3, BLACK);
	//ÑÛ¾¦
	hdc_arc(base_x - 44, base_y - 240, 15, -80, 80, 8, BLACK);
	hdc_point(base_x - 53, base_y - 235, 10, WHITE);
	hdc_point(base_x - 28, base_y - 235, 10, WHITE);
	hdc_arc(base_x + 4, base_y - 240, 15, -80, 80, 8, BLACK);
	hdc_point(base_x + 12, base_y - 240, 10, WHITE);
	//±Ç×Ó
	hdc_circle(base_x - 15, base_y - 205, 20, true, 3, RED);
	hdc_circle(base_x - 15, base_y - 205, 20, false, 3, BLACK);
	hdc_circle(base_x - 17, base_y - 210, 5, true, 3, WHITE);
	hdc_arc(base_x - 140, base_y - 140, 140, 70, 90, 3, BLACK);
	//×ì
	hdc_sector(base_x - 17, base_y - 140, 120, 180, 275, true, 3, RED);
	hdc_sector(base_x - 17, base_y - 140, 120, 180, 275, false, 3, BLACK);
	hdc_sector(base_x - 25, base_y - 140, 120, 85, 180, true, 3, RED);
	hdc_sector(base_x - 25, base_y - 140, 120, 85, 180, false, 3, BLACK);
	hdc_line(base_x - 25, base_y - 140, base_x - 25, base_y - 20, 8, RED);
	hdc_ellipse(base_x - 39, base_y - 68, 80, 40, 15, true, 3, ORANGE);
	hdc_ellipse(base_x - 39, base_y - 68, 82, 42, 15, false, 3, BLACK);
	hdc_arc(base_x - 17, base_y - 140, 120, 180, 275, 5, BLACK);
	hdc_arc(base_x - 25, base_y - 140, 120, 85, 180, 5, BLACK);
	//¾íºúÐë
	hdc_arc(base_x + 100, base_y - 180, 30, -40, 180, 3, BLACK);
	hdc_line(base_x - 25, base_y - 140, base_x + 100, base_y - 150, 3, BLACK);
	//ÓÒºúÐë
	hdc_line(base_x + 40, base_y - 190, base_x + 150, base_y - 250, 3, BLACK);
	hdc_line(base_x + 50, base_y - 180, base_x + 160, base_y - 200, 3, BLACK);
	hdc_line(base_x + 40, base_y - 170, base_x + 140, base_y - 150, 3, BLACK);
	//×óºúÐë
	hdc_line(base_x - 50, base_y - 180, base_x - 160, base_y - 220, 3, BLACK);
	hdc_line(base_x - 60, base_y - 170, base_x - 160, base_y - 180, 3, BLACK);
	hdc_line(base_x - 50, base_y - 160, base_x - 155, base_y - 130, 3, BLACK);
}
static void hdc_arm(const int base_x, const int base_y)
{
	//ÓÒÊÖ±Û
	for (int i = 31; i <= 60; i++)
		for (int j = 185; j <= 193; j++)
		{
			int x1 = (base_x - 80) + int(300 * sin(i * PI / 180));
			int y1 = (base_y + 250) - int(300 * cos(i * PI / 180));
			int x2 = (base_x + 220) + int(500 * sin(j * PI / 180));
			int y2 = (base_y - 380) - int(500 * cos(j * PI / 180));
			hdc_line(x1, y1, x2, y2, 3, BLUE);
		}
	hdc_arc(base_x - 80, base_y + 250, 300, 31, 60, 5, BLACK);
	hdc_arc(base_x + 220, base_y - 380, 500, 185, 193, 5, BLACK);
	hdc_circle(base_x + 170, base_y + 100, 30, true, 3, WHITE);
	hdc_circle(base_x + 170, base_y + 100, 32, false, 5, BLACK);
	//×óÊÖ±Û
	for (int i = 13; i <= 36; i++)
		for (int j = 223; j <= 250; j++)
		{
			int x1 = (base_x - 300) + int(300 * sin(i * PI / 180));
			int y1 = (base_y + 250) - int(300 * cos(i * PI / 180));
			int x2 = (base_x + 80) + int(340 * sin(j * PI / 180));
			int y2 = (base_y - 150) - int(340 * cos(j * PI / 180));
			hdc_line(x1, y1, x2, y2, 3, BLUE);
		}
	hdc_arc(base_x - 300, base_y + 250, 300, 13, 36, 5, BLACK);
	hdc_arc(base_x + 80, base_y - 150, 340, 223, 250, 5, BLACK);
	hdc_circle(base_x - 230, base_y - 30, 30, true, 3, WHITE);
	hdc_circle(base_x - 230, base_y - 30, 32, false, 5, BLACK);
}
static void hdc_foot(const int base_x, const int base_y)
{
	hdc_ellipse(base_x + 60, base_y + 240, 80, 30, 0, true, 3, WHITE);
	hdc_ellipse(base_x + 60, base_y + 240, 80, 30, 0, false, 5, BLACK);
	hdc_ellipse(base_x - 62, base_y + 240, 90, 35, 0, true, 3, WHITE);
	hdc_ellipse(base_x - 62, base_y + 240, 90, 35, 0, false, 5, BLACK);
}
static void hdc_body(const int base_x, const int base_y)
{
	//Çû¸É
	hdc_sector(base_x - 90, base_y + 110, 200, 45, 90, true, 3, BLUE);
	hdc_sector(base_x - 87, base_y + 130, 200, 75, 112, true, 3, BLUE);
	hdc_arc(base_x - 90, base_y + 110, 200, 45, 90, 5, BLACK);
	hdc_arc(base_x - 87, base_y + 130, 200, 75, 112, 5, BLACK);

	hdc_sector(base_x + 50, base_y + 110, 200, 272, 315, true, 3, BLUE);
	hdc_sector(base_x + 50, base_y + 110, 200, 240, 272, true, 3, BLUE);
	hdc_arc(base_x + 50, base_y + 110, 202, 240, 274, 5, BLACK);

	hdc_ellipse(base_x + 50, base_y + 205, 50, 20, 0, true, 3, BLUE);
	hdc_ellipse(base_x + 50, base_y + 205, 50, 20, 0, false, 5, BLACK);
	hdc_ellipse(base_x - 80, base_y + 205, 52, 22, 0, true, 3, BLUE);
	hdc_ellipse(base_x - 80, base_y + 205, 52, 22, 0, false, 5, BLACK);

	hdc_rectangle(base_x - 127, base_y + 150, 223, 58, 0, true, 3, BLUE);
	hdc_line(base_x - 30, base_y + 208, base_x + 3, base_y + 208, 5, BLACK);
	hdc_line(base_x + 3, base_y + 208, base_x + 15, base_y + 180, 5, BLACK);

	//¶Ç×Ó
	hdc_ellipse(base_x - 10, base_y + 70, 110, 90, 0, true, 3, WHITE);
	hdc_ellipse(base_x - 10, base_y + 70, 112, 92, 0, false, 5, BLACK);
	//¿Ú´ü
	hdc_arc(base_x - 10, base_y + 70, 75, 90, 270, 5, BLACK);
	hdc_line(base_x - 85, base_y + 70, base_x + 65, base_y + 70, 5, BLACK);
	
}
static void hdc_tail(const int base_x, const int base_y)
{
	//Î²°Í
	hdc_circle(base_x - 200, base_y + 150, 20, true, 3, RED);
	hdc_circle(base_x - 200, base_y + 150, 22, false, 5, BLACK);
	hdc_line(base_x - 180, base_y + 150, base_x - 150, base_y + 140, 5, BLACK);
}
static void hdc_bell(const int base_x, const int base_y)
{
	//Áåîõ
	hdc_circle(base_x - 10, base_y + 40, 25, true, 3, YELLOW);
	hdc_circle(base_x - 10, base_y + 40, 27, false, 3, BLACK);
	hdc_arc(base_x - 10, base_y + 65, 40, -40, 40, 3, BLACK);
	hdc_arc(base_x - 10, base_y + 65, 35, -50, 50, 3, BLACK);
	hdc_circle(base_x - 10, base_y + 45, 5, true, 3, GREY);
	hdc_circle(base_x - 10, base_y + 45, 7, false, 3, BLACK);
	hdc_line(base_x - 10, base_y + 50, base_x - 10, base_y + 65, 3, BLACK);
}

/* ÀÏÊ¦µãÆÀ£º·Öº¯Êý¡¢¼Ó×¢ÊÍ£¬ºÃÆÀ */
void hdc_draw_cartoon_2052479(const int base_x, const int base_y)
{
	hdc_cls();
	hdc_rectangle(base_x -370, base_y - 370, 750, 730, 0, true, 2, WHITE);
	hdc_arm(base_x, base_y);//ÊÖ±Û
	hdc_foot(base_x, base_y);//½Å
	hdc_body(base_x, base_y);//ÉíÌå
	hdc_head(base_x, base_y);//Í·
	hdc_tail(base_x, base_y);//Î²°Í
	hdc_bell(base_x, base_y);//Áåîõ
}
