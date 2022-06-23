/* 2152611 邹良顺  信02 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;
#include<io.h>
#include<sstream>
#include "../include/class_aat.h"


#define  HUCE   50

struct Stu
{
	string no = "*****";
	char name[70];
	bool truee = 0;
	bool if_ex = 0;
	bool if_ex_true = 0;
};//互测学生信息
struct info
{
	string classno;
	string no;
	string name;
	//首行
	string class_name_all;
	string class_name_simple;
	int res=0;

	bool if_self;
	bool if_check;
	bool if_tijiao = 1;
	Stu stu[HUCE];
};

//首行
int no_to_int(const char* n1)
{
	int int_no = 0;
	for (int i = 0; n1[i] != '\0'; i++)
	{
		int_no *= 10;
		int_no += n1[i] - '0';
	}
	return int_no;
}
int peek(FILE* file)
{
	int a;
	a = fgetc(file);
	ungetc(a, file);
	return a;
}
void ignore_n(FILE* file)
{
	while (1)
	{
		int c = fgetc(file);
		if (!(c == '\x0d' || c == '\x0a' || c == '\x20' || c == '\x09'))
		{
			ungetc(c, file);
			break;
		}
	}
}
void read_judge_firstline(FILE* stu_file, struct info& res)
{
	char STU_R[4][64];
	//忽略空格空行
	ignore_n(stu_file);
	//判断注释格式
	int if_true = 0;
	char geshi[2];
	fread(&geshi[0], 1, 1, stu_file);
	fread(&geshi[1], 1, 1, stu_file);
	if (geshi[0] == '/' && geshi[1] == '/')
		if_true = 1;
	else if (geshi[0] == '/' && geshi[1] == '*')
	{
		int c;
		while ((c = fgetc(stu_file)) != '\x0a' && c != '\x0d')
			if (c == '*')
				if (peek(stu_file) == '/')
				{
					if_true = 1;
					break;
				}
	}
	if (if_true == 0)
	{
		res.res = 2;
		return;
	}
	//读入信息
		//回到注释符号后面
	fseek(stu_file, 0, SEEK_SET);
	ignore_n(stu_file);
	fseek(stu_file, 2, SEEK_CUR);
	int if_in[4] = { 0 };
	//读入三个数据
		//判断个数
	for (int i = 0, con = 1; i < 4 && con == 1; i++)
	{
		while (1)
		{
			int c = fgetc(stu_file);
			if (c == '\x20' || c == '\x09')
				continue;
			else
			{
				ungetc(c, stu_file);
				break;
			}
		}

		int j;
		for (j = 0; j < 25; j++)
		{
			int c = fgetc(stu_file);
			if (c == '\x20' || c == '\x09')
				break;
			else if (c == '\x0a' || c == '\x0d')
			{
				con = 0;
				break;
			}
			else if (c == '*')
			{
				if (peek(stu_file) == '/')
				{
					con = 0;
					break;
				}
			}
			else
			{
				STU_R[i][j] = c;
				if_in[i] = 1;
			}
		}
		STU_R[i][j] = '\0';
	}
	//首行信息过多或过少
	if (if_in[0] + if_in[1] + if_in[2] < 3)
	{
		res.res = 3;
		return;
	}
	if (if_in[3] == 1)
	{
		res.res = 4;
		return;
	}
	//比较读入数据
	int if_no = 0, if_name = 0, if_class = 0;
	for (int i = 0; i < 3; i++)
	{
		if (strcmp(STU_R[i], res.no.c_str()) == 0)
			if_no = 1;
		else if (strcmp(STU_R[i], res.name.c_str()) == 0)
			if_name = 1;
		else if (strcmp(STU_R[i], res.class_name_all.c_str()) == 0)
			if_class = 1;
		else if (strcmp(STU_R[i], res.class_name_simple.c_str()) == 0)
			if_class = 1;
	}
	//判断读入数据
	if (if_no == 0)
		res.res += 10;
	if (if_name == 0)
		res.res += 50;
	if (if_class == 0)
		res.res += 100;
	if (if_no + if_name + if_class == 3)
		res.res = 0;

	return;
}
int if_a_is_small(string ch_a, string ch_b)
{
	int int_a[3] = { 0 };
	int int_b[3] = { 0 };

	for (int i = 0, j = 0; i < 3; i++, j++)
	{
		if (ch_a[j] == '-')
			continue;
		else if (ch_a[j] == '.')
			break;
		else if (!(ch_a[j] >= '0' && ch_a[j] <= '9'))
			j++;
		int_a[i] *= 10;
		int_a[i] += (ch_a[j] - '0');
	}
	for (int i = 0, j = 0; i < 3; i++, j++)
	{
		if (ch_b[j] == '-')
			continue;
		else if (ch_b[j] == '.')
			break;
		else if (!(ch_a[j] >= '0' && ch_a[j] <= '9'))
			j++;
		int_b[i] *= 10;
		int_b[i] += (ch_b[j] - '0');
	}

	if (int_a[0] < int_b[0])
		return 1;
	else if (int_a[0] == int_b[0])
		if (int_a[1] < int_b[1])
			return 1;
		else if (int_a[1] == int_b[1])
			if (int_a[2] < int_b[2])
				return 1;
			else
				return 0;
		else
			return 0;
	else
		return 0;
}

//次行

void ignore_n(fstream& file)
{
	while (1)
	{
		int c = file.peek();
		if (!(c == '\x0d' || c == '\x0a' || c == '\x20' || c == '\x09'))
			break;
		else
			file.get();
	}
}
void my_getline(char* a, fstream& file, int n)
{
	char ch;
	int i;
	for (i = 0; i < n - 1; i++)
	{
		ch = file.get();
		if (ch == ' ' || ch == '\t' || ch == '\x0d' || ch == '\x0a')
			break;
		a[i] = ch;
	}
	a[i] = '\0';
}
bool read_stulist(ostringstream& msg, info*& big_inf,const char courseid[8],const char stulist[64],int type=1)
{
	//15-b9 --secondline --courseid 100692 --filename 5-b14.c --debug 11111
	fstream file;
	//打开文件.dat
	char filename[50];
	sprintf(filename, "./source/%s", stulist);
	file.open(filename, ios::in | ios::binary);
	if (file.is_open() == 0)
	{
		cout << "无法打开" << stulist  << endl;
		return 0;
	}

	//判断学生人数
	int time = 1, no_of_n = 1, stu = 0, i;
	bool mmm = 1;
	int numm = 0;
	while (1)
	{
		numm++;
		int ch = file.get();
		if (ch == '#')
		{
			no_of_n++;
			while (file.get() != '\x0a')
				;
			numm = 0;
		}
		else if (ch == '\n')
		{
			numm = 0;
			if (file.peek() != -1)
				time++;
			no_of_n++;
		}
		else if (ch == -1)
			break;
		else if (numm == 256)
			break;
	}
	file.close();

	//读
	file.open(filename, ios::in | ios::binary);
	big_inf = new info[time + 1];
	if (big_inf == NULL)
	{
		msg.str("");
		msg << "内存申请失败" << endl;
		return 0;
	}
	for (i = 1; i <= no_of_n; i++)
	{
		if (file.peek() == -1)
			break;
		//忽略注释行
		while (file.peek() == '#')
		{
			msg << "\t--> 学生名单[./source/" << courseid << ".dat]中的第[" << i << "]行为注释行，忽略" << endl;
			i++;
			while (file.get() != '\x0a')
				;
		}
		file >> big_inf[stu].classno >> big_inf[stu].no;

		//判断学号是否重复
		bool ident = 0;
		for (int j = 0; j < stu; j++)
			if (big_inf[stu].no==big_inf[j].no)
			{
				mmm = 0;
				msg << "\t--> 学生名单[./source/" << courseid << ".dat]中的第[" << i << "]行学号[" << big_inf[j].no << "]重复，忽略" << endl;
				ident = 1;
				while (file.get() != '\x0a')
					;
				break;
			}
		//判断结束
		if (ident == 1)
			continue;

		file >> big_inf[stu].name;
		if (type == 1)
			file >> big_inf[stu].if_self >> big_inf[stu].if_check;
		else
			file >> big_inf[stu].class_name_all >> big_inf[stu].class_name_simple;

		stu++;
	}

	big_inf[stu - mmm].classno="*****";
	file.close();
	msg << "读取完成，共[" << i - 1 - mmm << "]行有内容，去重后学生总数[" << stu - mmm << "]个" << endl;

	return 1;
}
void print_stulist(info*& big_inf, ostringstream& msg, const char courseid[8], const char filename[64])
{
	for (int i = 0; strcmp(big_inf[i + 1].classno.c_str(), "*****") != 0; i++)
	{
		int min = i;
		for (int j = i + 1; strcmp(big_inf[j].classno.c_str(), "*****") != 0; j++)
		{
			if (no_to_int(big_inf[j].classno.c_str()) < no_to_int(big_inf[min].classno.c_str()))
				min = j;
		}
		info cup = big_inf[i];
		big_inf[i] = big_inf[min];
		big_inf[min] = cup;
	}

	for (int i = 0; strcmp(big_inf[i + 1].classno.c_str(), "*****") != 0; i++)
	{
		int min = i;
		for (int j = i + 1; strcmp(big_inf[j].classno.c_str(), "*****") != 0 && strcmp(big_inf[i].classno.c_str(), big_inf[j].classno.c_str()) == 0; j++)
		{
			if (no_to_int(big_inf[j].no.c_str()) < no_to_int(big_inf[min].no.c_str()))
				min = j;
		}
		info cup = big_inf[i];
		big_inf[i] = big_inf[min];
		big_inf[min] = cup;

	}
	msg << "序号    课号    学号    姓名    原始程序正确    校验程序正确" << endl;

	for (int i = 0; strcmp(big_inf[i].classno.c_str(), "*****") != 0; i++)
	{
		//417#    10069204        2150270 姚轶恺  1       1
		msg << i + 1 << "#\t" << big_inf[i].classno << "\t" << big_inf[i].no << '\t' << big_inf[i].name << "\t" << big_inf[i].if_self << "\t" << big_inf[i].if_check << endl;
	}

}
void read_2nd_line(info*& big_inf, ostringstream& msg, const char courseid[8], const char filename[64])
{
	msg << "序号    课号    学号    姓名    文件名  分析结果" << endl;
	for (int i = 0; strcmp(big_inf[i].classno.c_str(), "*****") != 0; i++)
	{
		char fname[200];
		sprintf(fname, "./source/%s-%s/%s-%s-%s", big_inf[i].classno.c_str(), filename, big_inf[i].no.c_str(), big_inf[i].name.c_str(), filename);
		fstream file;
		file.open(fname, ios::in | ios::binary);
	
		//打开文件
		if (file.is_open() == 0)
		{
			//892#    10069206        2154316 陈远哲  5-b14.c 未提交
			big_inf[i].if_tijiao = 0;
			msg << i + 1 << "#\t" << big_inf[i].classno << "\t" << big_inf[i].no << "\t" << big_inf[i].name << "\t" << filename << '\t' << "未提交" << endl;
			continue;
		}

		//忽略首行
		ignore_n(file);
		while (file.get() != '\x0a')
			;

		//忽略空格空行
		ignore_n(file);
		//判断注释格式
		int if_true = 0;
		char geshi[2];
		geshi[0] = file.get();
		geshi[1] = file.get();
		if (geshi[0] == '/' && geshi[1] == '/')
			if_true = 1;
		else if (geshi[0] == '/' && geshi[1] == '*')
		{
			int c;
			while ((c = file.get()) != '\x0a' && c != '\x0d')
				if (c == '*')
					if (file.peek() == '/')
					{
						if_true = 1;
						break;
					}
		}
		if (if_true == 0)
		{
			msg << i + 1 << "#\t" << big_inf[i].classno << "\t" << big_inf[i].no << "\t" << big_inf[i].name << "\t" << filename << '\t' << "第2行信息有错[不是//或/*开头，或者以/*开头但*/不在同一行]" << endl;
			continue;
		}
		//读入信息
			//回到注释符号后面
		file.seekg(0, ios::beg);
		ignore_n(file);
		while (file.get() != '\x0a')
			;
		ignore_n(file);
		file.seekg(2, ios::cur);
		//判断互测学生个数
		int time = 0, count = 0;
		while (1)
		{
			count++;
			int ch, chp;
			if ((ch = file.get()) != '\t' && ch != '*' && ch != '\x20' && ch != '/' && ch != '\x0d' && ch != '\x0a' && ((chp = file.peek()) == '\t' || chp == '*' || chp == '\x20' || chp == '\x0a' || chp == '\x0d'))
			{
				count = 0;
				time++;
			}
			if (count == 63)
				time++;
			if (ch == '\x0a' || (ch == '*' && (chp = file.peek()) == '/'))
				break;
		}
		bool un_complete = 0;
		if (time % 2 == 1)
			un_complete = 1;
		time = (time - time % 2) / 2;//time奇数表示不完整，未读入不完整信息

			//读入				

		//回到注释符后面
		file.seekg(0, ios::beg);
		ignore_n(file);
		while (file.get() != '\x0a')
			;
		ignore_n(file);
		file.seekg(2, ios::cur);
		ignore_n(file);
		int m;
		for (m = 0; m < time; m++)
		{
			char no[200];
			my_getline(no, file, 64);		
			ignore_n(file);
			my_getline(big_inf[i].stu[m].name, file, 64);			
			ignore_n(file);
			big_inf[i].stu[m].no = no;
		}

		if (big_inf[i].stu[m - 1].name[strlen(big_inf[i].stu[m - 1].name) - 2] == '*' && big_inf[i].stu[m - 1].name[strlen(big_inf[i].stu[m - 1].name) - 1] == '/')
			big_inf[i].stu[m - 1].name[strlen(big_inf[i].stu[m - 1].name) - 2] = '\0';

		//判断学号姓名是否匹配		
		for (int m = 0; m < time; m++)
		{
			for (int n = 0; strcmp(big_inf[n].classno.c_str(), "*****") != 0; n++)
			{
				if (strcmp(big_inf[i].stu[m].no.c_str(), big_inf[n].no.c_str()) == 0 && strcmp(big_inf[i].stu[m].name, big_inf[n].name.c_str()) == 0)
				{
					big_inf[i].stu[m].truee = 1;
					break;
				}
			}
		}

		//输出结果
			//错误输出
		msg << i + 1 << "#\t" << big_inf[i].classno << "\t" << big_inf[i].no << "\t" << big_inf[i].name << "\t" << filename << '\t';
		bool if_first = 1, truee = 0, self = 0;
		int selfno = time;
		for (int m = 0; m < time; m++)
		{
			//验了自己
			if (big_inf[i].stu[m].no== big_inf[i].no)
			{
				self = 1;
				selfno = m;
				msg << (if_first == 1 ? "" : "                                        ") << "第[" << m + 1 << "]项写了自己，耍无赖么？" << endl;
				big_inf[i].stu[m + 1].no= "*****";
				break;
			}
			//不匹配
			if (big_inf[i].stu[m].truee == 0)
			{
				if (if_first)
					msg << "第[" << m + 1 << "]项的学号[" << big_inf[i].stu[m].no << "]/姓名[" << big_inf[i].stu[m].name << "]不正确，忽略" << endl;
				else
					msg << "                                        " << "第[" << m + 1 << "]项的学号[" << big_inf[i].stu[m].no << "]/姓名[" << big_inf[i].stu[m].name << "]不正确，忽略" << endl;
				if_first = 0;
				continue;
			}
			else if (big_inf[i].stu[m].truee == 1)
				truee = 1;
			//重复
			for (int l = 0; l < m; l++)
				if (big_inf[i].stu[m].no== big_inf[i].stu[l].no)
				{
					big_inf[i].stu[m].truee = 0;
					msg << (if_first == 1 ? "" : "                                        ") << "互验列表第[" << m + 1 << "]项的学号[" << big_inf[i].stu[m].no << "]重复，忽略" << endl;
					if_first = 0;
					break;
				}
		}

		if (un_complete == 1)
			msg << (if_first == 1 ? "" : "                                        ") << "第[" << time << "]个学生后面的信息不全，忽略" << endl;

		if (if_first == 1 && un_complete == 0 && self == 0)
			msg << "ok" << endl;
		//正确输出
		if (truee)
		{
			int num = 1;
			msg << "        读到的正确互验者" << endl;


			//学号升序
			for (int m = 0; m < time && m < selfno; m++)
			{
				int min = m;
				for (int j = m + 1; j < time && j < selfno; j++)
				{
					if (no_to_int(big_inf[i].stu[j].no.c_str()) < no_to_int(big_inf[i].stu[min].no.c_str()))
						min = j;
				}
				Stu cup = big_inf[i].stu[m];
				big_inf[i].stu[m] = big_inf[i].stu[min];
				big_inf[i].stu[min] = cup;
			}

			for (int m = 0; m < time && m < selfno; m++)
			{
				if (big_inf[i].stu[m].truee == 1)
				{
					//1       2151128 林天天
					msg << "        " << num << "\t" << big_inf[i].stu[m].no << '\t' << big_inf[i].stu[m].name << endl;
					num++;
				}
			}
		}
		else
			big_inf[i].stu[0].no= "*****";
		file.close();

	}
	
}
void print_2nd_line(info*& big_inf, ostringstream& msg, const char courseid[8], const char filename[64])
{
	msg << "序号    课号    学号    姓名" << endl;
	for (int i = 0; big_inf[i].classno!="*****"; i++)
	{
		//894#    10069206        2154392 袁嘉佐  无有效匹配项
		if (big_inf[i].stu[0].no=="*****")
		{
			msg << i + 1 << "#\t" << big_inf[i].classno << "\t" << big_inf[i].no << "\t" << big_inf[i].name << "\t" << "无有效匹配项" << endl;
			continue;
		}
		for (int m = 0; big_inf[i].stu[m].no!="*****"; m++)
		{
			if (big_inf[i].stu[m].truee == 1)
			{
				//寻找所验学生
				for (int n = 0; strcmp(big_inf[n].classno.c_str(), "*****") != 0; n++)
				{
					if (big_inf[i].stu[m].no== big_inf[n].no)//学号匹配
					{
						big_inf[i].stu[m].if_ex_true = big_inf[n].if_check;
						for (int j = 0; big_inf[n].stu[j].no!="*****"; j++)
							if (big_inf[n].stu[j].no!=big_inf[i].no && big_inf[n].stu[j].truee == 1)//成功互验
							{
								big_inf[i].stu[m].if_ex = 1;
								break;
							}
						break;
					}
				}

			}
		}

		msg << i + 1 << "#\t" << big_inf[i].classno << "\t" << big_inf[i].no << "\t" << big_inf[i].name << endl;
		for (int m = 0, time = 1; big_inf[i].stu[m].no!="*****"; m++)
		{
			if (big_inf[i].stu[m].truee == 1)
			{
				//      $6      2154309 林越野  抛弃了你
				msg << "        $" << time << "\t" << big_inf[i].stu[m].no << '\t' << big_inf[i].stu[m].name << '\t';
				if (big_inf[i].stu[m].if_ex == 1)
					msg << "ok" << endl;
				else
					msg << "抛弃了你" << endl;
				time++;
			}
		}
	}
}
void print_finalscore(info*& big_inf, ostringstream& msg, const char courseid[8], const char filename[64])
{
	msg << "序号    课号    学号    姓名    原始程序得分    检查程序原始分  检查程序扣分1   检查程序扣分2   检查程序总分" << endl;
	for (int i = 0; strcmp(big_inf[i].classno.c_str(), "*****") != 0; i++)
	{
		//1#      10069201        2150233 朱申哲  100     100     -200    0       -100
		int result[5] = { 0 }, time = 0;
		if (big_inf[i].if_self == 1)
			result[4] = 100;
		if (big_inf[i].if_check == 1 && big_inf[i].if_tijiao == 1)
			result[0] = 100;
		for (int m = 0; big_inf[i].stu[m].no!= "*****"; m++)
		{
			if (big_inf[i].stu[m].truee == 1)
			{
				time++;
				if (big_inf[i].stu[m].if_ex_true == 0)
					result[2] -= 20;
				if (big_inf[i].stu[m].if_ex == 0)
					result[1] -= 100;
			}
		}
		if (time < 5)
			result[2] -= 20 * (5 - time);
		result[3] = result[0] + result[1] + result[2];

		msg << i + 1 << '#' << "\t" << big_inf[i].classno << "\t" << big_inf[i].no << '\t' << big_inf[i].name << "\t" << result[4] << "\t" << result[0] << '\t' << result[1] << "\t" << result[2] << "\t" << result[3] << endl;
	}
	delete[]big_inf;
}
static int second_line_check(const char courseid[8],const char filename[64],const char debug[5],const char *stulist) //参数自行约定，其中有一个是debug[5] 
{
	ostringstream msg;
	bool conti = 1;
	/* 允许加入其它语句，但不能有cout */
	info* big_inf = NULL;//大数组


	/* 读课号.dat */
	msg << "1.读取课号配置文件" << endl;
	conti = read_stulist(msg, big_inf, courseid, stulist); //允许带返回值（也可以不要），参数自行约定，其中有一个是msg 
	/* 允许加入其它语句(也可以不要)，但不能有cout */
	if (conti == 0)
		return 0;
	if (debug[0] == '1')
		cout << msg.str() << endl;
	/* 允许加入其它语句，但不能有cout */

	msg.str(""); //清空msg中的信息
	msg << "2.按课号+学号排序的学生名单" << endl;
	print_stulist(big_inf, msg, courseid, filename); //允许带返回值（也可以不要），参数自行约定，其中有一个是msg 
	/* 允许加入其它语句(也可以不要)，但不能有cout */
	if (debug[1] == '1')
		cout << msg.str() << endl;

	/* 允许加入其它语句，但不能有cout */

	msg.str(""); //清空msg中的信息
	msg << "3.所有学生读取第2行的解析信息" << endl;
	read_2nd_line(big_inf, msg, courseid, filename); //允许带返回值（也可以不要），参数自行约定，其中有一个是msg 
	/* 允许加入其它语句(也可以不要)，但不能有cout */
	if (debug[2] == '1')
		cout << msg.str() << endl;

	/* 允许加入其它语句，但不能有cout */

	/* 将双方进行信息匹配 */
	msg.str(""); //清空msg中的信息
	msg << "4.所有学生的第2行互验匹配结果" << endl;
	print_2nd_line(big_inf, msg, courseid, filename); //允许带返回值（也可以不要），参数自行约定，其中有一个是msg 
	/* 允许加入其它语句(也可以不要)，但不能有cout */
	if (debug[3] == '1')
		cout << msg.str() << endl;

	/* 允许加入其它语句，但不能有cout */

	/* 再根据通过与否进行检查 */
	msg.str(""); //清空msg中的信息
	msg << "5.所有学生的第2行互验最终得分" << endl;
	print_finalscore(big_inf, msg, courseid, filename); //允许带返回值（也可以不要），参数自行约定，其中有一个是msg 
	/* 允许加入其它语句(也可以不要)，但不能有cout */
	if (debug[4] == '1')
		cout << msg.str() << endl;

	/* 允许加入其它语句，但不能有cout */
	delete[]big_inf; 
	return 0;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：具体略，实际使用时，放入另一个cpp(例：hw_check_secondline.cpp)更合理
 ***************************************************************************/
int check_secondline(const string& cno, const string &stulist_fname, const string& filename, const string &debug)
{
	cout << "开始进行源程序文件次行检查..." << endl;

	ostringstream msg;
	second_line_check(cno.c_str(), filename.c_str(), debug.c_str(), stulist_fname.c_str());
	cout << msg.str();

	return 0;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：具体略，实际使用时，放入另一个cpp(例：hw_check_secondline.cpp)更合理
 ***************************************************************************/
int check_firstline(const string& cno, const string &stilist_fname, const string& filename)
{
	cout << "开始进行源程序文件首行检查..." << endl;
	
	//读学生名单
	info *big_info;
	ostringstream  msg;
	read_stulist(msg, big_info, cno.c_str(), stilist_fname.c_str(), 0);
	//打开学生文件
	for (int i = 0; big_info[i + 1].classno!="*****"; i++)
	{
		string fname = "./source/" + big_info[i].classno + "-" + filename + "/" + big_info[i].no + "-" + big_info[i].name + "-" + filename;
		FILE* file;
		file = fopen(fname.c_str(), "r");
		if (file == NULL)
		{
			big_info[i].res = 1;
			continue;
		}
		read_judge_firstline(file, big_info[i]);
		fclose(file);		
	}
	//输出
	for (int i = 0; big_info[i + 1].classno != "*****"; i++)
	{
		cout << big_info[i].no << "-" << big_info[i].name << "-" << big_info[i].class_name_all << " : " << filename<< " : ";
		if (big_info[i].res == 0)
			cout<<"通过"<<endl;
		else if (big_info[i].res == 1)
			cout<<"未提交"<<endl;
		else if (big_info[i].res == 2)
			cout<<"未取到首行信息"<<endl;
		else if (big_info[i].res == 3)
			cout<<"首行信息不全"<<endl;
		else if (big_info[i].res == 4)
			cout<<"首行信息过多"<<endl;
		else if (big_info[i].res == 160)
			cout<<"学号不匹配 姓名不匹配 班级不匹配 "<<endl;
		else if (big_info[i].res == 150)
			cout<<"姓名不匹配 班级不匹配 "<<endl;
		else if (big_info[i].res == 110)
			cout<<"学号不匹配 班级不匹配 "<<endl;
		else if (big_info[i].res == 60)
			cout<<"学号不匹配 姓名不匹配 "<<endl;
		else if (big_info[i].res == 10)
			cout<<"学号不匹配 "<<endl;
		else if (big_info[i].res == 50)
			cout<<"姓名不匹配 "<<endl;
		else if (big_info[i].res == 100)
			cout<<"班级不匹配 "<<endl;

		if (big_info[i].no != big_info[i + 1].no && "all" == filename)
			cout<<endl;
	}

	return 0;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
static void usage(const char* const procname, const int args_num)
{
	const int wkey = 7 + strlen(procname) + 1;
	const int wopt = 7 + strlen(procname) + 4;

	cout << endl;
	cout << "Usage: " << procname << " { --firstline | --secondline  }" << endl;
	cout << setw(wkey) << ' ' << "{ --courseid cid }" << endl;
	cout << setw(wkey) << ' ' << "{ --filename name/all }" << endl;
	cout << setw(wkey) << ' ' << "{ --stulist_fname name }" << endl;
	cout << setw(wkey) << ' ' << "{ --debug 11111 }" << endl;
	cout << endl;

	cout << setw(wkey) << ' ' << "必选项：指定检查类型(多选一)" << endl;
	cout << setw(wopt) << ' ' << "--firstline     : 首行检查" << endl;
	cout << setw(wopt) << ' ' << "--fileformat    : 次行检查" << endl;
	cout << setw(wkey) << ' ' << "必选项：" << endl;
	cout << setw(wopt) << ' ' << "--courseid      : 课号" << endl;
	cout << setw(wopt) << ' ' << "--filename      : 文件名(all表示全部)" << endl;
	cout << setw(wopt) << ' ' << "--stulist_fname : 对应的学生列表文件名" << endl;
	cout << setw(wkey) << ' ' << "可选项：" << endl;
	cout << setw(wopt) << ' ' << "--debug         : Debug选项(仅适用于--secondline，默认11111)" << endl;
	cout << endl;

	cout << "e.g.   " << procname << " --firstline --courseid 100692 --filename 3-b1.cpp --stulist_fname 100692.txt               : 检查100692课程的3-b1.cpp的首行" << endl;
	cout << "       " << procname << " --firstline --courseid 100692 --filename all --stulist_fname 100692-firstline.txt          : 检查100692课程的全部文件的首行" << endl;
	cout << "       " << procname << " --secondline --courseid 100742 --filename 15-b5.c --stulist_fname 100692.dat               : 检查100742课程的15-b5.c的次行，输出全部信息" << endl;
	cout << "       " << procname << " --secondline --courseid 100742 --filename 15-b5.c --stulist_fname 100692.dat --debug 01001 : 检查100742课程的15-b5.c的次行，仅输出2、5项信息" << endl;
	cout << endl;

	if (args_num == 1) {
		cout << endl << endl << "请在cmd下加参数运行." << endl << endl;
		system("pause");
	}
}

/* enum的顺序要和args的排列顺序保持一致
   不用enum class 只是不想每次都做强制转换 */
enum OPT_ARGS { OPT_ARGS_HELP = 0, OPT_ARGS_FIRSTLINE, OPT_ARGS_SECONDLINE, OPT_ARGS_COURSEID, OPT_ARGS_FILENAME, OPT_ARGS_STULIST_FNAME, OPT_ARGS_DEBUG
};

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int main(int argc, char** argv)
{
	args_analyse_tools args[] = {
		args_analyse_tools("--help", ST_EXTARGS_TYPE::boolean, 0, false),
		args_analyse_tools("--firstline", ST_EXTARGS_TYPE::boolean, 0, false),
		args_analyse_tools("--secondline", ST_EXTARGS_TYPE::boolean, 0, false),
		args_analyse_tools("--courseid", ST_EXTARGS_TYPE::str, 1, string("")),
		args_analyse_tools("--filename", ST_EXTARGS_TYPE::str, 1, string("")),
		args_analyse_tools("--stulist_fname", ST_EXTARGS_TYPE::str, 1, string("")),
		args_analyse_tools("--debug", ST_EXTARGS_TYPE::str, 1, string("11111")),
		args_analyse_tools()  //最后一个，用于结束
	};

	int cur_argc, ret = 0;

	//最后一个参数1，表示除选项参数外，还有其它参数
	if ((cur_argc = args_analyse_process(argc, argv, args, 0)) < 0) {
		//错误信息在函数中已打印
		
		return -1;
	}

	/* 需要自己实现 */
	args_analyse_print(args);

	/* 对help做特殊处理 */
	if (args[OPT_ARGS_HELP].existed()) {
		//只要有 --help，其它参数都忽略，显示帮助即可
		usage(argv[0], argc);
		return -1; //执行完成直接退出
	}

	/* 检查参数互斥性 */
	if (args[OPT_ARGS_FIRSTLINE].existed() + args[OPT_ARGS_SECONDLINE].existed() != 1) {
		usage(argv[0], argc);
		cout << "参数[" << args[OPT_ARGS_FIRSTLINE].get_name() << "|" << args[OPT_ARGS_SECONDLINE].get_name() << "]必须指定一个且只能指定一个" << endl;
		return -1;
	}

	/* 判断必选项是否存在 */
	if (args[OPT_ARGS_COURSEID].existed() == 0) {
		cout << "必须指定参数[" << args[OPT_ARGS_COURSEID].get_name() << "]" << endl;
		usage(argv[0], argc);
		return -1;
	}

	/* 判断必选项是否存在 */
	if (args[OPT_ARGS_FILENAME].existed() == 0) {
		cout << "必须指定参数[" << args[OPT_ARGS_FILENAME].get_name() << "]" << endl;
		usage(argv[0], argc);
		return -1;
	}

	/* 判断必选项是否存在 */
	if (args[OPT_ARGS_STULIST_FNAME].existed() == 0) {
		cout << "必须指定参数[" << args[OPT_ARGS_STULIST_FNAME].get_name() << "]" << endl;
		usage(argv[0], argc);
		return -1;
	}

	/* 判断 --firstline 和 --debug 是否冲突 */
	if (args[OPT_ARGS_FIRSTLINE].existed() + args[OPT_ARGS_DEBUG].existed() == 2) {
		cout << "参数[" << args[OPT_ARGS_FIRSTLINE].get_name() << "]不需要[" << args[OPT_ARGS_DEBUG].get_name() << "]" << endl;
		usage(argv[0], argc);
		return -1;
	}

	/* 判断 --secondline 和 --filename all 是否冲突 */
	if (args[OPT_ARGS_SECONDLINE].existed()) {
		if (args[OPT_ARGS_FILENAME].get_string() == "all") {
			cout << "参数[" << args[OPT_ARGS_SECONDLINE].get_name() << "]的[" << args[OPT_ARGS_SECONDLINE].get_name() << "]不能为all" << endl;
			usage(argv[0], argc);
			return -1;
		}
	}

	if (args[OPT_ARGS_FIRSTLINE].existed()) {
		/* 进行首行检查 */
		check_firstline(args[OPT_ARGS_COURSEID].get_string(), args[OPT_ARGS_STULIST_FNAME].get_string(), args[OPT_ARGS_FILENAME].get_string());
	}
	else if (args[OPT_ARGS_SECONDLINE].existed()) {
		/* 进行次行检查 */
		check_secondline(args[OPT_ARGS_COURSEID].get_string(), args[OPT_ARGS_STULIST_FNAME].get_string(), args[OPT_ARGS_FILENAME].get_string(), args[OPT_ARGS_DEBUG].get_string());
	}

	return 0;
}
