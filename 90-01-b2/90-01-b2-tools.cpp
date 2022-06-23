//2152611 邹良顺 信02
#include<iostream>
#include "../include/cmd_console_tools.h"
using namespace std;
void input(int& r, int& c, int& obj, int select)
{
	cct_cls();
	while (1)
	{
		cout << "请输入行数(5-8)：" << endl;
		cin >> r;
		if (cin.fail() || r < 5 || r>8)
			cout << "输入错误" << endl;
		else
			break;
	}
	while (1)
	{
		cout << "请输入列数(5-10)：" << endl;
		cin >> c;
		if (cin.fail() || c < 5 || c>10)
			cout << "输入错误" << endl;
		else
			break;
	}
	if (select == 3 || select == 4 || select == 8 || select == 9)
	{
		while (1)
		{
			cout << "请输入合成目标(5-20)：" << endl;
			cin >> obj;
			if (cin.fail() || obj < 5 || obj>20)
				cout << "输入错误" << endl;
			else
				break;
		}
	}
}

int simple_score(int a[8][10], char in[8][10], int column, int row, char s1, int s2)
{
	int s = 0;
	for (int i = 0; i < row; i++)
		for (int j = 0; j < column; j++)
			if (in[i][j] == '*')
				++s;
	s = s * 3 * (a[s1 - 'A'][s2] - 1);
	return s;
}

void add_score(int& sim_s, int& score, int& obj, int a[8][10], char in[8][10], int column, int row, char s1, int s2)
{
	sim_s = simple_score(a, in, column, row, s1, s2);
	score += sim_s;
	cout << "本次得分：" << sim_s << " 总得分：" << score << " 合成目标：" << obj << endl;
}

bool end(int a[8][10], int row, int column)
{
	int b[9][11];
	for (int ii = 0; ii < 11; ii++)
		for (int jj = 0; jj < 9; jj++)
			b[jj][ii] = 0;

	for (int ii = 1; ii <= column; ii++)
		for (int jj = 1; jj <= row; jj++)
			b[jj][ii] = a[jj - 1][ii - 1];
	for (int ii = 1; ii <= column; ii++)
		for (int jj = 1; jj <= row; jj++)
			if (b[jj][ii] == b[jj + 1][ii] || b[jj][ii] == b[jj - 1][ii] || b[jj][ii] == b[jj][ii + 1] || b[jj][ii] == b[jj][ii - 1])
				return 1;
	return 0;

}

void continu()
{
	char a[10];
	while (1)
	{
		cout << "本小题结束，按输入End继续...";
		cin >> a;
		if (a[0] == 'E' && a[1] == 'n' && a[2] == 'd')
			break;
		else
		{
			cin.ignore(10000, '\n');
			cout << "输入错误，请重新输入" << endl;
		}
	}
}

void re_write(int row)
{
	cct_gotoxy(0, 4 * row + 3);
	cout << "                                                                                                                                         " << endl;
	/*cout << "                                                                                                                                          " << endl;
	cout<< "                                                                                                                                                   ";*/
	cct_gotoxy(0, 4 * row + 3);
}

int rand_num(int max)
{
	int a = rand() % 100 + 1, b = rand() % 3 + 1, c = rand() % 4 + 1;
	if (max == 3)
		return b;
	else if (max == 4)
	{
		if (a <= 90)
			return b;
		else
			return 4;
	}
	else if (max == 5)
	{
		if (a <= 75)
			return b;
		else if (a > 75 && a <= 90)
			return 4;
		else
			return 5;
	}
	else if (max == 6)
	{
		if (a <= 80)
			return c;
		else if (a > 80 && a <= 95)
			return 5;
		else
			return 6;
	}
	else
	{
		if (a <= 80)
			return rand() % (max - 3) + 1;
		else if (a > 80 && a <= 90)
			return max - 2;
		else if (a > 90 && a <= 95)
			return max - 1;
		else
			return max;
	}
}

int give_rand(int max)
{
	return  rand_num(max);
}