/* 2152611 邹良顺 信02 */
#include"90-02-b1.h"
struct step
{
	char row;
	char col;
	char num;
	char fo_num;
};

void backspace(int sudoku[9][9], step Steps[], int* time,int fix_num[9][9])
{
	if (*time > 0)
	{
		print_cell(sudoku, Steps, time, 0, fix_num);
		(*time)--;
		sudoku[Steps[*time].row - '1'][Steps[*time].col - 'A'] = Steps[*time].fo_num - '0';
		print_cell(sudoku, Steps, time, 1, fix_num);
		cct_gotoxy(60, 10);
		cout << "回退成功              " << endl;
	}
	else
	{
		cct_gotoxy(60, 10);
		cout << "无法回退              " << endl;
	}	
}
void in_num(int sudoku[9][9], int fix_num[9][9], int* time, struct step Steps[], char select, char &numm,bool &loop)
{
	if (fix_num[Steps[*time].row - '1'][Steps[*time].col - 'A'] != 0)
	{
		cct_gotoxy(60, 10);
		cout << "该值不可修改     ";
		Sleep(1000);
		cct_gotoxy(60, 10);
		cout << "                 ";
	}
	else
	{
		cct_gotoxy(3 + 6 * (Steps[*time].col - 'A') + 3 - 1, 1 + 3 * (Steps[*time].row - '1') + 2 - 1);
		cout << ' ';
		Steps[*time].fo_num = sudoku[Steps[*time].row - '1'][Steps[*time].col - 'A'] + '0';
		numm = _getch();
		while (numm < '0' || numm>'9')
		{
			cct_gotoxy(60, 10);
			cout << "输入错误";
			Sleep(1000);
			cct_gotoxy(60, 10);
			cout << "                 ";
			numm = _getch();
		}
		cct_gotoxy(3 + 6 * (Steps[*time].col - 'A') + 3 - 1, 1 + 3 * (Steps[*time].row - '1') + 2 - 1);
		cout << numm;
		Steps[*time].num = sudoku[Steps[*time].row - '1'][Steps[*time].col - 'A'] = numm - '0';
		(*time)++;
		Steps[*time].row = Steps[*time - 1].row;
		Steps[*time].col = Steps[*time - 1].col;
		loop = 0;
	}
}

