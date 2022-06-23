//2152611 信02 邹良顺
#include <iostream>
using namespace std;
#include"90-01-b1-hanoi.h"
int top1, top2, top3;
int mm;//步数
int a[10], b[10], c[10];
int v;
int main()
{
	cct_setconsoleborder(120, 40, 120, 9000);
	cct_setcolor();
	while (1)
	{
		top1 = 0;
		top2 = 0;
		top3 = 0;
		mm = 0;//步数
		for (int i = 0; i < 10; i++)
		{
			a[i] = 0;
			b[i] = 0;
			c[i] = 0;
		}
		v = 0;
		cct_cls();
		int select;
		select = get_menu();

		if (select == 0)
			break;
		else
			menu1(select);
	}
	return 0;
}