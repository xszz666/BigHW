/* 邹良顺 2152611 信02 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <io.h>
#include "../include/class_cft.h"
#include "../include/class_cft_gai.h"
//允许加入其它需要的头文件
using namespace std;

#define size_of_n 2

#if ! ENABLE_LIB_TCFG_TOOLS	//禁用lib后才能编译

/* ---------------------------------------------------------------
	 允许加入其它需要的struct/class/union/函数等（内部工具用）
	 1、函数必须为静态，不对外
	 2、允许定义符号常量/常变量
	 3、尽量不要用全局变量，如果一定要用，加static
   ---------------------------------------------------------------- */
static int size_of_file(fstream& f)
{
	int pos = int(f.tellg());
	int n = 0;

	f.seekg(0, ios::beg);
	while (1)
	{
		char ch = f.get();
		if (ch == -1)
			break;
		else
			n++;
	}
	f.clear();
	f.seekg(pos, ios::beg);

	return n;

}

//未改变文件大小  删除指针当前位置前m个字节  指针后移m字节
static void delete_in_file(fstream& fp, int size_of_delete)
{
	while (1)
	{
		char ch = fp.get();

		fp.seekg(-size_of_delete - 1, ios::cur);

		fp << ch;
		if (ch == -1)
			break;

		fp.seekg(size_of_delete, ios::cur);
	}
	fp.clear();

}

//函数调用结束，指针指在写入位置
static void insert_to_file(fstream& fp, int insert_pos, int insert_size, const char* insert_s)
{

	fp.seekg(0, ios::end);
	//整体后移insert_size
		//最后insert_size字节
	for (int i = 0; i < insert_size; i++)
	{
		fp.seekg(-insert_size, ios::cur);
		char ch = fp.get();
		fp.seekg(insert_size - 1, ios::cur);
		fp << ch;
	}

	//其余字节
	fp.clear();
	fp.seekg(-insert_size - 1, ios::end);
	while (fp.tellg() >= insert_size)
	{
		fp.seekg(-insert_size, ios::cur);
		char ch = fp.get();
		fp.seekg(insert_size - 1, ios::cur);
		fp << ch;
		fp.seekg(-2, ios::cur);
	}

	//部分前移  insert_pos字节						
	fp.seekg(0, ios::beg);
	for (int i = 0; i < insert_pos; i++)
	{
		fp.seekg(insert_size, ios::cur);
		char ch = fp.get();
		fp.seekg(-insert_size - 1, ios::cur);
		fp << ch;
	}

	//写入
	fp.clear();
	fp.seekp(insert_pos, ios::beg);
	fp << insert_s << "\r\n";
}

/* ---------------------------------------------------------------
    下面给出class cft_gai中成员函数的实现
    整个实现过程中不要出现cout，可以将信息放入msg中，在test中调用
  ---------------------------------------------------------------- */