void print_cell(int sudoku[9][9],step Steps[],int *time,int choose,int fix_num[9][9])
{
	cct_setcolor(3*choose,fix_num[Steps[*time].row - '1'][Steps[*time].col - 'A']==0?5:1);
	cct_gotoxy(3 + 6 * (Steps[*time].col-'A') + 3-1, 1 + 3 * (Steps[*time].row-'1') + 2-1);
	cout <<sudoku[Steps[*time].row-'1'][Steps[*time].col-'A'];
	cct_setcolor();
}
void print_file(long &HAND, _finddata_t result[15], int&k,char choose[])
{
	//共max个文件,add与菜单滚动有关
	int Y_of_key = 2,max=0,add=0;

	for (int i = 1; k != -1; i++)
	{
		k = _findnext(HAND, &result[i]);
		max = i;
	}

	int k1, k2, z, l, s, ret;
	bool loop=1;
	while (loop)
	{
		cct_setcursor(3);
		cct_gotoxy(0, 1);
		cout << "╔═══════════╗" << endl;
		for (int i = 0; i < 6; i++)
		{
			cout << "║";
			if (Y_of_key ==  i + 2)
				cct_setcolor(7, 0);
			cout << setw(22) << setiosflags(ios::left) << result[i+add].name;
			cct_setcolor();
			cout << "║" << endl;
		}
		cout << "╚═══════════╝" << endl;
		while (1)
		{
			//2-7
			ret = cct_read_keyboard_and_mouse(z, l, s, k1, k2);
			if (ret == 1)
			{
				if (224 == k1 && 80 == k2)
				{
					7==Y_of_key?(max==6+add?add+=0:add++):Y_of_key++;
					break;
				}
				else if (224 == k1 && 72 == k2)
				{
					2==Y_of_key?(0==add?add+=0:add--):Y_of_key--;
					break;
				}
				else if (13 == k1)
				{
					strcpy(choose, result[Y_of_key-2+add].name);
					loop = 0;
					cct_setcursor(2);
					break;
				}
				else
					continue;
			}

			else
				continue;
		}
	}
}
void print_pic(int sudoku[9][9], int fix_num[9][9], int identical[3][9],char select)
{
	if ('1' != select)
	{
		cct_cls();
		cct_gotoxy(0, 0);
	}

	if('1'==select)
		cout << "-+-a-b-c-+-d-e-f-+-g-h-i-" << endl;
	else
		cout << "     a     b     c     d     e     f     g     h     i" << endl;

	for (int i = 0; i < 9; i++)
	{	
		if ('1' == select)
		{
			if (i != 0 && !(i % 3))
				cout << "-+-------+-------+-------" << endl;

			cout << i + 1 << "| ";

			for (int j = 0; j < 9; j++)
			{
				//原始固定数据
				bool mod = 0, ident = 0;
				if (fix_num[i][j] == 0)
					mod = 1;
				//重复
				if (1 == identical[0][i] || 1 == identical[1][j] || 1 == identical[2][i / 3 * 3 + j / 3 + 1])
					ident = 1;

				cct_setcolor(7 * ident, sudoku[i][j] == 0 ? 5 : 1 + mod);
				cout << sudoku[i][j];
				cct_setcolor();

				cout << ((j + 1) % 3 ? " " : " | ");
			}
			cout << endl;
		}
		else
		{
			for (int turn = 1; turn <= 3; turn++)
			{
				if(2==turn)
					cout << ' ' << i + 1 << ' ';
				else
					cout << ' ' << ' ' << ' ';

				for (int j = 0; j < 9; j++)
				{
					//原始固定数据
					bool mod = 0, ident = 0;
					if (fix_num[i][j] == 0)
						mod = 1;
					//重复
					if (1 == identical[0][i] || 1 == identical[1][j] || 1 == identical[2][i / 3 * 3 + j / 3 + 1])
						ident = 1;

					switch (turn)
					{
					case 1:
						cct_setcolor(7 * ident, sudoku[i][j] == 0 ? 5 : 1 + mod);
						cout << "╔═╗";
						cct_setcolor();
						break;
					case 2:
						cct_setcolor(7 * ident, sudoku[i][j] == 0 ? 5 : 1 + mod);
						cout << "║" << sudoku[i][j] << " ║";
						cct_setcolor();
						break;
					case 3:
						cct_setcolor(7 * ident, sudoku[i][j] == 0 ? 5 : 1 + mod);
						cout << "╚═╝";
						cct_setcolor();
						break;
					}
					}
				cout << endl;
			}			
		}
	}

	if('1' == select)
		cout << "-+-------+-------+-------" << endl;
	if (select == '5')
	{
		cct_gotoxy(60, 11);
		cout << "++++++++++++++++++++++" << endl;
		cct_gotoxy(60, 12);
		cout << "+      慎点！！！    +" << endl;
		cct_gotoxy(60, 13);
		cout << "+   点一次收费一元   +" <<"  <--这是回退按钮  "<< endl;
		cct_gotoxy(60, 14);
		cout << "+将自动于一卡通中扣除+" << endl;
		cct_gotoxy(60, 15);
		cout << "++++++++++++++++++++++" << endl;
	}
}

void search_files(char select, char choose[20])
{
	int k;
	long HAND;
	_finddata_t result[15];
	HAND=k=_findfirst("sudoku*.txt", &result[0]);

	if ('1' == select)
	{
		while (k != -1)
		{
			cout << result[0].name << endl;
			k = _findnext(HAND, &result[0]);
		}
	}
	else
		print_file(HAND, result, k,choose);
	_findclose(HAND);
}
void open_files(int sudoku[9][9], int fix_num[9][9], int identical[3][9],char select,char choose[],bool &if_in_suc)
{
	fstream in;
	while (1)
	{
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 9; j++)
				identical[i][j] = 0;

		char file_name[20];
		if ('1' == select)
		{
			cout << "请输入数独题目文件名(回车表示默认sudoku.txt)：";
			cin.getline(file_name, 21, '\n');
			if (0 == strcmp(file_name, ""))
				strcpy(file_name, "sudoku.txt");
		}
		else
			strcpy(file_name, choose);

		in.open(file_name, ios::in);

		if (in.is_open() == 0)
			cout << "嘿嘿嘿，文件[" << file_name << "]打开失败喽！" << endl;
		else
		{
			bool con = 1;
			for (int i = 0; i < 81; i++)
				in >> *(*sudoku + i);
			in.close();

			for (int i = 0; i < 81; i++)
			{
				if (*(*sudoku + i) > 9 || *(*sudoku + i) < 0)
				{
					cout << "数独题目文件[" << file_name << "]有非法数字，请重新输入" << endl;
					con = 0;
					for (int i = 0; i < 81; i++)
						*(*sudoku + i)=0;
					break;
				}
			}
			if (if_identical(sudoku, identical) != 0)
			{
				cout << "原始数据有误，请重新输入。具体错误为：" << endl;
				print_pic(sudoku, fix_num, identical, select);
				if_in_suc = 0;
				con = 0;
			}
			if (0 == con)
				if (select == '1')
					continue;
				else
					break;

			for (int i = 0; i < 81; i++)
				*(*fix_num + i) = *(*sudoku + i);

			cout << "读入的数据为：" << endl;
			print_pic(sudoku, fix_num,identical, select);
			break;
		}		
	}
}

