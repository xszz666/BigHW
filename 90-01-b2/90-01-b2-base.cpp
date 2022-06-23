//2152611 邹良顺 信02
#include<iostream>
using namespace std;
#include<iomanip>
#include<conio.h>
#include<Windows.h>
#include"90-01-b2.h"
#include "../include/cmd_console_tools.h"
//初始化数组
void first(int a[8][10], int row, int column)
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 10; j++)
			a[i][j] = rand() % 3 + 1;
	for (int i = 0; i < column; i++)
		a[row][i] = 0;
	for (int i = 0; i < row; i++)
		a[i][column] = 0;
}

void output(int row, int column, int a[8][10])
{
	cout << "  |";
	for (int i = 0; i < column; i++)
		cout << setw(3) << i;
	cout << endl << "--+";
	for (int i = 0; i < column; i++)
		cout << "---";
	cout << endl;
	for (int j = 0; j < row; j++)
	{
		cout << (char)('A' + j) << " |";
		for (int i = 0; i < column; i++)
			cout << setw(3) << a[j][i];
		cout << endl;
	}
	cout << endl;
}

void outputchar(int row, int column, char in[8][10])
{
	cout << "  |";
	for (int i = 0; i < column; i++)
		cout << setw(3) << i;
	cout << endl << "--+";
	for (int i = 0; i < column; i++)
		cout << "---";
	cout << endl;
	for (int j = 0; j < row; j++)
	{
		cout << (char)('A' + j) << " |";
		for (int i = 0; i < column; i++)
			cout << setw(3) << in[j][i];
		cout << endl;
	}
	cout << endl;
}

void search(char s1, int s2, int row, int column, int a[8][10], char in[8][10])
{
	int i = s2, j = s1 - 'A';
	in[j][i] = '*';
	bool c = 1;
	while (c == 1)
	{
		c = 0;
		for (int ii = 0; ii < column; ii++)
			for (int jj = 0; jj < row; jj++)
				if (in[jj][ii] == '*')
				{
					for (i = ii - 1, j = jj; i >= 0; i--)
					{
						if (a[j][i] == a[s1 - 'A'][s2] && in[j][i] != '*')
						{
							in[j][i] = '*';
							c = 1;
						}
						else
							break;
					}

					for (i = ii, j = jj - 1; j >= 0; j--)
					{
						if (a[j][i] == a[s1 - 'A'][s2] && in[j][i] != '*')
						{
							in[j][i] = '*';
							c = 1;
						}
						else
							break;
					}

					for (i = ii, j = jj + 1; j < row; j++)
					{
						if (a[j][i] == a[s1 - 'A'][s2] && in[j][i] != '*')
						{
							in[j][i] = '*';
							c = 1;
						}
						else
							break;
					}

					for (i = ii + 1, j = jj; i < column; i++)
					{
						if (a[j][i] == a[s1 - 'A'][s2] && in[j][i] != '*')
						{
							in[j][i] = '*';
							c = 1;
						}
						else
							break;
					}
				}
	}
}

void outputcolour(int row, int column, int a[8][10], char in[8][10])
{
	cout << "  |";
	for (int i = 0; i < column; i++)
		cout << setw(3) << i;
	cout << endl << "--+";
	for (int i = 0; i < column; i++)
		cout << "---";
	cout << endl;
	for (int j = 0; j < row; j++)
	{
		cout << (char)('A' + j) << " |";
		for (int i = 0; i < column; i++)
		{
			if (in[j][i] == '*')
				cct_setcolor(0, 13);
			cout << setw(3) << a[j][i];
			cct_setcolor(0, 15);
		}
		cout << endl;
	}
	cout << endl;
}

