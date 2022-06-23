/* 2051565 ������ ����ң */
// ��ѧͼ��
// ����ݹ��ѭ�������η��ͣ�

#include <iostream>
#include <cmath>
using namespace std;

// �Զ���ͷ�ļ�ֻ������һ��
#include "../include/cmd_hdc_tools.h"

static const int CENTER_X = 400;
static const int CENTER_Y = 400;

static const int PREV_Y_UNDEFINED = -90000000;

/**
 * ����һ�����ֵ�ƽ����
 * 
 * @param x - Ҫ��ƽ��������
 * @return x ��ƽ����
 */
template <typename T>
static inline T pow2(const T x)
{
	return x * x;
}

// ��������Χ��ԲȦ������
static void drawFace()
{
	int prevY = PREV_Y_UNDEFINED;
	int prevX;
	int y;
	for (int x = -243; x <= 243; x++) {
		y = int(sqrt(pow2(243) - pow2(x)) * 0.98);
		if (prevY >= -CENTER_Y) {
			hdc_line(
				prevX + CENTER_X, prevY + CENTER_Y,
				x + CENTER_X, y + CENTER_Y,
				1, 0x00a0ff
			);
			hdc_line(
				prevX + CENTER_X, -prevY + CENTER_Y,
				x + CENTER_X, -y + CENTER_Y,
				1, 0x00a0ff
			);
		}
		prevY = y;
		prevX = x;
	}
}

// ������
static void drawRouge()
{
	int prevY = PREV_Y_UNDEFINED;
	int prevX;
	int y;
	for (int x = -224; x <= -104; x++) {
		y = int(sqrt(400 - pow2((x + 164) / 3.0)));
		if (prevY >= -CENTER_Y) {
			hdc_line(
				prevX + CENTER_X, prevY + CENTER_Y - 45,
				x + CENTER_X, y + CENTER_Y - 45,
				1, 0x00a0ff
			);
			hdc_line(
				prevX + CENTER_X, -prevY + CENTER_Y - 45,
				x + CENTER_X, -y + CENTER_Y - 45,
				1, 0x00a0ff
			);
		}
		prevY = y;
		prevX = x;
	}

	prevY = PREV_Y_UNDEFINED;
	for (int x = 76; x <= 196; x++) {
		y = int(sqrt(400 - pow2((x - 136) / 3.0)));
		if (prevY >= -CENTER_Y) {
			hdc_line(
				prevX + CENTER_X, prevY + CENTER_Y - 45,
				x + CENTER_X, y + CENTER_Y - 45,
				1, 0x00a0ff
			);
			hdc_line(
				prevX + CENTER_X, -prevY + CENTER_Y - 45,
				x + CENTER_X, -y + CENTER_Y - 45,
				1, 0x00a0ff
			);
		}
		prevY = y;
		prevX = x;
	}
}

// ����
static void drawMouth()
{
	int prevY = PREV_Y_UNDEFINED;
	int prevX;
	int y;
	for (int x = -202; x <= 190; x++) {
		y = int(-((sqrt(sqrt(pow2(158) - pow2((x + 6) / 1.24)) - 20) + 2 * (sqrt(sqrt(pow2(158) - pow2((x + 6) / 1.24)) + 20))) / 3 + 1) * (sqrt(sqrt(pow2(158) - pow2((x + 6) / 1.24)) - 20) + 1));
		if (prevY >= -CENTER_Y) {
			hdc_line(
				prevX + CENTER_X, -prevY + CENTER_Y + 31,
				x + CENTER_X, -y + CENTER_Y + 31,
				1, 0x00a0ff
			);
		}
		prevY = y;
		prevX = x;
	}

	prevY = PREV_Y_UNDEFINED;
	for (int x = -202; x <= 190; x++) {
		y = int(-(((sqrt(sqrt(pow2(159) - pow2((x + 6) / 1.24)) - 30) + 2 * (sqrt(sqrt(pow2(159) - pow2((x + 6) / 1.24)) - 30))) / 3 + 1) * (sqrt(sqrt(pow2(159) - pow2((x + 6) / 1.24)) - 30) + 1) - 1) / 1.15);
		if (prevY >= -CENTER_Y) {
			hdc_line(
				prevX + CENTER_X, -prevY + CENTER_Y + 30,
				x + CENTER_X, -y + CENTER_Y + 30,
				1, 0x00a0ff
			);
		}
		prevY = y;
		prevX = x;
	}
}

// ������
static void drawPupil()
{
	int prevY = PREV_Y_UNDEFINED;
	int prevX;
	int y;
	for (int x = -224; x <= -186; x++) {
		y = int(sqrt(361 - pow2(x + 205)));
		if (prevY >= -CENTER_Y) {
			hdc_line(
				prevX + CENTER_X, prevY + CENTER_Y - 105,
				x + CENTER_X, y + CENTER_Y - 105,
				1, 0x00a0ff
			);
			hdc_line(
				prevX + CENTER_X, -prevY + CENTER_Y - 105,
				x + CENTER_X, -y + CENTER_Y - 105,
				1, 0x00a0ff
			);
		}
		prevY = y;
		prevX = x;
	}

	prevY = PREV_Y_UNDEFINED;
	for (int x = 71; x <= 109; x++) {
		y = int(sqrt(361 - pow2(x - 90)));
		if (prevY >= -CENTER_Y) {
			hdc_line(
				prevX + CENTER_X, prevY + CENTER_Y - 105,
				x + CENTER_X, y + CENTER_Y - 105,
				1, 0x00a0ff
			);
			hdc_line(
				prevX + CENTER_X, -prevY + CENTER_Y - 105,
				x + CENTER_X, -y + CENTER_Y - 105,
				1, 0x00a0ff
			);
		}
		prevY = y;
		prevX = x;
	}
}

