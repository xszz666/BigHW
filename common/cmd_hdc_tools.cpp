/* 2152611 邹良顺 信02*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include "../include/cmd_hdc_tools.h"
using namespace std;

#if !HDC_SERIES_BY_TEACHER	//未定义的情况下才打开条件编译

/* 允许添加需要的头文件 */

extern "C" WINBASEAPI HWND WINAPI GetConsoleWindow(); //VS中此处会有波浪线，不影响正常使用

/* 已定义的静态全局变量 */
static HWND hWnd = GetConsoleWindow();
static HDC hdc = NULL;
static const double PI = 3.14159;
static int _BgColor_, _FgColor_, _Width_, _High;
static int _Delay_ms;

/* 允许适度使用静态全局变量，但仅限static，即外部不可见 */
static int direction = 1;
static int start_angle = 0;
/* 此处允许添加自定义函数，但仅限static，即外部不可见 */
static int Max(int x1, int x2, int x3)
{
	int max = x1 > x2 ? x1 : x2;
	max = max > x3 ? max : x3;
	return max;
}
static int Min(int x1, int x2, int x3)
{
	int max = x1 < x2 ? x1 : x2;
	max = max < x3 ? max : x3;
	return max;
}
//是否在图形内部
static bool if_in(int x, int y, int x1, int x2, int x3, int y1, int y2, int y3)
{
	if (fabs(x1 * y2 + x2 * y3 + x3 * y1 - x1 * y3 - x2 * y1 - x3 * y2) == (fabs(x * y2 + x2 * y3 + x3 * y - x * y3 - x2 * y - x3 * y2) + fabs(x1 * y + x * y3 + x3 * y1 - x1 * y3 - x * y1 - x3 * y) + fabs(x1 * y2 + x2 * y + x * y1 - x1 * y - x2 * y1 - x * y2)))
		return 1;
	else
		return 0;
}
/* 下面给出了几个基本函数的完整实现，不要改动 */
/***************************************************************************
  函数名称：
  功    能：初始化
  输入参数：const int bgcolor：背景色
			const int fgcolor：前景色
			const int width  ：屏幕宽度（点阵）
			const int high   ：屏幕高度（点阵）
  返 回 值：
  说    明：
***************************************************************************/
void hdc_init(const int bgcolor, const int fgcolor, const int width, const int high)
{
	/* 先释放，防止不release而再次init（hdc_release可重入） */
	hdc_release();

	/* 窗口init后，用一个静态全局量记录，后续hdc_cls()会用到 */
	_BgColor_ = bgcolor;
	_FgColor_ = fgcolor;
	_Width_ = width;
	_High = high;

	hdc = GetDC(hWnd);

	cct_setcursor(CURSOR_INVISIBLE);
	cct_setcolor(bgcolor, fgcolor);
	cct_setfontsize("点阵字体", 16);
	cct_setconsoleborder(width / 8 + !!(width % 8), high / 16 + !!(high % 16)); //将点阵的宽度及高度转换为特定字体的行列数，!!的含义：如果不是8/16的倍数，行列多+1
	cct_cls();
}

/***************************************************************************
  函数名称：
  功    能：释放画图资源
  输入参数：
  返 回 值：
  说    明：可重入
***************************************************************************/
void hdc_release()
{
	if (hdc) {
		ReleaseDC(hWnd, hdc);
		hdc = NULL;
		cct_setcursor(CURSOR_VISIBLE_NORMAL);
	}
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void hdc_set_delay(int ms)
{
	if (ms > 0)
		_Delay_ms = ms;
	else
		_Delay_ms = 0;
}

/***************************************************************************
  函数名称：
  功    能：设置画笔颜色，传入RGB值
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void hdc_set_pencolor(const int RGB_value)
{
	SelectObject(hdc, GetStockObject(DC_PEN));
	SetDCPenColor(hdc, RGB_value);
}

/***************************************************************************
  函数名称：
  功    能：设置画笔颜色，传入RGB三色，值0-255
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void hdc_set_pencolor(const unsigned char red, const unsigned char green, const unsigned char blue)
{
	hdc_set_pencolor(RGB(red, green, blue));
}

/***************************************************************************
  函数名称：
  功    能：清除屏幕上现有的图形
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void hdc_cls()
{
	/* 发现一定要换一种颜色初始化才能清除像素点，找到更简便方法的同学可以通知我 */
	hdc_init(_BgColor_, (_FgColor_ + 1) % 16, _Width_, _High);

	hdc_init(_BgColor_, _FgColor_, _Width_, _High);

	/* 部分机器上运行demo时，会出现hdc_cls()后第一根线有缺线的情况，加延时即可
	   如果部分机器运行还有问题，调高此延时值 */
	Sleep(30);
}

