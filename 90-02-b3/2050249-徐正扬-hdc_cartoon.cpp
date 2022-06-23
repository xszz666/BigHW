/* 2050249 信14 徐正扬 */
#include <iostream>
#include <iomanip>
#include <Windows.h>
#include "../include/cmd_hdc_tools.h"
#include "../include/cmd_console_tools.h"

#define BLUE RGB(3, 159, 236)
#define MOUTH_RED RGB(229, 0, 14)
#define YELLOW RGB(230, 209, 95)
#define ORANGE RGB(238, 124, 28)
#define NOSE_RED RGB(224, 3, 43)
#define FACE_RED RGB(225, 3, 44)
#define WHITE RGB(255, 255, 255)
#define LINE_BLACK RGB(20, 20, 20)
#define DYELLOW RGB(123, 102, 77)
#define PI 3.141592653589793
#define thick_line 4
#define thin_line 2

static void hdc_ellipse_arc(const int point_x, const int point_y, const int radius_a, const int radius_b,
	const int angle_begin, const int angle_end,
	const int rotation_angles, const bool filled, const int thickness, const int RGB_value)
{
	if (RGB_value != INVALID_RGB)
		hdc_set_pencolor(RGB_value);
	double theta = (double)rotation_angles;
	double st = sin(theta / 180 * PI);
	double ct = cos(theta / 180 * PI);
	double px = (double)point_x;
	double py = (double)point_y;
	double ra = (double)radius_a;
	double rb = (double)radius_b;
	double tn = (double)thickness / 2;

	for (double i = (double)angle_begin; i < (double)angle_end; i += (tn * 20 / ra))
	{
		double _x1, _y1;
		_x1 = sin(i / 180 * PI) * ra;
		_y1 = cos(i / 180 * PI) * rb;
		double x1 = _x1 * ct - _y1 * st + px;
		double y1 = _x1 * st + _y1 * ct + py;
		hdc_point(int(x1), int(y1), thickness, RGB_value);
	}
	return;
}

