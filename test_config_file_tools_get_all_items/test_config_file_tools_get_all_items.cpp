/* 邹良顺 2152611 信02 */
/*2152205 邹明宇 2153592 胡逸凡 2153689 黄泽华*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <conio.h>
#include "../include/class_cft.h"
#include "../include/class_cft_gai.h"
using namespace std;

/***************************************************************************
  函数名称：
  功    能：显示提示信息
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
static void to_be_continued(const char* prompt = NULL, const char ch = '\r')
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
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int test_readconfig_cpp(const char* cfgname, const char** group_name, const char **item, InsertPosition pos)
{
	cft_gai	fcfg;
	int ret, i;

	/* 第1组测试，添加若干组 */
	if (1) {
		ret = remove(cfgname); //删除文件

		fcfg.open(cfgname, OPEN_OPT_RDWR);
		if (fcfg.is_open() == false) {
			cout << "无法打开数据文件(" << cfgname << ")." << endl;
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

		cout << "第1组测试完成，请打开数据文件(" << cfgname << ")，观察是否仅有6个空组";
		to_be_continued();
	}

	/* 第2组测试，每组添加若干项 */
	if (1) {
		fcfg.open(cfgname, OPEN_OPT_RDWR);
		if (fcfg.is_open() == false) {
			cout << "无法打开数据文件(" << cfgname << ")." << endl;
			return -1;
		}
		fcfg.set_insert_position(pos);
		fcfg.set_comment_switch(CommentSwitch::on);


		/* 测试数据中，每个group对应一个item，一个item中可含\r\n */
		for (i = 0; group_name[i]; i++) {
			ret = fcfg.item_add(group_name[i], item[i]);
			cout << "增加[" << group_name[i] << "]/" << item[i] << (ret > 0 ? "成功." : "失败.") << endl;
		}
		fcfg.close(); //关闭文件，模拟本次设置完成

		cout << "第2组测试完成，请打开配置文件(" << cfgname << ")，观察是否6个组均有1个配置项" << endl;
		to_be_continued();
	}

	/* 第3组测试，删除及增加某个组中的项
		注：1、因为不是 name = value 的形式，因此要删除的内容必须完全匹配，不能只给出 name
			2、同样理由，不支持Update，Update可以用Delete+Add实现 */
	if (1) {
		fcfg.open(cfgname, OPEN_OPT_RDWR);
		if (fcfg.is_open() == false) {
			cout << "无法打开配置文件(" << cfgname << ")." << endl;
			return -1;
		}
		fcfg.set_insert_position(pos);
		fcfg.set_comment_switch(CommentSwitch::on);

		/* 对于 FIRST_LINE_AFTER_GROUP 等形式，不符合对应题目的读取要求不是工具集的错误 */
		fcfg.group_add("5-b18-err-04");

		fcfg.item_add("5-b18-err-04", "请输入密码长度(12-16)，大写字母个数(≥2)，小写字母个数(≥2)，数字个数(≥2)，其它符号个数(≥2)");
		fcfg.item_add("5-b18-err-04", "17 2 2 2 2");
		fcfg.item_add("5-b18-err-04", "*B{7M4K;llFL:gOCd");
		fcfg.item_add("5-b18-err-04", "Ru(DP!+JlX*h5~2y^");
		fcfg.item_add("5-b18-err-04", "0>{4xqG5@e`rj0hCw");
		fcfg.item_add("5-b18-err-04", "_#K%?Mpa&*L8`2RNQ");
		fcfg.item_add("5-b18-err-04", "dn2FI6+Lyp_GX&6$@");
		fcfg.item_add("5-b18-err-04", ",!luVb<W37U*'51~=");
		fcfg.item_add("5-b18-err-04", "j<:#|Weq9g6A(}YR'");
		fcfg.item_add("5-b18-err-04", "zU2n[l4J|#Pj4qo6]");
		fcfg.item_add("5-b18-err-04", "Tl`f{7|rF4f(S6sP+");
		fcfg.item_add("5-b18-err-04", "(m';e8ngE^9p;GaYx");

		string s1 = "1234.5678        # 新的测试数据";
	
		/* 通过插入+删除实现更新 */
		fcfg.item_add("3-b4-01", s1);
		fcfg.item_del("3-b4-01", item[0]);

		/* 通过删除+插入实现更新 */
		fcfg.item_del("3-b4-02", item[1]);
		fcfg.item_add("3-b4-02", "0.07");

		/* 仅删除 */
		fcfg.item_del("3-b4-03", item[2]);

		/* 仅插入（测试程序操作错误导致数据重复，不是工具的错） */
		fcfg.item_add("3-b4-04", item[3]);

		/* 仅插入 */
		fcfg.item_add("5-b17-ok-01", "# 插入的注释行1.23.45.678");

		fcfg.close(); //关闭文件，模拟本次设置完成

		cout << "第3组测试完成，请打开配置文件" << cfgname << "，观察上述配置是否已修改" << endl;;
		to_be_continued();
	}

	/* 第4组测试，删除刚才插入的带注释的"1234.5678  # 新的测试数据" */
	if (1) {
		fcfg.open(cfgname, OPEN_OPT_RDWR);
		if (fcfg.is_open() == false) {
			cout << "无法打开配置文件(" << cfgname << ")." << endl;
			return -1;
		}
		fcfg.set_insert_position(pos);
		fcfg.set_comment_switch(CommentSwitch::on);

		string s1 = "        1234.5678        # 新的测试数据";

		/* 删除刚才插入的"1234.5678  # 新的测试数据" */
		fcfg.item_del("3-b4-01", s1.substr(0, 20)); //删除有效匹配项"1234.5678"，前后都多给了空格

		fcfg.close(); //关闭文件，模拟本次设置完成

		cout << "第4组测试完成，请打开配置文件" << cfgname << "，观察上述配置是否已修改" << endl;;
		to_be_continued();
	}

	/* 第5组测试，删除某个组 */
	if (1) {
		fcfg.open(cfgname, OPEN_OPT_RDWR);
		if (fcfg.is_open() == false) {
			cout << "无法打开配置文件(" << cfgname << ")." << endl;
			return -1;
		}
		fcfg.set_insert_position(pos);
		fcfg.set_comment_switch(CommentSwitch::on);

		cout << "删除[3-b4-02]共" << fcfg.group_del("3-b4-02") << "组" << endl;
		cout << "删除[5-b18-err-04]共" << fcfg.group_del("5-b18-err-04") << "组" << endl;

		fcfg.close(); //关闭文件，模拟本次设置完成

		cout << "第5组测试完成，请打开数据文件(" << cfgname << ")，观察[3-b4-02]/[5-b18-ok-02]是否已被删除" << endl;
		to_be_continued();
	}

	/* 第6组测试，读（忽略注释） */
	if (1) {
		fcfg.open(cfgname, OPEN_OPT_RDONLY);
		if (fcfg.is_open() == false) {
			cout << "无法打开配置文件(" << cfgname << ")." << endl;
			return -1;
		}
		fcfg.set_insert_position(pos);
		fcfg.set_comment_switch(CommentSwitch::on);

		/* 循环读出[5-b18-err-04]的全部内容] */
		string *list = fcfg.item_get_all("5-b18-ok-02");
		int num = 0;

		for (num = 0; list && list[num] != ""; num++)
			cout << num << " : " << list[num] << endl;

		fcfg.close(); //关闭文件，模拟本次设置完成
		delete[]list; //记得释放

		cout << "第6组测试完成，请打开配置文件(" << cfgname << ")，观察上述配置读取是否正确" << endl;
		to_be_continued();
	}

	/* 第7组测试，读(不忽略注释) */
	if (1) {
		fcfg.open(cfgname, OPEN_OPT_RDONLY);
		if (fcfg.is_open() == false) {
			cout << "无法打开配置文件(" << cfgname << ")." << endl;
			return -1;
		}
		fcfg.set_insert_position(pos);
		fcfg.set_comment_switch(CommentSwitch::off);

		/* 循环读出[5-b18-err-04]的全部内容] */
		string* list = fcfg.item_get_all("5-b18-ok-02");
		int num = 0;

		for (num = 0; list && list[num] != ""; num++)
			cout << num << " : " << list[num] << endl;

		fcfg.close(); //关闭文件，模拟本次设置完成
		delete[]list; //记得释放

		cout << "第7组测试完成，请打开配置文件(" << cfgname << ")，观察上述配置读取是否正确" << endl;
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
	if (sizeof(cft_gai) != 1024) {
		cout << "class cft 不是1024字节，如果使用 lib_tcfg_tools.lib 中的函数则可能出错" << endl;
		return -1;
	}

	const char* cfgname = "u2152611_g.cfg";
	const char* group_name[] = {
		"3-b4-01",
		"3-b4-02",
		"3-b4-03",
		"3-b4-04",
		"5-b17-ok-01",
		"5-b18-ok-02",
		NULL
	};

	const char *item[] =
	{
		"xszz666",
		"0.35           # 用于测试的额外注释内容",
		"10001.34",
		"0.07",
		"12 2 2 2 2",
		/* 注意，下面两行中，第一行没有逗号，因此两行组合为一个完整的字符串（这是一种使用技巧，你读到了你就掌握了） */
		"落叶捎来讯息,\r\n在雾的彼端,\r\n我们的故乡交界地,\r\n褪色者当上了艾尔登之王,\r\n在王的治理之下,\r\n相比人们会如此形容——那是个衰颓时代",
		NULL
	};

#if 1
	int loop = 1;
	char sel;
	while (loop) {
		/* 偷懒了*/
		cout << "============================" << endl;
		cout << "请选择插入方式" << endl;
		cout << "  1.在组名后插入" << endl;
		cout << "  2.在组名后的第一个空行位置" << endl;
		cout << "  3.在下一个组名前" << endl;
		cout << "  0.退出" << endl;
		cout << "============================" << endl;
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
#else
	/* 改为调用公共菜单函数，三选一即可*/
	test_readconfig_cpp(cfgname, group_name, item, InsertPosition::First_line_after_group);
//	to_be_continued("\n\n\n按C继续", 'C');

//	test_readconfig_cpp(cfgname, group_name, item, InsertPosition::First_blank_line_after_group);
//	to_be_continued("\n\n\n按C继续", 'C');

//	test_readconfig_cpp(cfgname, group_name, item, InsertPosition::Before_next_group);
//	to_be_continued("\n\n\n按C继续", 'C');
#endif

	return 0;

}
