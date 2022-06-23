/* 2051565 大数据 龚天遥 */
// 卡通人物
// 默认基准点值是 (400, 400)
// 禁止递归和循环

// 蜜雪冰城 logo
// 设计画布大小默认为 600 × 600
// 雪王肚子为中心点

#include <iostream>
#include <cmath>
using namespace std;

// 不可加入除此之外的自定义头文件
#include "../include/cmd_hdc_tools.h"

/** 画布宽度。 */
static const int CANVAS_WIDTH = 600;
/** 画布高度。 */
static const int CANVAS_HEIGHT = 600;

/**
 * 以下参数可以控制图片颜色。按照 8 bit BGR 格式设置。
 */
/** 背景颜色。 */
static const int BACKGROUND_COLOR = 0x5600e6;
/** 身体皮肤颜色。 */
static const int SKIN_COLOR = 0xffffff;
/** 身体边缘线颜色。 */
static const int OUTLINE_COLOR = 0x000000;
/** 皇冠颜色。 */
static const int CROWN_COLOR = 0xffffff;
/** 冰淇淋颜色。 */
static const int ICE_CREAM_COLOR = 0xffffff;
/** 蛋筒主体颜色。 */
static const int CONE_PRIMARY_COLOR = 0x36c6fd;
/** 蛋筒条纹颜色。（暂时为用到） */
static const int CONE_TEXTURE_COLOR = 0x0094f3;
/** 眼珠瞳孔颜色。 */
static const int EYE_PUPIL_COLOR = 0x89330c;
/** 嘴颜色。 */
static const int MOUTH_COLOR = 0x89330c;
/** 舌头颜色。 */
static const int TONGUE_COLOR = 0x5600e6;
/** 鼻子颜色。 */
static const int NOSE_COLOR = 0x0197f2;
/** 斗篷颜色。 */
static const int CLOAK_COLOR = 0x5600e6;

/** 画布半宽度。（该参数不许改） */
static const int CANVAS_HALF_WIDTH = CANVAS_WIDTH / 2;
/** 画布半高度。（该参数不许改） */
static const int CANVAS_HALF_HEIGHT = CANVAS_HEIGHT / 2;

/**
 * 返回一个数字的平方。
 *
 * @param x - 要被平方的数。
 * @return x 的平方。
 */
template <typename T>
static inline T pow2(const T x)
{
	return x * x;
}

// 输出欢迎词：蜜雪冰城甜蜜蜜~~
static void sayHello()
{
	cct_gotoxy(0, 0);
	cout << "你爱我~~ ╰(*°▽°*)╯" << endl
	     << "我爱你~~ O(∩_∩)O" << endl
	 	 << "蜜雪冰城甜蜜蜜~~ q(≧▽≦q)" << endl;
}

// 画一个圆圆的小脑袋
static void drawCuteHead(const int base_x, const int base_y)
{
	// 头背景
	hdc_ellipse(
		base_x + CANVAS_HALF_WIDTH * 2 / 27, base_y - CANVAS_HALF_HEIGHT * 5 / 18,
		CANVAS_HALF_WIDTH * 7 / 18, CANVAS_HALF_HEIGHT * 16 / 54,
		0, true, 1, SKIN_COLOR
	);

	// 头边框
	hdc_ellipse(
		base_x + CANVAS_HALF_WIDTH * 2 / 27, base_y - CANVAS_HALF_HEIGHT * 5 / 18,
		CANVAS_HALF_WIDTH * 7 / 18, CANVAS_HALF_HEIGHT * 16 / 54,
		0, false, CANVAS_HALF_WIDTH / 36, OUTLINE_COLOR
	);

	// 画眼睛
	int pupilCenterX[2] = {
		-CANVAS_HALF_WIDTH / 27,
		CANVAS_HALF_WIDTH / 5
	};
	int pupilCenterY[2] = {
		-CANVAS_HALF_HEIGHT * 13 / 36,
		-CANVAS_HALF_HEIGHT * 13 / 36
	};
	
	for (int i = 0; i < 2; i++) {
		// 瞳孔
		hdc_ellipse(
			pupilCenterX[i] + base_x, pupilCenterY[i] + base_y,
			CANVAS_HALF_HEIGHT / 12, CANVAS_HALF_WIDTH / 18,
			100, true, 1, EYE_PUPIL_COLOR
		);
		// 瞳孔反光
		hdc_ellipse(
			pupilCenterX[i] + CANVAS_HALF_WIDTH / 18 + base_x,
			pupilCenterY[i] + CANVAS_HALF_HEIGHT / 72 + base_y,
			CANVAS_HALF_HEIGHT / 18, CANVAS_HALF_WIDTH / 27,
			100, true, 1, SKIN_COLOR
		);
	}

	// 鼻子
	int leftTopX = CANVAS_HALF_WIDTH / 9;
	int leftDownX = CANVAS_HALF_WIDTH / 12;
	int leftTopY = -CANVAS_HALF_HEIGHT / 3;
	int leftDownY = -CANVAS_HALF_HEIGHT / 5;
	int dist = int(sqrt(pow2(leftTopX - leftDownX) + pow2(leftTopY - leftDownY)));
	hdc_triangle(
		CANVAS_HALF_WIDTH * 5 / 18 + base_x, base_y - CANVAS_HALF_HEIGHT * 5 / 18, // 右顶点
		leftTopX + base_x, base_y + leftTopY, // 左上
		leftDownX + base_x, base_y + leftDownY, // 左下
		true, 1, NOSE_COLOR
	);
	hdc_ellipse(
		(leftTopX + leftDownX) / 2 + base_x, (leftTopY + leftDownY) / 2 + base_y, dist / 2, dist / 4,
		105, // 这个角度算的不太好。应该通过两点坐标计算得出。
		true, 1, NOSE_COLOR
	);

	// 嘴
	hdc_arc(
		CANVAS_HALF_WIDTH * 2 / 27 + base_x, base_y - CANVAS_HALF_HEIGHT * 17 / 45,
		CANVAS_HALF_HEIGHT / 4, 130, 210, CANVAS_HALF_HEIGHT / 45, MOUTH_COLOR
	);

	// 舌头
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
		58, // 这个角度算的不太好。应该通过两点坐标计算得出。
		true, 1, TONGUE_COLOR
	); 
	hdc_ellipse(
		(topX + leftX) / 2 + base_x, (topY + leftY) / 2 + base_y, 
		distLeftToTop / 2, distLeftToTop / 4,
		-48, // 这个角度算的不太好。应该通过两点坐标计算得出。
		true, 1, TONGUE_COLOR
	); 
	hdc_ellipse(
		(leftX + rightDownX) / 2 + base_x, (leftY + rightDownY) / 2 + base_y, 
		distLeftToRD / 2, distLeftToRD / 6,
		27, // 这个角度算的不太好。应该通过两点坐标计算得出。
		true, 1, TONGUE_COLOR
	);
}