/***************************************************************************
  函数名称：
  功    能：与class ctf不同
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
int cft_gai::item_add(const char* group_name, const char* item_value)
{
	
	fp.clear();
	fp.seekg(0, ios::beg);

	int num = 0;

	//判断是否为不含组名的简单配置文件
	if (group_name == NULL)
	{
		//判断是否为不含组名的简单配置文件
		bool is_simple = 1;
		while (file_read())		
			if (infor.include_group_name == 1)			
				return 0;

		fp.clear();
		fp.seekg(0, ios::beg);
		if(inspos==InsertPosition::Begin_of_file)
			fp << item_value << "\r\n";
		else if (inspos == InsertPosition::End_of_file)
		{
			fp.seekg(0, ios::end);
			fp << item_value << "\r\n";
		}
		else
		{
			while (file_read())
			{
				if (infor.if_null == 1)
				{
					move_to_last_line();
					fp << item_value << "\r\n";
				}
			}
		}
		return 1;
	}


	while (file_read())
	{
		num += infor.num;
		if (group_name == infor.group_name)
		{
			if (inspos == InsertPosition::First_line_after_group)
			{
				insert_to_file(fp, num, strlen(item_value)+2, item_value);
				return 1;
			}
			else if (inspos == InsertPosition::First_blank_line_after_group)
			{
				while (file_read())
				{
					num += infor.num;

					if (infor.if_null == 1)
					{
						move_to_last_line();
						num -= infor.num;
						insert_to_file(fp, num, strlen(item_value)+2, item_value);
						return 1;
					}
				}
			}
			else
			{
				while (file_read())
				{
					num += infor.num;
					if (infor.name_of_group == 1)
					{
						move_to_last_line();
						num -= infor.num;
						insert_to_file(fp, num, strlen(item_value)+2, item_value);
						return 1;
					}
				}
			}
		}
	}
	
	return 0; //按需修改
}

/***************************************************************************
  函数名称：
  功    能：与class ctf不同
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
int cft_gai::item_add(const char* group_name, const string& item_value)
{
	return item_add(group_name, item_value.c_str());
}

/***************************************************************************
  函数名称：
  功    能：与class ctf不同
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
int cft_gai::item_del(const char* group_name, const char* item_value)
{
	fp.clear();
	fp.seekg(0, ios::beg);
	
	stringstream s;
	if (is_ignore_comment == CommentSwitch::on)
	{		
		for (int i = 0; item_value[i] != '\0'; i++)
		{
			if (item_value[i] != ' ' && item_value[i] != '\t')
				s << item_value[i];
			else if (item_value[i] == '#' || item_value[i] == ';')
				break;
		}
	}
	else
		for (int i = 0; item_value[i] != '\0'; i++)
		{
			if (item_value[i] != ' ' && item_value[i] != '\t')
				s << item_value[i];
		}
	
	//判断是否为不含组名的简单配置文件
	bool is_simple = 0;
	if (group_name == NULL)
	{
		is_simple = 1;
		while (file_read())
			if (infor.include_group_name == 1)
				return 0;
	}

	while (file_read())
	{
		if (is_simple == 1||infor.group_name == group_name)
		{
			while (file_read(1))
			{
				if (infor.name_of_group == 1)
					break;

				if (infor.item_vaule == s.str())
				{					
					delete_in_file(fp, infor.num);
					int size = size_of_file(fp);
					fp.seekg(ios::beg, 0);
					file_resize(size - infor.num);
					return 1;
				}
			}
		}
	}
	return 0; //按需修改
}

/***************************************************************************
  函数名称：
  功    能：与class ctf不同
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
int cft_gai::item_del(const char* group_name, const string& item_value)
{
	return item_del(group_name, item_value.c_str());
}

/***************************************************************************
  函数名称：
  功    能：取得某group下的全部有效行（空行、仅含空格/tab的行等都排除）
  输入参数：
  返 回 值：动态申请一个string数组，每个元素存一行，返回首地址即可
  说    明：按需申请，不要浪费，调用出记得释放
 ***************************************************************************/
string* cft_gai::item_get_all(const char* group_name)
{
	string* str=NULL;
	int n=0,m=0;//n记录总行数，m记录空行数

	fp.clear();
	fp.seekg(0,ios::beg);

	//判断是否为不含组名的简单配置文件
	bool is_simple = 0;

	if (group_name == NULL)
	{
		is_simple = 1;
		while (file_read())
			if (infor.include_group_name == 1)
				return 0;
	}

	while (file_read(1))
	{
		if (is_simple == 1||infor.group_name == group_name)
		{
			while (file_read(1))
			{
				if (infor.name_of_group == 1)
					break;
				if (infor.if_null == 1)
					m++;
				n++;
			}

			for (int i = 0; i < n; i++)
				move_to_last_line();

			str = new(nothrow) string[n-m+1];

			for (int i = 0; i < n-m; i++)
			{
				file_read(1);
				if (infor.if_null != 1)				
					str[i] = infor.item_vaule;									
			}
			str[n - m] = "\0";
		}
	}

	
	return str; //按需修改
}

#endif
