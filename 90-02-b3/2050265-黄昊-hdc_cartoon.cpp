/*1953977 信20 黄昊*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <stdio.h>  
#include <stdlib.h>  
#include <conio.h>  
#include <math.h>
#include <time.h>

#include "../include/cmd_hdc_tools.h"
#include "hdc_student_works.h"
static const int BLACK = RGB(0, 0, 0);
void hdc_draw_catoon_crown()
{
	/*CROWN*/
	hdc_triangle(335, 0, 330, 80, 395, 0, 1, 1, RGB(250, 201, 22));
	hdc_triangle(330, 80, 395, 0, 375, 85, 1, 1, RGB(250, 201, 22));
	hdc_ellipse(370, 40, 20, 5, 100, 1, 1, RGB(255, 255, 255));
	hdc_circle(365, 72, 5, 1, 1, RGB(255, 255, 255));
	hdc_line(335, 0, 330, 80, 2, BLACK);
	hdc_line(395, 0, 375, 85, 2, BLACK);
	hdc_line(350, 0, 345, 10, 2, BLACK);
	hdc_line(375, 0, 375, 10, 2, BLACK);
	hdc_line(375, 10, 380, 0, 2, BLACK);
}

void hdc_draw_catoon_clothes()
{
	hdc_triangle(485, 520, 565, 555, 485, 510, 1, 2, RGB(246, 215, 27));
	hdc_triangle(485, 510, 565, 545, 565, 555, 1, 2, RGB(246, 215, 27));
	hdc_triangle(325, 480, 195, 502, 325, 470, 1, 2, RGB(246, 215, 27));
	hdc_triangle(325, 470, 195, 490, 200, 502, 1, 2, RGB(246, 215, 27));
	hdc_triangle(408, 510, 320, 550, 408, 515, 1, 2, RGB(175, 100, 17));
	hdc_triangle(408, 515, 310, 560, 320, 550, 1, 2, RGB(175, 100, 17));
	hdc_triangle(310, 560, 320, 550, 318, 480, 1, 2, RGB(175, 100, 17));
	hdc_triangle(318, 480, 325, 480, 320, 550, 1, 2, RGB(175, 100, 17));
	hdc_triangle(320, 555, 350, 620, 310, 560, 1, 2, RGB(246, 215, 27));
	hdc_triangle(310, 560, 340, 620, 350, 620, 1, 2, RGB(246, 215, 27));
	hdc_triangle(310, 560, 245, 620, 310, 550, 1, 2, RGB(246, 215, 27));
	hdc_triangle(310, 550, 230, 620, 245, 620, 1, 2, RGB(246, 215, 27));
	hdc_triangle(485, 520, 560, 550, 461, 620, 1, 2, RGB(250, 250, 250));
	hdc_triangle(461, 620, 461, 540, 560, 550, 1, 2, RGB(250, 250, 250));
	hdc_triangle(408, 515, 320, 555, 350, 620, 1, 2, RGB(250, 250, 250));
	hdc_triangle(350, 620, 405, 620, 408, 515, 1, 2, RGB(250, 250, 250));
	hdc_triangle(195, 502, 318, 480, 310, 550, 1, 2, RGB(250, 250, 250));
	hdc_triangle(195, 502, 310, 550, 230, 620, 1, 2, RGB(250, 250, 250));
	hdc_triangle(195, 502, 230, 620, 200, 620, 1, 2, RGB(250, 250, 250));
	hdc_triangle(461, 620, 560, 550, 580, 620, 1, 2, RGB(128, 88, 48));
	hdc_triangle(340, 620, 245, 620, 310, 560, 1, 2, RGB(69, 55, 11));
	hdc_triangle(230, 620, 200, 620, 195, 502, 1, 1, RGB(69, 55, 11));
	hdc_triangle(195, 502, 210, 500, 210, 550, 1, 1, RGB(69, 55, 11));
	hdc_line(408, 510, 320, 550, 2, BLACK);
	hdc_line(485, 520, 565, 555, 2, BLACK);
	hdc_line(485, 510, 565, 545, 2, BLACK);
	hdc_line(408, 515, 310, 560, 2, BLACK);

	hdc_line(310, 560, 318, 480, 2, BLACK);

	hdc_line(320, 555, 350, 620, 2, BLACK);
	hdc_line(310, 560, 340, 620, 2, BLACK);

	hdc_line(310, 560, 245, 620, 2, BLACK);
	hdc_line(310, 550, 230, 620, 2, BLACK);

	hdc_line(325, 480, 195, 502, 2, BLACK);
	hdc_line(325, 470, 195, 490, 2, BLACK);

	hdc_arc(500, 500, 290, 245, 270, 2, BLACK);

	hdc_line(461, 620, 560, 550, 2, BLACK);
	hdc_line(560, 550, 580, 620, 2, BLACK);

}
void hdc_draw_catoon_lunkuo()
{
	/*边框*/
	hdc_arc(340, 380, 300, -30, 0, 2, BLACK);
	hdc_arc(320, 270, 190, 5, 45, 2, BLACK);
	hdc_arc(360, 230, 134, 45, 90, 2, BLACK);
	hdc_line(492, 230, 485, 530, 2, BLACK);
	hdc_arc(606, 535, 120, 224, 277, 2, BLACK);
	hdc_arc(606, 535, 142, 230, 277, 2, BLACK);
	hdc_arc(360, 230, 110, 65, 90, 2, BLACK);
	hdc_line(468, 230, 461, 620, 2, BLACK);
	hdc_arc(330, 230, 100, 45, 90, 2, BLACK);
	hdc_line(428, 230, 423, 620, 2, BLACK);
	hdc_arc(307, 230, 105, 35, 102, 2, BLACK);
	hdc_line(408, 230, 405, 620, 2, BLACK);
	hdc_arc(306, 270, 105, 35, 90, 2, BLACK);
	hdc_arc(520, 80, 202, 212, 233, 2, BLACK);
	hdc_line(370, 215, 330, 170, 2, BLACK);
	hdc_arc(245, 250, 120, 60, 100, 2, BLACK);
	hdc_arc(525, 45, 270, 215, 235, 2, BLACK);
	hdc_arc(575, 150, 280, 240, 260, 2, BLACK);
	hdc_line(405, 400, 340, 440, 2, BLACK);
	hdc_arc(320, 270, 170, 170, 180, 2, BLACK);
	hdc_arc(420, 137, 315, 195, 215, 2, BLACK);
	hdc_arc(548, 168, 380, 232, 240, 2, BLACK);
	hdc_arc(92, 400, 133, 45, 72, 2, BLACK);
	hdc_arc(270, 190, 145, 213, 233, 2, BLACK);
	hdc_arc(286, 230, 140, 250, 315, 2, BLACK);
	hdc_arc(295, 235, 130, 225, 250, 2, BLACK);
	hdc_arc(280, 205, 130, 220, 250, 2, BLACK);
	hdc_arc(280, 250, 100, 240, 270, 2, BLACK);
	hdc_arc(350, 190, 180, 230, 265, 2, BLACK);
	hdc_line(200, 180, 208, 298, 2, BLACK);
	hdc_arc(400, 130, 215, 220, 245, 2, BLACK);
	hdc_line(255, 188, 253, 291, 2, BLACK);
	hdc_arc(455, 110, 215, 215, 248, 2, BLACK);
	hdc_line(200, 620, 185, 300, 2, BLACK);
	hdc_line(178, 540, 160, 280, 2, BLACK);
	hdc_line(175, 620, 150, 270, 2, BLACK);
	hdc_line(140, 620, 170, 550, 2, BLACK);
	//hdc_arc(450, 180, 170, 220, 250, 1, BLACK);
	/*眉毛部分*/
	hdc_arc(420, 430, 200, 328, 338, 2, BLACK);
	hdc_arc(420, 430, 200, 343, 351, 2, BLACK);
	hdc_arc(420, 430, 198, 328, 338, 2, BLACK);
	hdc_arc(420, 430, 198, 343, 351, 2, BLACK);
	hdc_arc(225, 380, 100, -15, 0, 2, BLACK);
	hdc_arc(225, 380, 100, 5, 10, 2, BLACK);
	hdc_arc(225, 380, 98, -35, 5, 2, BLACK);
	hdc_arc(225, 380, 98, -35, 5, 2, BLACK);
	/*眼睛部分*/
	hdc_ellipse(370, 300, 24, 16, 73, false, 1, BLACK);
	hdc_arc(370, 360, 85, -35, 10, 1, BLACK);
	hdc_arc(380, 360, 85, -45, 5, 1, BLACK);
	hdc_arc(360, 360, 85, -5, 25, 2, BLACK);
	hdc_line(393, 277, 387, 317, 1, BLACK);
	hdc_arc(370, 295, 30, 145, 215, 1, BLACK);
	hdc_arc(440, 250, 110, 225, 253, 1, BLACK);
	hdc_ellipse(240, 334, 24, 14, 74, false, 1, BLACK);
	hdc_arc(240, 395, 85, -25, 10, 1, BLACK);
	hdc_arc(250, 395, 85, -35, 5, 1, BLACK);
	hdc_arc(230, 395, 85, -5, 20, 1, BLACK);
	hdc_line(252, 312, 255, 350, 1, BLACK);
	hdc_arc(240, 330, 30, 145, 200, 1, BLACK);
	hdc_arc(310, 295, 110, 225, 253, 1, BLACK);
	/*脖子*/
	hdc_line(408, 510, 320, 550, 2, BLACK);
	hdc_line(320, 550, 330, 445, 2, BLACK);
	/*衣服*/
	hdc_line(408, 510, 320, 550, 2, BLACK);
	hdc_line(485, 520, 565, 555, 2, BLACK);
	hdc_line(485, 510, 565, 545, 2, BLACK);
	hdc_line(408, 515, 310, 560, 2, BLACK);
	hdc_line(310, 560, 318, 480, 2, BLACK);
	hdc_line(320, 555, 350, 620, 2, BLACK);
	hdc_line(310, 560, 340, 620, 2, BLACK);
    hdc_line(310, 560, 245, 620, 2, BLACK);
	hdc_line(310, 550, 230, 620, 2, BLACK);
	hdc_line(318, 480, 200, 502, 2, BLACK);
	hdc_line(318, 470, 195, 490, 2, BLACK);
	hdc_arc(500, 500, 290, 245, 270, 2, BLACK);
	hdc_line(461, 620, 560, 550, 2, BLACK);
	hdc_line(560, 550, 580, 620, 2, BLACK);


}

