/* 2152611 ����˳ ��02*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include "../include/cmd_hdc_tools.h"
using namespace std;

#if !HDC_SERIES_BY_TEACHER	//δ���������²Ŵ���������

/* ���������Ҫ��ͷ�ļ� */

extern "C" WINBASEAPI HWND WINAPI GetConsoleWindow(); //VS�д˴����в����ߣ���Ӱ������ʹ��

/* �Ѷ���ľ�̬ȫ�ֱ��� */
static HWND hWnd = GetConsoleWindow();
static HDC hdc = NULL;
static const double PI = 3.14159;
static int _BgColor_, _FgColor_, _Width_, _High;
static int _Delay_ms;

/* �����ʶ�ʹ�þ�̬ȫ�ֱ�����������static�����ⲿ���ɼ� */
static int direction = 1;
static int start_angle = 0;
/* �˴���������Զ��庯����������static�����ⲿ���ɼ� */
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
//�Ƿ���ͼ���ڲ�
static bool if_in(int x, int y, int x1, int x2, int x3, int y1, int y2, int y3)
{
	if (fabs(x1 * y2 + x2 * y3 + x3 * y1 - x1 * y3 - x2 * y1 - x3 * y2) == (fabs(x * y2 + x2 * y3 + x3 * y - x * y3 - x2 * y - x3 * y2) + fabs(x1 * y + x * y3 + x3 * y1 - x1 * y3 - x * y1 - x3 * y) + fabs(x1 * y2 + x2 * y + x * y1 - x1 * y - x2 * y1 - x * y2)))
		return 1;
	else
		return 0;
}
/* ��������˼�����������������ʵ�֣���Ҫ�Ķ� */
/***************************************************************************
  �������ƣ�
  ��    �ܣ���ʼ��
  ���������const int bgcolor������ɫ
			const int fgcolor��ǰ��ɫ
			const int width  ����Ļ��ȣ�����
			const int high   ����Ļ�߶ȣ�����
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void hdc_init(const int bgcolor, const int fgcolor, const int width, const int high)
{
	/* ���ͷţ���ֹ��release���ٴ�init��hdc_release�����룩 */
	hdc_release();

	/* ����init����һ����̬ȫ������¼������hdc_cls()���õ� */
	_BgColor_ = bgcolor;
	_FgColor_ = fgcolor;
	_Width_ = width;
	_High = high;

	hdc = GetDC(hWnd);

	cct_setcursor(CURSOR_INVISIBLE);
	cct_setcolor(bgcolor, fgcolor);
	cct_setfontsize("��������", 16);
	cct_setconsoleborder(width / 8 + !!(width % 8), high / 16 + !!(high % 16)); //������Ŀ�ȼ��߶�ת��Ϊ�ض��������������!!�ĺ��壺�������8/16�ı��������ж�+1
	cct_cls();
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ��ͷŻ�ͼ��Դ
  ���������
  �� �� ֵ��
  ˵    ����������
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
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void hdc_set_delay(int ms)
{
	if (ms > 0)
		_Delay_ms = ms;
	else
		_Delay_ms = 0;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ����û�����ɫ������RGBֵ
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void hdc_set_pencolor(const int RGB_value)
{
	SelectObject(hdc, GetStockObject(DC_PEN));
	SetDCPenColor(hdc, RGB_value);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ����û�����ɫ������RGB��ɫ��ֵ0-255
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void hdc_set_pencolor(const unsigned char red, const unsigned char green, const unsigned char blue)
{
	hdc_set_pencolor(RGB(red, green, blue));
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ������Ļ�����е�ͼ��
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void hdc_cls()
{
	/* ����һ��Ҫ��һ����ɫ��ʼ������������ص㣬�ҵ�����㷽����ͬѧ����֪ͨ�� */
	hdc_init(_BgColor_, (_FgColor_ + 1) % 16, _Width_, _High);

	hdc_init(_BgColor_, _FgColor_, _Width_, _High);

	/* ���ֻ���������demoʱ�������hdc_cls()���һ������ȱ�ߵ����������ʱ����
	   ������ֻ������л������⣬���ߴ���ʱֵ */
	Sleep(30);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���(x,y)λ�ô���ָ����ɫ����һ�����ص�
  ���������const int x��x���꣬���Ͻ�Ϊ(0,0)
			const int y��y���꣬���Ͻ�Ϊ(0,0)
  �� �� ֵ��
  ˵    ������ɫֱ���õ�ǰ�趨�������ڵ��ô�ָ��
***************************************************************************/
static inline void hdc_base_point(const int x, const int y)
{
	MoveToEx(hdc, x - 1, y - 1, NULL);
	LineTo(hdc, x, y);
	if (_Delay_ms > 0)
		Sleep(_Delay_ms);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���(x1,y1)-(x2,y2)֮�仭��һ�����ص������
  ���������const int x1�����x���꣬���Ͻ�Ϊ(0,0)
			const int y1�����y���꣬���Ͻ�Ϊ(0,0)
			const int x2���յ�y���꣬���Ͻ�Ϊ(0,0)
			const int y2���յ�y���꣬���Ͻ�Ϊ(0,0)
  �� �� ֵ��
  ˵    ������ɫֱ���õ�ǰ�趨
***************************************************************************/
static inline void hdc_base_line(const int x1, const int y1, const int x2, const int y2)
{
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
	if (_Delay_ms > 0)
		Sleep(_Delay_ms);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���(x,y)λ�ô���ָ����ɫ��һ��ָ����ϸ�ĵ�(�û�ʵ��Բ��ģ��)
  ���������const int x			��x���꣬���Ͻ�Ϊ(0,0)
			const int y			��y���꣬���Ͻ�Ϊ(0,0)
			const int thickness	����Ĵ�ϸ������λ1�����޲���(�����ᵼ�²���ȫ���)����ȱʡֵ��
			const int RGB_value	�������ɫ����ȱʡֵ��
  �� �� ֵ��
  ˵    �����Ľ�����Ч��
***************************************************************************/
void hdc_point(const int x, const int y, const int thickness, const int RGB_value)
{
	int tn = thickness;
	if (tn < 1)
		tn = 1;		//��������
	/* ������ֱ�������ޣ����ǵ����޳���һ����С�ǣ�������Բ����λ��δʵ�� */
	const int tn_end = (tn <= 1) ? 1 : tn / 2;

	if (RGB_value != INVALID_RGB)
		hdc_set_pencolor(RGB_value);

	for (int i = x - thickness / 2; i <= x + thickness / 2; i++)
		for (int j = y - thickness / 2; j <= y + thickness / 2; j++)
			if ((x - i) * (x - i) + (y - j) * (y - j) <= thickness * thickness / 4)
				hdc_base_point(i, j);

}

/* -------------------------------------------------------------------------
	�������к�����ʵ�֣���������������׼�Ķ�
	1������Ҫ����ϵͳ�������й�ͼ�β����ĺ���
	2�����к�����ʵ�ֶ�����hdc_base_point/hdc_base_line���������
	3����һ�룬�ǲ������к�������Ҫ����������ʵ�ֹ��̣�Ӧ����ʵ����Щ������
	4�������ʵ������ӵĲ���
	5��ϵͳ�ĽǶ��뺯�������еĽǶȺ������180��
   ------------------------------------------------------------------------- */

   /***************************************************************************
	 �������ƣ�
	 ��    �ܣ����߶�
	 ���������const int x1		������x
			   const int y1		������y
			   const int x2		���յ��x
			   const int y2		���յ��y
			   const int thickness	���߶εĴ�ϸ����ȱʡֵ��
			   const int RGB_value	���߶ε���ɫ����ȱʡֵ��
	 �� �� ֵ��
	 ˵    ���������������û���hdc_point����ϣ��ٶ�����
					 Ҳ������hdc_base_point/hdc_base_line����ϣ��ٶȿ죩
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
  �������ƣ�
  ��    �ܣ�������������꣬��һ��������
  ���������const int x1		����1�����x
			const int y1		����1�����y
			const int x2		����2�����x
			const int y2		����2�����y
			const int x3		����3�����x
			const int y3		����3�����y
			bool filled			���Ƿ���Ҫ��䣨��ȱʡֵ��
			const int thickness	���ߵĴ�ϸ����ȱʡֵ��
			const int RGB_value	����ɫ����ȱʡֵ��
  �� �� ֵ��
  ˵    �������ж������Ƿ��ߣ�������ߣ�����һ��ֱ�߼���
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
  �������ƣ�
  ��    �ܣ��������Ͻ����꼰��ȡ��߶ȣ�����һ��������
  ���������const int left_up_x			�����Ͻ�x
			const int left_up_y			�����Ͻ�y
			const int width				�����
			const int high				���߶�
			const int rotation_angles	�������Ͻ�Ϊ֧�㣬��x�����ת��ǣ�����תΪ����
			bool filled					���Ƿ���Ҫ��䣨��ȱʡֵ��
			const int thickness			���ߵĴ�ϸ����ȱʡֵ��
			const int RGB_value			����ɫ����ȱʡֵ��
  �� �� ֵ��
  ˵    ����
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
  �������ƣ�
  ��    �ܣ��������Ͻ����꼰�߳�������һ��������
  ���������const int left_up_x			�����Ͻ�x
			const int left_up_y			�����Ͻ�y
			const int length			���߳�
			const int rotation_angles	�������Ͻ�Ϊ֧�㣬��x�����ת��ǣ�����תΪ��������ȱʡֵ��
			const bool filled			���Ƿ���Ҫ��䣨��ȱʡֵ��
			const int thickness			���ߵĴ�ϸ����ȱʡֵ��
			const int RGB_value			����ɫ����ȱʡֵ��
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void hdc_square(const int left_up_x, const int left_up_y, const int length, const int rotation_angles, const bool filled, const int thickness, const int RGB_value)
{
	hdc_rectangle(left_up_x, left_up_y, length, length, rotation_angles, filled, thickness, RGB_value);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ����ո����Ĳ�����һ��Բ��
  ���������const int point_x		��Բ�ĵ�x
			const int point_y		��Բ�ĵ�y
			const int radius		���뾶
			const int angle_begin	����ʼ�Ƕȣ���Բ�����Ϸ�Ϊ0�㣬˳ʱ��Ϊ����ע�⣺��ϵͳ�������180��!!!������ȱʡֵ��
			const int angle_end		�������Ƕȣ�ͬ�ϣ�����ȱʡֵ��
			const int thickness		����ϸ����ȱʡֵ��
			const int RGB_value		����ɫ����ȱʡֵ��
  �� �� ֵ��
  ˵    ����
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
  �������ƣ�
  ��    �ܣ����ո����Ĳ�����һ������
  ���������const int point_x		��Բ�ĵ�x
			const int point_y		��Բ�ĵ�y
			const int radius		���뾶
			const int angle_begin	����ʼ�Ƕȣ���Բ�����Ϸ�Ϊ0�㣬˳ʱ��Ϊ����ע�⣺��ϵͳ�������180��!!!������ȱʡֵ��
			const int angle_end		�������Ƕȣ�ͬ�ϣ�����ȱʡֵ��
			const bool filled		���Ƿ���Ҫ��䣨��ȱʡֵ��
			const int thickness		����ϸ����ȱʡֵ��
			const int RGB_value		����ɫ����ȱʡֵ��
  ���������
  �� �� ֵ��
  ˵    ��������ʼ/�����ǶȲ�ֵΪ360�ı���ʱ������������
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
  �������ƣ�
  ��    �ܣ����ո����Ĳ�����һ��Բ
  ���������const int point_x		��Բ�ĵ�x
			const int point_y		��Բ�ĵ�y
			const int radius		���뾶
			const bool filled		���Ƿ���Ҫ��䣨��ȱʡֵ��
			const int thickness		����ϸ����ȱʡֵ��
			const int RGB_value		����ɫ����ȱʡֵ��
  �� �� ֵ��
  ˵    ����
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
  �������ƣ�
  ��    �ܣ����ո����Ĳ�����һ����Բ
  ���������const int point_x			��Բ�ĵ�x
			const int point_y			��Բ�ĵ�y
			const int radius_a			��ƽ����X��İ뾶
			const int radius_b			��ƽ����Y��İ뾶
			const int rotation_angles	����Բ��Ϊ֧�㣬��x�����ת��ǣ�����תΪ��������ȱʡֵ��
			const bool filled			���Ƿ���Ҫ��䣨��ȱʡֵ��
			const int thickness			����ϸ����ȱʡֵ��
			const int RGB_value			����ɫ����ȱʡֵ��
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void hdc_ellipse(const int point_x, const int point_y, const int radius_a, const int radius_b, const int rotation_angles, const bool filled, const int thickness, const int RGB_value)
{
	int x, y, old_x = INT_MAX, old_y = INT_MAX, x_c, x_cc, y_c, y_cc;
	if (RGB_value != INVALID_RGB)
		hdc_set_pencolor(RGB_value);

	int radius_c = (int)sqrt(fabs(radius_a * radius_a - radius_b * radius_b));
	int angle = rotation_angles;//������������������

	if (radius_a < radius_b)
	{
		y_c = point_y + (int)(radius_c * cos(angle * PI / 180)), x_c = point_x - (int)(radius_c * sin(angle * PI / 180));//�ҽ���
		y_cc = point_y - (int)(radius_c * cos(angle * PI / 180)), x_cc = point_x + (int)(radius_c * sin(angle * PI / 180));//�󽹵�
	}
	else
	{
		x_c = point_x + (int)(radius_c * cos(angle * PI / 180)), y_c = point_y + (int)(radius_c * sin(angle * PI / 180));//�ҽ���
		x_cc = point_x - (int)(radius_c * cos(angle * PI / 180)), y_cc = point_y - (int)(radius_c * sin(angle * PI / 180));//�󽹵�
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