/***************************************************************************
  函数名称：
  功    能：在(x,y)位置处用指定颜色画出一个像素点
  输入参数：const int x：x坐标，左上角为(0,0)
			const int y：y坐标，左上角为(0,0)
  返 回 值：
  说    明：颜色直接用当前设定，可以在调用处指定
***************************************************************************/
static inline void hdc_base_point(const int x, const int y)
{
	MoveToEx(hdc, x - 1, y - 1, NULL);
	LineTo(hdc, x, y);
	if (_Delay_ms > 0)
		Sleep(_Delay_ms);
}

/***************************************************************************
  函数名称：
  功    能：在(x1,y1)-(x2,y2)之间画出一个像素点的连线
  输入参数：const int x1：起点x坐标，左上角为(0,0)
			const int y1：起点y坐标，左上角为(0,0)
			const int x2：终点y坐标，左上角为(0,0)
			const int y2：终点y坐标，左上角为(0,0)
  返 回 值：
  说    明：颜色直接用当前设定
***************************************************************************/
static inline void hdc_base_line(const int x1, const int y1, const int x2, const int y2)
{
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
	if (_Delay_ms > 0)
		Sleep(_Delay_ms);
}

/***************************************************************************
  函数名称：
  功    能：在(x,y)位置处用指定颜色画一个指定粗细的点(用画实心圆来模拟)
  输入参数：const int x			：x坐标，左上角为(0,0)
			const int y			：y坐标，左上角为(0,0)
			const int thickness	：点的粗细，下限位1，上限不限(如过大会导致不完全填充)（有缺省值）
			const int RGB_value	：点的颜色（有缺省值）
  返 回 值：
  说    明：改进运行效率
***************************************************************************/
void hdc_point(const int x, const int y, const int thickness, const int RGB_value)
{
	int tn = thickness;
	if (tn < 1)
		tn = 1;		//处理下限
	/* 不卡点直径的上限，但是单上限超过一定大小是，画出的圆部分位置未实心 */
	const int tn_end = (tn <= 1) ? 1 : tn / 2;

	if (RGB_value != INVALID_RGB)
		hdc_set_pencolor(RGB_value);

	for (int i = x - thickness / 2; i <= x + thickness / 2; i++)
		for (int j = y - thickness / 2; j <= y + thickness / 2; j++)
			if ((x - i) * (x - i) + (y - j) * (y - j) <= thickness * thickness / 4)
				hdc_base_point(i, j);

}

/* -------------------------------------------------------------------------
	给出下列函数的实现，函数名及参数表不准改动
	1、不需要调用系统的其他有关图形操作的函数
	2、下列函数的实现都基于hdc_base_point/hdc_base_line函数的组合
	3、想一想，是不是所有函数都需要给出独立的实现过程？应该先实现哪些函数？
	4、填充是实现中最复杂的部分
	5、系统的角度与函数参数中的角度含义相差180°
   ------------------------------------------------------------------------- */

   /***************************************************************************
	 函数名称：
	 功    能：画线段
	 输入参数：const int x1		：起点的x
			   const int y1		：起点的y
			   const int x2		：终点的x
			   const int y2		：终点的y
			   const int thickness	：线段的粗细（有缺省值）
			   const int RGB_value	：线段的颜色（有缺省值）
	 返 回 值：
	 说    明：本函数可以用基于hdc_point的组合（速度慢）
					 也可以用hdc_base_point/hdc_base_line的组合（速度快）
   ***************************************************************************/
void hdc_line(const int x1, const int y1, const int x2, const int y2, const int thickness, const int RGB_value)
{
	int x11, y11, x22, y22, old_x1 = INT_MAX, old_y1 = INT_MAX;

	if (RGB_value != INVALID_RGB)
		hdc_set_pencolor(RGB_value);

	hdc_base_line(x1, y1, x2, y2);
	for (int level = 1; level <= thickness / 2; level++)
	{
		for (int angle = 0; angle <= 360; angle++)
		{
			x11 = x1 + (int)(level * sin(angle * PI / 180));
			y11 = y1 - (int)(level * cos(angle * PI / 180));
			x22 = x2 + (int)(level * sin(angle * PI / 180));
			y22 = y2 - (int)(level * cos(angle * PI / 180));

			if (x11 != old_x1 || y11 != old_y1)
			{
				old_x1 = x11;
				old_y1 = y11;

				hdc_base_line(x11, y11, x22, y22);
			}
		}
	}
	if (thickness % 2 == 0)
	{
		if (y1 == y2 || fabs((x1 - x2) / (y1 - y2)) >= 1)
		{
			x11 = x1;
			y11 = y1 - (int)((thickness / 2 + 1));
			x22 = x2;
			y22 = y2 - (int)((thickness / 2 + 1));

			hdc_base_line(x11, y11, x22, y22);
		}
		else
		{
			x11 = x1 - (int)((thickness / 2));
			y11 = y1;
			x22 = x2 - (int)((thickness / 2));
			y22 = y2;

			hdc_base_line(x11, y11, x22, y22);
		}
	}
}

