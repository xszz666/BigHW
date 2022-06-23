/* 2051565 ������ ����ң */
// ��ͨ����
// Ĭ�ϻ�׼��ֵ�� (400, 400)
// ��ֹ�ݹ��ѭ��

// ��ѩ���� logo
// ��ƻ�����СĬ��Ϊ 600 �� 600
// ѩ������Ϊ���ĵ�

#include <iostream>
#include <cmath>
using namespace std;

// ���ɼ������֮����Զ���ͷ�ļ�
#include "../include/cmd_hdc_tools.h"

/** ������ȡ� */
static const int CANVAS_WIDTH = 600;
/** �����߶ȡ� */
static const int CANVAS_HEIGHT = 600;

/**
 * ���²������Կ���ͼƬ��ɫ������ 8 bit BGR ��ʽ���á�
 */
/** ������ɫ�� */
static const int BACKGROUND_COLOR = 0x5600e6;
/** ����Ƥ����ɫ�� */
static const int SKIN_COLOR = 0xffffff;
/** �����Ե����ɫ�� */
static const int OUTLINE_COLOR = 0x000000;
/** �ʹ���ɫ�� */
static const int CROWN_COLOR = 0xffffff;
/** �������ɫ�� */
static const int ICE_CREAM_COLOR = 0xffffff;
/** ��Ͳ������ɫ�� */
static const int CONE_PRIMARY_COLOR = 0x36c6fd;
/** ��Ͳ������ɫ������ʱΪ�õ��� */
static const int CONE_TEXTURE_COLOR = 0x0094f3;
/** ����ͫ����ɫ�� */
static const int EYE_PUPIL_COLOR = 0x89330c;
/** ����ɫ�� */
static const int MOUTH_COLOR = 0x89330c;
/** ��ͷ��ɫ�� */
static const int TONGUE_COLOR = 0x5600e6;
/** ������ɫ�� */
static const int NOSE_COLOR = 0x0197f2;
/** ������ɫ�� */
static const int CLOAK_COLOR = 0x5600e6;

/** �������ȡ����ò�������ģ� */
static const int CANVAS_HALF_WIDTH = CANVAS_WIDTH / 2;
/** ������߶ȡ����ò�������ģ� */
static const int CANVAS_HALF_HEIGHT = CANVAS_HEIGHT / 2;

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

// �����ӭ�ʣ���ѩ����������~~
static void sayHello()
{
	cct_gotoxy(0, 0);
	cout << "�㰮��~~ �t(*�㨌��*)�s" << endl
	     << "�Ұ���~~ O(��_��)O" << endl
	 	 << "��ѩ����������~~ q(�R���Qq)" << endl;
}