// ���۰�
static void drawWhite()
{
	int prevY = PREV_Y_UNDEFINED;
	int prevX;
	int y;
	for (int x = -320; x <= 0; x++) {
		y = int(((sqrt(sqrt(pow2(160) - pow2(x + 160)) - (sqrt(3) * 170 / 2)) + 2 * (sqrt(sqrt(pow2(160) - pow2(x + 160)) - (sqrt(3) / 2)))) / 3 + 1) * (sqrt(sqrt(pow2(160) - pow2(x + 160)) - (sqrt(3) * 170 / 2)) + 1));
		if (prevY >= -CENTER_Y) {
			hdc_line(
				prevX + CENTER_X, -prevY + CENTER_Y - 101,
				x + CENTER_X, -y + CENTER_Y - 101,
				1, 0x00a0ff
			);
			hdc_line(
				prevX + CENTER_X, -prevY + CENTER_Y - 52,
				x + CENTER_X, -y + CENTER_Y - 52,
				1, 0x00a0ff
			);
		}
		prevY = y;
		prevX = x;
	}

	prevY = PREV_Y_UNDEFINED;
	for (int x = -25; x <= 295; x++) {
		y = int(((sqrt(sqrt(pow2(160) - pow2(x - 135)) - (sqrt(3) * 170 / 2)) + 2 * (sqrt(sqrt(pow2(160) - pow2(x - 135)) - (sqrt(3) / 2)))) / 3 + 1) * (sqrt(sqrt(pow2(160) - pow2(x - 135)) - (sqrt(3) * 170 / 2)) + 1));
		if (prevY >= -CENTER_Y) {
			hdc_line(
				prevX + CENTER_X, -prevY + CENTER_Y - 101,
				x + CENTER_X, -y + CENTER_Y - 101,
				1, 0x00a0ff
			);
			hdc_line(
				prevX + CENTER_X, -prevY + CENTER_Y - 52,
				x + CENTER_X, -y + CENTER_Y - 52,
				1, 0x00a0ff
			);
		}
		prevY = y;
		prevX = x;
	}
}

// ��üë
static void drawEyebrows()
{
	int prevY = PREV_Y_UNDEFINED;
	int prevX;
	int y;
	for (int x = -130; x <= 220; x++) {
		y = int(sqrt(45 * 45 - pow2(x - 175)));
		if (prevY >= -CENTER_Y) {
			hdc_line(
				prevX + CENTER_X, -prevY + CENTER_Y - 154,
				x + CENTER_X, -y + CENTER_Y - 154,
				1, 0x00a0ff
			);
		}
		prevY = y;
		prevX = x;
	}

	prevY = PREV_Y_UNDEFINED;

	for (int x = -215; x <= -125; x++) {
		y = int(sqrt(45 * 45 - pow2(x + 170)));
		if (prevY >= -CENTER_Y) {
			hdc_line(
				prevX + CENTER_X, -prevY + CENTER_Y - 154,
				x + CENTER_X, -y + CENTER_Y - 154,
				1, 0x00a0ff
			);
		}
		prevY = y;
		prevX = x;
	}

	prevY = PREV_Y_UNDEFINED;

	for (int x = -130; x <= 220; x++) {
		y = int(((sqrt(sqrt(pow2(45.75) - pow2((x - 175) / 1.2)) - 25.5) + 2 * (sqrt(sqrt(pow2(45.75) - pow2((x - 175) / 1.2)) - 25.5))) / 3 + 1) * (sqrt(sqrt(pow2(45.75) - pow2((x - 175) / 1.2)) - 25.5) + 1));
		if (prevY >= -CENTER_Y) {
			hdc_line(
				prevX + CENTER_X, -prevY + CENTER_Y - 153,
				x + CENTER_X, -y + CENTER_Y - 153,
				1, 0x00a0ff
			);
		}
		prevY = y;
		prevX = x;
	}

	prevY = PREV_Y_UNDEFINED;

	for (int x = -215; x <= -125; x++) {
		y = int(((sqrt(sqrt(pow2(45.75) - pow2((x + 170) / 1.2)) - 25.5) + 2 * (sqrt(sqrt(pow2(45.75) - pow2((x + 170) / 1.2)) - 25.5))) / 3 + 1) * (sqrt(sqrt(pow2(45.75) - pow2((x + 170) / 1.2)) - 25.5) + 1));
		if (prevY >= -CENTER_Y) {
			hdc_line(
				prevX + CENTER_X, -prevY + CENTER_Y - 153,
				x + CENTER_X, -y + CENTER_Y - 153,
				1, 0x00a0ff
			);
		}
		prevY = y;
		prevX = x;
	}
}

void hdc_draw_Mathematical_curve_2051565()
{
	hdc_cls(); // �������Ļ
	cout << "������֮��� q(�R���Qq)" << endl;

	drawFace();
	drawRouge();
	drawMouth();
	drawPupil();
	drawWhite();
	drawEyebrows();
}
