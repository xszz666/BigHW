//2152611 信02 邹良顺
#include <iostream>
using namespace std;
#include<iomanip>
#include "../include/cmd_console_tools.h"
#include<windows.h>
#include <conio.h>

extern int top1, top2, top3;
extern int mm;//步数
extern int a[10], b[10], c[10];
extern int v;
//输入三柱
void start(int* n, char* qs, char* mb, char* zj, int select, int cl[])
{
    while (1)
    {
        cout << "请输入汉诺塔的层数(1-10)" << endl;
        cin >> *n;
        cin.clear();
        cin.ignore(1000, '\n');
        if (cin.good() && *n > 0 && *n < 11)
            break;
    }
    while (1)
    {
        cout << "请输入起始柱(A-C)" << endl;
        cin >> *qs;
        cin.clear();
        cin.ignore(1000, '\n');
        if (*qs == 'A' || *qs == 'B' || *qs == 'C' || *qs == 'a' || *qs == 'b' || *qs == 'c')
            break;
    }
    if (*qs > 96)
        *qs -= 32;
    while (1)
    {
        cout << "请输入目标柱(A-C)" << endl;
        cin >> *mb;
        cin.clear();
        cin.ignore(1000, '\n');
        if ((*mb == 'A' || *mb == 'B' || *mb == 'C' || *mb == 'a' || *mb == 'b' || *mb == 'c') && *mb != *qs && *mb != *qs + 32)
            break;
    }
    if (*mb > 96)
        *mb -= 32;
    for (int i = *n; i > 0; i--)
    {
        a[top1++] = i;
        cl[i - 1] = i;
    }
    *zj = char('A' + 'B' + 'C' - *qs - *mb);
    if (select == 4 || select == 8)
    {
        while (1)
        {
            cout << "请输入移动速度(0-5: 0-按回车单步演示 1-延时最长 5-延时最短)" << endl;
            cin >> v;
            cin.clear();
            cin.ignore(1000, '\n');
            if (cin.good() && v >= 0 && v <= 5)
                break;
        }
    }
}
void yd(char src, char dst, char qs, char zj, char mb)
{
    if (dst == qs)
    {
        if (src == zj)
        {
            a[top1++] = b[--top2];
            b[top2] = 0;
        }
        else
        {
            a[top1++] = c[--top3];
            c[top3] = 0;
        }
    }
    else if (dst == zj)
    {
        if (src == qs)
        {
            b[top2++] = a[--top1];
            a[top1] = 0;
        }
        else
        {
            b[top2++] = c[--top3];
            c[top3] = 0;
        }
    }
    else//mb
    {
        if (src == qs)
        {
            c[top3++] = a[--top1];
            a[top1] = 0;
        }
        else
        {
            c[top3++] = b[--top2];
            b[top2] = 0;
        }
    }
}
void jbj(char src, char dst, char qs, char zj, char mb)
{
    //移动盘号
    if (src == qs)
        cout << a[top1 - 1];
    else if (src == zj)
        cout << b[top2 - 1];
    else
        cout << c[top3 - 1];
    cout << "# " << src << "-->" << dst << endl;
}
void bzjl(char src, char dst, char tmp, char qs, char zj, char mb)
{
    ++mm;
    cout << "第" << setw(4) << mm << "步(";
    if (src == qs)
        cout << setw(2) << a[top1 - 1];
    else if (src == zj)
        cout << setw(2) << b[top2 - 1];
    else
        cout << setw(2) << c[top3 - 1];
    cout << "#: " << src << "-->" << dst;
    cout << ") ";
}
void Dy(int l[10], int top)
{
    for (int i = 0; i < top; i++)
        cout << setw(2) << l[i];
    for (int i = top; i < 10; i++)
        cout << "  ";
}
void dy(char dy, char qs, char zj, char mb)
{
    if (dy == qs)
        Dy(a, top1);
    else if (dy == zj)
        Dy(b, top2);
    else
        Dy(c, top3);
}
void ture_dy(char qs, char zj, char mb)
{
    for (char i = 'A'; i < 'D'; i++)
    {
        cout << ' ' << i << ":";
        dy(i, qs, zj, mb);
    }
}
void judge()
{
    if (v == 0)
    {
        int ch;
        ch = _getch();
        while (ch != 13)
            ch = getchar();
    }
    else
        Sleep(60 - v * 10);
}
void column()
{
    cct_cls();
    for (int j = 0; j <= 2 * (9 + 23); j += 9 + 23)
        for (int i = 1; i <= 23; i++)
        {
            Sleep(5);
            cct_showch(i + j, 15, ' ', 3, 1, 1);
        }
    for (int i = 1; i <= 12; i++)
        for (int j = 12; j <= 2 * (9 + 23) + 12; j += 9 + 23)
        {
            Sleep(5);
            cct_showch(j, 15 - i, ' ', 3, 1, 1);
        }
}
void platform(char qs, char zj, char mb, int cl[])
{
    char m[21];
    for (int i = 0; i < 21; i++)
        m[i] = ' ';
    int x = 12 + (qs - 'A') * (23 + 9);
    int y = 15 - top1 - 1;
    for (int i = 1; i <= top1; i++)
        cct_showstr(x - i, y + i, m, cl[i - 1], 1, 1, 2 * i + 1);
    cct_setcolor();
}
//用于case4||8的起始
void first(char qs, char zj, char mb, int n, int select, int cl[])
{
    int  y = 0;
    cct_gotoxy(0, 0);
    cout << "从 " << qs << " 移动到 " << mb << "，共 " << n << " 层，延时设置为 " << v << "，";
    if (select == 8 || select == 9)
    {
        y = 16;
        column();
        platform(qs, zj, mb, cl);
        cct_setcolor();
    }
    cct_gotoxy(0, 17 + y);
    cout << "初始: ";
    for (char i = 'A'; i < 'D'; i++)
    {
        cout << ' ' << i << ":";
        dy(i, qs, zj, mb);
    }
    cct_gotoxy(9, 12 + y);
    for (int i = 0; i < 25; i++)
        cout << "=";
    cct_gotoxy(11, 13 + y);
    cout << "A";
    cct_gotoxy(21, 13 + y);
    cout << "B";
    cct_gotoxy(31, 13 + y);
    cout << "C";  for (int i = 0; i < top1; i++)
    {
        cct_gotoxy(10 + (qs - 'A') * 10, 11 - i + y);
        cout << setw(2) << a[i];
    }

    for (int i = 0; i < top2; i++)
    {
        cct_gotoxy(10 + (zj - 'A') * 10, 11 - i + y);
        cout << setw(2) << b[i];
    }

    for (int i = 0; i < top3; i++)
    {
        cct_gotoxy(10 + (mb - 'A') * 10, 11 - i + y);
        cout << setw(2) << c[i];
    }
}