void putin_num(int sudoku[9][9], int fix_num[9][9], int* time, struct step Steps[],char select='2')
{				
	if (select <= '2')
	{
		while (1)
		{
			cout << "请按行/列/值的方式输入(例如:5c6=第5行第c列为6)，输入bk表示回退一次：";
			cin >> Steps[*time].row;
			cin >> Steps[*time].col;
			if (('b' == Steps[*time].row || 'B' == Steps[*time].row) && ('k' == Steps[*time].col || 'K' == Steps[*time].col))
			{
				if (*time > 0)
				{
					(*time)--;
					sudoku[Steps[*time].row - '1'][Steps[*time].col - 'A'] = Steps[*time].fo_num - '0';					
					break;
				}
				else
					cout << "回退失败" << endl;				
			}
			else
			{
				cin >> Steps[*time].num;//列以大写为准
				if (Steps[*time].col >= 'a' && Steps[*time].col <= 'z')
					Steps[*time].col -= 32;
				if (!(Steps[*time].row >= '1' && Steps[*time].row <= '9'))
					cout << "行" << Steps[*time].row << "不是[1-9]，请重新输入" << endl;
				else if (!(Steps[*time].col >= 'A' && Steps[*time].col <= 'Z'))
					cout << "列" << Steps[*time].col << "不是[a-i]，请重新输入" << endl;
				else if (!(Steps[*time].num >= '1' && Steps[*time].num <= '9'))
					cout << "值" << Steps[*time].num << "不是[1-9]，请重新输入" << endl;
				else if (0 != fix_num[Steps[*time].row - '1'][Steps[*time].col - 'A'])
					cout << "该位置是题目原始值，不能改变，请重新输入" << endl;
				else
				{
					Steps[*time].fo_num = sudoku[Steps[*time].row - '1'][Steps[*time].col - 'A'] + '0';
					sudoku[Steps[*time].row - '1'][Steps[*time].col - 'A'] = Steps[*time].num - '0';
					(*time)++;
					break;
				}
			}
		}
	}
	else if (select == '4')
	{			
		bool loop = 1;
		while (loop==1)
		{			
			print_cell(sudoku, Steps, time,1,fix_num);
			int x1, x2, x3, k1, k2,ret;
			char numm;
			ret = cct_read_keyboard_and_mouse(x1, x2, x3, k1, k2);
			if (ret == 1)
			{
				switch (k1)
				{
				case 224:
					print_cell(sudoku, Steps, time, 0,fix_num);
					switch (k2)
					{
					case KB_ARROW_LEFT:
						if (Steps[*time].col > 'A')
							Steps[*time].col--;
						break;
					case KB_ARROW_RIGHT:
						if (Steps[*time].col < 'I')
							Steps[*time].col++;
						break;
					case KB_ARROW_UP:
						if (Steps[*time].row > '1')
							Steps[*time].row--;
						break;
					case KB_ARROW_DOWN:
						if (Steps[*time].row < '9')
							Steps[*time].row++;
						break;
						}
					break;
				case 13:
					in_num(sudoku, fix_num, time, Steps, select, numm, loop);				
					break;
				case 8:
					backspace(sudoku, Steps, time, fix_num);
					break;
				}
			}
		}
	}
	else if (select == '5')
	{
		bool loop = 1, print = 0;
		while (loop)
		{
			if (print == 1)
				print_cell(sudoku, Steps, time, 1, fix_num);
			int x, y, m, k1, k2, ret;
			char numm;
			cct_enable_mouse();
			ret = cct_read_keyboard_and_mouse(x, y, m, k1, k2);
			if (ret == 0)
			{
				if (x >= 60 && x <= 82 && y >= 11 && y <= 15 && m == 0x0002)
				{
					backspace(sudoku, Steps, time, fix_num);
					continue;
				}
				if (x < 3 + 3 - 1 - 3 || y < 1 + 2 - 1 - 2 || x>3 + 6 * 9 + 3 - 1 - 3 || y>1 + 3 * 9 + 2 - 1 + 3 - 2)
					continue;
				for (int i = 0; i < 9; i++)
					if (3 + 6 * i + 3 - 1 - 3 <= x && 3 + 6 * i + 3 - 1 + 6 - 3 >= x)
					{
						print_cell(sudoku, Steps, time, 0, fix_num);
						Steps[*time].col = i + 'A';
						print = 1;
						break;
					}
				for (int i = 0; i < 9; i++)
					if (1 + 3 * i + 2 - 1 - 2 <= y && 1 + 3 * i + 2 - 1 + 3 - 2 >= y)
					{
						Steps[*time].row = i + '1';
						print = 1;
						break;
					}
				cct_gotoxy(60, 10);
				cout << "当前位置：row=" << Steps[*time].row << " col=" << Steps[*time].col << endl;

				if (m == 0x0002)
				{
					cct_gotoxy(60, 10);
					cout << "已选中 row=" << Steps[*time].row << " col=" << Steps[*time].col << "         " << endl;
					in_num(sudoku, fix_num, time, Steps, select, numm, loop);
					}
				}
			}
			cct_disable_mouse();
		}
	}
 