// ��һ��ԲԲ��С�Դ�
static void drawCuteHead(const int base_x, const int base_y)
{
	// ͷ����
	hdc_ellipse(
		base_x + CANVAS_HALF_WIDTH * 2 / 27, base_y - CANVAS_HALF_HEIGHT * 5 / 18,
		CANVAS_HALF_WIDTH * 7 / 18, CANVAS_HALF_HEIGHT * 16 / 54,
		0, true, 1, SKIN_COLOR
	);

	// ͷ�߿�
	hdc_ellipse(
		base_x + CANVAS_HALF_WIDTH * 2 / 27, base_y - CANVAS_HALF_HEIGHT * 5 / 18,
		CANVAS_HALF_WIDTH * 7 / 18, CANVAS_HALF_HEIGHT * 16 / 54,
		0, false, CANVAS_HALF_WIDTH / 36, OUTLINE_COLOR
	);

	// ���۾�
	int pupilCenterX[2] = {
		-CANVAS_HALF_WIDTH / 27,
		CANVAS_HALF_WIDTH / 5
	};
	int pupilCenterY[2] = {
		-CANVAS_HALF_HEIGHT * 13 / 36,
		-CANVAS_HALF_HEIGHT * 13 / 36
	};
	
	for (int i = 0; i < 2; i++) {
		// ͫ��
		hdc_ellipse(
			pupilCenterX[i] + base_x, pupilCenterY[i] + base_y,
			CANVAS_HALF_HEIGHT / 12, CANVAS_HALF_WIDTH / 18,
			100, true, 1, EYE_PUPIL_COLOR
		);
		// ͫ�׷���
		hdc_ellipse(
			pupilCenterX[i] + CANVAS_HALF_WIDTH / 18 + base_x,
			pupilCenterY[i] + CANVAS_HALF_HEIGHT / 72 + base_y,
			CANVAS_HALF_HEIGHT / 18, CANVAS_HALF_WIDTH / 27,
			100, true, 1, SKIN_COLOR
		);
	}

	// ����
	int leftTopX = CANVAS_HALF_WIDTH / 9;
	int leftDownX = CANVAS_HALF_WIDTH / 12;
	int leftTopY = -CANVAS_HALF_HEIGHT / 3;
	int leftDownY = -CANVAS_HALF_HEIGHT / 5;
	int dist = int(sqrt(pow2(leftTopX - leftDownX) + pow2(leftTopY - leftDownY)));
	hdc_triangle(
		CANVAS_HALF_WIDTH * 5 / 18 + base_x, base_y - CANVAS_HALF_HEIGHT * 5 / 18, // �Ҷ���
		leftTopX + base_x, base_y + leftTopY, // ����
		leftDownX + base_x, base_y + leftDownY, // ����
		true, 1, NOSE_COLOR
	);
	hdc_ellipse(
		(leftTopX + leftDownX) / 2 + base_x, (leftTopY + leftDownY) / 2 + base_y, dist / 2, dist / 4,
		105, // ����Ƕ���Ĳ�̫�á�Ӧ��ͨ�������������ó���
		true, 1, NOSE_COLOR
	);

	// ��
	hdc_arc(
		CANVAS_HALF_WIDTH * 2 / 27 + base_x, base_y - CANVAS_HALF_HEIGHT * 17 / 45,
		CANVAS_HALF_HEIGHT / 4, 130, 210, CANVAS_HALF_HEIGHT / 45, MOUTH_COLOR
	);

	// ��ͷ
	int topX = -CANVAS_HALF_WIDTH * 7 / 54;
	int topY = -CANVAS_HALF_HEIGHT * 13 / 45;
	int rightDownX = -CANVAS_HALF_WIDTH / 18;
	int rightDownY = -CANVAS_HALF_HEIGHT * 17 / 108;
	int leftX = -CANVAS_HALF_WIDTH * 7 / 36;
	int leftY = -CANVAS_HALF_HEIGHT * 2 / 9;
	int distLeftToRD = int(sqrt(pow2(leftX - rightDownX) + pow2(leftY - rightDownY)));
	int distLeftToTop = int(sqrt(pow2(leftX - topX) + pow2(leftY - topY)));
	int distTopToRD = int(sqrt(pow2(topX - rightDownX) + pow2(topY - rightDownY)));
	hdc_triangle(
		topX + base_x, topY + base_y, rightDownX + base_x, rightDownY + base_y,
		leftX + base_x, leftY + base_y, true, 1, TONGUE_COLOR
	);
	hdc_ellipse(
		(topX + rightDownX) / 2 + base_x, (topY + rightDownY) / 2 + base_y, 
		distTopToRD / 2, distTopToRD / 6,
		58, // ����Ƕ���Ĳ�̫�á�Ӧ��ͨ�������������ó���
		true, 1, TONGUE_COLOR
	); 
	hdc_ellipse(
		(topX + leftX) / 2 + base_x, (topY + leftY) / 2 + base_y, 
		distLeftToTop / 2, distLeftToTop / 4,
		-48, // ����Ƕ���Ĳ�̫�á�Ӧ��ͨ�������������ó���
		true, 1, TONGUE_COLOR
	); 
	hdc_ellipse(
		(leftX + rightDownX) / 2 + base_x, (leftY + rightDownY) / 2 + base_y, 
		distLeftToRD / 2, distLeftToRD / 6,
		27, // ����Ƕ���Ĳ�̫�á�Ӧ��ͨ�������������ó���
		true, 1, TONGUE_COLOR
	);
}