//纵向打印数组
void dyy(char src, char dst, char qs, char zj, char mb, int select)
{
    for (char i = 'A'; i < 'D'; i++)
    {
        cout << ' ' << i << ":";
        dy(i, qs, zj, mb);
    }
    int k;
    if (select == 8)
        k = 29;
    else
        k = 13;

    int x1, x2;
    x1 = (src - 64) * 10;
    x2 = (dst - 64) * 10;

    if (src == qs)
    {
        cct_gotoxy(x1, k - top1 - 2);
        cout << "  ";
    }
    else if (src == zj)
    {
        cct_gotoxy(x1, k - top2 - 2);
        cout << "  ";
    }
    else
    {
        cct_gotoxy(x1, k - top3 - 2);
        cout << "  ";
    }
    if (dst == qs)
    {
        cct_gotoxy(x2, k - top1 - 1);
        cout << setw(2) << a[top1 - 1];
    }
    else if (dst == zj)
    {
        cct_gotoxy(x2, k - top2 - 1);
        cout << setw(2) << b[top2 - 1];
    }
    else
    {
        cct_gotoxy(x2, k - top3 - 1);
        cout << setw(2) << c[top3 - 1];
    }
}

int top(char test, char qs, char zj, char mb)
{
    if (test == qs)
        return top1;
    else if (test == zj)
        return top2;
    else
        return top3;
}

