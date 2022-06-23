/* 2053394 信10 张弛 */
#include "../include/cmd_hdc_tools.h"
#include <Windows.h>

#define BLACK      RGB(0, 0, 0)
#define BACK_COL   RGB(249, 193, 22)
#define FACE_WHITE RGB(234, 230, 232)
#define HAIR_RED   RGB(255, 150, 119)
#define CLOTHE     RGB(106, 108, 105)
#define EYE        RGB(142, 128, 75)
#define MOUTH      RGB(240, 124, 130)
#define FACE_RED   RGB(242, 202, 201)

/* 老师点评：准垃圾代码，差评 */
void hdc_draw_cartoon_2053394(const int base_x, const int base_y)
{
	hdc_cls();
	int x = base_x, y = base_y - 45;
	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	while (x >= 100)
		x -= 100;
	while (y >= 100)
		y -= 100;

	hdc_rectangle(100 + x, 90 + y, 620, 650, 0, true, 3, BACK_COL);

	//衣服
	hdc_triangle(500 + x, 430 + y, 180 + x, 740 + y, 650 + x, 740 + y, true, 3, CLOTHE);
	hdc_triangle(465 + x, 430 + y, 180 + x, 740 + y, 650 + x, 740 + y, true, 3, CLOTHE);
	hdc_triangle(500 + x, 490 + y, 590 + x, 590 + y, 560 + x, 450 + y, true, 3, BACK_COL);
	hdc_triangle(435 + x, 490 + y, 320 + x, 590 + y, 360 + x, 450 + y, true, 3, BACK_COL);

	hdc_ellipse(280 + x, 440 + y, 140, 30, 95, true, 3, HAIR_RED);
	hdc_ellipse(280 + x, 440 + y, 140, 30, 95, false, 3, BLACK);

	hdc_triangle(280 + x, 540 + y, 275 + x, 575 + y, 292 + x, 580 + y, true, 3, HAIR_RED);
	hdc_arc(540 + x, 270 + y, 400, 218, 223, 3, BLACK);
	hdc_line(292 + x, 580 + y, 280 + x, 490, 3, BLACK);
	hdc_line(270 + x, 570 + y, 270 + x, 480, 3, BLACK);

	hdc_triangle(405 + x, 520 + y, 495 + x, 515 + y, 450 + x, 560 + y, true, 3,	FACE_WHITE);

	hdc_triangle(400 + x, 510 + y, 405 + x, 590 + y, 450 + x, 560 + y, true, 3, FACE_WHITE);
	hdc_triangle(400 + x, 510 + y, 405 + x, 590 + y, 450 + x, 560 + y, false, 3, BLACK);

	hdc_rectangle(480 + x, 570 + y, 30, 55, 30, true, 3, FACE_WHITE);
	hdc_triangle(525 + x, 480 + y, 503 + x, 595 + y, 450 + x, 560 + y, true, 3, FACE_WHITE);
	hdc_triangle(525 + x, 480 + y, 503 + x, 595 + y, 450 + x, 560 + y, false, 3, BLACK);

	hdc_triangle(405 + x, 590 + y, 410 + x, 670 + y, 430 + x, 610 + y, true, 3, FACE_WHITE);

	hdc_triangle(405 + x, 590 + y, 420 + x, 570 + y, 425 + x, 630 + y, true, 3, FACE_WHITE);

	hdc_triangle(450 + x, 620 + y, 478 + x, 631 + y, 458 + x, 690 + y, true, 3, FACE_WHITE);

	//头发
	hdc_ellipse(542 + x, 380 + y, 80, 60, 0, true, 3, HAIR_RED);

	hdc_ellipse(290 + x, 270 + y, 90, 70, 105, true, 3, HAIR_RED);
	hdc_ellipse(290 + x, 270 + y, 90, 70, 105, false, 3, BLACK);

	hdc_ellipse(440 + x, 440 + y, 180, 80, 0, true, 3, FACE_WHITE);
	hdc_ellipse(440 + x, 440 + y, 180, 80, 0, false, 3, BLACK);

	hdc_ellipse(450 + x, 180 + y, 160, 70, 0, true, 3, HAIR_RED);
	hdc_ellipse(450 + x, 180 + y, 160, 70, 0, false, 3, BLACK);

	hdc_ellipse(570 + x, 240 + y, 160, 70, 45, true, 3, HAIR_RED);
	hdc_ellipse(570 + x, 240 + y, 160, 70, 45, false, 3, BLACK);

	hdc_ellipse(304 + x, 310 + y, 80, 50, 90, true, 3, HAIR_RED);
	hdc_ellipse(304 + x, 310 + y, 80, 50, 90, false, 3, BLACK);

	hdc_ellipse(304 + x, 310 + y, 90, 50, 90, true, 3, HAIR_RED);
	hdc_ellipse(304 + x, 310 + y, 90, 50, 90, false, 3, BLACK);

	hdc_ellipse(320 + x, 270 + y, 110, 50, 80, true, 3, HAIR_RED);

	hdc_ellipse(340 + x, 260 + y, 110, 58, 115, true, 3, HAIR_RED);
	hdc_ellipse(340 + x, 260 + y, 110, 58, 115, false, 3, BLACK);

	hdc_ellipse(360 + x, 315 + y, 100, 40, 115, true, 3, FACE_WHITE);
	hdc_ellipse(360 + x, 315 + y, 100, 40, 115, false, 3, BLACK);

	hdc_ellipse(382 + x, 365 + y, 90, 30, 160, true, 3, FACE_WHITE);

	hdc_ellipse(432 + x, 270 + y, 120, 60, 90, true, 3, HAIR_RED);
	hdc_ellipse(432 + x, 270 + y, 120, 60, 90, false, 3, BLACK);
	hdc_ellipse(440 + x, 270 + y, 130, 50, 80, true, 3, HAIR_RED);
	hdc_ellipse(440 + x, 270 + y, 130, 50, 80, false, 3, BLACK);

	hdc_ellipse(470 + x, 270 + y, 110, 40, 95, true, 3, HAIR_RED);
	hdc_ellipse(470 + x, 270 + y, 110, 40, 95, false, 3, BLACK);
	hdc_ellipse(480 + x, 260 + y, 115, 40, 95, true, 3, HAIR_RED);
	hdc_ellipse(480 + x, 260 + y, 115, 40, 95, false, 3, BLACK);
	hdc_ellipse(540 + x, 280 + y, 130, 60, 45, true, 3, HAIR_RED);
	hdc_ellipse(540 + x, 280 + y, 130, 60, 45, false, 3, BLACK);
	hdc_ellipse(560 + x, 310 + y, 80, 40, 55, true, 3, HAIR_RED);
	hdc_ellipse(560 + x, 310 + y, 80, 40, 55, false, 3, BLACK);
	hdc_ellipse(570 + x, 280 + y, 130, 50, 45, true, 3, HAIR_RED);
	hdc_ellipse(570 + x, 280 + y, 130, 50, 45, false, 3, BLACK);

	//耳朵
	hdc_ellipse(630 + x, 410 + y, 40, 35, 115, true, 3, FACE_WHITE);
	hdc_ellipse(630 + x, 410 + y, 40, 35, 115, false, 3, BLACK);
	hdc_ellipse(630 + x, 410 + y, 30, 25, 115, false, 3, BLACK);

	//麻花辫
	hdc_ellipse(630 + x, 480 + y, 35, 25, 80, true, 3, HAIR_RED);
	hdc_ellipse(630 + x, 480 + y, 35, 25, 80, false, 3, BLACK);
	hdc_ellipse(610 + x, 490 + y, 35, 25, 80, false, 3, BLACK);

	hdc_ellipse(634 + x, 540 + y, 30, 28, 0, true, 3, HAIR_RED);
	hdc_ellipse(634 + x, 540 + y, 30, 28, 0, false, 3, BLACK);
	hdc_ellipse(634 + x, 540 + y, 18, 12, 0, false, 3, BLACK);

	hdc_ellipse(638 + x, 590 + y, 24, 22, 0, true, 3, HAIR_RED);
	hdc_ellipse(638 + x, 590 + y, 24, 22, 0, false, 3, BLACK);
	hdc_ellipse(638 + x, 596 + y, 8, 16, 0, false, 3, BLACK);

	hdc_ellipse(643 + x, 630 + y, 20, 20, 0, true, 3, HAIR_RED);
	hdc_ellipse(643 + x, 630 + y, 20, 20, 0, false, 3, BLACK);
	hdc_ellipse(645 + x, 628 + y, 8, 12, 0, false, 3, BLACK);

	hdc_triangle(650 + x, 650 + y, 650 + x, 700 + y, 700 + x, 680 + y, true, 3, HAIR_RED);
	hdc_triangle(640 + x, 650 + y, 660 + x, 700 + y, 650 + x, 660 + y, true, 3, HAIR_RED);

	hdc_arc(725 + x, 650 + y, 80, 230, 270, 2, BLACK);
	hdc_arc(735 + x, 630 + y, 85, 220, 250, 2, BLACK);
	hdc_arc(745 + x, 610 + y, 90, 210, 240, 2, BLACK);
	
	//右边的头发
	hdc_rectangle(575 + x, 375, 45, 175, 0, true, 3, HAIR_RED);
	hdc_triangle(570 + x, 560 + y, 580 + x, 580 + y, 550 + x, 600 + y, true, 3, HAIR_RED);
	hdc_triangle(575 + x, 550 + y, 615 + x, 550 + y, 580 + x, 590 + y, true, 3, HAIR_RED);

	hdc_arc(495 + x, 530 + y, 80, 90, 150, 2, BLACK);
	hdc_arc(530 + x, 540 + y, 60, 90, 180, 2, BLACK);
	hdc_arc(550 + x, 520 + y, 70, 90, 160, 2, BLACK);

	hdc_line(575 + x, 375 + y, 575 + x, 550 + y, 3, BLACK);
	hdc_line(620 + x, 375 + y, 620 + x, 530 + y, 3, BLACK);

	//遮挡线条
	hdc_ellipse(600 + x, 275 + y, 110, 40, 45, true, 3, HAIR_RED);
	hdc_ellipse(481 + x, 360 + y, 40, 15, 115, true, 3, HAIR_RED);
	hdc_ellipse(525 + x, 180 + y, 120, 50, 25, true, 3, HAIR_RED);
	hdc_ellipse(495 + x, 210 + y, 110, 40, 40, true, 3, HAIR_RED);
	hdc_ellipse(415 + x, 160 + y, 60, 30, 0, true, 3, HAIR_RED);
	hdc_arc(740 + x, 140 + y, 250, 200, 240, 2, BLACK);
	hdc_arc(750 + x, 100 + y, 250, 210, 255, 2, BLACK);

	//眼睛与眉毛
	hdc_ellipse(342 + x, 400 + y, 28, 22, 95, true, 3, EYE);
	hdc_ellipse(342 + x, 400 + y, 28, 22, 95, false, 3, BLACK);
	hdc_ellipse(342 + x, 400 + y, 18, 12, 95, false, 3, BLACK);
	hdc_ellipse(342 + x, 398 + y, 6, 3, 95, true, 3, BLACK);

	hdc_arc(400 + x, 510 + y, 140, 320, 345, 10, BLACK);
	hdc_ellipse(305 + x, 385 + y, 9, 5, 35, true, 3, BLACK);
	hdc_ellipse(330 + x, 370 + y, 9, 5, 50, true, 3, BLACK);
	hdc_ellipse(354 + x, 365 + y, 9, 5, 60, true, 3, BLACK);

	hdc_ellipse(535 + x, 398 + y, 28, 22, 95, true, 3, EYE);
	hdc_ellipse(535 + x, 398 + y, 28, 22, 95, false, 3, BLACK);
	hdc_ellipse(535 + x, 398 + y, 18, 12, 95, false, 3, BLACK);
	hdc_ellipse(535 + x, 396 + y, 6, 3, 95, true, 3, BLACK);

	hdc_arc(520 + x, 500 + y, 120, -5, 27, 10, BLACK);
	hdc_ellipse(515 + x, 365 + y, 12, 5, 60, true, 3, BLACK);
	hdc_ellipse(540 + x, 365 + y, 12, 5, 70, true, 3, BLACK);
	hdc_ellipse(560 + x, 375 + y, 12, 5, 75, true, 3, BLACK);

	//嘴巴
	hdc_ellipse(430 + x, 445 + y, 33, 22, 70, true, 3, MOUTH);
	hdc_ellipse(430 + x, 445 + y, 33, 22, 70, false, 3, BLACK);
	hdc_rectangle(405 + x, 397 + y, 50, 43, 0, true, 3, FACE_WHITE);
	hdc_sector(430 + x, 475 + y, 40, -32, 32, true, 3, MOUTH);
	hdc_arc(430 + x, 475 + y, 40, -32, 32, 3, BLACK);

	//手
	hdc_sector(285 + x, 624 + y, 150, 222, 270, true, 3, CLOTHE);
	hdc_ellipse(250 + x, 624 + y, 32, 20, 0, true, 3, BACK_COL);

	hdc_ellipse(220 + x, 610 + y, 20, 10, 140, true, 3, FACE_WHITE);
	hdc_ellipse(220 + x, 610 + y, 20, 10, 140, false, 3, BLACK);

	hdc_ellipse(175 + x, 590 + y, 60, 40, 135, true, 3, FACE_WHITE);
	hdc_ellipse(175 + x, 590 + y, 60, 40, 135, false, 3, BLACK);

	//修整下巴
	hdc_triangle(375 + x, 500 + y, 535 + x, 470 + y, 505 + x, 570 + y, true, 3, FACE_WHITE);
	hdc_arc(420 + x, 470 + y, 90, 120, 160, 2, BLACK);
	hdc_sector(570 + x, 560 + y, 75, 320, 362, true, 2, BACK_COL);
	hdc_arc(635 + x, 670 + y, 200, 320, 342, 2, BLACK);

	//雀斑与腮红
	hdc_point(310 + x, 425 + y, 7, BLACK);
	hdc_point(320 + x, 430 + y, 7, BLACK);
	hdc_point(335 + x, 435 + y, 7, BLACK);

	hdc_point(540 + x, 435 + y, 7, BLACK);
	hdc_point(550 + x, 430 + y, 7, BLACK);
	hdc_point(560 + x, 425 + y, 7, BLACK);

	hdc_point(405 + x, 423 + y, 4, BLACK);

	hdc_ellipse(420 + x, 405 + y, 20, 10, 0, true, 3, FACE_RED);

	//眉毛
	hdc_arc(350 + x, 440 + y, 100, -35, 15, 2, BLACK);
	hdc_arc(520 + x, 400 + y, 60, -15, 50, 2, BLACK);

	//衣服上的线
	hdc_line(522 + x, 512 + y, 567 + x, 565 + y, 4, BLACK);
	hdc_line(580 + x, 585 + y, 650 + x, 740 + y, 4, BLACK);
	hdc_arc(805 + x, 765 + y, 350, 274, 300, 2, BLACK);
	hdc_line(473 + x, 577 + y, 450 + x, 620 + y, 4, BLACK);
	hdc_line(459 + x, 690 + y, 450 + x, 620 + y, 4, BLACK);

	hdc_line(422 + x, 577 + y, 402 + x, 590 + y, 3, BLACK);
	hdc_line(422 + x, 577 + y, 432 + x, 620 + y, 4, BLACK);
	hdc_line(412 + x, 672 + y, 432 + x, 620 + y, 4, BLACK);
	hdc_line(412 + x, 672 + y, 417 + x, 730 + y, 4, BLACK);

	hdc_line(380 + x, 540 + y, 300 + x, 610 + y, 5, BLACK);
	hdc_arc(333 + x, 648 + y, 50, 280, 320, 3, BLACK);
	hdc_arc(250 + x, 610 + y, 35, 130, 240, 3, BLACK);
	hdc_arc(285 + x, 624 + y, 153, 220, 270, 3, BLACK);

	hdc_arc(175 + x, 610 + y, 30, 10, 80, 2, BLACK);
	hdc_arc(165 + x, 620 + y, 30, 15, 75, 2, BLACK);

	hdc_line(135 + x, 660 + y, 170 + x, 640 + y, 6, BLACK);
	hdc_line(145 + x, 690 + y, 185 + x, 635 + y, 6, BLACK);

	hdc_line(330 + x, 585 + y, 335 + x, 600 + y, 5, BLACK);
	hdc_line(360 + x, 620 + y, 335 + x, 600 + y, 5, BLACK);
	hdc_line(360 + x, 620 + y, 330 + x, 660 + y, 5, BLACK);
	hdc_line(365 + x, 700 + y, 330 + x, 660 + y, 5, BLACK);
	hdc_line(375 + x, 720 + y, 390 + x, 740 + y, 5, BLACK);

	hdc_line(545 + x, 660 + y, 470 + x, 740 + y, 5, BLACK);
	hdc_line(545 + x, 660 + y, 525 + x, 630 + y, 5, BLACK);
	hdc_line(570 + x, 600 + y, 525 + x, 630 + y, 5, BLACK);
	hdc_line(570 + x, 600 + y, 565 + x, 595 + y, 5, BLACK);

	//一些小细节
	hdc_arc(210 + x, 350 + y, 50, 120, 185, 2, BLACK);
	hdc_arc(400 + x, 360 + y, 180, 100, 125, 2, BLACK);
}