/* 老师点评：分函数分一半，中评 */
void hdc_draw_cartoon_2050265(const int base_x, const int base_y)
{
	hdc_cls();
	hdc_triangle(0, 0, 800, 0, 800, 800, 1, 1, RGB(255, 255, 255));
	hdc_triangle(0, 0, 0, 800, 800, 800, 1, 1, RGB(255, 255, 255));
	hdc_line(0, 620, 800, 620, 1, BLACK);
	hdc_draw_catoon_crown();
	hdc_draw_catoon_clothes();
	/*头发及脸部*/
	hdc_triangle(195, 490, 180, 170, 480, 450, 1, 1, RGB(251, 236, 225));
	hdc_triangle(180, 170, 480, 450, 480, 170, 1, 1, RGB(251, 236, 225));
	hdc_ellipse(367, 297, 26, 28, -12, 1, 1, RGB(255, 255, 255));
	hdc_triangle(252, 312, 255, 350, 225, 360, 1, 1, RGB(255, 255, 255));
	hdc_triangle(225, 360, 205, 312, 252, 312, 1, 1, RGB(255, 255, 255));
	hdc_triangle(195, 490, 325, 470, 330, 440, 1, 1, RGB(175, 100, 17));
	hdc_triangle(195, 490, 230, 395, 330, 440, 1, 1, RGB(175, 100, 17));
	hdc_triangle(195, 490, 240, 395, 180, 300, 1, 1, RGB(175, 100, 17));
	hdc_triangle(468, 230, 461, 620, 428, 230, 1, 1, RGB(175, 100, 17));
	hdc_triangle(428, 230, 423, 620, 461, 620, 1, 1, RGB(175, 100, 17));
	hdc_triangle(428, 230, 423, 620, 405, 620, 1, 2, RGB(175, 100, 17));
	hdc_triangle(405, 620, 408, 230, 428, 230, 1, 2, RGB(175, 100, 17));
	hdc_triangle(492, 230, 485, 530, 408, 230, 1, 1, RGB(175, 100, 17));
	hdc_triangle(408, 230, 406, 530, 485, 530, 1, 1, RGB(175, 100, 17));
	hdc_sector(606, 535, 142, 224, 277, 1, 1, RGB(175, 100, 17));
	hdc_sector(606, 535, 120, 224, 277, 1, 1, RGB(255, 255, 255));
	hdc_triangle(400, 620, 600, 620, 500, 700, 1, 1, RGB(255, 255, 255));
    hdc_triangle(485, 520, 565, 555, 485, 510, 1, 1, RGB(246, 215, 27));
	hdc_triangle(485, 510, 565, 545, 565, 555, 1, 1, RGB(246, 215, 27));
	hdc_triangle(520, 620, 560, 550, 570, 580, 1, 1, RGB(128, 88, 48));
	hdc_triangle(520, 620, 560, 550, 495, 595, 1, 1, RGB(128, 88, 48));
	hdc_triangle(200, 620, 185, 300, 175, 620, 1, 1, RGB(175, 100, 17));
	hdc_triangle(175, 620, 150, 270, 185, 300, 1, 1, RGB(175, 100, 17));
	hdc_ellipse(334, 145, 130, 60, 7, 1, 2, RGB(175, 100, 17));
	hdc_triangle(490, 230, 400, 245, 350, 190, 1, 1, RGB(175, 100, 17));
	hdc_ellipse(445, 200, 41, 90, -22, 1, 2, RGB(175, 100, 17));
	hdc_ellipse(185, 195, 30, 85, 18, 1, 2, RGB(175, 100, 17));
	hdc_triangle(200, 180, 208, 298, 182, 258, 1, 1, RGB(175, 100, 17));
	hdc_triangle(255, 168, 253, 291, 165, 168, 1, 1, RGB(175, 100, 17));
	hdc_triangle(300, 200, 330, 291, 240, 180, 1, 1, RGB(175, 100, 17));
	hdc_triangle(300, 200, 362, 263, 350, 160, 1, 1, RGB(175, 100, 17));
	hdc_triangle(170, 270, 174, 300, 155, 270, 1, 1, RGB(175, 100, 17));
	hdc_triangle(170, 270, 195, 305, 170, 250, 1, 1, RGB(175, 100, 17));
	hdc_triangle(140, 620, 170, 550, 170, 620, 1, 1, RGB(175, 100, 17));
	
	/*眼睛部分*/
	hdc_ellipse(370, 300, 24, 16, 73, 1, 1, RGB(128,88,48));
	hdc_ellipse(373, 310, 15, 13, 73, 1, 1, RGB(231, 185, 97));
	hdc_sector(371, 305, 14, -95, 85, 1, 1, RGB(175, 100, 17));
	hdc_circle(372, 306, 6, 1, 1, RGB(175, 100, 17));
	hdc_circle(360, 285, 7, 1, 1, RGB(255, 255, 255));
	hdc_arc(375, 360, 85, -40, 0, 2, RGB(128, 88, 48));
	
	hdc_ellipse(240, 334, 24, 14, 74, 1, 1, RGB(128, 88, 48));
	hdc_ellipse(243, 344, 14, 12, 74, 1, 1, RGB(231, 185, 97));
	hdc_sector(241, 339, 14, -95, 85, 1, 1, RGB(175, 100, 17));
	hdc_circle(242, 340, 6, 1, 1, RGB(175, 100, 17));
	hdc_circle(230, 321, 6, 1, 1, RGB(255, 255, 255));
	hdc_arc(240, 395, 85, -25, 10, 2, RGB(128, 88, 48));
	/*脖子*/
	hdc_triangle(403, 510, 320, 550, 340, 345, 1, 1, RGB(251, 236, 225));
	hdc_triangle(403, 510, 400, 450, 350, 450, 1, 1, RGB(251, 236, 225));
	/*嘴巴*/
	hdc_point(300, 400, 4, BLACK);
	hdc_point(320, 397, 4, BLACK);
	/*鼻子*/
	hdc_triangle(290, 350, 290, 340, 285, 343, 1, 1, RGB(255, 225, 189));
	hdc_triangle(290, 350, 290, 340, 285, 343, 0, 2, BLACK);
	hdc_draw_catoon_lunkuo();
}