void move(int n, char src, char tmp, char dst, char qs, char zj, char mb, int cl[], int select)
{
    int vv = 50;
    if (select == 9)
        vv = 0;

    char m[21];
    for (int i = 0; i < 21; i++)
        m[i] = ' ';

    int topa, topb;
    topa = top(src, qs, zj, mb);
    topb = top(dst, qs, zj, mb);

    int x = 12 + (src - 'A') * (23 + 9);
    int x_ = 12 + (dst - 'A') * (23 + 9);
    int y = 15 - topa - 1;
    int i = n;

    for (int ii = y; ii > 0; ii--)
    {
        Sleep(vv);
        cct_showstr(x - i, ii, m, 0, 0, 1, 2 * i + 1);
        if (ii > 2)
            cct_showch(x, ii, ' ', 3, 1, 1);
        Sleep(vv);     if (ii > 1)
            cct_showstr(x - i, ii - 1, m, cl[i - 1], 1, 1, 2 * i + 1);
    }
    cct_setcolor();

    for (int xx = x; mb > qs ? xx < x_ : xx>x_; mb > qs ? xx++ : xx--)
    {
        Sleep(vv);
        cct_showstr(mb > qs ? xx - i : xx + i, 1, m, 0, 1, 1, 2 * i + 1);
        cct_showstr(xx - i + 1, 1, m, cl[i - 1], 1, 1, 2 * i + 1);
    }
    cct_showstr(mb > qs ? x_ - i : x_ + i, 1, m, 0, 1, 1, 2 * i + 1);
    cct_setcolor();

    for (int ii = 1; ii < 15 - topb; ii++)
    {
        Sleep(vv);
        cct_showstr(x_ - i, ii, m, 0, 0, 1, 2 * i + 1);
        if (ii > 2)
            cct_showch(x_, ii, ' ', 3, 3, 1);
        Sleep(vv);
        cct_showstr(x_ - i, ii + 1, m, cl[i - 1], 1, 1, 2 * i + 1);
    }
    cct_setcolor();

}

void act(int select, int n, char src, char tmp, char dst, char qs, char zj, char mb, int cl[])
{
    switch (select)
    {
    case 1:
        jbj(src, dst, qs, zj, mb);
        yd(src, dst, qs, zj, mb);
        break;
    case 2:
        bzjl(src, dst, tmp, qs, zj, mb);
        yd(src, dst, qs, zj, mb);
        cout << endl;
        break;
    case 3:
        bzjl(src, dst, tmp, qs, zj, mb);
        yd(src, dst, qs, zj, mb);
        ture_dy(qs, zj, mb);
        cout << endl;
        break;
    case 4:
        judge();
        cct_gotoxy(0, 17);
        bzjl(src, dst, tmp, qs, zj, mb);
        yd(src, dst, qs, zj, mb);
        dyy(src, dst, qs, zj, mb, select);
        break;
    case 8:
        judge();//28  33
        cct_gotoxy(0, 33);
        bzjl(src, dst, tmp, qs, zj, mb);
        yd(src, dst, qs, zj, mb);
        dyy(src, dst, qs, zj, mb, select);
        move(n, src, tmp, dst, qs, zj, mb, cl, select);
        cct_setcolor();
    }
}

void hanoi(int n, char src, char tmp, char dst, char qs, char zj, char mb, int select, int cl[])
{

    if (n != 1)
    {
        hanoi(n - 1, src, dst, tmp, qs, zj, mb, select, cl);
        act(select, n, src, tmp, dst, qs, zj, mb, cl);
        hanoi(n - 1, tmp, src, dst, qs, zj, mb, select, cl);
    }
    else
        act(select, n, src, tmp, dst, qs, zj, mb, cl);
}