/***************************************************************************
  函数名称：
  功    能：给出三点的坐标，画一个三角形
  输入参数：const int x1		：第1个点的x
			const int y1		：第1个点的y
			const int x2		：第2个点的x
			const int y2		：第2个点的y
			const int x3		：第3个点的x
			const int y3		：第3个点的y
			bool filled			：是否需要填充（有缺省值）
			const int thickness	：边的粗细（有缺省值）
			const int RGB_value	：颜色（有缺省值）
  返 回 值：
  说    明：不判断三点是否共线，如果共线，划出一条直线即可
***************************************************************************/
void hdc_triangle(const int x1, const int y1, const int x2, const int y2, const int x3, const int y3, bool filled, const int thickness, const int RGB_value)
{
	if (RGB_value != INVALID_RGB)
		hdc_set_pencolor(RGB_value);

	hdc_line(x1, y1, x2, y2, thickness, RGB_value);
	hdc_line(x3, y3, x2, y2, thickness, RGB_value);
	hdc_line(x1, y1, x3, y3, thickness, RGB_value);
	if (filled)
	{
		int max_x = Max(x1, x2, x3), max_y = Max(y1, y2, y3), min_x = Min(x1, x2, x3), min_y = Min(y1, y2, y3);
		for (int x = min_x; x <= max_x; x++)
			for (int y = min_y; y <= max_y; y++)
				if (if_in(x, y, x1, x2, x3, y1, y2, y3) == 1)
					hdc_point(x, y, 1, RGB_value);
	}
}

/***************************************************************************
  函数名称：
  功    能：给出左上角坐标及宽度、高度，画出一个长方形
  输入参数：const int left_up_x			：左上角x
			const int left_up_y			：左上角y
			const int width				：宽度
			const int high				：高度
			const int rotation_angles	：以左上角为支点，与x轴的旋转倾角（向下转为正）
			bool filled					：是否需要填充（有缺省值）
			const int thickness			：边的粗细（有缺省值）
			const int RGB_value			：颜色（有缺省值）
  返 回 值：
  说    明：
***************************************************************************/
void hdc_rectangle(const int left_up_x, const int left_up_y, const int width, const int high, const int rotation_angles, const bool filled, const int thickness, const int RGB_value)
{
	int x1 = left_up_x, y1 = left_up_y, x2, x3, x4, y2, y3, y4;

	if (RGB_value != INVALID_RGB)
		hdc_set_pencolor(RGB_value);

	x2 = left_up_x + (int)(width * cos(rotation_angles * PI / 180));
	y2 = left_up_y + (int)(width * sin(rotation_angles * PI / 180));

	x3 = left_up_x - (int)(high * sin(rotation_angles * PI / 180));
	y3 = left_up_y + (int)(high * cos(rotation_angles * PI / 180));

	x4 = x3 + (int)(width * cos(rotation_angles * PI / 180));
	y4 = y3 + (int)(width * sin(rotation_angles * PI / 180));

	hdc_line(x1, y1, x2, y2, thickness, RGB_value);
	hdc_line(x3, y3, x4, y4, thickness, RGB_value);
	hdc_line(x1, y1, x3, y3, thickness, RGB_value);
	hdc_line(x4, y4, x2, y2, thickness, RGB_value);

	if (filled)
	{
		int max_x = Max(x1, x2, x3) > x4 ? Max(x1, x2, x3) : x4, max_y = Max(y1, y2, y3) > y4 ? Max(y1, y2, y3) : y4, min_x = Min(x1, x2, x3) < x4 ? Min(x1, x2, x3) : x4, min_y = Min(y1, y2, y3) < y4 ? Min(y1, y2, y3) : y4;
		for (int x = min_x; x <= max_x; x++)
			for (int y = min_y; y <= max_y; y++)
				if (if_in(x, y, x1, x2, x3, y1, y2, y3) == 1 || if_in(x, y, x4, x2, x3, y4, y2, y3) == 1)
					hdc_point(x, y, 1, RGB_value);
	}
}

