/* 2053394 信10 张弛 */
#include <Windows.h>
#include <math.h>
#include "../include/cmd_hdc_tools.h"
#define PI 3.1415926535

/* 画星形线 */
void hdc_draw_Mathematical_curve_2053394()
{
	hdc_cls();
	const int   win_width = 800, win_high = 800;	//设定屏幕宽度
	//随机显示20个星星
	for (int i = 0; i < 20; i++) {
		int x, y, a, angle;

		hdc_set_pencolor(rand() % 256, rand() % 256, rand() % 256);
		x = win_width / 4 + rand() % (win_width / 2);
		y = win_high / 4 + rand() % (win_high / 2);
		a = win_width / 10 + rand() % (win_width / 4);
		angle = rand() % 360;

		Sleep(100);


		int col__old = int(x + a);
		int row__old = int(y);
		int col_old = int(x + (col__old - x) * cos(angle * PI / 180) - (row__old - y) * sin(angle * PI / 180));
		int row_old = int(y + (col__old - x) * sin(angle * PI / 180) + (row__old - y) * cos(angle * PI / 180));

		for (double _angle = 0; _angle < 360; _angle += 0.5)
		{
			int col__ = int(x + a * cos(_angle * PI / 180) * cos(_angle * PI / 180) * cos(_angle * PI / 180));
			int row__ = int(y + a * sin(_angle * PI / 180) * sin(_angle * PI / 180) * sin(_angle * PI / 180));
			int col = int(x + (col__ - x) * cos(angle * PI / 180) - (row__ - y) * sin(angle * PI / 180));
			int row = int(y + (col__ - x) * sin(angle * PI / 180) + (row__ - y) * cos(angle * PI / 180));

			hdc_line(row_old, col_old, row, col);

			row_old = row;
			col_old = col;
		}
	}
}