void game(int n, char qs, char zj, char mb, int cl[])
{
    char st, hh, en;
    while (1)
    {
        cct_gotoxy(0, 35);
        cout << "请输入移动的柱号(命令形式：AC=A顶端的盘子移动到C，Q=退出) ：                                      ";

        cct_gotoxy(60, 35);
        st = getchar();
        en = getchar();
        if ((st == 'q' || st == 'Q') && en == '\n')
            break;
        else if ((st >= 'A' && st <= 'C' || st >= 'a' && st <= 'c') && en != st && (en >= 'A' && en <= 'C' || en >= 'a' && en <= 'c'))
        {
            if (st >= 97)
                st -= 32;
            if (en >= 97)
                en -= 32;
            hh = 65 + 66 + 67 - st - en;

            int topa = top(st, qs, zj, mb);
            if (topa == 0)
            {
                cct_gotoxy(0, 36);
                cout << "柱源为空!" << endl;
                Sleep(200);
                cct_gotoxy(0, 36);
                cout << "                                                                                                  ";
                continue;
            }

            int o;
            if (st == qs)
                o = a[top1 - 1];
            else if (st == zj)
                o = b[top2 - 1];
            else
                o = c[top3 - 1];

            int oo;
            if (en == qs)
                oo = a[top1 - 1];
            else if (en == zj)
                oo = b[top2 - 1];
            else
                oo = c[top3 - 1];

            int topb = top(en, qs, zj, mb);
            if (o > oo && topb != 0)
            {
                cct_gotoxy(0, 36);
                cout << "大盘压小盘，非法移动" << endl;
                Sleep(200);
                cct_gotoxy(0, 36);
                cout << "                                                                                                  ";
                continue;
            }

            cct_gotoxy(0, 33);
            cout << "                                                                                                  ";
            cct_gotoxy(0, 33);
            bzjl(st, en, hh, qs, zj, mb);
            yd(st, en, qs, zj, mb);
            dyy(st, en, qs, zj, mb, 8);
            move(o, st, hh, en, qs, zj, mb, cl, 9);

            int zls = 0;
            for (int i = 0; i < n; i++)
                if (c[i] != n - i)
                    zls = 1;
            if (zls == 0)
            {
                cct_gotoxy(0, 36);
                cout << "游戏结束!!!!!" << endl << endl;
                break;
            }
        }
        else
        {
            cct_gotoxy(0, 36);
            cout << "                                                                                                  ";
            continue;
        }


    }

}

void end()
{
    cout << "按回车键继续";
    char ch;
    ch = _getch();
    while (ch != 13)
        ch = _getch();

}

void menu1(int select)
{
    if (select == 5)
    {
        column();
        cct_setcolor();
        cct_gotoxy(0, 38);
    }
    else
    {
        int n;//层数
        char qs, mb, zj;

        int cl[10];//颜色
        start(&n, &qs, &mb, &zj, select, cl);

        if (select == 4 || select == 8 || select == 9)
        {
            cct_cls();
            first(qs, zj, mb, n, select, cl);
        }

        if (select == 6 || select == 7)
        {
            cout << "从 " << qs << " 移动到 " << mb << "，共" << n << "层" << endl;
            column();
            platform(qs, zj, mb, cl);
            if (select == 7)
            {
                yd(qs, mb, qs, zj, mb);
                move(1, qs, zj, mb, qs, zj, mb, cl, select);
            }
            cct_setcolor();
            cct_gotoxy(0, 38);
        }
        else if (select == 9)
            game(n, qs, zj, mb, cl);
        else
            hanoi(n, qs, zj, mb, qs, zj, mb, select, cl);
    }


    if (select > 0 && select < 4)
        cout << endl;
    else
        cct_gotoxy(0, 38);
    end();
}