/***************************************************************************
  函数名称：
  功    能：给出左上角坐标及边长，画出一个长方形
  输入参数：const int left_up_x			：左上角x
			const int left_up_y			：左上角y
			const int length			：边长
			const int rotation_angles	：以左上角为支点，与x轴的旋转倾角（向下转为正）（有缺省值）
			const bool filled			：是否需要填充（有缺省值）
			const int thickness			：边的粗细（有缺省值）
			const int RGB_value			：颜色（有缺省值）
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void hdc_square(const int left_up_x, const int left_up_y, const int length, const int rotation_angles, const bool filled, const int thickness, const int RGB_value)
{
	hdc_rectangle(left_up_x, left_up_y, length, length, rotation_angles, filled, thickness, RGB_value);
}

/***************************************************************************
  函数名称：
  功    能：按照给出的参数画一段圆弧
  输入参数：const int point_x		：圆心的x
			const int point_y		：圆心的y
			const int radius		：半径
			const int angle_begin	：起始角度（以圆的最上方为0°，顺时针为正，注意：与系统坐标差了180°!!!）（有缺省值）
			const int angle_end		：结束角度（同上）（有缺省值）
			const int thickness		：粗细（有缺省值）
			const int RGB_value		：颜色（有缺省值）
  返 回 值：
  说    明：
***************************************************************************/
void hdc_arc(const int point_x, const int point_y, const int radius, const int angle_begin, const int angle_end, const int thickness, const int RGB_value)
{
	int end, beg;
	if (direction == 1)
	{
		beg = angle_begin + start_angle;
		end = angle_end + start_angle;
	}
	else
	{
		end = -(angle_begin + start_angle);
		beg = -(angle_end + start_angle);
	}
	while (end <= beg)
		end += 360;

	while (end-beg>360)
		beg += 360;

	int x, y, old_x = point_x + (int)(radius * sin(beg * PI / 180)), old_y = point_y - (int)(radius * cos(beg * PI / 180));

	if (RGB_value != INVALID_RGB)
		hdc_set_pencolor(RGB_value);

	for (int angle = beg; angle <= end; angle++)
	{
		x = point_x + (int)(radius * sin(angle * PI / 180));
		y = point_y - (int)(radius * cos(angle * PI / 180));
		hdc_line(old_x, old_y, x, y, thickness, RGB_value);
		old_x = x;
		old_y = y;
	}
}

/***************************************************************************
  函数名称：
  功    能：按照给出的参数画一个扇形
  输入参数：const int point_x		：圆心的x
			const int point_y		：圆心的y
			const int radius		：半径
			const int angle_begin	：起始角度（以圆的最上方为0°，顺时针为正，注意：与系统坐标差了180°!!!）（有缺省值）
			const int angle_end		：结束角度（同上）（有缺省值）
			const bool filled		：是否需要填充（有缺省值）
			const int thickness		：粗细（有缺省值）
			const int RGB_value		：颜色（有缺省值）
  输入参数：
  返 回 值：
  说    明：当起始/结束角度差值为360的倍数时，不画两条边
***************************************************************************/
void hdc_sector(const int point_x, const int point_y, const int radius, const int angle_begin, const int angle_end, const bool filled, const int thickness, const int RGB_value)
{
	int endd, beg;
	if (direction == 1)
	{
		beg = angle_begin + start_angle;
		endd = angle_end + start_angle;
	}
	else
	{
		endd = -(angle_begin + start_angle);
		beg = -(angle_end + start_angle);
	}
	int x1 = point_x, y1 = point_y, x2 = point_x + (int)(radius * sin(beg * PI / 180)), y2 = point_y - (int)(radius * cos(beg * PI / 180)), x3 = point_x + (int)(radius * sin(endd * PI / 180)), y3 = point_y - (int)(radius * cos(endd * PI / 180));

	if (RGB_value != INVALID_RGB)
		hdc_set_pencolor(RGB_value);

	while (endd <= beg)
		endd += 360;

	while (endd - beg > 360)
		beg += 360;

	hdc_arc(point_x, point_y, radius, beg, endd, thickness, RGB_value);

	if (filled)
	{
		int end = endd;


		for (int i = point_x - radius ; i <= point_x + radius ; i++)
			for (int j = point_y - radius ; j <= point_y + radius ; j++)
			{
				for (int angle = beg+1; angle < end; angle++)
				{				

					if (fabs(sin(angle * PI / 180) - (i - point_x) / sqrt((i - point_x)* (i - point_x)+ (j - point_y)*(j - point_y))) <= 0.01 && fabs(cos(angle * PI / 180) + (j - point_y) / sqrt((i - point_x) * (i - point_x) + (j - point_y) * (j - point_y))) <= 0.01)
						if ((point_x - i) * (point_x - i) + (point_y - j) * (point_y - j) <= radius * radius)
							hdc_point(i, j);
				}
				
			}
	}
	if ((beg- endd) % 360 != 0)
	{
		hdc_line(point_x, point_y, x2, y2, thickness, RGB_value);
		hdc_line(point_x, point_y, x3, y3, thickness, RGB_value);
	}
}

