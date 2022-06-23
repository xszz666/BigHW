/* 2053642 信18 李博宇 */
// 彩虹猫
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include "../include/cmd_hdc_tools.h"
using namespace std;

const static int win_high = 360;
const static int win_width = 640;
const int border_per_pixel = 4;

#define LEFTUP_X (base_x - win_width / 2)
#define LEFTUP_Y (base_y - win_high / 2)

static inline void hdc_ext_bigpixel(const int base_x, const int base_y, int shift_x, int shift_y, int RGB_value) {
	for (int i = 1; i <= border_per_pixel; i++)
		hdc_line(LEFTUP_X + shift_x, LEFTUP_Y + shift_y + i - 1,
			LEFTUP_X + shift_x + border_per_pixel, LEFTUP_Y + shift_y + i - 1, 
			1, RGB_value);
}

/* 渲染背景 */
static void rbcat_bgcolor(const int base_x, const int base_y) {
	const static int rbcat_bgc_r = 0;
	const static int rbcat_bgc_g = 52;
	const static int rbcat_bgc_b = 99;

	hdc_rectangle(base_x - win_width / 2, base_y - win_high / 2,
		win_width, win_high, 0, true, 3, RGB(rbcat_bgc_r, rbcat_bgc_g, rbcat_bgc_b));
}

/* 在全都画完之后，点几颗星星 */
static void rbcat_star(const int base_x, const int base_y) {
	const static int rbcat_star_color = RGB(252, 253, 253);
	const static int rbcat_star_count = 9;
	const static struct {
		int x, y, type, serial;
	} stars[rbcat_star_count + 1] = {
		{ 0, 0, 0, 0 },
		{ 160, 10, 0, 0x1 },
		{ 560, 20, 0, 0x1 },
		{ 320, 50, 0, 0x6 },
		{ 400, 100, 0, 0x1 },
		{ 500, 210, 0, 0xd },
		{ 20, 240, 1, 0x8 },
		{ 300, 300, 0, 0x6 },
		{ 160, 340, 0, 0x2 },
		{ 540, 340, 0, 0x2 }
	};
	const int dir[8][2] = {
		{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}
	};
	for (int i = 1; i <= rbcat_star_count; i++) 
		for (int _ser = stars[i].serial, bias = 0; _ser; _ser = _ser >> 1, bias = bias + 1) 
			if (_ser & 1) 
				for (int k = 0; k < (stars[i].type ? 8 : 4); k++) 
					hdc_ext_bigpixel(base_x, base_y, stars[i].x + bias * border_per_pixel * dir[k][0],
						stars[i].y + bias * border_per_pixel * dir[k][1], rbcat_star_color);
}

/* 画彩虹 */
static void rbcat_rainbow(const int base_x, const int base_y) {
	const static int rainbow_w = 12;
	const static int rainbow_rgb[7] = {
		INVALID_RGB,
		RGB(255, 0, 0), RGB(255, 154, 0), RGB(255, 255, 0),
		RGB(49, 255, 0), RGB(0, 153, 255), RGB(99, 51, 255)
	};
	for (int i = 1; i <= 6; i++) {
		for (int j = 0; j <= 6; j++) {
			hdc_rectangle(LEFTUP_X + 40 * j, LEFTUP_Y + 180 + rainbow_w * (i - 4) + (j % 2 ? 6 : 0),
				40, rainbow_w, 
				0, true, 1, rainbow_rgb[i]);
		}
	}
}

struct pixel_info {
	int x, y, rgb;
} static;

/* 身体花纹填充：国旗 */
static void rbcat_bodyfill_national_flag(pixel_info (&dest)[19][14]) {
	const static int bx = 32, by = 4;
	const static int rgb_nflag_bgc = RGB(244, 0, 2);
	const static int rgb_nflag_star = RGB(250, 244, 8);
	for (int i = 0; i < 19; i++)
		for (int j = 0; j < 14; j++)
			dest[i][j] = { bx + i * 4, by + j * 4, rgb_nflag_bgc };
	
}

/* 身体花纹填充：默认样式 */
static void rbcat_bodyfill_standard(pixel_info dest[19][14]) {
	const static int bx = 32, by = 4;
	const static int rgb_body_border = RGB(253, 209, 147);
	const static int rgb_body_content = RGB(255, 155, 254);
	const static int rgb_body_spot = RGB(245, 63, 167);
	for (int i = 0, _rgb; i < 19; i++)
		for (int j = 0; j < 14; j++) {
			_rgb = ((i == 0 || i == 18 || j == 0 || j == 13) ? rgb_body_border : rgb_body_content);
			dest[i][j] = { bx + i * 4, by + j * 4, _rgb };
		}
	for (int i = 1, x, y; i <= 12; i++) {
		x = rand() % 17 + 1, y = rand() % 12 + 1;
		dest[x][y] = { bx + x * 4, by + y * 4, rgb_body_spot };
	}
}

