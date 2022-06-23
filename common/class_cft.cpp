/* 邹良顺 2152611 信02 */

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <io.h>
#include "../include/class_cft.h"
//允许加入其它需要的头文件
#include<sstream>
using namespace std;

#if ! ENABLE_LIB_TCFG_TOOLS	//禁用lib后才能编译

/* ---------------------------------------------------------------
	 允许加入其它需要的struct/class/union/函数等（内部工具用）
	 1、函数必须为静态，不对外
	 2、允许定义符号常量/常变量
	 3、尽量不要用全局变量，如果一定要用，加static
   ---------------------------------------------------------------- */
#define size_of_n 2 //换行

static int size_of_file(fstream &f)
{
	int pos =int( f.tellg());
	int n = 0;

	f.seekg(0, ios::beg);
	while(1)
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
static void insert_to_file(fstream& fp, int insert_pos, int insert_size,const char*insert_s)
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
	fp << insert_s <<"\r\n";
}

bool cft::file_read(bool gai)
{
	infor.group_name = "";
	infor.item_name = "";
	infor.item_vaule = "";

	infor.if_null = 0;//是否为空行

	infor.if_true = 0;

	//读入该行数据
	string in_str;
	stringstream s;
	int n;
	for (n = 0; ; n++)
	{
		fp.clear();
		char ch = fp.get();
		s << ch;

		if (ch == '\n')
		{			
			n++;			
			break;
		}
		if (ch == -1)
		{
			infor.num = 0;
			fp.clear();
			return 0;
		}
	}
	infor.num = n;

	in_str = s.str();
	s.str("");

	//对读入数据进行处理
		//注释
	//if (is_ignore_comment == CommentSwitch::on)
	//{
	//	for (int i = 0; i < n; i++)
	//		if (in_str[i] == '#' || in_str[i] == ';')
	//		{
	//			in_str[i] = '\0';
	//		}			
	//}
	//cout << in_str << "*" << endl;

	//是否为有效项
	for (int i = 0; in_str[i]!='\0'&&in_str[i]!='#'&&in_str[i]!=';'; i++)
		if (in_str[i] == '=')
		{
			infor.if_true = 1;
			break;
		}

	//去除前空格
	int num_front = 0;
	for (int i = 0; i < n; i++)
	{
		if (in_str[i] == ' ' || in_str[i] == '\t')
			num_front++;
		else
			break;	
	}
	for (int i = 0; i <= n - num_front; i++)
	{		
		in_str[i] = in_str[i + num_front];
	}	
	if (in_str[0] == '\0'||in_str[0]=='#'||in_str[0]==';')
	{
		infor.if_null = 1;
		return 1;
	}

	//去除后空格
	int size = 0;
	for(int i = n - num_front-1; i > 0; i--)
	{		
		if (in_str[i] == ' ' || in_str[i] == '\t')
		{			
			if (in_str[i - 1] != ' ' && in_str[i - 1] != '\t')
			{
				
				in_str[i] = '\0';
				size = i;			
				break;
			}
		}
		else if(in_str[i]!='\n'&& in_str[i]!='\r')
		{
			in_str[i+1] = '\0';
			size = i+1;
			break;
		}
	}
	
	if (in_str[0] == '\r'|| in_str[0] == '\n')
	{
		infor.if_null = 1;
		infor.name_of_group = 0;
	}

	
	//处理各项数据  此时数组大小为size+1
	if (in_str[0] == '[' && in_str[size - 1] == ']')
	{		
		infor.include_group_name = 1;
		in_str[size - 1] = '\0';//方便读入infor中
		infor.name_of_group = 1;
		infor.if_true = 1;

		for (int i = 1;in_str[i]!='\0';i++)
		{
			if (in_str[i] == ' ' || in_str[i] == '\t')
			{
				for (int j = i; in_str[j] != '\0'; j++)
					in_str[j] = in_str[j + 1];
			}
		}

		infor.group_name = &in_str[1];

	}
	else
	{		
		infor.name_of_group = 0;
		if (gai == 1)
		{
			s.str("");
			for (int i = 0; i < size + 1 && in_str[i] != ' ' && in_str[i] != '\t'&&in_str[i]!=0; i++)			
				s << in_str[i];
			
			infor.item_vaule = s.str();

		}
		else
		{
			int i;
			for (i = 0; in_str[i] != '=' && in_str[i] != ' ' && i < size + 1; i++)
				s << in_str[i];
			infor.item_name = s.str();

			s.str("");
			//忽略=之后的空格
			for (i += 1; i < size + 1; i++)
			{
				if (in_str[i] != ' ' && in_str[i] != '\t'&&in_str[i]!='=')
					break;
			}

			int j = 0;
			for (j = 0; i < size + 1; i++, j++)
			{
				if (in_str[i] == ' '||in_str[i]=='\t')
					break;
				s << in_str[i];
			}
			infor.item_vaule = s.str();

			//cout << infor.item_name << " " << infor.item_vaule<<"*" << endl;
			//system("pause");
		}
	}
	return 1;
}

