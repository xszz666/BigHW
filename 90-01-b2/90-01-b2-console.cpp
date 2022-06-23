//2152611 邹良顺 信02
#include<Windows.h>
#include"90-01-b2.h"
#include<iostream>
#include<iomanip>
#include "../include/cmd_console_tools.h"
using namespace std;
void background(int a[8][10], int row, int column)
{
	cct_cls();
	int r = 3 * row + 10, c = 3 * column * 2 + 6;
	cct_setconsoleborder(c, r, c, r);
	cout << "屏幕当前设置为：" << r << "行" << c << "列" << endl;
	for (int i = 0; i < column; i++)
		cout << setw(6) << setiosflags(ios::right) << i;
	cout << endl << ' ';
	cct_setcolor(15, 0);
	cout << "┏";
	for (int i = 0; i < 3 * column; i++)
	{
		cout << "━";
		Sleep(1);
	}
	cout << "┓" << endl;
	cct_setcolor(0, 15);
	for (int j = 0; j < row * 3; j++)
	{
		if ((j - 1) % 3 == 0)
			cout << (char)('A' + (j - 1) / 3);
		else
			cout << ' ';
		cct_setcolor(15, 0);
		cout << "┃";
		for (int j = 0; j < 6 * column; j++)
		{
			cout << ' ';
			Sleep(1);
		}
		cout << "┃" << endl;
		cct_setcolor(0, 15);
	}
	cout << ' ';
	cct_setcolor(15, 0);
	cout << "┗";
	for (int i = 0; i < 3 * column; i++)
	{
		cout << "━";
		Sleep(1);
	}
	cout << "┛" << endl;
	cct_setcolor(0, 15);
}
void element(int a[8][10], int row, int column)
{
	for (int i = 0; i < row; i++)
		for (int j = 0; j < column; j++)//3 3
		{
			cct_setcolor(a[i][j], 0);
			cct_gotoxy(3 + 6 * j, 3 + 3 * i);
			cout << "┏━┓";
			Sleep(1);
			cct_gotoxy(3 + 6 * j, 3 + 3 * i + 1);
			cout << "┃" << a[i][j] << " ┃";
			Sleep(1);
			cct_gotoxy(3 + 6 * j, 3 + 3 * i + 2);
			cout << "┗━┛";
			Sleep(1);
		}
	cct_setcolor(0, 15);
	cout << endl << endl << endl;
}
void _background(int a[8][10], int row, int column, bool if_sleep)
{
	cct_cls();
	int r = 3 * row + 10 + 2 * row - 2, c = 3 * column * 2 + 6 + 2 * column - 2 * 1;
	cct_setconsoleborder(c + 2, r, c + 2, r);
	cout << "屏幕当前设置为：" << r << "行" << c << "列" << endl;
	for (int i = 0; i < column; i++)
		cout << setw(8) << setiosflags(ios::right) << i;
	cout << endl;
	cout << ' ';
	cct_setcolor(15, 0);
	cout << "┏";
	for (int m = 0; m < column - 1; m++)
	{
		for (int i = 0; i < 3; i++)
		{
			cout << "━";
			if (if_sleep == 1)
				Sleep(1);
		}
		cout << "┳";
	}
	for (int i = 0; i < 3; i++)
	{
		cout << "━";
		if (if_sleep == 1)
			Sleep(1);
	}
	cout << "┓" << endl;
	cct_setcolor(0, 15);
	for (int j = 0; j < row * 4 - 1; j++)
	{
		if ((j + 1) % 4 == 0)
		{
			cout << " ";
			cct_setcolor(15, 0);
			cout << "┣";
			for (int m = 0; m < column - 1; m++)
			{
				for (int i = 0; i < 3; i++)
				{
					cout << "━";
					if (if_sleep == 1)
						Sleep(1);
				}
				cout << "╋";
			}
			for (int i = 0; i < 3; i++)
			{
				cout << "━";
				if (if_sleep == 1)
					Sleep(1);
			}
			cout << "┫" << endl;
			cct_setcolor(0, 15);
		}
		else
		{
			if ((j - 1) % 4 == 0)
				cout << (char)('A' + (j - 1) / 4);
			else
				cout << ' ';

			cct_setcolor(15, 0);
			cout << "┃";
			for (int i = 0; i < 4 * column - 1; i++)
			{
				if ((i + 1) % 4 == 0)
					cout << "┃";
				else
					cout << "  ";
				if (if_sleep == 1)
					Sleep(1);
			}
			cout << "┃" << endl;
			cct_setcolor(0, 15);
		}
	}
	cout << ' ';
	cct_setcolor(15, 0);
	cout << "┗";
	for (int m = 0; m < column - 1; m++)
	{
		for (int i = 0; i < 3; i++)
		{
			cout << "━";
			if (if_sleep == 1)
				Sleep(1);
		}
		cout << "┻";
	}
	for (int i = 0; i < 3; i++)
	{
		cout << "━";
		if (if_sleep == 1)
			Sleep(1);
	}
	cout << "┛" << endl;
	cct_setcolor(0, 15);
}
void _element(int a[8][10], int row, int column, bool if_sleep)
{
	for (int i = 0; i < row; i++)
		for (int j = 0; j < column; j++)//3 3
		{
			cct_setcolor(a[i][j] + 1, 0);
			cct_gotoxy(3 + 8 * j, 3 + 4 * i);
			cout << "┏━┓";
			if (if_sleep == 1)
				Sleep(1);
			cct_gotoxy(3 + 8 * j, 3 + 4 * i + 1);
			cout << "┃" << a[i][j] << " ┃";
			if (if_sleep == 1)
				Sleep(1);
			cct_gotoxy(3 + 8 * j, 3 + 4 * i + 2);
			cout << "┗━┛";
			if (if_sleep == 1)
				Sleep(1);
		}
	cct_setcolor(0, 15);
	cout << endl << endl << endl;
}
void draw_element(int i, int j, int a[8][10], int c)
{
	cct_setcolor(a[i][j] + 1, c);
	cct_gotoxy(3 + 8 * j, 3 + 4 * i);
	cout << "┏━┓";
	cct_gotoxy(3 + 8 * j, 3 + 4 * i + 1);
	cout << "┃" << a[i][j] << " ┃";
	cct_gotoxy(3 + 8 * j, 3 + 4 * i + 2);
	cout << "┗━┛";
	cct_setcolor(0, 15);
}
int can_(int row, int column, char s1, int s2, char in[8][10])
{
	for (int ii = 0; ii < column; ii++)
		for (int jj = 0; jj < row; jj++)
			if (in[jj][ii] == '*' && (jj != s1 - 'A' || ii != s2))
				return 1;
	return 0;

}
void mouse_keyboard(int row, int column, int a[8][10], char in[8][10], char& s1, int& s2, int select)
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 10; j++)
			in[i][j] = '0';

	int x, y, action, k1, k2, ret, loop = 1, continu = 1, time = 0, can = 1;
	int rr = -1, cc = -1;
	while (loop)
	{
		ret = cct_read_keyboard_and_mouse(x, y, action, k1, k2);

		if (action == MOUSE_LEFT_BUTTON_CLICK || k1 == 13)
			continu = 0;
		else if (ret == CCT_MOUSE_EVENT)
		{
			for (int i = 0; i < row; i++)
				if (y + 1 >= 4 * (i + 1) && y + 1 <= 4 * (i + 1) + 2)
				{
					rr = i;
					break;
				}
				else
					rr = -1;
			for (int i = 0; i < column; i++)
				if (x >= (2 * i + 1) * 4 - 1 && x <= (2 * i + 1) * 4 + 5 - 1)
				{
					cc = i;
					break;
				}
				else
					cc = -1;
		}
		else if (ret == CCT_KEYBOARD_EVENT)
		{
			switch (k1)
			{
			case 224:
				switch (k2) {
				case KB_ARROW_UP:
					if (rr == 0)
						rr = row - 1;
					else
						--rr;
					break;
				case KB_ARROW_DOWN:
					if (rr == row - 1)
						rr = 0;
					else
						++rr;
					break;
				case KB_ARROW_LEFT:
					if (cc == 0)
						cc = column - 1;
					else
						--cc;
					break;
				case KB_ARROW_RIGHT:
					if (cc == column - 1)
						cc = 0;
					else
						++cc;
					break;
				}
				break;
			}
		}

		if (continu == 0)
		{
			for (int i = 0; i < 8; i++)
				for (int j = 0; j < 10; j++)
					in[i][j] = '0';
			search_digui(a, in, s1, s2, column, row);

			for (int j = 0; j < column; j++)
				for (int i = 0; i < row; i++)
				{
					if (in[i][j] == '*' && (i != s1 - 'A' || j != s2))
						draw_element(i, j, a, 7);
				}

			can = can_(row, column, s1, s2, in);
			if (can == 0)
			{
				cct_setcolor(0, 11);
				cct_gotoxy(0, 4 * row + 3);
				cout << "                                                                             ";
				cct_gotoxy(0, 4 * row + 3);
				cout << "周围无相同值，" << endl;
				cct_setcolor(0, 15);
				cct_setcursor(CURSOR_INVISIBLE);
			}

			if (can != 0)
			{
				cct_gotoxy(0, 4 * row + 3);
				cout << "                                                                             ";
				cct_gotoxy(0, 4 * row + 3);
			}

			if (select == 7)
			{
				s1 = 'A' + rr;
				s2 = cc;
				break;
			}
			else
			{
				cout << "移动鼠标或按箭头键取消，单机鼠标或按回车键继续...";
				while (1)
				{
					ret = cct_read_keyboard_and_mouse(x, y, action, k1, k2);
					if (action == MOUSE_LEFT_BUTTON_CLICK || k1 == 13)
						break;
					else if (ret == CCT_MOUSE_EVENT)
					{
						for (int i = 0; i < row; i++)
							if (y + 1 >= 4 * (i + 1) && y + 1 <= 4 * (i + 1) + 2)
							{
								rr = i;
								break;
							}

						for (int i = 0; i < column; i++)
							if (x >= (2 * i + 1) * 4 - 1 && x <= (2 * i + 1) * 4 + 5 - 1)
							{
								cc = i;
								break;
							}

						if (rr + 'A' != s1 || s2 != cc)
						{
							continu = 1;
							break;
						}
					}

					else if (ret == CCT_KEYBOARD_EVENT)
					{
						switch (k1)
						{
						case 224:
							switch (k2) {
							case KB_ARROW_UP:
								if (rr == 0)
									rr = row - 1;
								else
									--rr;
								break;
							case KB_ARROW_DOWN:
								if (rr == row - 1)
									rr = 0;
								else
									++rr;
								break;
							case KB_ARROW_LEFT:
								if (cc == 0)
									cc = column - 1;
								else
									--cc;
								break;
							case KB_ARROW_RIGHT:
								if (cc == column - 1)
									cc = 0;
								else
									++cc;
								break;
							}
							break;
						}
						if (rr + 'A' != s1 || s2 != cc)
						{
							continu = 1;
							break;
						}
					}
				}
			}
		}

		if (continu == 0)
		{
			s1 = rr + 'A';
			s2 = cc;
			if (can != 0)
				break;
		}
		if (cc != -1 && rr != -1 && continu == 1)
		{
			re_write(row);
			if (ret == CCT_MOUSE_EVENT)
				cout << "[当前鼠标]" << char(rr + 'A') << "行" << " " << cc << "列" << endl << "                                           ";
			else if (ret == CCT_KEYBOARD_EVENT)
				cout << "[当前键盘]" << char(rr + 'A') << "行" << " " << cc << "列" << endl << "                                           ";
			s1 = rr + 'A';
			s2 = cc;

			for (int i = 0; i < row; i++)
				for (int j = 0; j < column; j++)
				{
					if (i == rr && j == cc)
						draw_element(i, j, a, 15);
					else
						draw_element(i, j, a, 0);
				}
		}
		else
		{
			re_write(row);
			cout << "[当前鼠标]" << "位置非法";
		}
	}
}//完成移动
void stop(int aa)
{
	int x, y, action, k1, k2;

	while (1)
	{
		cct_read_keyboard_and_mouse(x, y, action, k1, k2);
		if (action == MOUSE_LEFT_BUTTON_CLICK || k1 == (aa == 0 ? 13 : 67) || k1 == (aa == 0 ? 13 : 67 + 32))
			break;
	}
}
void draw_null(int j, int i)
{
	cct_setcolor(15, 15);
	cct_gotoxy(3 + 8 * j, 3 + 4 * i);
	cout << "      ";
	cct_gotoxy(3 + 8 * j, 3 + 4 * i + 1);
	cout << "      ";
	cct_gotoxy(3 + 8 * j, 3 + 4 * i + 2);
	cout << "      ";
	cct_setcolor(0, 15);
}
void draw_merge(int a[8][10], int row, int column)
{
	for (int i = 0; i < row; i++)
		for (int j = 0; j < column; j++)
		{
			if (a[i][j] == 0)
				draw_null(j, i);
			else
				draw_element(i, j, a, 0);
		}
}