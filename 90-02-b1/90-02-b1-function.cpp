/* 2152611 ����˳ ��02 */
#include"90-02-b1.h"
struct step
{
	char row;
	char col;
	char num;
	char fo_num;
};
void fun1(int sudoku[9][9], int fix_num[9][9], int identical[3][9], int *time, struct step Steps[],char select)
{
	bool if_in_suc = 1;
	char choose[20];
	cct_cls();
	cout << "��ǰĿ¼�·���sudoku*.txt��ƥ���ļ��У�" << endl;
	search_files(select, choose);
	open_files(sudoku,fix_num,identical,select, choose,if_in_suc);//�򿪲�����
	if (!(if_in_suc == 0 && select != '1'))
	{
		if ('3' != select && '4' != select&&'5'!=select)
			while (1)
			{
				if (1 == if_end(sudoku, identical))
				{
					cout << "��������ɹ��ˣ�" << endl;
					break;
				}
				putin_num(sudoku, fix_num, time, Steps, select);
				if (if_identical(sudoku, identical, 1) != 0)
				{
					(*time)--;
					print_pic(sudoku, fix_num, identical, select);
					cout << "���������ظ������������롣" << endl;
					identical[0][Steps[*time].row - '1'] = 0;
					identical[1][Steps[*time].col - 'A'] = 0;
					identical[2][(Steps[*time].row - '1') * 3 / 3 * 3 + (Steps[*time].col - 'A') * 3 / 3 + 1] = 0;
					sudoku[Steps[*time].row - '1'][Steps[*time].col - 'A'] = Steps[*time].fo_num - '0';
				}
				else
				{
					print_pic(sudoku, fix_num, identical, select);
					cout << "����������ȷ" << endl;
				}
			}
		else if (select == '4'||select=='5')
		{
			cct_setcursor(3);
			Steps[0].col = 'A';
			Steps[0].row = '1';
			while (1)
			{
				if (1 == if_end(sudoku, identical))
				{
					cct_gotoxy(60,8);
					cout << "��������ɹ��ˣ�   " << endl;
					break;
				}
				putin_num(sudoku, fix_num, time, Steps, select);
				if (if_identical(sudoku, identical, 0) != 0)
				{
					(*time)--;
					cct_gotoxy(60, 10);
					cout << "���������ظ������������롣  ";
					Sleep(1000);
					cct_gotoxy(60, 10);
					cout << "                           ";
					identical[0][Steps[*time].row - '1'] = 0;
					identical[1][Steps[*time].col - 'A'] = 0;
					identical[2][(Steps[*time].row - '1') * 3 / 3 * 3 + (Steps[*time].col - 'A') * 3 / 3 + 1] = 0;
					sudoku[Steps[*time].row - '1'][Steps[*time].col - 'A'] = Steps[*time].fo_num - '0';
					print_cell(sudoku, Steps, time, 0, fix_num);
				}
				else
				{
					cct_gotoxy(60, 10);
					cout << "����������ȷ         ";
					Sleep(1000);
				}
			}
		}
		else
		{
			int n = 0;
			bool succ = 0;
			AI(n, sudoku, succ, fix_num, identical, select);
			if (succ == 1)
				cout << "������д��ɡ�" << endl;
			else
				cout << "����ʧ�ܡ�" << endl;
		}
	}
	else
		cout << "ԭʼ��������"<<endl;
}