// 画皇冠
static void drawCrown(const int base_x, const int base_y)
{
	for (int isFilled = 0; isFilled < 2; isFilled += 1) {
		// 皇冠上的圆环
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
		// 三个三角形
		int yDelta = CANVAS_HALF_HEIGHT * 1 / 100; // 纵向微调
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
		// 圆润皇冠底部
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

// 画斗篷（身后部分）
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

	// 外框线
	hdc_ellipse(
		(topX + rightX) / 2 + base_x, (topY + rightY) / 2 + base_y,
		distT2R / 2, distT2R / 15,
		angleT2R, // 这个角度算的不太好。应该通过两点坐标计算得出。
		false, CANVAS_HALF_WIDTH / 18, OUTLINE_COLOR
	);
	hdc_ellipse((topX + leftX) / 2 + base_x, (topY + leftY) / 2 + base_y,
		distL2T / 2, distL2T / 15,
		angleL2T, // 这个角度算的不太好。应该通过两点坐标计算得出。
		false, CANVAS_HALF_WIDTH / 18, OUTLINE_COLOR
	);
	hdc_ellipse(
		(leftX + rightX) / 2 + base_x, (leftY + rightY) / 2 + base_y,
		distL2R / 2, distL2R / 8,
		angleL2R, // 这个角度算的不太好。应该通过两点坐标计算得出。
		false, CANVAS_HALF_WIDTH / 18, OUTLINE_COLOR
	);

	hdc_triangle(
		topX + base_x, topY + base_y, rightX + base_x, rightY + base_y,
		leftX + base_x, leftY + base_y, true, 1, CLOAK_COLOR
	);

	hdc_ellipse(
		(topX + rightX) / 2 + base_x, (topY + rightY) / 2 + base_y,
		distT2R / 2, distT2R / 15,
		angleT2R, // 这个角度算的不太好。应该通过两点坐标计算得出。
		true, 1, CLOAK_COLOR
	);
	hdc_ellipse((topX + leftX) / 2 + base_x, (topY + leftY) / 2 + base_y,
		distL2T / 2, distL2T / 15,
		angleL2T, // 这个角度算的不太好。应该通过两点坐标计算得出。
		true, 1, CLOAK_COLOR
	);
	hdc_ellipse(
		(leftX + rightX) / 2 + base_x, (leftY + rightY) / 2 + base_y,
		distL2R / 2, distL2R / 8,
		angleL2R, // 这个角度算的不太好。应该通过两点坐标计算得出。
		true, 1, CLOAK_COLOR
	);
}

// 画斗篷（衣领）
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

		// 外框线
		hdc_ellipse(
			(topX + rightX) / 2 + base_x, (topY + rightY) / 2 + base_y,
			distT2R / 2, distT2R / 15,
			angleT2R, // 这个角度算的不太好。应该通过两点坐标计算得出。
			false, CANVAS_HALF_WIDTH / 18, OUTLINE_COLOR
		);
		hdc_ellipse((topX + leftX) / 2 + base_x, (topY + leftY) / 2 + base_y,
			distL2T / 2, distL2T / 15,
			angleL2T, // 这个角度算的不太好。应该通过两点坐标计算得出。
			false, CANVAS_HALF_WIDTH / 18, OUTLINE_COLOR
		);
		hdc_ellipse(
			(leftX + rightX) / 2 + base_x, (leftY + rightY) / 2 + base_y,
			distL2R / 2, distL2R / 8,
			angleL2R, // 这个角度算的不太好。应该通过两点坐标计算得出。
			false, CANVAS_HALF_WIDTH / 18, OUTLINE_COLOR
		);

		hdc_triangle(
			topX + base_x, topY + base_y, rightX + base_x, rightY + base_y,
			leftX + base_x, leftY + base_y, true, 1, CLOAK_COLOR
		);

		hdc_ellipse(
			(topX + rightX) / 2 + base_x, (topY + rightY) / 2 + base_y,
			distT2R / 2, distT2R / 15,
			angleT2R, // 这个角度算的不太好。应该通过两点坐标计算得出。
			true, 1, CLOAK_COLOR
		);
		hdc_ellipse((topX + leftX) / 2 + base_x, (topY + leftY) / 2 + base_y,
			distL2T / 2, distL2T / 15,
			angleL2T, // 这个角度算的不太好。应该通过两点坐标计算得出。
			true, 1, CLOAK_COLOR
		);
		hdc_ellipse(
			(leftX + rightX) / 2 + base_x, (leftY + rightY) / 2 + base_y,
			distL2R / 2, distL2R / 8,
			angleL2R, // 这个角度算的不太好。应该通过两点坐标计算得出。
			true, 1, CLOAK_COLOR
		);
	}
}

