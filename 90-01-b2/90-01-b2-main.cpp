//2152611 ����˳ ��02
#include<iostream>
#include"90-01-b2.h"
#include<conio.h>
#include "../include/cmd_console_tools.h"
#include<Windows.h>
using namespace std;
void menu(char& select);

int main()
{
	while (1)
	{
		//�������
		cct_setconsoleborder(45, 35, 45, 35);
		cct_setcolor(0, 15);
		char select;
		menu(select);

		if (select == '0')
			return 0;

		int row, column, obj = 999, sim_s = 0, score = 0, max = 3;
		int a[8][10];
		char s1;
		int s2;

		if (select >= '0' && select <= '9')
			select = select - '0';

		if (select > 0 && select < 10)
		{
			char in[8][10];
			input(row, column, obj, select);

			//a��ʼ��
			first(a, row, column);
			//inΪ'0'
			for (int i = 0; i < 8; i++)
				for (int j = 0; j < 10; j++)
					in[i][j] = '0';

			if (select == 5)
			{
				cct_setcursor(CURSOR_INVISIBLE);
				background(a, row, column);
				element(a, row, column);
			}
			else if (select == 6 || select == 7 || select == 8 || select == 9)
			{
				cct_enable_mouse();
				cct_setcursor(CURSOR_INVISIBLE);
				_background(a, row, column);
				_element(a, row, column);
				if (select == 7 || select == 8 || select == 9)
					while (1)
					{

						mouse_keyboard(row, column, a, in, s1, s2, select);
						if (select == 7)
						{
							cout << "ѡ����" << s1 << "��" << s2 << "��" << endl;
							break;
						}
						//�ڲ�����

						//�ϲ�
						merge(a, in, row, column, s1, s2);
						draw_merge(a, row, column);
						cct_gotoxy(0, 0);
						cout << "                                     ";
						cct_gotoxy(0, 0);
						add_score(sim_s, score, obj, a, in, column, row, s1, s2);

						if (select == 8)
						{
							re_write(row);
							cout << "�ϳ����,���������س���������0" << endl;
							stop();
						}
						mis_zero(a, row, column, 1);

						if (select == 8)
						{
							re_write(row);
							cout << "����0���,���������س����������ֵ" << endl;
							stop();
						}
						putin(row, column, a, in, max);
						_element(a, row, column);

						if (select == 8)
						{
							re_write(row);
							cct_setcolor(0, 11);
							cout << "���κϳɽ�������c�򵥻����������һ�κϳ�";
							cct_setcolor(0, 15);
							stop(1);
						}
						if (select == 8)
							break;
						max_(a, row, column, max);
						if (max == obj)
						{
							re_write(row);
							cct_setcolor(0, 13);
							cout << "�Ѿ��ϳɵ�" << max << endl;
							cct_setcolor(0, 15);
							cout << "���س����򵥻�������������Ŀ�����..." << endl << endl;;
							stop();
							++obj;
						}
						if (end(a, row, column) == 0)
						{
							cct_gotoxy(0, 4 * row + 3);
							cout << "�޿ɺϲ������Ϸ������";
							cout << "��Q����                          " << endl;
							while (_getch() != 'q' && _getch() != 'Q')
								;
							break;
						}
					}
				cct_disable_mouse();
			}
			while (select != 6 && select != 5 && select != 7 && select != 8 && select != 9)
			{
				cout << "��ǰ���飺" << endl;
				output(row, column, a);

				bool can = 0;
				while (can == 0)
				{
					while (1)
					{
						cout << "������ĸ+������ʽ[����c2]����������꣺";
						cin >> s1 >> s2;

						if (s1 >= 'a' && s1 <= 'z')
							s1 += 'A' - 'a';

						if (s1 >= 'A' && s1 <= 'A' + row - 1 && s2 >= 0 && s2 <= column - 1 && cin.good())
							break;
						else
						{
							cin.clear();
							cin.ignore(1000, '\n');
							cout << "�������" << endl;
						}
					}
					cout << "����Ϊ" << s1 << "��" << s2 << "��" << endl;

					for (int i = 0; i < 8; i++)
						for (int j = 0; j < 10; j++)
							in[i][j] = '0';

					if (select == 1)
						search(s1, s2, row, column, a, in);
					else
						search_digui(a, in, s1, s2, column, row);

					can = can_(row, column, s1, s2, in);
					if (can == 0)
						cout << "����ľ�������λ�ô���������ֵͬ������������" << endl;
				}
				cout << endl;
				cout << "���ҽ�����飺" << endl;
				outputchar(row, column, in);
				cout << endl;
				cout << "��ǰ����(��ͬɫ��ʶ)��" << endl;
				outputcolour(row, column, a, in);

				if (select == 3 || select == 4)
				{
					char ynq = '0';
					cout << "��ȷ���Ƿ�����ڵ���ֵͬ�ϲ���" << s1 << s2 << "��(Y / N / Q)��";
					while (ynq != 'y' && ynq != 'Y' && ynq != 'n' && ynq != 'N' && ynq != 'q' && ynq != 'Q')
					{
						ynq = _getch();
					}//**********************************************************
					if (ynq == 'y' || ynq == 'Y')
					{
						cout << ynq;
						cout << endl << "��ֵͬ�鲢�������(��ͬɫ��ʶ)��" << endl;
						merge(a, in, row, column, s1, s2);
						outputcolour(row, column, a, in);
						add_score(sim_s, score, obj, a, in, column, row, s1, s2);

						cout << "���س����������������0����..." << endl;


						while (_getch() != '\r')
							;


						mis_zero(a, row, column, 0);
						outputmiszero(row, column, a, in);

						cout << "���س���������ֵ���..." << endl;

						while (_getch() != '\r')
							;

						cout << "��ֵ���������(��ͬɫ��ʶ)��" << endl;
						putin(row, column, a, in, max);
						outputcolour(row, column, a, in);

						if (select == 4)
						{
							cout << "���κϳɽ��������س���������һ�εĺϳ�..." << endl;

							while (_getch() != '\r')
								;
						}
					}
					else if (ynq == 'q' || ynq == 'Q')
					{
						cout << ynq;
						break;
					}
					else if (ynq != 'n' && ynq != 'N')
						cout << ynq;
				}
				max_(a, row, column, max);
				if (max == obj)
				{
					cct_setcolor(0, 13);
					cout << "�Ѿ��ϳɵ�5" << endl;
					cct_setcolor(0, 15);
					cout << "���س������������Ŀ�����..." << endl << endl;;
					while (_getch() != '\n')
						;
					++obj;
				}

				if (end(a, row, column) == 0)
				{
					cout << "��������������λ����ȣ���Ϸ����" << endl;
					break;
				}
				if (select != 4)
					break;
			}

			if (select >= 0 && select <= 4)
				;
			else
				re_write(row);

			continu();
		}
	}
	return 0;
}