/* 画猫 */
static void rbcat_entity(const int base_x, const int base_y) {
	const static int _lx = 252;
	const static int _ly = 144; // 彩虹猫的绘图范围在(_lx, _ly) - (_lx + 131, _ly + 71)
	const static int rgb_body = RGB(148, 155, 148);
	const static int rgb_border = RGB(2, 0, 0);
	const static int rgb_eyec = RGB(255, 255, 254);
	const static int rgb_blush = RGB(254, 155, 150);
	static void (*bodyfiller)(pixel_info [19][14]) = rbcat_bodyfill_standard;
	const static pixel_info 
		limb_and_tail[] = {
		{ -1, -1, -1 },
		// tail
		{ 0, 24, rgb_border}, {0, 28, rgb_border}, {4, 32, rgb_border}, {8, 36, rgb_border },
		{ 12, 36, rgb_border}, { 16, 40, rgb_border}, {20, 40, rgb_border}, {24, 40, rgb_border}, {4, 20, rgb_border}, {8, 20, rgb_border}, {12, 24, rgb_border}, {12, 28, rgb_border},
		{16, 28, rgb_border}, {20, 28, rgb_border}, {24, 28, rgb_border}, {4, 24, rgb_body}, {8, 24, rgb_body}, {4, 28, rgb_body}, {8, 28, rgb_body}, 
		{8, 32, rgb_body}, {12, 32, rgb_body}, {16, 32, rgb_body}, {20, 32, rgb_body}, {24, 32, rgb_body}, {16, 36, rgb_body}, {20, 36, rgb_body}, {24, 36, rgb_body}, 
		// legs
		{ 24, 52, rgb_border}, { 20, 56, rgb_border}, { 16, 60, rgb_border }, { 16, 64, rgb_border}, { 16, 68, rgb_border}, { 20, 68, rgb_border}, { 24, 68, rgb_border }, { 28, 64, rgb_border}, 
		{ 24, 56, rgb_body }, { 20, 60, rgb_body }, { 24, 60, rgb_body }, { 28, 60, rgb_body }, { 20, 64, rgb_body }, { 24, 64, rgb_body}, { 36, 64, rgb_border }, { 36, 68, rgb_border },
		{ 40, 68, rgb_border}, { 44, 68, rgb_border}, { 48, 64, rgb_border}, { 40, 64, rgb_body }, { 44, 64, rgb_body },
		// paws
		{ 80, 64, rgb_border }, { 80, 68, rgb_border}, {84, 68, rgb_border}, {88, 68, rgb_border}, {92, 64, rgb_border},
		{ 112, 64, rgb_border }, { 112, 68, rgb_border}, {108, 68, rgb_border}, {104, 68, rgb_border}, {100, 64, rgb_border},
		{ 84, 64, rgb_body}, { 88, 64, rgb_body}, {104, 64, rgb_body}, {108, 64, rgb_body},
		{ -1, -1, -1}
	}, body_border[] = {
		{ -1, -1, -1},
		{ 28, 4, rgb_border }, {28, 8, rgb_border }, {28, 12, rgb_border}, {28, 16, rgb_border}, { 28, 20, rgb_border }, {28, 24, rgb_border }, {28, 28, rgb_border}, {28, 32, rgb_border}, { 28, 36, rgb_border }, {28, 40, rgb_border }, {28, 44, rgb_border}, {28, 48, rgb_border}, { 28, 52, rgb_border }, {28, 56, rgb_border }, 
		{ 108, 4, rgb_border }, {108, 8, rgb_border }, {108, 12, rgb_border}, {108, 16, rgb_border}, { 108, 20, rgb_border }, {108, 24, rgb_border }, {108, 28, rgb_border}, {108, 32, rgb_border}, { 108, 36, rgb_border }, {108, 40, rgb_border }, {108, 44, rgb_border}, {108, 48, rgb_border}, { 108, 52, rgb_border }, {108, 56, rgb_border },
		{ 32, 0, rgb_border}, {36, 0, rgb_border }, {40, 0, rgb_border}, {44, 0, rgb_border}, { 48, 0, rgb_border}, {52, 0, rgb_border }, {56, 0, rgb_border}, {60, 0, rgb_border}, { 64, 0, rgb_border}, {68, 0, rgb_border }, {72, 0, rgb_border}, {76, 0, rgb_border}, { 80, 0, rgb_border}, {84, 0, rgb_border }, {88, 0, rgb_border}, {92, 0, rgb_border}, { 96, 0, rgb_border}, {100, 0, rgb_border }, {104, 0, rgb_border}, 
		{ 32, 60, rgb_border}, {36, 60, rgb_border }, {40, 60, rgb_border}, {44, 60, rgb_border}, { 48, 60, rgb_border}, {52, 60, rgb_border }, {56, 60, rgb_border}, {60, 60, rgb_border}, { 64, 60, rgb_border}, {68, 60, rgb_border }, {72, 60, rgb_border}, {76, 60, rgb_border}, { 80, 60, rgb_border}, {84, 60, rgb_border }, {88, 60, rgb_border}, {92, 60, rgb_border}, { 96, 60, rgb_border}, {100, 60, rgb_border }, {104, 60, rgb_border},
		{ -1, -1, -1}
	}, head[] = {
		{ -1, -1, -1},
		{ 72, 16, rgb_border}, { 72, 20, rgb_border}, { 72, 24, rgb_border}, { 72, 28, rgb_border},
		{ 124, 16, rgb_border}, { 124, 20, rgb_border}, { 124, 24, rgb_border}, { 124, 28, rgb_border},
		{ 68, 32, rgb_border}, {68, 36, rgb_border}, {68, 40, rgb_border}, {68, 44, rgb_border}, {68, 48, rgb_border},
		{ 128, 32, rgb_border}, {128, 36, rgb_border}, {128, 40, rgb_border}, {128, 44, rgb_border}, {128, 48, rgb_border},
		{ 72, 52, rgb_border}, { 76, 56, rgb_border}, {80, 60, rgb_border}, {84, 60, rgb_border}, {88, 60, rgb_border}, {92, 60, rgb_border}, {96, 60, rgb_border},
		{ 124, 52, rgb_border}, { 120, 56, rgb_border}, {116, 60, rgb_border}, {112, 60, rgb_border}, {108, 60, rgb_border}, {104, 60, rgb_border}, {100, 60, rgb_border},
		{ 76, 12, rgb_border}, { 80, 12, rgb_border}, { 84, 16, rgb_border}, { 88, 20, rgb_border}, { 92, 24, rgb_border}, { 96, 24, rgb_border},
		{ 120, 12, rgb_border}, { 116, 12, rgb_border}, { 112, 16, rgb_border}, { 108, 20, rgb_border}, { 104, 24, rgb_border}, { 100, 24, rgb_border},
		// body (ear + forehead)
		{ 76, 16, rgb_body}, { 76, 20, rgb_body}, { 76, 24, rgb_body}, { 76, 28, rgb_body}, { 80, 16, rgb_body}, { 80, 20, rgb_body}, { 80, 24, rgb_body}, { 80, 28, rgb_body},
		{ 116, 16, rgb_body}, { 116, 20, rgb_body}, { 116, 24, rgb_body}, { 116, 28, rgb_body}, { 120, 16, rgb_body}, { 120, 20, rgb_body}, { 120, 24, rgb_body}, { 120, 28, rgb_body},
		{84, 20, rgb_body}, {84, 24, rgb_body}, {84, 28, rgb_body}, { 88, 24, rgb_body}, {88, 28, rgb_body}, {92, 28, rgb_body}, {96, 28, rgb_body},
		{112, 20, rgb_body}, {112, 24, rgb_body}, {112, 28, rgb_body}, {108, 24, rgb_body}, {108, 28, rgb_body}, {104, 28, rgb_body}, {100, 28, rgb_body},
		// body (face background)
		{ 72, 32, rgb_body }, { 72, 36, rgb_body }, { 72, 40, rgb_body }, { 72, 44, rgb_body }, { 72, 48, rgb_body },{ 76, 32, rgb_body }, { 76, 36, rgb_body }, { 76, 40, rgb_body }, { 76, 44, rgb_body }, { 76, 48, rgb_body },
		{ 80, 32, rgb_body }, { 80, 36, rgb_body }, { 80, 40, rgb_body }, { 80, 44, rgb_body }, { 80, 48, rgb_body },{ 84, 32, rgb_body }, { 84, 36, rgb_body }, { 84, 40, rgb_body }, { 84, 44, rgb_body }, { 84, 48, rgb_body },
		{ 88, 32, rgb_body }, { 88, 36, rgb_body }, { 88, 40, rgb_body }, { 88, 44, rgb_body }, { 88, 48, rgb_body },{ 92, 32, rgb_body }, { 92, 36, rgb_body }, { 92, 40, rgb_body }, { 92, 44, rgb_body }, { 92, 48, rgb_body },
		{ 96, 32, rgb_body }, { 96, 36, rgb_body }, { 96, 40, rgb_body }, { 96, 44, rgb_body }, { 96, 48, rgb_body },{ 100, 32, rgb_body }, { 100, 36, rgb_body }, { 100, 40, rgb_body }, { 100, 44, rgb_body }, { 100, 48, rgb_body },
		{ 104, 32, rgb_body }, { 104, 36, rgb_body }, { 104, 40, rgb_body }, { 104, 44, rgb_body }, { 104, 48, rgb_body },{ 108, 32, rgb_body }, { 108, 36, rgb_body }, { 108, 40, rgb_body }, { 108, 44, rgb_body }, { 108, 48, rgb_body },
		{ 112, 32, rgb_body }, { 112, 36, rgb_body }, { 112, 40, rgb_body }, { 112, 44, rgb_body }, { 112, 48, rgb_body },{ 116, 32, rgb_body }, { 116, 36, rgb_body }, { 116, 40, rgb_body }, { 116, 44, rgb_body }, { 116, 48, rgb_body },
		{ 120, 32, rgb_body }, { 120, 36, rgb_body }, { 120, 40, rgb_body }, { 120, 44, rgb_body }, { 120, 48, rgb_body },{ 124, 32, rgb_body }, { 124, 36, rgb_body }, { 124, 40, rgb_body }, { 124, 44, rgb_body }, { 124, 48, rgb_body },
		// body (jaw)
		{ 76, 52, rgb_body }, { 80, 52, rgb_body }, { 84, 52, rgb_body }, { 88, 52, rgb_body }, { 92, 52, rgb_body }, { 96, 52, rgb_body }, { 100, 52, rgb_body }, { 104, 52, rgb_body }, { 108, 52, rgb_body }, { 112, 52, rgb_body }, { 116, 52, rgb_body }, { 120, 52, rgb_body },
		{ 80, 56, rgb_body }, { 84, 56, rgb_body }, { 88, 56, rgb_body }, { 92, 56, rgb_body }, { 96, 56, rgb_body }, { 100, 56, rgb_body }, { 104, 56, rgb_body }, { 108, 56, rgb_body }, { 112, 56, rgb_body }, { 116, 56, rgb_body },
		// face details
		{ 84, 36, rgb_eyec}, { 108, 36, rgb_eyec}, { 88, 36, rgb_border}, {84, 40, rgb_border}, {88, 40, rgb_border}, {112, 36, rgb_border}, {112, 40, rgb_border}, {108, 40, rgb_border},
		{ 100, 40, rgb_border}, { 88, 48, rgb_border}, {100, 48, rgb_border}, {108, 48, rgb_border},
		{ 88, 52, rgb_border }, { 92, 52, rgb_border }, { 96, 52, rgb_border }, { 100, 52, rgb_border }, { 104, 52, rgb_border }, { 108, 52, rgb_border },
		{ 76, 44, rgb_blush}, {80, 44, rgb_blush}, { 80, 48, rgb_blush}, {76, 48, rgb_blush},
		{120, 44, rgb_blush}, {116, 44, rgb_blush}, {116, 48, rgb_blush}, {120, 48, rgb_blush},
		{ -1, -1, -1}
	};
	for (int i = 1; limb_and_tail[i].rgb != -1; i++)
		hdc_ext_bigpixel(base_x, base_y, _lx + limb_and_tail[i].x, _ly + limb_and_tail[i].y,  limb_and_tail[i].rgb);
	for (int i = 1; body_border[i].rgb != -1; i++)
		hdc_ext_bigpixel(base_x, base_y, _lx + body_border[i].x, _ly + body_border[i].y, body_border[i].rgb);
	static pixel_info body_content[19][14];
	bodyfiller(body_content);
	for (int i = 0; i < 19; i++)
		for (int j = 0; j < 14; j++)
			hdc_ext_bigpixel(base_x, base_y, _lx + body_content[i][j].x, _ly + body_content[i][j].y, body_content[i][j].rgb);
	for (int i = 1; head[i].rgb != -1; i++)
		hdc_ext_bigpixel(base_x, base_y, _lx + head[i].x, _ly + head[i].y, head[i].rgb);
}

/* 辅助函数 */
static void rbcat_enhance_grid(const int base_x, const int base_y) {
	int rgb = RGB(255, 255, 255);
	for (int i = 40; i < 640; i += 40)
		hdc_line(LEFTUP_X + i, LEFTUP_Y, LEFTUP_X + i, LEFTUP_Y + win_high - 1, 1, rgb);
	for (int i = 40; i < 360; i += 40)
		hdc_line(LEFTUP_X, LEFTUP_Y + i, LEFTUP_X + win_width - 1, LEFTUP_Y + i, 1, rgb);
}

/* 老师点评：分函数、加注释，好评 */
void hdc_draw_cartoon_2053642(const int base_x, const int base_y) {
	hdc_cls();
	rbcat_bgcolor(base_x, base_y);
	//rbcat_enhance_grid(base_x, base_y);
	rbcat_rainbow(base_x, base_y);
	rbcat_entity(base_x, base_y);
	rbcat_star(base_x, base_y);
}