// 画蛋筒和冰淇淋
static void drawIceCreamCone(const int base_x, const int base_y)
{
	// 手柄
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

	// 蛋筒三角形
	hdc_triangle(
		-CANVAS_HALF_WIDTH * 13 / 18 + base_x, -CANVAS_HALF_HEIGHT / 2 + base_y, // 左
		-CANVAS_HALF_WIDTH * 4 / 9 + base_x, -CANVAS_HALF_HEIGHT * 14 / 27 + base_y, // 右
		-CANVAS_HALF_WIDTH * 15 / 27 + base_x, -CANVAS_HALF_HEIGHT / 9 + base_y, // 下
		true, 1, CONE_PRIMARY_COLOR
	);
	hdc_triangle(
		-CANVAS_HALF_WIDTH * 13 / 18 + base_x, -CANVAS_HALF_HEIGHT / 2 + base_y, // 左
		-CANVAS_HALF_WIDTH * 4 / 9 + base_x, -CANVAS_HALF_HEIGHT * 14 / 27 + base_y, // 右
		-CANVAS_HALF_WIDTH * 15 / 27 + base_x, -CANVAS_HALF_HEIGHT / 9 + base_y, // 下
		false, CANVAS_HALF_HEIGHT / 36, OUTLINE_COLOR
	);

	// 蛋筒中间的圆环
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

	// 冰淇淋奶油部分
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

// 画身体（含手）
static void drawBody(const int base_x, const int base_y)
{

	// 圆圆的肚子（外框线）
	hdc_ellipse(
		CANVAS_HALF_WIDTH * 2 / 27 + base_x, CANVAS_HALF_HEIGHT * 7 / 18 + base_y,
		CANVAS_HALF_WIDTH * 6 / 12, CANVAS_HALF_HEIGHT * 5 / 9,
		0, false, CANVAS_HALF_WIDTH / 18, OUTLINE_COLOR
	);

	// 左手
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
	
	// 右手
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


	// 圆圆的肚子（皮肤）
	hdc_ellipse(
		CANVAS_HALF_WIDTH * 2 / 27 + base_x, CANVAS_HALF_HEIGHT * 7 / 18 + base_y,
		CANVAS_HALF_WIDTH * 6 / 12, CANVAS_HALF_HEIGHT * 5 / 9,
		0, true, 1, SKIN_COLOR
	);
}

/* 老师点评：分函数、加注释，好评 */
void hdc_draw_cartoon_2051565(const int base_x, const int base_y)
{
	hdc_cls(); // 先清空屏幕

	// 背景
	hdc_rectangle(base_x - CANVAS_HALF_WIDTH, base_y - CANVAS_HALF_HEIGHT, CANVAS_WIDTH, CANVAS_HEIGHT, 0, true, 1, BACKGROUND_COLOR);

	// 欢迎词
	sayHello();

	drawCloakBack(base_x, base_y);
	drawBody(base_x, base_y);
	drawCloakCollar(base_x, base_y);
	drawCuteHead(base_x, base_y);
	drawCrown(base_x, base_y);
	drawIceCreamCone(base_x, base_y);
}
