/*邹良顺 2152611 信02*/
/*2152205 邹明宇 2153592 胡逸凡 2153689 黄泽华*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <string>
#include <io.h>
#include <stdio.h>
#include <conio.h>
using namespace std;

#include "../include/class_cft.h"

union cfg_value {
	int ivalue;
	double dvalue;
	char svalue[256];//如果字符串长度超过255，则只取前255个字符
	char cvalue;
	void* value;
};

struct cfg_item {
	const char* cfg_item_name;
	enum ITEM_TYPE cfg_item_type;
	union cfg_value cfg_item_value;
};

/***************************************************************************
  函数名称：
  功    能：每次测试前都需要删除文件
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
static void ask_for_remove_cfgfile(const char* const cfgname, const char ch_yes = 'Y', const char ch_no = 'N')
{
	char sel;

	/*  文件不存在则直接返回 */
	if (_access(cfgname, 0x00) < 0)
		return;

	cout << "请选择是否删除文件(" << cfgname << ")[" << ch_yes << "=删除/" << ch_no << "=保留] : " << endl;

	while (1) {
		sel = _getch();
		if (sel == ch_yes || sel == ch_no)
			break;
	}

	/* 可能会因为正在查看文件而导致删除不成功，要反复删 */
	while (sel == ch_yes) {
		if (remove(cfgname) == 0)
			break; //删除成功则退出循环

		cout << "文件(" << cfgname << ")删除失败，如果是因为正在查看该文件，请关闭后按回车再次尝试删除" << endl;
		while (_getch() != '\r')
			;
	}

	return;
}

/***************************************************************************
  函数名称：
  功    能：显示提示信息
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
static void to_be_continued(const char* const prompt = NULL, const char ch = '\r')
{
	char tmp[64];

	/*条件表达式的2/3必须相容类型，不能一个串一个字符(ch=='\r' ? "回车" : ch)，因此要特殊处理一下 */
	if (ch == '\r')
		sprintf(tmp, "回车");
	else
		sprintf(tmp, "%c[%d]", ch, ch);

	if (prompt)
		cout << prompt << "，按" << tmp << "键继续...";
	else
		cout << "按" << tmp << "键继续...";

	/* 忽略除回车键外的所有输入（注意：_getch的回车是\r，而getchar是\n）*/
	while (_getch() != ch)
		;
	cout << endl;

	return;
}