//判断是否重复  1 重复  0 不重复
int check_row(int sudoku[9][9], int identical[3][9])
{
	bool loop = 1;
	int ret=0;
	for (int i = 0; i < 9; i++)
		for(int j=0;j<9;j++)
			if (sudoku[i][j] != 0)
			{
				if (loop == 0)
					break;
				for (int k = j + 1; k < 9; k++)
					if (sudoku[i][j] == sudoku[i][k])
					{
						identical[0][i] = 1;
						ret++;
						loop = 0;
						break;
					}
					else
						identical[0][i] = 0;
			}
	return ret;
}
int check_col(int sudoku[9][9], int identical[3][9])
{
	bool loop = 1;
	int ret = 0;
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			if (sudoku[j][i] != 0)
			{
				if (loop == 0)
					break;
				for (int k = j + 1; k < 9; k++)
					if (sudoku[j][i] == sudoku[k][i])
					{
						identical[1][i] = 1;
						ret++;
						loop = 0;
						break;
					}
					else
						identical[1][i] = 0;
			}
	return ret;
}
int check_cell(int sudoku[9][9], int identical[3][9])
{
	bool loop = 1;
	int ret = 0;
	//0 3 6
	for (int i = 0; i < 3; i ++)
		for (int j = 0; j < 3; j ++)
			for (int k = 0; k < 9; k++)
				if (sudoku[i * 3 + k / 3][j * 3 + k % 3] != 0)
				{
					if (loop == 0)
						break;
					for (int l = k + 1; l < 9; l++)
						if (sudoku[i * 3 + k / 3][j * 3 + k % 3] == sudoku[i * 3 + l / 3][j * 3 + l % 3])
						{
							identical[2][i * 3 / 3 * 3 + j * 3 / 3 + 1] = 1;
							ret++;
							loop = 0;
							break;
						}
						else
							identical[2][i * 3 / 3 * 3 + j * 3 / 3 + 1] = 0;
				}
	return ret;
}
bool if_identical(int sudoku[9][9], int identical[3][9],bool p)
{
	if (p == 1)
	{
		cout << "存在重复的行、列、格个数分别为";
		cout << " row:" << check_row(sudoku, identical) << " col:" << check_col(sudoku, identical) << " cell:" << check_cell(sudoku, identical) << endl;
	}
	return check_row(sudoku,identical) + check_col(sudoku,identical) + check_cell(sudoku,identical);
}

bool if_end(int sudoku[9][9], int identical[3][9])
{
	bool full = 1;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
			if (0 == sudoku[i][j])
			{
				full = 0;
				break;
			}
		if (full == 0)
			break;
	}
	if (full && if_identical(sudoku,identical,0) == 0)
		return 1;
	else
		return 0;
}

void continu(char select)
{
	char a[10];
	while (1)
	{
		if (select == '4' || select == '5')
		{
			cct_gotoxy(60, 9);
			cout << "                       " << endl;
			cct_gotoxy(60, 9);
		}
		cout << "本小题结束，按输入End继续...";
		cin >> a;
		if (a[0] == 'E' && a[1] == 'n' && a[2] == 'd')
			break;
		else
		{
			cin.ignore(10000, '\n');
			if (select == '4' || select == '5')
				cct_gotoxy(60, 10);
			cout << "输入错误，请重新输入" << endl;
		}
	}
}

bool AI(int n,int sudoku[9][9],bool &succ, int fix_num[9][9], int identical[3][9], char select)
{
	if (n > 80)
	{
		succ = 1;
		return 1;
	}
	else
	{
		if (sudoku[n / 9][n % 9] != 0)
			AI(n + 1, sudoku, succ, fix_num, identical, select);
		else
		{
			for (int i = 1; i < 10; i++)
			{
				sudoku[n / 9][n % 9] = i;
				print_pic(sudoku, fix_num, identical, select);
				Sleep(10);
				if (if_identical(sudoku,identical,0) == 0)
					AI(n + 1, sudoku, succ, fix_num, identical, select);
				
				if (succ == 1)
					break;
				else
				{
					sudoku[n / 9][n % 9] = 0;
					if_identical(sudoku, identical, 0);
				}

			}
		}
		if (succ == 1)
			return 1;
		else
			return 0;
	}
}