void search_digui(int a[8][10], char in[8][10], char s1, int s2, int column, int row)
{
	int i = s2, j = s1 - 'A';
	in[j][i] = '*';
	bool c = 0;
	for (int ii = 0; ii < column; ii++)
		for (int jj = 0; jj < row; jj++)
			if (in[jj][ii] == '*')
			{
				for (i = ii - 1, j = jj; i >= 0; i--)
				{
					if (a[j][i] == a[s1 - 'A'][s2] && in[j][i] != '*')
					{
						in[j][i] = '*';
						c = 1;
					}
					else
						break;
				}

				for (i = ii, j = jj - 1; j >= 0; j--)
				{
					if (a[j][i] == a[s1 - 'A'][s2] && in[j][i] != '*')
					{
						in[j][i] = '*';
						c = 1;
					}
					else
						break;
				}

				for (i = ii, j = jj + 1; j < row; j++)
				{
					if (a[j][i] == a[s1 - 'A'][s2] && in[j][i] != '*')
					{
						in[j][i] = '*';
						c = 1;
					}
					else
						break;
				}

				for (i = ii + 1, j = jj; i < column; i++)
				{
					if (a[j][i] == a[s1 - 'A'][s2] && in[j][i] != '*')
					{
						in[j][i] = '*';
						c = 1;
					}
					else
						break;
				}
			}
	if (c == 1)
		search_digui(a, in, s1, s2, column, row);
}

void merge(int a[8][10], char in[8][10], int row, int column, char s1, int s2)
{
	for (int i = 0; i < column; i++)
		for (int j = 0; j < row; j++)
		{
			if (in[j][i] == '*')
			{
				if (j == s1 - 'A' && i == s2)
					++a[j][i];
				else
					a[j][i] = 0;
			}
		}
}

void mis_zero(int a[8][10], int row, int column, bool if_draw)
{
	for (int j = 0; j < column; j++)
		for (int i = 0; i < row; i++)
			if (a[i][j] == 0)
			{
				for (int jj = i; jj > 0; jj--)
				{
					a[jj][j] = a[jj - 1][j];
					if (if_draw == 1)
					{
						draw_null(j, jj - 1);
						cct_setcolor(a[i][j] + 1, 0);
						cct_gotoxy(3 + 8 * j, 3 + 4 * i - 2);
						cout << "┏━┓";
						cct_gotoxy(3 + 8 * j, 3 + 4 * i + 1 - 2);
						cout << "┃" << a[i][j] << " ┃";
						cct_gotoxy(3 + 8 * j, 3 + 4 * i + 2 - 2);
						cout << "┗━┛";
						Sleep(1);
						cct_setcolor(15, 0);
						cct_gotoxy(3 + 8 * j, 3 + 4 * i - 2);
						cout << "      ";
						cct_gotoxy(3 + 8 * j, 3 + 4 * i + 1 - 2);
						cout << "━━━";
						cct_gotoxy(3 + 8 * j, 3 + 4 * i + 2 - 2);
						cout << "      ";
						cct_setcolor(0, 15);
						draw_merge(a, row, column);
						draw_null(j, jj - 1);
					}
					Sleep(5);
				}
				a[0][j] = 0;
				if (if_draw == 1)
					draw_merge(a, row, column);
				Sleep(1);
			}
}

void outputmiszero(int row, int column, int a[8][10], char in[8][10])
{
	cout << "  |";
	for (int i = 0; i < column; i++)
		cout << setw(3) << i;
	cout << endl << "--+";
	for (int i = 0; i < column; i++)
		cout << "---";
	cout << endl;
	for (int j = 0; j < row; j++)
	{
		cout << (char)('A' + j) << " |";
		for (int i = 0; i < column; i++)
		{
			if (a[j][i] == 0)
				cct_setcolor(0, 13);
			cout << setw(3) << a[j][i];
			cct_setcolor(0, 15);
		}
		cout << endl;
	}
	cout << endl;
}

void putin(int row, int column, int a[8][10], char in[8][10], int max)
{
	for (int i = 0; i < column; i++)
		for (int j = 0; j < row; j++)
		{
			in[j][i] = '0';
			if (a[j][i] == 0)
			{
				in[j][i] = '*';
				a[j][i] = give_rand(max);
			}
		}
}

void max_(int a[8][10], int row, int column, int& max)
{
	for (int i = 0; i < column; i++)
		for (int j = 0; j < row; j++)
			max = (max > a[j][i] ? max : a[j][i]);
}