// ���ʹ�
static void drawCrown(const int base_x, const int base_y)
{
	for (int isFilled = 0; isFilled < 2; isFilled += 1) {
		// �ʹ��ϵ�Բ��
		int circleCenterCoord[3][2] = {
			{-CANVAS_HALF_WIDTH * 2 / 27, -CANVAS_HALF_HEIGHT * 20 / 27},
			{CANVAS_HALF_WIDTH * 2 / 27, -CANVAS_HALF_HEIGHT * 7 / 9},
			{CANVAS_HALF_WIDTH * 6 / 27, -CANVAS_HALF_HEIGHT * 34 / 45}
		};
		for (int i = 0; i < 3; i++) {
			hdc_circle(
				circleCenterCoord[i][0] + base_x, circleCenterCoord[i][1] + base_y,
				CANVAS_HALF_WIDTH / 9 / 2 / 2, isFilled, 
				(isFilled ? 1 : CANVAS_HALF_WIDTH / 18), 
				(isFilled ? CROWN_COLOR : OUTLINE_COLOR)
			);
		}
		// ����������
		int yDelta = CANVAS_HALF_HEIGHT * 1 / 100; // ����΢��
		int triangleCoord[3][3][2] = {
			{
				{-CANVAS_HALF_WIDTH * 2 / 27, -CANVAS_HALF_HEIGHT * 20 / 27 + yDelta},
				{-CANVAS_HALF_WIDTH / 27, -CANVAS_HALF_HEIGHT * 16 / 27 + yDelta},
				{CANVAS_HALF_WIDTH / 9, -CANVAS_HALF_HEIGHT * 16 / 27 + yDelta}
			},
			
			{
				{CANVAS_HALF_WIDTH * 2 / 27, -CANVAS_HALF_HEIGHT * 7 / 9 + yDelta},
				{-CANVAS_HALF_WIDTH / 27, -CANVAS_HALF_HEIGHT * 16 / 27 + yDelta},
				{CANVAS_HALF_WIDTH / 6, -CANVAS_HALF_HEIGHT * 16 / 27 + yDelta}
			},
			{
				{CANVAS_HALF_WIDTH * 6 / 27, -CANVAS_HALF_HEIGHT * 34 / 45 + yDelta},
				{CANVAS_HALF_WIDTH / 27, -CANVAS_HALF_HEIGHT * 16 / 27 + yDelta},
				{CANVAS_HALF_WIDTH / 6, -CANVAS_HALF_HEIGHT * 16 / 27 + yDelta}
			}
		};
		for (int i = 0; i < 3; i++) {
			hdc_triangle(
				triangleCoord[i][0][0] + base_x, triangleCoord[i][0][1] + base_y,
				triangleCoord[i][1][0] + base_x, triangleCoord[i][1][1] + base_y,
				triangleCoord[i][2][0] + base_x, triangleCoord[i][2][1] + base_y,
				isFilled, (isFilled ? 1 : CANVAS_HALF_WIDTH / 18), 
				(isFilled ? CROWN_COLOR : OUTLINE_COLOR)
			);
		}
		// Բ��ʹڵײ�
		hdc_ellipse(
			(triangleCoord[1][1][0] + triangleCoord[1][2][0]) / 2 + base_x,
			(triangleCoord[1][1][1] + triangleCoord[1][2][1]) / 2 + base_y + yDelta,
			(triangleCoord[1][2][0] - triangleCoord[1][1][0]) / 2,
			CANVAS_HALF_HEIGHT / 56,
			0, isFilled,
			(isFilled ? 1 : CANVAS_HALF_WIDTH / 18),
			(isFilled ? CROWN_COLOR : OUTLINE_COLOR)
		);
	}

}

