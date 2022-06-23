/* 2152611 邹良顺 信02 */
#include"90-02-b1.h"
struct step
{
	char row;
	char col;
	char num;
	char fo_num;
};
int main()
{
	cct_setconsoleborder(100, 30, 100, 30);
	char select;
	while (1) {
		menu_b1(&select);

		int time = 0;
		struct step Steps[1000];
		int sudoku[9][9];
		int fix_num[9][9] = { 0 };
		int identical[3][9] = { 0 };//行 列 格  1 重复  0 不重复
		
		if ('0' == select)
			return 0;
		else if (select>'0')
		{
			fun1(sudoku, fix_num, identical, &time, Steps, select);

			continu(select);
		}
	}
	return 0;
}