void cft::move_to_next_line()
{
	while (fp.get() != '\n')
		;
}

void cft::move_to_last_line()
{
	fp.clear();
	//跳过第一个回车
	fp.seekg(-size_of_n,ios::cur);
	if (fp.tellp() == 0)
		return;
	while (1)
	{
		fp.seekg(-1,ios::cur);
		int ch = fp.get();
		
		if (ch == '\n')
			break;

		fp.seekg(-1,ios::cur);

	}
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：C++17中有filesystem::resize_file直接可以修改文件大小，
            之前的版本无，因此本函数用了C方式的_chsize方法
		已实现，不要动
 ***************************************************************************/
int cft::file_resize(int newsize)
{
	msg.str("");
	/* 如果大小是负数则直接返回-1 */
	if (newsize < 0) {
		msg << "file_resize - invalid size(" << newsize << ")." << endl;
		return -1;
	}

	if (!fp.good())
		fp.clear();

	/* 取fp当前指针位置 */
	int now_pos = int(fp.tellg());

	/* 首先：C++方式关闭 */
	fp.close();

	/* 其次：C方式打开并改变文件大小 */
	FILE* fp_cstyle;
	fp_cstyle = fopen(filename.c_str(), "rb+"); //rw方式打开
	if (fp_cstyle) {
		if (_chsize(_fileno(fp_cstyle), newsize) < 0)
			msg << "file_resize - chsize failed" << endl; //给出出错信息，继续执行(恢复C++方式打开)

		fclose(fp_cstyle); //不管是否正确都flcose
	}
	else
		msg << "file_resize - fopen (" << filename << ") failed" << endl;//给出出错信息，继续执行(恢复C++方式打开)

	/* 再次：C++方式重新打开（能调用resize的一定是rw） */
	fp.open(filename, ios::in | ios::out|ios::binary);
	if (fp.is_open() == 0) {
		msg << "file_resize - reopen (" << filename << ") failed" << endl;//C++方式出错则返回-1
		return -1;
	}
	
	/* 文件指针移动到原位置 */
	fp.seekg(ios::beg,now_pos < newsize ? now_pos : newsize);
	
	return 0;
}

/* ---------------------------------------------------------------
	 下面给出class cft中成员函数的实现
	 整个实现过程中不要出现cout，可以将信息放入msg中，在test中调用
---------------------------------------------------------------- */

/*读文件时，为了读取方便，现在文件末尾加上'\n'，避免最后一行无回车导致的错误*/

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
cft::cft()
{
	filename = "";
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
cft::~cft()
{
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
cft::cft(const char* cfgname, int opt)
{
	filename = cfgname;

	infor.include_group_name = 0;

	if (opt == OPEN_OPT_RDONLY)
		fp.open(filename, ios::in|ios::binary);
	else
	{
		fp.open(filename, ios::in | ios::out | ios::binary);
		if (fp.is_open() == 0)
			fp.open(filename, ios::in | ios::out | ios::binary | ios::trunc);
	}
	is_ignore_comment = CommentSwitch::on;
	inspos = InsertPosition::First_line_after_group;

	fp.seekg(0, ios::end);
	fp << "\r\n";
	fp.seekg(0, ios::beg);
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
cft::cft(const string& cfgname, int opt)
{
	filename = cfgname;
	infor.include_group_name = 0;
	if (opt == OPEN_OPT_RDONLY)
		fp.open(filename, ios::in|ios::binary );
	else
	{
		fp.open(filename, ios::in | ios::out | ios::binary);
		if (fp.is_open() == 0)
			fp.open(filename, ios::in | ios::out | ios::binary | ios::trunc);
	}
	is_ignore_comment = CommentSwitch::on;
	inspos = InsertPosition::First_line_after_group;

	fp.seekg(0, ios::end);
	fp << "\r\n";
	fp.seekg(0, ios::beg);
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
void cft::open(const char* cfgname, int opt)
{
	filename = cfgname;
	infor.include_group_name = 0;
	if (opt == OPEN_OPT_RDONLY)
		fp.open(filename, ios::in | ios::binary );
	else
	{
		fp.open(filename, ios::in | ios::out | ios::binary);
		if(fp.is_open()==0)
			fp.open(filename, ios::in | ios::out | ios::binary | ios::trunc);
	}
	is_ignore_comment = CommentSwitch::on;
	inspos = InsertPosition::First_line_after_group;

	fp.seekg(0, ios::end);
	fp << "\r\n";
	fp.seekg(0, ios::beg);
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
void cft::open(const string& cfgname, int opt)
{
	filename = cfgname;
	infor.include_group_name = 0;
	if (opt == OPEN_OPT_RDONLY)
		fp.open(filename, ios::in | ios::binary );
	else
	{
		fp.open(filename, ios::in | ios::out | ios::binary);
		if (fp.is_open() == 0)
			fp.open(filename, ios::in | ios::out | ios::binary | ios::trunc);
	}
	is_ignore_comment = CommentSwitch::on;
	inspos = InsertPosition::First_line_after_group;

	fp.seekg(0, ios::end);
	fp << "\r\n";
	fp.seekg(0, ios::beg);
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
bool cft::is_open(void)
{
	return fp.is_open(); //按需修改
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
void cft::close()
{
	fp.close();
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
void cft::print() const
{
	cout << msg.str() << endl;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：默认为on
 ***************************************************************************/
void cft::set_comment_switch(CommentSwitch flag)
{
	is_ignore_comment = flag;	
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：已实现，不要动
 ***************************************************************************/
CommentSwitch cft::get_comment_switch() const
{
	return this->is_ignore_comment;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：默认为First_line_after_group
 ***************************************************************************/
void cft::set_insert_position(InsertPosition pos)
{
	inspos = pos;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：已实现，不要动
 ***************************************************************************/
InsertPosition cft::get_insert_position() const
{
	return this->inspos;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
int cft::group_add(const char* group_name)
{
	fp.seekg(0,ios::beg);

	while (file_read())
	{	

		if (infor.group_name == group_name)
			return 0;
	}
	
	fp.clear();
	
	fp << "\r\n[" << group_name << "]" <<"\r\n";

	return 1; //按需修改
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
int cft::group_add(const string& group_name)
{
	return group_add(group_name.c_str());
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
  ● 删除成功返回n(删除组的数量)，否则返回0
  ● 如果[test]组不存在，直接返回0即可
  ● 如果[test]组重复存在（例如：手工修改使两组同名），则要删除所有同名组并返回2
 ***************************************************************************/
int cft::group_del(const char* group_name)
{
	fp.clear();
	fp.seekg(0,ios::beg);
	int n = 0;//删除组的个数
	while (file_read())
	{		
		int num = 0;
		if (infor.group_name == group_name)
		{			
			//记录目标组的字符数
			num +=infor.num;
			while (file_read())
			{				
				if (infor.name_of_group==0)
					num +=infor.num;
				else
				{					
					move_to_last_line();						
					break;
				}
			}
			//根据字符数 覆盖目标组内容			
			delete_in_file(fp, num);

			int size = size_of_file(fp);
			fp.seekg(ios::beg, 0);
			file_resize(size - num);

			n++;			
		}
	}

	fp.clear();
	return n; //按需修改
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
  ● 删除成功返回n(删除组的数量)，否则返回0
  ● 如果[test]组不存在，直接返回0即可
  ● 如果[test]组重复存在（例如：手工修改使两组同名），则要删除所有同名组并返回2
 ***************************************************************************/
int cft::group_del(const string& group_name)
{
	return group_del(group_name.c_str());
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
int cft::item_add(const char* group_name, const char* item_name, const int item_value)
{
	stringstream a;
	a << item_value;

	return item_add(group_name, item_name, a.str());
	
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
int cft::item_add(const char* group_name, const char* item_name, const double item_value)
{
	stringstream a;
	a << item_value;

	return item_add(group_name, item_name, a.str());
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
int cft::item_add(const char* group_name, const char* item_name, const char* item_value)
{
	                          //=                         \n
	int len = strlen(item_name) + 1 + strlen(item_value) + 2;
	fp.seekg(0,ios::beg);
	int num = 0,num1=0;  //含目标组名所在行，共多少字节

	if (group_name == NULL)
	{
		//判断是否为不含组名的简单配置文件
		bool is_simple = 1;
		while (file_read())		
			if (infor.include_group_name == 1)			
				return 0;
				
		fp.clear();
		fp.seekg(0, ios::beg);

		//判断目标项是否存在
		while (file_read())
			if (infor.item_name == item_name)
				return 0;

		//目标项不存在
		fp.clear();
		fp.seekg(0, ios::beg);

		string s = item_name;
		s += '=';
		s += item_value;

		if (inspos == InsertPosition::Begin_of_file)
			insert_to_file(fp, 0, s.length() + 2, s.c_str());
		else if (inspos == InsertPosition::End_of_file)
		{
			fp.clear();
			fp.seekg(0, ios::end);
			fp << item_name << "=" << item_value << "\r\n";
		}
		else
		{
			int n = 0;
			while (file_read())
			{				
				n += infor.num;
				if (infor.if_null == 1)
				{
					n -= infor.num;
					move_to_last_line();
					insert_to_file(fp, n, s.length() + 2, s.c_str());
					return 1;
				}
			}
			fp.clear();
			fp.seekg(0, ios::end);
			fp << item_name << "=" << item_value << "\r\n";
		}
		return 1;
	}

	while (file_read())
	{
		num +=infor.num;
		if (infor.group_name == group_name&&infor.name_of_group)
		{			
			if (inspos == InsertPosition::First_blank_line_after_group)
			{
				//若为最后一个组，组后无空行，直接到文件尾，则返回0
				while (file_read())
				{
					//无空行
					if (infor.name_of_group == 1)
						return 0;

					//有空行
					num +=infor.num;
					if (infor.if_null == 1)
					{
						num -=infor.num;
						move_to_last_line();
						//插入新数据
						string str = item_name;
						str += "=";
						str += item_value;
						insert_to_file(fp, num, len, str.c_str());
						
						return 1;
					}
				}
				return 0;
			}
			else
			{				
				while (1)
				{					
					bool eof = !file_read();
					num1 +=infor.num-eof;	

					if (infor.item_name == item_name)
						return 0;
					
					if (infor.name_of_group==1||eof)
					{
						
						num1 -= infor.num;
						if (inspos == InsertPosition::Before_next_group)
							num += num1;

						string str = item_name ;
						str += "=";
						str +=item_value;

						insert_to_file(fp, num, len, str.c_str());
					
						return 1;
					}
					
					if (eof)
						break;
				}
			}
		}
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
int cft::item_add(const char* group_name, const char* item_name, const string& item_value)
{
	return item_add(group_name, item_name, item_value.c_str());
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
int cft::item_add(const char* group_name, const char* item_name, const char item_value)
{
	char a[2];
	sprintf(a, "%c", item_value);
	return item_add(group_name, item_name,a);
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
int cft::item_add(const char* group_name, const char* item_name)
{
	const char *a="\0";
	return item_add(group_name, item_name, a);
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int cft::item_del(const char* group_name, const char* item_name)
{
	fp.seekg(0, ios::beg);
	int n = 0;

	if (group_name == NULL)
	{
		//判断是否为不含组名的简单配置文件
		bool is_simple = 1;

		//含组名的文件
		while (file_read())
			if (infor.include_group_name == 1)
			{
				//含组名
				fp.clear();
				fp.seekg(0, ios::beg);

				while (file_read())
				{
					if (infor.item_name == item_name)
					{
						//根据字符数 覆盖目标组内容
						delete_in_file(fp,infor.num);

						int size = size_of_file(fp);
						fp.seekg(0,ios::beg);
						file_resize(size - infor.num);

						n++;
					}
				}

				return n;
			}


		//不含组名
		fp.clear();
		fp.seekg(0, ios::beg);

		while (file_read())
		{
			if (infor.item_name == item_name)
			{
				//根据字符数 覆盖目标组内容
				delete_in_file(fp,infor.num);

				int size = size_of_file(fp);
				fp.seekg(0,ios::beg);
				file_resize(size - infor.num);

				n++;
			}
		}
		return n;
	}

	fp.clear();
	fp.seekg(0, ios::beg);

	while (file_read())
	{
		if (infor.group_name == group_name)
		{
			while (1)
			{
				bool eof = !file_read();
				if (infor.name_of_group == 1 || eof)
					break;

				if (infor.item_name == item_name)
				{
					int num =infor.num;
					
					//根据字符数 覆盖目标组内容
					delete_in_file(fp, num);

					int size = size_of_file(fp);
					fp.seekg(ios::beg, 0);
					file_resize(size - num);

					n++;
					break;
				}
			}
		}
	}

	return n;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
int cft::item_update(const char* group_name, const char* item_name, const int item_value)
{
	stringstream a;
	a << item_value;

	return item_update(group_name, item_name, a.str());

}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
int cft::item_update(const char* group_name, const char* item_name, const double item_value)
{
	stringstream a;
	a << item_value;

	return item_update(group_name, item_name, a.str());
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
int cft::item_update(const char* group_name, const char* item_name, const char* item_value)
{
	
	int num = 0;
	fp.seekg(0,ios::beg);

	if (group_name == NULL)
	{
		//判断是否为不含组名的简单配置文件
		bool is_simple = 1;
		while (file_read())
			if (infor.include_group_name == 1)
				return 0;

		fp.clear();
		fp.seekg(0, ios::beg);

		//判断目标组是否存在
		int n = 0;
		while (file_read())
		{
			n += infor.num;
			if (infor.item_name == item_name)
			{
				n -= infor.num;
				string str = item_name;
				str += '=';
				str += item_value;
				insert_to_file(fp, n, str.length() + 2, str.c_str());

				fp.seekg(0, ios::beg);
				while (file_read())
				{
					if (infor.item_name == item_name)
					{
						file_read();

						delete_in_file(fp, infor.num);

						int size = size_of_file(fp);
						fp.seekg(ios::beg, 0);
						file_resize(size - infor.num);

						return 1;
					}										
				}
			}
		}
		//目标组不存在
		fp.clear();
		fp.seekg(0, ios::end);

		return item_add(group_name, item_name, item_value);
	}

	while (file_read())
	{
		num +=infor.num;
		if (infor.group_name == group_name)
		{			
			while (1)
			{
				bool eof = !file_read();
				num +=infor.num;

				if (infor.name_of_group==1||eof)
					break;

				if (infor.item_name == item_name)
				{
					//先插入至原位置之前
					num -=infor.num;

					string str=item_name;
					str += '=';
					str += item_value;

					insert_to_file(fp, num, str.length()+2, str.c_str());
				
					
					//再删除原item
					fp.seekg(0, ios::beg);
					while (file_read())
					{
						if (infor.group_name == group_name)
						{
							while (file_read())
							{
								if (infor.item_name == item_name)
								{
									file_read();

									delete_in_file(fp, infor.num);

									int size = size_of_file(fp);
									fp.seekg(ios::beg, 0);
									file_resize(size - infor.num);
									return 1;
								}
							}							
						}
					}					
				}
			}
			return item_add(group_name, item_name, item_value);
		}
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
int cft::item_update(const char* group_name, const char* item_name, const string& item_value)
{
	stringstream a;
	a << item_value;

	return item_update(group_name, item_name, a.str().c_str());
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
int cft::item_update(const char* group_name, const char* item_name, const char item_value)
{
	stringstream a;
	a << item_value;

	return item_update(group_name, item_name, a.str());
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
int cft::item_update(const char* group_name, const char* item_name)
{
	char a[1];
	a[0] = '\0';
	return item_update(group_name, item_name, a);
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
int cft::item_get_value(const char* group_name, const char* item_name, int& item_value)
{
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
	
	fp.clear();
	fp.seekg(0, ios::beg);

	while (file_read())
	{
		if (is_simple == 1||group_name == infor.group_name)
		{
			//cout << group_name << "+" << endl;
			while (file_read())
			{
				if (is_simple==0&&infor.name_of_group == 1 && group_name != infor.group_name&&infor.if_true==1)
					break;

				if (item_name == infor.item_name)
				{
					stringstream s;
					s << infor.item_vaule;
					s >> item_value;

					//cout << group_name << " " << item_name << " " << item_value << endl;
					//system("pause");

					return 1;
				}
			}
		}
	}
	return 0; //按需修改
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
int cft::item_get_value(const char* group_name, const char* item_name, double& item_value)
{
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

	fp.clear();
	fp.seekg(0, ios::beg);

	while (file_read())
	{
		if (is_simple == 1 || group_name == infor.group_name)
		{
			while (file_read())
			{
				if (is_simple == 0 && infor.name_of_group == 1 && group_name != infor.group_name)
					break;

				if (item_name == infor.item_name)
				{
					stringstream s;
					s << infor.item_vaule;
					s >> item_value;

					return 1;
				}
			}
		}
	}

	return 0; //按需修改
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
int cft::item_get_value(const char* group_name, const char* item_name, char* item_value, bool enable_space)
{

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

	fp.clear();
	fp.seekg(0, ios::beg);

	while (file_read())
	{
		if (is_simple == 1 || group_name == infor.group_name)
		{
			while (file_read())
			{
				if (is_simple == 0 && infor.name_of_group == 1 && group_name != infor.group_name)
					break;

				if (item_name == infor.item_name)
				{
					strcpy(item_value, infor.item_vaule.c_str());

					if (enable_space == 0)
					{
						for (int i = 0; item_value[i] != '\0'; i++)
						{
							if (item_value[i] == ' ' || item_value[i] == '\t')
								for (int j = i; item_value[j] != '\0'; j++)
									item_value[j] = item_value[j + 1];
						}
					}

					return 1;
				}
			}
		}
	}

	return 0; //按需修改
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
int cft::item_get_value(const char* group_name, const char* item_name, string& item_value, bool enable_space)
{
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

	fp.clear();
	fp.seekg(0, ios::beg);

	while (file_read())
	{
		if (is_simple == 1 || group_name == infor.group_name)
		{
			while (file_read())
			{
				if (is_simple == 0 && infor.name_of_group == 1 && group_name != infor.group_name)
					break;

				if (item_name == infor.item_name)
				{
					item_value = infor.item_vaule;

					if (enable_space == 0)
					{
						for (int i = 0; item_value[i] != '\0'; i++)
						{
							if (item_value[i] == ' ' || item_value[i] == '\t')
								for (int j = i; item_value[j] != '\0'; j++)
									item_value[j] = item_value[j + 1];
						}
					}

					return 1;
				}
			}
		}
	}

	return 0; //按需修改
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
int cft::item_get_value(const char* group_name, const char* item_name, char& item_value)
{
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

	fp.clear();
	fp.seekg(0, ios::beg);

	while (file_read())
	{
		if (is_simple == 1 || group_name == infor.group_name)
		{
			while (file_read())
			{
				if (is_simple == 0 && infor.name_of_group == 1 && group_name != infor.group_name)
					break;

				if (item_name == infor.item_name)
				{
					const char* a = infor.item_vaule.c_str();
					item_value = a[0];
					return 1;
				}
			}
		}
	}

	return 0; //按需修改
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
int cft::item_get_value(const char* group_name, const char* item_name)
{
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

	fp.clear();
	fp.seekg(0, ios::beg);

	while (file_read())
	{
		if (is_simple == 1 || group_name == infor.group_name)
		{
			while (file_read())
			{
				if (is_simple == 0 && infor.name_of_group == 1 && group_name != infor.group_name)
					break;

				if (item_name == infor.item_name)
					return 1;
			
			}
		}
	}

	return 0; //按需修改
}

#endif  //end of ! ENABLE_LIB_TCFG_TOOLS