/* 老师点评：准垃圾代码，差评 */
void hdc_draw_cartoon_2050249(const int base_x, const int base_y)
{
	hdc_cls();

	hdc_rectangle(20, 20, 760, 760, 0, true, 2, WHITE);

	/* feet */
	hdc_ellipse(base_x - 60, base_y + 230, 80, 60, 115, false, thin_line, LINE_BLACK);
	hdc_ellipse(base_x + 100, base_y + 210, 80, 60, 75, false, thin_line, LINE_BLACK);

	hdc_ellipse(base_x - 50, base_y + 195, 81, 61, 140, false, thick_line, LINE_BLACK);
	hdc_ellipse(base_x + 80, base_y + 175, 81, 61, 60, false, thick_line, LINE_BLACK);

	/* arms */
	hdc_arc(base_x - 30, base_y - 40, 250, 95, 240, thick_line, LINE_BLACK);
	hdc_sector(base_x - 30, base_y - 40, 250, 95, 240, true, thin_line, BLUE);

	hdc_sector(base_x - 70, base_y - 330, 400, 135, 200, true, thin_line, WHITE);
	hdc_arc(base_x - 70, base_y - 330, 400, 135, 200, thin_line, LINE_BLACK);

	/* hands */
	hdc_circle(base_x - 230, base_y + 55, 41, false, thick_line, LINE_BLACK);
	hdc_circle(base_x - 230, base_y + 55, 40, true, thin_line, WHITE);

	hdc_circle(base_x + 210, base_y - 10, 41, false, thick_line, LINE_BLACK);
	hdc_circle(base_x + 210, base_y - 10, 40, true, thin_line, WHITE);

	/* leg_fill */
	hdc_rectangle(base_x - 40, base_y + 200, 100, 40, -10, true, thin_line, BLUE);
	hdc_arc(base_x + 25, base_y + 265, 40, -40, 30, thin_line, LINE_BLACK);
	hdc_sector(base_x + 25, base_y + 265, 38, -40, 30, true, thin_line, WHITE);

	/* legs */
	hdc_ellipse(base_x - 50, base_y + 195, 80, 60, 140, true, thin_line, BLUE);
	hdc_ellipse(base_x + 80, base_y + 175, 80, 60, 60, true, thin_line, BLUE);

	/* belly */
	hdc_arc(base_x + 70, base_y + 155, 200, 250, 265, thick_line, LINE_BLACK);
	hdc_sector(base_x + 70, base_y + 155, 198, 250, 265, true, thick_line, BLUE);

	hdc_arc(base_x - 50, base_y + 120, 200, 80, 110, thick_line, LINE_BLACK);
	hdc_sector(base_x - 50, base_y + 120, 198, 80, 110, true, thick_line, BLUE);

	/* magic_pocket */
	hdc_ellipse(base_x + 14, base_y + 146, 121, 71, -8, false, thick_line, LINE_BLACK);
	hdc_ellipse(base_x + 14, base_y + 146, 120, 70, -8, true, thin_line, WHITE);

	hdc_ellipse_arc(base_x + 10, base_y + 156, 100, 40, -90, 105, -8, false, thin_line, LINE_BLACK);
	hdc_arc(base_x - 68, base_y - 230, 400, 155, 182, thin_line, LINE_BLACK);

	/* top_head */
	hdc_ellipse(base_x - 85, base_y - 320, 80, 25, -10, false, thin_line, LINE_BLACK);

	hdc_ellipse_arc(base_x - 85, base_y - 320, 70, 22, 45, 90, -10, false, thin_line, LINE_BLACK);
	hdc_ellipse_arc(base_x - 85, base_y - 320, 60, 19, 45, 90, -10, false, thin_line, LINE_BLACK);
	hdc_ellipse_arc(base_x - 85, base_y - 320, 50, 15, 45, 90, -10, false, thin_line, LINE_BLACK);
	hdc_ellipse_arc(base_x - 85, base_y - 320, 40, 12, 45, 90, -10, false, thin_line, LINE_BLACK);
	hdc_ellipse_arc(base_x - 85, base_y - 320, 30, 9, 45, 90, -10, false, thin_line, LINE_BLACK);
	hdc_ellipse_arc(base_x - 85, base_y - 320, 20, 6, 45, 90, -10, false, thin_line, LINE_BLACK);

	hdc_ellipse_arc(base_x - 85, base_y - 320, 70, 22, 225, 270, -10, false, thin_line, LINE_BLACK);
	hdc_ellipse_arc(base_x - 85, base_y - 320, 60, 19, 225, 270, -10, false, thin_line, LINE_BLACK);
	hdc_ellipse_arc(base_x - 85, base_y - 320, 50, 15, 225, 270, -10, false, thin_line, LINE_BLACK);
	hdc_ellipse_arc(base_x - 85, base_y - 320, 40, 12, 225, 270, -10, false, thin_line, LINE_BLACK);
	hdc_ellipse_arc(base_x - 85, base_y - 320, 30, 9, 225, 270, -10, false, thin_line, LINE_BLACK);
	hdc_ellipse_arc(base_x - 85, base_y - 320, 20, 6, 225, 270, -10, false, thin_line, LINE_BLACK);


	//hdc_arc(base_x - 25, base_y + 60, 295, -13, -10, thick_line, LINE_BLACK);
	//hdc_arc(base_x - 25, base_y + 60, 293, -13, -10, thick_line, YELLOW);

	hdc_rectangle(base_x - 79, base_y - 320, 80, 8, 80, false, thick_line, LINE_BLACK);
	hdc_rectangle(base_x - 79, base_y - 320, 80, 8, 80, true, thin_line, YELLOW);

	hdc_ellipse(base_x - 82, base_y - 321, 8, 4, -10, false, thick_line, LINE_BLACK);
	hdc_ellipse(base_x - 82, base_y - 321, 7, 3, -10, true, thin_line, YELLOW);

	hdc_ellipse_arc(base_x - 81, base_y - 315, 8, 4, 50, 310, -10, true, thick_line, LINE_BLACK);
	hdc_ellipse(base_x - 81, base_y - 315, 7, 3, -10, true, thin_line, YELLOW);

	hdc_ellipse_arc(base_x - 81, base_y - 312, 6, 3, 90, 270, -10, true, thin_line, LINE_BLACK);

	hdc_circle(base_x - 68, base_y - 240, 17, false, thin_line, LINE_BLACK);
	hdc_circle(base_x - 68, base_y - 240, 15, true, thin_line, YELLOW);

	/* head */
	hdc_circle(base_x - 25, base_y - 60, 186, false, thick_line, LINE_BLACK);
	hdc_circle(base_x - 25, base_y - 60, 185, true, thin_line, BLUE);
	hdc_circle(base_x - 20, base_y - 20, 160, false, thick_line, LINE_BLACK);
	hdc_circle(base_x - 20, base_y - 20, 160, true, thin_line, FACE_RED);

	/* bell */
	hdc_circle(base_x + 20, base_y + 150, 31, true, thick_line, LINE_BLACK);
	hdc_circle(base_x + 20, base_y + 150, 30, true, thin_line, YELLOW);

	hdc_arc(base_x + 42, base_y + 345, 200, -15, 2, 1, LINE_BLACK);
	hdc_arc(base_x + 42, base_y + 335, 200, -15, 2, 1, LINE_BLACK);

	hdc_arc(base_x - 8, base_y + 148, 6, 210, -45, thick_line, LINE_BLACK);
	hdc_sector(base_x - 8, base_y + 148, 5, 210, -45, true, thin_line, YELLOW);

	hdc_arc(base_x + 46, base_y + 140, 6, -5, 130, thick_line, LINE_BLACK);
	hdc_sector(base_x + 46, base_y + 140, 5, -5, 130, true, thin_line, YELLOW);

	hdc_ellipse(base_x + 20, base_y + 160, 8, 5, -10, false, thin_line, LINE_BLACK);
	hdc_ellipse(base_x + 20, base_y + 160, 7, 4, -10, true, thin_line, DYELLOW);

	hdc_line(base_x + 20, base_y + 165, base_x + 22, base_y + 183, thin_line, LINE_BLACK);

	/* face */
	hdc_sector(base_x - 25, base_y - 35, 164, 60, 135, true, thin_line, WHITE);
	hdc_sector(base_x - 25, base_y - 35, 164, 225, 270, true, thin_line, WHITE);
	hdc_sector(base_x - 25, base_y - 62, 184, 140, 220, true, thin_line, WHITE);

	hdc_ellipse(base_x - 38, base_y - 80, 164, 105, -15, true, thin_line, WHITE);
	hdc_ellipse_arc(base_x - 38, base_y - 80, 164, 105, 100, 270, -15, true, thin_line, LINE_BLACK);

	/* eyes */
	hdc_ellipse(base_x - 98, base_y - 150, 60, 50, 75, false, thick_line, LINE_BLACK);
	hdc_ellipse(base_x - 98, base_y - 150, 59, 49, 75, true, thin_line, WHITE);

	hdc_ellipse(base_x + 8, base_y - 175, 60, 50, 75, false, thick_line, LINE_BLACK);
	hdc_ellipse(base_x + 8, base_y - 175, 59, 49, 75, true, thin_line, WHITE);

	hdc_ellipse(base_x - 15, base_y - 155, 15, 10, 75, true, thin_line, LINE_BLACK);
	hdc_ellipse(base_x - 17, base_y - 155, 5, 4, 75, true, thin_line, WHITE);

	hdc_ellipse(base_x - 69, base_y - 143, 15, 10, 75, true, thin_line, LINE_BLACK);
	hdc_ellipse(base_x - 67, base_y - 143, 5, 4, 75, true, thin_line, WHITE);

	/* mouth */
	hdc_sector(base_x - 25, base_y - 40, 140, 90, 255, true, thin_line, MOUTH_RED);
	hdc_arc(base_x - 25, base_y - 40, 140, 90, 255, thin_line, LINE_BLACK);

	hdc_line(base_x - 25, base_y - 40, base_x + 115, base_y - 40, thin_line, LINE_BLACK);
	hdc_line(base_x - 25, base_y - 40, base_x - 161, base_y - 5, thin_line, LINE_BLACK);

	hdc_sector(base_x - 155, base_y - 56, 50, 180, 270, true, thin_line, WHITE);
	hdc_arc(base_x - 155, base_y - 56, 50, 180, 270, thin_line, LINE_BLACK);

	hdc_sector(base_x - 165, base_y - 56, 40, -90, 30, true, thin_line, WHITE);
	hdc_arc(base_x - 165, base_y - 56, 40, -90, 30, thin_line, LINE_BLACK);

	hdc_sector(base_x + 110, base_y - 86, 45, 90, 180, true, thin_line, WHITE);
	hdc_arc(base_x + 110, base_y - 86, 45, 90, 180, thin_line, LINE_BLACK);

	hdc_sector(base_x + 115, base_y - 86, 40, -30, 90, true, thin_line, WHITE);
	hdc_arc(base_x + 115, base_y - 86, 40, -30, 90, thin_line, LINE_BLACK);

	/* tongue */
	hdc_arc(base_x - 25, base_y - 40, 120, 135, 210, 36, ORANGE);

	hdc_sector(base_x - 56, base_y + 50, 40, 225, -70, true, thin_line, ORANGE);
	hdc_arc(base_x - 73, base_y + 350, 300, -3, 10, 36, ORANGE);
	hdc_arc(base_x + 45, base_y + 345, 300, -10, 2, 36, ORANGE);

	/* nose */
	hdc_circle(base_x - 35, base_y - 120, 21, false, thick_line, LINE_BLACK);
	hdc_circle(base_x - 35, base_y - 120, 20, true, thin_line, NOSE_RED);

	hdc_circle(base_x - 30, base_y - 130, 7, true, thin_line, WHITE);

	hdc_line(base_x - 30, base_y - 97, base_x - 25, base_y - 40, thin_line, LINE_BLACK);

	hdc_line(base_x - 200, base_y - 90, base_x - 100, base_y - 80, thin_line, LINE_BLACK);
	hdc_line(base_x - 205, base_y - 68, base_x - 105, base_y - 64, thin_line, LINE_BLACK);
	hdc_line(base_x - 190, base_y - 25, base_x - 100, base_y - 50, thin_line, LINE_BLACK);

	hdc_line(base_x + 30, base_y - 100, base_x + 120, base_y - 160, thin_line, LINE_BLACK);
	hdc_line(base_x + 37, base_y - 80, base_x + 144, base_y - 116, thin_line, LINE_BLACK);
	hdc_line(base_x + 45, base_y - 65, base_x + 140, base_y - 78, thin_line, LINE_BLACK);

	return;
}