// ��������󲿷֣�
static void drawCloakBack(const int base_x, const int base_y)
{
	int topX = CANVAS_HALF_WIDTH / 18;
	int topY = -CANVAS_HALF_HEIGHT / 3;
	int rightX = CANVAS_HALF_WIDTH * 2 / 3;
	int rightY = CANVAS_HALF_HEIGHT * 2 / 3;
	int leftX = -CANVAS_HALF_WIDTH * 5 / 9;
	int leftY = CANVAS_HALF_HEIGHT * 2 / 3;
	int distL2R = int(sqrt(pow2(leftX - rightX) + pow2(leftY - rightY)));
	int distL2T = int(sqrt(pow2(leftX - topX) + pow2(leftY - topY)));
	int distT2R = int(sqrt(pow2(topX - rightX) + pow2(topY - rightY)));

	int angleL2R = 0;
	int angleL2T = -60;
	int angleT2R = 60;

	// �����
	hdc_ellipse(
		(topX + rightX) / 2 + base_x, (topY + rightY) / 2 + base_y,
		distT2R / 2, distT2R / 15,
		angleT2R, // ����Ƕ���Ĳ�̫�á�Ӧ��ͨ�������������ó���
		false, CANVAS_HALF_WIDTH / 18, OUTLINE_COLOR
	);
	hdc_ellipse((topX + leftX) / 2 + base_x, (topY + leftY) / 2 + base_y,
		distL2T / 2, distL2T / 15,
		angleL2T, // ����Ƕ���Ĳ�̫�á�Ӧ��ͨ�������������ó���
		false, CANVAS_HALF_WIDTH / 18, OUTLINE_COLOR
	);
	hdc_ellipse(
		(leftX + rightX) / 2 + base_x, (leftY + rightY) / 2 + base_y,
		distL2R / 2, distL2R / 8,
		angleL2R, // ����Ƕ���Ĳ�̫�á�Ӧ��ͨ�������������ó���
		false, CANVAS_HALF_WIDTH / 18, OUTLINE_COLOR
	);

	hdc_triangle(
		topX + base_x, topY + base_y, rightX + base_x, rightY + base_y,
		leftX + base_x, leftY + base_y, true, 1, CLOAK_COLOR
	);

	hdc_ellipse(
		(topX + rightX) / 2 + base_x, (topY + rightY) / 2 + base_y,
		distT2R / 2, distT2R / 15,
		angleT2R, // ����Ƕ���Ĳ�̫�á�Ӧ��ͨ�������������ó���
		true, 1, CLOAK_COLOR
	);
	hdc_ellipse((topX + leftX) / 2 + base_x, (topY + leftY) / 2 + base_y,
		distL2T / 2, distL2T / 15,
		angleL2T, // ����Ƕ���Ĳ�̫�á�Ӧ��ͨ�������������ó���
		true, 1, CLOAK_COLOR
	);
	hdc_ellipse(
		(leftX + rightX) / 2 + base_x, (leftY + rightY) / 2 + base_y,
		distL2R / 2, distL2R / 8,
		angleL2R, // ����Ƕ���Ĳ�̫�á�Ӧ��ͨ�������������ó���
		true, 1, CLOAK_COLOR
	);
}

// ���������죩
static void drawCloakCollar(const int base_x, const int base_y)
{
	int rightCollarOffsetX = CANVAS_HALF_WIDTH * 5 / 9;
	for (int i = 0; i <= rightCollarOffsetX; i += rightCollarOffsetX) {
		int topX = -CANVAS_HALF_WIDTH * 2 / 9 + i;
		int topY = -CANVAS_HALF_HEIGHT / 12;
		int rightX = 0 + i;
		int rightY = CANVAS_HALF_HEIGHT / 27;
		int leftX = -CANVAS_HALF_WIDTH * 7 / 18 + i;
		int leftY = CANVAS_HALF_HEIGHT / 18;
		int distL2R = int(sqrt(pow2(leftX - rightX) + pow2(leftY - rightY)));
		int distL2T = int(sqrt(pow2(leftX - topX) + pow2(leftY - topY)));
		int distT2R = int(sqrt(pow2(topX - rightX) + pow2(topY - rightY)));

		int angleL2R = 0;
		int angleL2T = -40;
		int angleT2R = 32;

		// �����
		hdc_ellipse(
			(topX + rightX) / 2 + base_x, (topY + rightY) / 2 + base_y,
			distT2R / 2, distT2R / 15,
			angleT2R, // ����Ƕ���Ĳ�̫�á�Ӧ��ͨ�������������ó���
			false, CANVAS_HALF_WIDTH / 18, OUTLINE_COLOR
		);
		hdc_ellipse((topX + leftX) / 2 + base_x, (topY + leftY) / 2 + base_y,
			distL2T / 2, distL2T / 15,
			angleL2T, // ����Ƕ���Ĳ�̫�á�Ӧ��ͨ�������������ó���
			false, CANVAS_HALF_WIDTH / 18, OUTLINE_COLOR
		);
		hdc_ellipse(
			(leftX + rightX) / 2 + base_x, (leftY + rightY) / 2 + base_y,
			distL2R / 2, distL2R / 8,
			angleL2R, // ����Ƕ���Ĳ�̫�á�Ӧ��ͨ�������������ó���
			false, CANVAS_HALF_WIDTH / 18, OUTLINE_COLOR
		);

		hdc_triangle(
			topX + base_x, topY + base_y, rightX + base_x, rightY + base_y,
			leftX + base_x, leftY + base_y, true, 1, CLOAK_COLOR
		);

		hdc_ellipse(
			(topX + rightX) / 2 + base_x, (topY + rightY) / 2 + base_y,
			distT2R / 2, distT2R / 15,
			angleT2R, // ����Ƕ���Ĳ�̫�á�Ӧ��ͨ�������������ó���
			true, 1, CLOAK_COLOR
		);
		hdc_ellipse((topX + leftX) / 2 + base_x, (topY + leftY) / 2 + base_y,
			distL2T / 2, distL2T / 15,
			angleL2T, // ����Ƕ���Ĳ�̫�á�Ӧ��ͨ�������������ó���
			true, 1, CLOAK_COLOR
		);
		hdc_ellipse(
			(leftX + rightX) / 2 + base_x, (leftY + rightY) / 2 + base_y,
			distL2R / 2, distL2R / 8,
			angleL2R, // ����Ƕ���Ĳ�̫�á�Ӧ��ͨ�������������ó���
			true, 1, CLOAK_COLOR
		);
	}
}

