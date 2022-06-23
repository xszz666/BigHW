/* 邹良顺 2152611 信02 */
#pragma once

#define ENABLE_LIB_TCFG_TOOLS   0

#if ENABLE_LIB_TCFG_TOOLS

#include "../include/lib_tcfg_tools.h"
typedef tcft cft;	//将tcft声明为cft

#else

/* 目前照抄lib_tcfg_tools.h，允许按规定要求做变化 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

enum class ITEM_TYPE {
	Int,		//为避免和int冲突，采用首字母大写形式
	Double,
	String,		//string类形式(含 char * / char [])
	Character,	//char 形式
	Line,		//cft_gai中的纯字符串形式
	Null
};

#define OPEN_OPT_RDONLY		0	//以只读方式打开（打不开则返回失败）
#define OPEN_OPT_RDWR		1	//以读写方式打开（打不开文件则创建）

/* ---------------------------------------------------------------
	 允许加入其它需要的定义
	 const全局变量/static全局变量(慎用)/define/class/struct/enum/enum class/union等
   ---------------------------------------------------------------- */
struct what_read_in
{	
	string group_name;
	string item_name;
	string item_vaule;
	bool name_of_group;
	bool include_group_name=0;
	bool if_true;//是否含=
	bool if_null=0;//是否为空行
	int num;//记录该行字节数
};

   /* 定义配置文件中组/项添加的位置

   /* 定义插入位置：
	   带组名的配置文件：组名后第一行、组名后第一个空行、该组最后（下一组的开始）
	   简单配置文件    ：整个文件的最开始、整个文件的结束、第一个空行后 */
enum class InsertPosition {
	//组配置文件的三个位置
	First_line_after_group = 0,	//组名后第一行
	First_blank_line_after_group,	//组名后第一个空行
	Before_next_group,			//该组最后（下一组的开始）
	//简单配置文件的三个位置
	Begin_of_file,				//整个文件的最开始（简单配置）
	First_blank_line,				//第一个空行位置（简单配置）
	End_of_file,					//整个文件的最后（简单配置）
};

/* 定义是否忽略注释语句：
	 on ：从#和;开始到本行行尾为注释语句，忽略掉
	 off：#和;当做有效字符看待 */
enum class CommentSwitch {
	on = 0,		//组名后第一行
	off
};

/* ---------------------------------------------------------------
	 class CFT的定义，已有部分不要动，允许protected部分加入其它需要的定义（包括数据成员和成员函数）
   ---------------------------------------------------------------- */
class cft {
protected:
	string filename;
	fstream fp;
	InsertPosition inspos;
	CommentSwitch is_ignore_comment;

	ostringstream msg;	//用于存放内部信息，方便调试（也可以不用）

	what_read_in infor;//存放每行读到的信息

	char pad[384-99];

	/* ---------------------------------------------------------------
		 内部函数，可以按需增加
	   ---------------------------------------------------------------- */
	int file_resize(int newsize); //已实现，不要动
	void move_to_next_line();
	void move_to_last_line();
	/* ---------------------------------------------------------------
		 允许声明友元
	   ---------------------------------------------------------------- */
	bool file_read(bool gai=0);//到达文件尾，返回0

public:
	cft();		//无参构造，置filename为""即可
	cft(const char* cfgname, int opt = OPEN_OPT_RDONLY);	//两参构造，功能同open
	cft(const string& cfgname, int opt = OPEN_OPT_RDONLY);	//两参构造，功能同open
	~cft();		//析构

	void open(const char* cfgname, int opt = OPEN_OPT_RDONLY);
	void open(const string& cfgname, int opt = OPEN_OPT_RDONLY);
	bool is_open();	//如果打开成功，则返回true，否则返回false
	void close();

	void print() const;	//打印内部msg信息(用于调试)

	/* 设置是否过滤注释语句（默认：yes） */
	void set_comment_switch(CommentSwitch flag);
	CommentSwitch get_comment_switch() const;

	/* 设置item_add的插入位置（默认：First_line_after_group） */
	void set_insert_position(InsertPosition pos);
	InsertPosition get_insert_position() const;

	/* 组增加与删除 */
	int group_add(const char* group_name);
	int group_add(const string& group_name);
	int group_del(const char* group_name);
	int group_del(const string& group_name);

	/* 项增加，多类型重载 */
	int item_add(const char* group_name, const char* item_name, const int item_value);
	int item_add(const char* group_name, const char* item_name, const double item_value);
	int item_add(const char* group_name, const char* item_name, const char* item_value);
	int item_add(const char* group_name, const char* item_name, const string& item_value);
	int item_add(const char* group_name, const char* item_name, const char item_value);
	int item_add(const char* group_name, const char* item_name);	//NULL

	/* 项删除 */
	int item_del(const char* group_name, const char* item_name);
	int item_del(const char* group_name, const string& item_name);

	/* 项更新，多类型重载 */
	int item_update(const char* group_name, const char* item_name, const int item_value);
	int item_update(const char* group_name, const char* item_name, const double item_value);
	int item_update(const char* group_name, const char* item_name, const char* item_value);
	int item_update(const char* group_name, const char* item_name, const string& item_value);
	int item_update(const char* group_name, const char* item_name, const char item_value);
	int item_update(const char* group_name, const char* item_name);	//NULL

	/* 取某项的值，多类型重载 */
	int item_get_value(const char* group_name, const char* item_name, int& item_value);
	int item_get_value(const char* group_name, const char* item_name, double& item_value);
	int item_get_value(const char* group_name, const char* item_name, char* item_value, bool space_enable = false); //最后一个参数为true表示读到的值允许含空格
	int item_get_value(const char* group_name, const char* item_name, string& item_value, bool space_enable = false);
	int item_get_value(const char* group_name, const char* item_name, char& item_value);
	int item_get_value(const char* group_name, const char* item_name);

	/* ---------------------------------------------------------------
		 不允许加入其它需要的定义（即对外呈现的只有上述各项）
	   ---------------------------------------------------------------- */
};

#endif
