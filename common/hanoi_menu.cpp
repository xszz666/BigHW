/* 邹良顺 2152611 信02*/
#include <iostream>
#include<conio.h>
#include "../include/cmd_console_tools.h"
#include<Windows.h>
using namespace std;
//90-01-b1
void print_menu()
{
	cout << "---------------------------------" << endl;
	cout << "1.基本解" << endl;
	cout << "2.基本解(步数记录)" << endl;
	cout << "3.内部数组显示(横向)" << endl;
	cout << "4.内部数组显示(纵向+横向)" << endl;
	cout << "5.图形解-预备-画三个圆柱" << endl;
	cout << "6.图形解-预备-在起始柱上画n个盘子" << endl;
	cout << "7.图形解-预备-第一次移动" << endl;
	cout << "8.图形解-自动移动版本" << endl;
	cout << "9.图形解-游戏版" << endl;
	cout << "0.退出" << endl;
	cout << "---------------------------------" << endl;
	cout << "[请选择:] ";
}
int get_menu()
{
	print_menu();
	int select;
	while (1)
	{
		select = (int)(_getch() - '0');
		if (select > -1 && select < 10)
		{
			cout << select;
			break;
		}

	}
	cout << endl << endl << endl;
	return select;
}
//90-01-b2
void menu(char& select)
{
	cout << "---------------------------------------" << endl;
	cout << "1.命令行找出可合成项并标识（非递归）" << endl;
	cout << "2.命令行找出可合成项并标识（递归）" << endl;
	cout << "3.命令行完成一次合成（分步骤显示）" << endl;
	cout << "4.命令行完整版（分步骤显示）" << endl;
	cout << "5.伪图形界面显示初始数组（无分隔线）" << endl;
	cout << "6.伪图形界面显示初始数组（有分隔线）" << endl;
	cout << "7.伪图形界面下用箭头键 / 鼠标选择当前色块" << endl;
	cout << "8.伪图形界面完成一次合成（分步骤）" << endl;
	cout << "9.伪图形界面完整版(支持鼠标)" << endl;
	cout << "---------------------------------------" << endl;
	cout << "A.命令行界面（网络自动解 - 基本版）" << endl;
	cout << "B.伪图形界面（网络自动解 - 基本版）" << endl;
	cout << "---------------------------------------" << endl;
	cout << "0.退出" << endl;
	cout << "---------------------------------------" << endl;
	cout << "[请选择:]" << endl;
	while (1)
	{
		select = _getch();
		if (select >= '0' && select <= '9' || select >= 'A' && select <= 'C' || select >= 'a' && select <= 'c')
		{
			cout << select;
			Sleep(1000);
			break;
		}
		else
		{
			cct_gotoxy(0, 18);
			cout << "                                                                                                                                         " << endl;
			cct_gotoxy(0, 18);
			cout << "输入错误" << endl;
			Sleep(1000);
			cct_gotoxy(0, 18);
			cout << "                                                                                                                                         " << endl;
			cct_gotoxy(0, 18);
		}

	}
}
//90-02-b1
void menu_b1(char * select)
{
	cct_cls();
	cout << "-------------------------------------------" << endl;
	cout << "1.字符界面游戏（带回退功能）" << endl;
	cout << "2.图形界面游戏（带回退功能）" << endl;
	cout << "3.图形界面自动解（(显示过程并带延时)）" << endl;
	cout << "4.图形界面游戏(键盘)" << endl;
	cout << "5.图形界面游戏(鼠标)" << endl;
	cout << "0.退出" << endl;
	cout<< "-------------------------------------------" << endl;
	cout << "请选择[0-5]";
	*select = _getch();
	if (*select >= '0' && *select <= '3')
		cout << " " << *select;
	Sleep(100);
}