// ����Ͳ�ͱ����
static void drawIceCreamCone(const int base_x, const int base_y)
{
	// �ֱ�
	hdc_rectangle(
		-CANVAS_HALF_WIDTH / 2 + base_x, -CANVAS_HALF_HEIGHT / 18 + base_y,
		CANVAS_HALF_WIDTH * 8 / 9, CANVAS_HALF_HEIGHT * 2 / 27,
		82, true, 1, CONE_PRIMARY_COLOR
	);
	hdc_rectangle(
		-CANVAS_HALF_WIDTH / 2 + base_x, -CANVAS_HALF_HEIGHT / 18 + base_y,
		CANVAS_HALF_WIDTH * 8 / 9, CANVAS_HALF_HEIGHT * 2 / 27,
		82, false, CANVAS_HALF_HEIGHT / 36, OUTLINE_COLOR
	);

	// ��Ͳ������
	hdc_triangle(
		-CANVAS_HALF_WIDTH * 13 / 18 + base_x, -CANVAS_HALF_HEIGHT / 2 + base_y, // ��
		-CANVAS_HALF_WIDTH * 4 / 9 + base_x, -CANVAS_HALF_HEIGHT * 14 / 27 + base_y, // ��
		-CANVAS_HALF_WIDTH * 15 / 27 + base_x, -CANVAS_HALF_HEIGHT / 9 + base_y, // ��
		true, 1, CONE_PRIMARY_COLOR
	);
	hdc_triangle(
		-CANVAS_HALF_WIDTH * 13 / 18 + base_x, -CANVAS_HALF_HEIGHT / 2 + base_y, // ��
		-CANVAS_HALF_WIDTH * 4 / 9 + base_x, -CANVAS_HALF_HEIGHT * 14 / 27 + base_y, // ��
		-CANVAS_HALF_WIDTH * 15 / 27 + base_x, -CANVAS_HALF_HEIGHT / 9 + base_y, // ��
		false, CANVAS_HALF_HEIGHT / 36, OUTLINE_COLOR
	);

	// ��Ͳ�м��Բ��
	hdc_ellipse(
		-CANVAS_HALF_WIDTH * 29 / 54 + base_x, -CANVAS_HALF_HEIGHT / 12 + base_y,
		CANVAS_HALF_WIDTH / 19, CANVAS_HALF_HEIGHT / 30, -9,
		true, 1, CONE_PRIMARY_COLOR
	);
	hdc_ellipse(
		-CANVAS_HALF_WIDTH * 29 / 54 + base_x, -CANVAS_HALF_HEIGHT / 12 + base_y,
		CANVAS_HALF_WIDTH / 19, CANVAS_HALF_HEIGHT / 30, -9,
		false, CANVAS_HALF_HEIGHT / 36, OUTLINE_COLOR
	);
	hdc_ellipse(
		-CANVAS_HALF_WIDTH * 15 / 27 + base_x, -CANVAS_HALF_HEIGHT * 5 / 36 + base_y, 
		CANVAS_HALF_WIDTH / 18, CANVAS_HALF_HEIGHT / 28, -9,
		true, 1, CONE_PRIMARY_COLOR
	);
	hdc_ellipse(
		-CANVAS_HALF_WIDTH * 15 / 27 + base_x, -CANVAS_HALF_HEIGHT * 5 / 36 + base_y,
		CANVAS_HALF_WIDTH / 18, CANVAS_HALF_HEIGHT / 28, -9,
		false, CANVAS_HALF_HEIGHT / 36, OUTLINE_COLOR
	);

	// ��������Ͳ���
	struct {
		int centerX;
		int centerY;
		int radiusA;
		int radiusB;
		int rotation;
	} ellipse[3] = {
		{
			-CANVAS_HALF_WIDTH * 63 / 108, -CANVAS_HALF_HEIGHT * 38 / 72, 
			CANVAS_HALF_WIDTH / 8, CANVAS_HALF_WIDTH / 24, -2
		},
		{
			-CANVAS_HALF_WIDTH * 16 / 27, -CANVAS_HALF_HEIGHT * 41 / 72,
			CANVAS_HALF_WIDTH / 10, CANVAS_HALF_WIDTH / 18, 3
		},
		{
			-CANVAS_HALF_WIDTH * 16 / 27, -CANVAS_HALF_HEIGHT * 44 / 72,
			CANVAS_HALF_WIDTH / 12, CANVAS_HALF_WIDTH / 13, 1
		}
	};
	for (int i = 0; i < 6; i++) {
		hdc_ellipse(
			ellipse[i % 3].centerX + base_x, ellipse[i % 3].centerY + base_y,
			ellipse[i % 3].radiusA, ellipse[i % 3].radiusB,
			ellipse[i % 3].rotation,
			i >= 3, (i < 3 ? CANVAS_HALF_HEIGHT / 18 : 1),
			(i < 3 ? OUTLINE_COLOR : ICE_CREAM_COLOR)
		);
	}


}

