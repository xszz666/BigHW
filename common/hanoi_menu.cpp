/* ����˳ 2152611 ��02*/
#include <iostream>
#include<conio.h>
#include "../include/cmd_console_tools.h"
#include<Windows.h>
using namespace std;
//90-01-b1
void print_menu()
{
	cout << "---------------------------------" << endl;
	cout << "1.������" << endl;
	cout << "2.������(������¼)" << endl;
	cout << "3.�ڲ�������ʾ(����)" << endl;
	cout << "4.�ڲ�������ʾ(����+����)" << endl;
	cout << "5.ͼ�ν�-Ԥ��-������Բ��" << endl;
	cout << "6.ͼ�ν�-Ԥ��-����ʼ���ϻ�n������" << endl;
	cout << "7.ͼ�ν�-Ԥ��-��һ���ƶ�" << endl;
	cout << "8.ͼ�ν�-�Զ��ƶ��汾" << endl;
	cout << "9.ͼ�ν�-��Ϸ��" << endl;
	cout << "0.�˳�" << endl;
	cout << "---------------------------------" << endl;
	cout << "[��ѡ��:] ";
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
	cout << "1.�������ҳ��ɺϳ����ʶ���ǵݹ飩" << endl;
	cout << "2.�������ҳ��ɺϳ����ʶ���ݹ飩" << endl;
	cout << "3.���������һ�κϳɣ��ֲ�����ʾ��" << endl;
	cout << "4.�����������棨�ֲ�����ʾ��" << endl;
	cout << "5.αͼ�ν�����ʾ��ʼ���飨�޷ָ��ߣ�" << endl;
	cout << "6.αͼ�ν�����ʾ��ʼ���飨�зָ��ߣ�" << endl;
	cout << "7.αͼ�ν������ü�ͷ�� / ���ѡ��ǰɫ��" << endl;
	cout << "8.αͼ�ν������һ�κϳɣ��ֲ��裩" << endl;
	cout << "9.αͼ�ν���������(֧�����)" << endl;
	cout << "---------------------------------------" << endl;
	cout << "A.�����н��棨�����Զ��� - �����棩" << endl;
	cout << "B.αͼ�ν��棨�����Զ��� - �����棩" << endl;
	cout << "---------------------------------------" << endl;
	cout << "0.�˳�" << endl;
	cout << "---------------------------------------" << endl;
	cout << "[��ѡ��:]" << endl;
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
			cout << "�������" << endl;
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
	cout << "1.�ַ�������Ϸ�������˹��ܣ�" << endl;
	cout << "2.ͼ�ν�����Ϸ�������˹��ܣ�" << endl;
	cout << "3.ͼ�ν����Զ��⣨(��ʾ���̲�����ʱ)��" << endl;
	cout << "4.ͼ�ν�����Ϸ(����)" << endl;
	cout << "5.ͼ�ν�����Ϸ(���)" << endl;
	cout << "0.�˳�" << endl;
	cout<< "-------------------------------------------" << endl;
	cout << "��ѡ��[0-5]";
	*select = _getch();
	if (*select >= '0' && *select <= '3')
		cout << " " << *select;
	Sleep(100);
}