/***************************************************************************
  函数名称：
  功    能：按照给出的参数画一个圆
  输入参数：const int point_x		：圆心的x
			const int point_y		：圆心的y
			const int radius		：半径
			const bool filled		：是否需要填充（有缺省值）
			const int thickness		：粗细（有缺省值）
			const int RGB_value		：颜色（有缺省值）
  返 回 值：
  说    明：
***************************************************************************/
void hdc_circle(const int point_x, const int point_y, const int radius, const bool filled, const int thickness, const int RGB_value)
{
	if (RGB_value != INVALID_RGB)
		hdc_set_pencolor(RGB_value);

	hdc_arc(point_x, point_y, radius, 0, 360, thickness, RGB_value);
	if (filled)		
		hdc_point(point_x, point_y, radius*2, RGB_value);

}

/***************************************************************************
  函数名称：
  功    能：按照给出的参数画一个椭圆
  输入参数：const int point_x			：圆心的x
			const int point_y			：圆心的y
			const int radius_a			：平行于X轴的半径
			const int radius_b			：平行于Y轴的半径
			const int rotation_angles	：以圆心为支点，与x轴的旋转倾角（向下转为正）（有缺省值）
			const bool filled			：是否需要填充（有缺省值）
			const int thickness			：粗细（有缺省值）
			const int RGB_value			：颜色（有缺省值）
  返 回 值：
  说    明：
***************************************************************************/
void hdc_ellipse(const int point_x, const int point_y, const int radius_a, const int radius_b, const int rotation_angles, const bool filled, const int thickness, const int RGB_value)
{
	int x, y, old_x = INT_MAX, old_y = INT_MAX, x_c, x_cc, y_c, y_cc;
	if (RGB_value != INVALID_RGB)
		hdc_set_pencolor(RGB_value);

	int radius_c = (int)sqrt(fabs(radius_a * radius_a - radius_b * radius_b));
	int angle = rotation_angles;//解决焦点在纵轴的问题

	if (radius_a < radius_b)
	{
		y_c = point_y + (int)(radius_c * cos(angle * PI / 180)), x_c = point_x - (int)(radius_c * sin(angle * PI / 180));//右焦点
		y_cc = point_y - (int)(radius_c * cos(angle * PI / 180)), x_cc = point_x + (int)(radius_c * sin(angle * PI / 180));//左焦点
	}
	else
	{
		x_c = point_x + (int)(radius_c * cos(angle * PI / 180)), y_c = point_y + (int)(radius_c * sin(angle * PI / 180));//右焦点
		x_cc = point_x - (int)(radius_c * cos(angle * PI / 180)), y_cc = point_y - (int)(radius_c * sin(angle * PI / 180));//左焦点
	}
	int max = radius_a > radius_b ? radius_a : radius_b;
	for (x = -max; x <= max; x++)
		for (y = -max; y <= max; y++)
			if (fabs(2 * max - (sqrt((x + point_x - x_c) * (x + point_x - x_c) + (y + point_y - y_c) * (y + point_y - y_c)) + sqrt((x + point_x - x_cc) * (x + point_x - x_cc) + (y + point_y - y_cc) * (y + point_y - y_cc)))) < 1)
			{
				hdc_point(x + point_x, y + point_y, thickness, RGB_value);
				if (filled)
				{
					old_x = (old_x == INT_MAX ? x : old_x);
					old_y = (old_y == INT_MAX ? y : old_y);
					hdc_line(old_x + point_x, old_y + point_y, x + point_x, y + point_y, 1, RGB_value);
					old_x = x;
					old_y = y;
				}
			}
}

#endif !HDC_SERIES_BY_TEACHER