// �����壨���֣�
static void drawBody(const int base_x, const int base_y)
{

	// ԲԲ�Ķ��ӣ�����ߣ�
	hdc_ellipse(
		CANVAS_HALF_WIDTH * 2 / 27 + base_x, CANVAS_HALF_HEIGHT * 7 / 18 + base_y,
		CANVAS_HALF_WIDTH * 6 / 12, CANVAS_HALF_HEIGHT * 5 / 9,
		0, false, CANVAS_HALF_WIDTH / 18, OUTLINE_COLOR
	);

	// ����
	hdc_ellipse(
		-CANVAS_HALF_WIDTH * 13 / 27 + base_x, CANVAS_HALF_HEIGHT * 4 / 27 + base_y,
		CANVAS_HALF_WIDTH * 1 / 6, CANVAS_HALF_HEIGHT * 1 / 14,
		40, true, 1, SKIN_COLOR
	);
	hdc_ellipse(
		-CANVAS_HALF_WIDTH * 13 / 27 + base_x, CANVAS_HALF_HEIGHT * 4 / 27 + base_y,
		CANVAS_HALF_WIDTH * 1 / 6, CANVAS_HALF_HEIGHT * 1 / 14,
		40, false, CANVAS_HALF_WIDTH / 36, OUTLINE_COLOR
	);
	
	// ����
	hdc_ellipse(
		CANVAS_HALF_WIDTH * 31 / 54 + base_x, CANVAS_HALF_HEIGHT * 1 / 3 + base_y,
		CANVAS_HALF_WIDTH * 1 / 6, CANVAS_HALF_HEIGHT * 1 / 14,
		72, true, 1, SKIN_COLOR
	);
	hdc_ellipse(
		CANVAS_HALF_WIDTH * 31 / 54 + base_x, CANVAS_HALF_HEIGHT * 1 / 3 + base_y,
		CANVAS_HALF_WIDTH * 1 / 6, CANVAS_HALF_HEIGHT * 1 / 14,
		72, false, CANVAS_HALF_WIDTH / 36, OUTLINE_COLOR
	);


	// ԲԲ�Ķ��ӣ�Ƥ����
	hdc_ellipse(
		CANVAS_HALF_WIDTH * 2 / 27 + base_x, CANVAS_HALF_HEIGHT * 7 / 18 + base_y,
		CANVAS_HALF_WIDTH * 6 / 12, CANVAS_HALF_HEIGHT * 5 / 9,
		0, true, 1, SKIN_COLOR
	);
}

/* ��ʦ�������ֺ�������ע�ͣ����� */
void hdc_draw_cartoon_2051565(const int base_x, const int base_y)
{
	hdc_cls(); // �������Ļ

	// ����
	hdc_rectangle(base_x - CANVAS_HALF_WIDTH, base_y - CANVAS_HALF_HEIGHT, CANVAS_WIDTH, CANVAS_HEIGHT, 0, true, 1, BACKGROUND_COLOR);

	// ��ӭ��
	sayHello();

	drawCloakBack(base_x, base_y);
	drawBody(base_x, base_y);
	drawCloakCollar(base_x, base_y);
	drawCuteHead(base_x, base_y);
	drawCrown(base_x, base_y);
	drawIceCreamCone(base_x, base_y);
}