/***************************************************************************
  函数名称：
  功    能：因为cfg_item中含有共用体，共用体只能初始化第一项，因此用函数初始化
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
static void set_item(struct cfg_item* item)
{
	item[0].cfg_item_value.ivalue = 9999999;
	item[1].cfg_item_value.dvalue = 888.888;
	strcpy(item[2].cfg_item_value.svalue, "Hello<char    *>");
	item[3].cfg_item_value.cvalue = 'Y';
	item[4].cfg_item_value.ivalue = 0;
	item[5].cfg_item_value.ivalue = 99999;
	strcpy(item[6].cfg_item_value.svalue, "xszz666");
	item[7].cfg_item_value.ivalue = 0;
}

/***************************************************************************
  函数名称：
  功    能：简单配置文件测试
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int test_readconfig_cpp(const char* cfgname, struct cfg_item* item, InsertPosition pos)
{
	cft	fcfg;
	int ret;

	//简单配置文件的三个位置
	if (pos< InsertPosition::Begin_of_file || pos > InsertPosition::End_of_file) {
		cout << "指定的插入位置不正确." << endl;
		return -1;
	}

	/* 第1组测试，添加若干项 */
	if (1) {
		int j;

		ask_for_remove_cfgfile(cfgname);

		fcfg.open(cfgname, OPEN_OPT_RDWR);
		if (fcfg.is_open() == false) {
			cout << "无法打开配置文件(" << cfgname << ")." << endl;
			return -1;
		}
		fcfg.set_insert_position(pos);
		fcfg.set_comment_switch(CommentSwitch::on);

		for (j = 0; item[j].cfg_item_name; j++) {
			/* 说明：item_add的第3个参数是void*，因此不管什么类型，均传入union第一个成员的地址，即其它成员地址 */
			switch (item[j].cfg_item_type) {
				case ITEM_TYPE::Int:
					ret = fcfg.item_add(NULL, item[j].cfg_item_name, item[j].cfg_item_value.ivalue);
					break;
				case ITEM_TYPE::Double:
					ret = fcfg.item_add(NULL, item[j].cfg_item_name, item[j].cfg_item_value.dvalue);
					break;
				case ITEM_TYPE::String:
					if (j == 2)
						ret = fcfg.item_add(NULL, item[j].cfg_item_name, item[j].cfg_item_value.svalue);
					else
						ret = fcfg.item_add(NULL, item[j].cfg_item_name, string(item[j].cfg_item_value.svalue)); //通过显式调用string来模拟string
					break;
				case ITEM_TYPE::Character:
					ret = fcfg.item_add(NULL, item[j].cfg_item_name, item[j].cfg_item_value.cvalue);
					break;
				case ITEM_TYPE::Null:
					ret = fcfg.item_add(NULL, item[j].cfg_item_name);
					break;
				default:
					break;
			}
			cout << "增加" << item[j].cfg_item_name << (ret > 0 ? "成功." : "失败.") << endl;
		}

		fcfg.close(); //关闭文件，模拟本次设置完成

		cout << "第1组测试完成，请打开配置文件(" << cfgname << ")，观察是否有6个配置项" << endl;
		to_be_continued();
	}

	/* 第2组测试，删除项 */
	if (1) {
		cout << "请打开配置文件(" << cfgname << ")，将设置项B复制若干份，且后面的值类型不同" << endl;
		to_be_continued();

		fcfg.open(cfgname, OPEN_OPT_RDWR);
		if (fcfg.is_open() == false) {
			cout << "无法打开配置文件(" << cfgname << ")." << endl;
			return -1;
		}
		fcfg.set_insert_position(pos);
		fcfg.set_comment_switch(CommentSwitch::on);

		cout << "删除<设置项A>共" << fcfg.item_del(NULL, "设置项A") << "项" << endl;
		cout << "删除<设置项B>共" << fcfg.item_del(NULL, "设置项B") << "项" << endl;

		fcfg.close(); //关闭文件，模拟本次设置完成

		cout << "第2组测试完成，请打开配置文件(" << cfgname << ")，观察<设置项A>/<设置项B>是否已被删除" << endl;
		to_be_continued();
	}

	/* 第3组测试，修改项 */
	if (1) {
		fcfg.open(cfgname, OPEN_OPT_RDWR);
		if (fcfg.is_open() == false) {
			cout << "无法打开配置文件(" << cfgname << ")." << endl;
			return -1;
		}
		fcfg.set_insert_position(pos);
		fcfg.set_comment_switch(CommentSwitch::on);

		int i = 123456789;
		double d = 111.111;
		char c = 'Z';
		string s = "helloworld <string>";

		/* 已存在项，更新 */
		fcfg.item_update(NULL, "设置项D", "helloworld");
		fcfg.item_update(NULL, "设置项E", d);
		fcfg.item_update(NULL, "设置项F");
		fcfg.item_update(NULL, "设置项C", c);
		fcfg.item_update(NULL, "设置项A", s);

		/* 不存在项，新增 */
		fcfg.item_update(NULL, "设置项U");
		fcfg.item_update(NULL, "设置项V", c);
		fcfg.item_update(NULL, "设置项W");
		fcfg.item_update(NULL, "设置项X", i);
		fcfg.item_update(NULL, "设置项Y", "helloworld");
		fcfg.item_update(NULL, "设置项Z", d);
		fcfg.item_update(NULL, "设置项Q", s);
		fcfg.close(); //关闭文件，模拟本次设置完成

		cout << "第3组测试完成，请打开配置文件(" << cfgname << ")，观察上述配置是否已修改" << endl;
		to_be_continued();
	}

	/* 第4组测试，读 */
	if (1) {
		fcfg.open(cfgname, OPEN_OPT_RDONLY);
		if (fcfg.is_open() == false) {
			cout << "无法打开配置文件(" << cfgname << ")." << endl;
			return -1;
		}
		fcfg.set_insert_position(pos);
		fcfg.set_comment_switch(CommentSwitch::on);

		int i;
		double d;
		char c, s[128];
		string str;

		/* 读 */
		if (fcfg.item_get_value(NULL, "设置项X", i) > 0)
			cout << "设置项X=" << i << endl;
		if (fcfg.item_get_value(NULL, "设置项V", c) > 0)
			cout << "设置项V=" << c << endl;
		if (fcfg.item_get_value(NULL, "设置项Y", s) > 0)
			cout << "设置项Y=" << s << endl;
		if (fcfg.item_get_value(NULL, "设置项Q", str) > 0)//值不允许带空格
			cout << "设置项Q=" << str << endl;
		if (fcfg.item_get_value(NULL, "设置项Q", str, true) > 0) //值允许带空格
			cout << "设置项Q=" << str << endl;
		if (fcfg.item_get_value(NULL, "设置项W") > 0)
			cout << "设置项W=<NULL>" << endl;
		if (fcfg.item_get_value(NULL, "设置项E", d) > 0)
			cout << "设置项E=" << d << endl;
		if (fcfg.item_get_value(NULL, "设置项100") > 0)
			cout << "设置项100=<NULL>" << endl;
		else
			cout << "设置项100 不存在" << endl;

		fcfg.close(); //关闭文件，模拟本次设置完成

		cout << "第4组测试完成，请打开配置文件(" << cfgname << ")，观察上述配置读取是否正确" << endl;
		to_be_continued();
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
int test_readconfig_cpp(const char* cfgname, const char** group_name, struct cfg_item* item, InsertPosition pos)
{
	cft	fcfg;
	int ret, i;
	char tmp[256];

	//组配置文件的三个位置
	if (pos< InsertPosition::First_line_after_group || pos > InsertPosition::Before_next_group) {
		cout << "指定的插入位置不正确." << endl;
		return -1;
	}

	/* 第1组测试，添加若干组 */
	if (1) {
		ask_for_remove_cfgfile(cfgname); //删除文件

		fcfg.open(cfgname, OPEN_OPT_RDWR);
		if (fcfg.is_open() == false) {
			cout << "无法打开配置文件(" << cfgname << ")." << endl;
			return -1;
		}
		fcfg.set_insert_position(pos);
		fcfg.set_comment_switch(CommentSwitch::on);

		for (i = 0; group_name[i]; i++) {
			if ((ret = fcfg.group_add(group_name[i])) <= 0)
				cout << "增加[" << group_name[i] << "]失败." << endl;
			else
				cout << "增加[" << group_name[i] << "]成功." << endl;
			
		}
		fcfg.close(); //关闭文件，模拟本次设置完成

		cout << "第1组测试完成，请打开配置文件(" << cfgname << ")，观察是否仅有8个空组";
		to_be_continued();
	}

	/* 第2组测试，每组添加若干项 */
	if (1) {
		cout << "请打开配置文件(" << cfgname << ")，将[配置组2/4/7]改为[  配置组2  ]/[配置组4  ]/[ 配置组7]" << endl;
		to_be_continued();

		int j;

		fcfg.open(cfgname, OPEN_OPT_RDWR);
		if (fcfg.is_open() == false) {
			cout << "无法打开配置文件(" << cfgname << ")." << endl;
			return -1;
		}
		fcfg.set_insert_position(pos);
		fcfg.set_comment_switch(CommentSwitch::on);
		
		for (i = 0; group_name[i]; i++) {
			for (j = 0; item[j].cfg_item_name; j++) {
				sprintf(tmp, "%s-%s", group_name[i], item[j].cfg_item_name);
				/* 说明：item_add的第3个参数是void*，因此不管什么类型，均传入union第一个成员的地址，即其它成员地址 */
				switch (item[j].cfg_item_type) {
					case ITEM_TYPE::Int:
						ret = fcfg.item_add(group_name[i], tmp, item[j].cfg_item_value.ivalue);
						break;
					case ITEM_TYPE::Double:
						ret = fcfg.item_add(group_name[i], tmp, item[j].cfg_item_value.dvalue);
						break;
					case ITEM_TYPE::String:
						if (j == 2)
							ret = fcfg.item_add(group_name[i], tmp, item[j].cfg_item_value.svalue);
						else
							ret = fcfg.item_add(group_name[i], tmp, string(item[j].cfg_item_value.svalue)); //通过显式调用string来模拟string
						break;
					case ITEM_TYPE::Character:
						ret = fcfg.item_add(group_name[i], tmp, item[j].cfg_item_value.cvalue);
						break;
					case ITEM_TYPE::Null:
						ret = fcfg.item_add(group_name[i], tmp);
						break;
					default:
						break;
				}
				cout << "增加[" << group_name[i] << "]/" << tmp << (ret > 0 ? "成功." : "失败.") << endl;
			}
		}
		fcfg.close(); //关闭文件，模拟本次设置完成

		cout << "第2组测试完成，请打开配置文件(" << cfgname << ")，观察是否8个组均有6个配置项" << endl;
		to_be_continued();
	}

	/* 第3组测试，删除组及项 */
	if (1) {
		cout << "请打开配置文件(" << cfgname << ")，将[配置组3]复制若干份，配置组2-设置项B复制若干份，且后面的值类型不同" << endl;
		to_be_continued();

		fcfg.open(cfgname, OPEN_OPT_RDWR);
		if (fcfg.is_open() == false) {
			cout << "无法打开配置文件(" << cfgname << ")." << endl;
			return -1;
		}
		fcfg.set_insert_position(pos);
		fcfg.set_comment_switch(CommentSwitch::on);

		cout << "删除[配置组3]共" << fcfg.group_del("配置组3") << "组" << endl;
		cout << "删除[配置组5]共" << fcfg.group_del("配置组5") << "组" << endl;

		cout << "删除<配置组2-设置项B>共" << fcfg.item_del("配置组2", "配置组2-设置项B") << "项" << endl;

		fcfg.close(); //关闭文件，模拟本次设置完成

		cout << "第3组测试完成，请打开配置文件(" << cfgname << ")，观察[配置组3]/[配置组5]/<配置组2-设置项B>是否已被删除" << endl;
		to_be_continued();
	}

	/* 第4组测试，修改项 */
	if (1) {
		fcfg.open(cfgname, OPEN_OPT_RDWR);
		if (fcfg.is_open() == false) {
			cout << "无法打开配置文件(" << cfgname << ")." << endl;
			return -1;
		}
		fcfg.set_insert_position(pos);
		fcfg.set_comment_switch(CommentSwitch::on);

		int i = 54321;
		double d = 1023.4567;
		char c = 'N';
		string s = "helloworld<string>";

		/* 已存在项，更新 */
		fcfg.item_update("配置组4", "配置组4-设置项B", i);
		fcfg.item_update("配置组1", "配置组1-设置项D", "helloworld");
		fcfg.item_update("配置组8", "配置组8-设置项E", d);
		fcfg.item_update("配置组6", "配置组6-设置项F");
		fcfg.item_update("配置组7", "配置组7-设置项C", c);
		fcfg.item_update("配置组2", "配置组2-设置项D", s);

		/* 不存在项，新增 */
		fcfg.item_update("配置组6", "配置组6-设置项U");
		fcfg.item_update("配置组7", "配置组7-设置项V", c);
		fcfg.item_update("配置组7", "配置组6-设置项W");
		fcfg.item_update("配置组4", "配置组4-设置项X", i);
		fcfg.item_update("配置组1", "配置组1-设置项Y", "helloworld");
		fcfg.item_update("配置组8", "配置组8-设置项Z", d);
		fcfg.item_update("配置组2", "配置组2-设置项Q", s);
		fcfg.close(); //关闭文件，模拟本次设置完成

		cout << "第4组测试完成，请打开配置文件(" << cfgname << ")，观察上述配置是否已修改" << endl;
		to_be_continued();
	}

	/* 第5组测试，读 */
	if (1) {
		fcfg.open(cfgname, OPEN_OPT_RDONLY);
		if (fcfg.is_open() == false) {
			cout << "无法打开配置文件(" << cfgname << ")." << endl;
			return -1;
		}
		fcfg.set_insert_position(pos);
		fcfg.set_comment_switch(CommentSwitch::on);

		int i;
		double d;
		char c, s[128];
		string str;

		/* 已存在项，更新 */
		if (fcfg.item_get_value("配置组4", "配置组4-设置项B", i) > 0)
			cout << "[配置组4]/配置组4-设置项B=" << i << endl;
		if (fcfg.item_get_value("配置组1", "配置组1-设置项F", i) > 0)
			cout << "[配置组1]/配置组1-设置项F=" << i << endl;
		if (fcfg.item_get_value("配置组6", "配置组6-设置项D", c) > 0)
			cout << "[配置组6]/配置组6-设置项D=" << c << endl;
		if (fcfg.item_get_value("配置组8", "配置组8-设置项C", s) > 0)			//默认读到的item_value不能带空格
			cout << "[配置组8]/配置组8-设置项C=" << s << endl;
		if (fcfg.item_get_value("配置组8", "配置组8-设置项C", s, true) > 0)	//最后加true参数表示读到的item_value允许带空格
			cout << "[配置组8]/配置组8-设置项C=" << s << endl;
		if (fcfg.item_get_value("配置组2", "配置组2-设置项Q", str) > 0)
			cout << "[配置组2]/配置组2-设置项Q=" << str << endl;
		if (fcfg.item_get_value("配置组7", "配置组7-设置项E") > 0)
			cout << "[配置组7]/配置组7-设置项E=<NULL>" << endl;
		if (fcfg.item_get_value("配置组6", "配置组6-设置项B", d) > 0)
			cout << "[配置组6]/配置组6-设置项B=" << d << endl;
		if (fcfg.item_get_value("配置组1", "设置项100") > 0)
			cout << "[配置组1]/设置项100=<NULL>" << endl;
		else
			cout << "[配置组1]/设置项100 不存在" << endl;

		fcfg.close(); //关闭文件，模拟本次设置完成

		cout << "第5组测试完成，请打开配置文件(" << cfgname << ")，观察上述配置读取是否正确" << endl;
		to_be_continued();
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
int main()
{
	/* 为了保持自己的程序与提供的lib可以互用，限制整个class的大小为 1024字节，不足则补齐 */
	if (sizeof(cft) != 768) {
		cout << "class cft 不是768字节，如果使用 lib_tcfg_tools.lib 中的函数则可能出错" << endl;
		return -1;
	}

	const char* cfgname = "u2152611_s.cfg";
	const char* group_name[] = {
		"配置组1",
		"配置组2",
		"配置组3",
		"配置组4",
		"配置组5",
		"配置组6",
		"配置组7",
		"配置组8",
		NULL
	};

	struct cfg_item item[] =
	{
		{ "设置项A",ITEM_TYPE::Int, 0 },		//共用体union的初始化，只能初始化第一个元素
		{ "设置项B",ITEM_TYPE::Double, 0 },
		{ "设置项C",ITEM_TYPE::String, 0 },
		{ "设置项D",ITEM_TYPE::Character, 0 },
		{ "设置项E",ITEM_TYPE::Null, 0 },
		{ "设置项F",ITEM_TYPE::Int, 0 },
		{ "设置项G",ITEM_TYPE::String, 0 },
		{ NULL,		ITEM_TYPE::Null, 0 }
	};
	set_item(item); //给union赋初值
#if 1
	int loop = 1;
	char sel;
	while (loop) {
		/* 偷懒了*/
		cout << "====================================" << endl;
		cout << "组配置文件测试，请选择插入方式" << endl;
		cout << "  1.在组名后插入" << endl;
		cout << "  2.在组名后的第一个空行位置" << endl;
		cout << "  3.在下一个组名前" << endl;
		cout << "  0.退出" << endl;
		cout << "====================================" << endl;
		cout << "请选择[0-3] : ";
		sel = _getch();
		putchar(sel);
		putchar('\n');

		switch (sel) {
			case '1':
				test_readconfig_cpp(cfgname, group_name, item, InsertPosition::First_line_after_group);
				to_be_continued("\n\n\n按C继续", 'C');
				break;
			case '2':
				test_readconfig_cpp(cfgname, group_name, item, InsertPosition::First_blank_line_after_group);
				to_be_continued("\n\n\n按C继续", 'C');
				break;
			case '3':
				test_readconfig_cpp(cfgname, group_name, item, InsertPosition::Before_next_group);
				break;
				to_be_continued("\n\n\n按C继续", 'C');
			case '0':
				loop = 0;
				break;
			default:
				break;
		}	//end of switch
	}
#elif 1
	int loop = 1;
	char sel;
	while (loop) {
		/* 偷懒了*/
		cout << "====================================" << endl;
		cout << "简单配置文件测试，请选择插入方式" << endl;
		cout << "  1.在文件最开始插入" << endl;
		cout << "  2.在第一个空行位置" << endl;
		cout << "  3.在文件最后插入" << endl;
		cout << "  0.退出" << endl;
		cout << "====================================" << endl;
		cout << "请选择[0-3] : ";
		sel = _getch();
		putchar(sel);
		putchar('\n');

		switch (sel) {
			case '1':
				test_readconfig_cpp(cfgname, item, InsertPosition::Begin_of_file);
				to_be_continued("\n\n\n按C继续", 'C');
				break;
			case '2':
				test_readconfig_cpp(cfgname, item, InsertPosition::First_blank_line);
				to_be_continued("\n\n\n按C继续", 'C');
				break;
			case '3':
				test_readconfig_cpp(cfgname, item, InsertPosition::End_of_file);
				break;
				to_be_continued("\n\n\n按C继续", 'C');
			case '0':
				loop = 0;
				break;
			default:
				break;
		}	//end of switch
	}

#elif 0
	/* 改为调用公共菜单函数，三选一即可*/
	test_readconfig_cpp(cfgname, group_name, item, InsertPosition::First_line_after_group);
	to_be_continued("\n\n\n按C继续", 'C');

	test_readconfig_cpp(cfgname, group_name, item, InsertPosition::First_blank_line_after_group);
	to_be_continued("\n\n\n按C继续", 'C');

	test_readconfig_cpp(cfgname, group_name, item, InsertPosition::Before_next_group);
	to_be_continued("\n\n\n按C继续", 'C');
#endif

	return 0;

}