/* 2152611 邹良顺 信02 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "../include/class_aat.h"
using namespace std;

/***************************************************************************
  函数名称：
  功    能：基本测试
  输入参数：
  返 回 值：
  说    明：命令行格式要求：先--开始的可变参数，顺序任意，最后是指定的固定参数
***************************************************************************/
int main(int argc, char* argv[])
{
	/* 因为引入了 lib_aat_tools.lib，此处先检查大小是否符合要求 */
	if (sizeof(args_analyse_tools) != 200) {
		cout << "class args_analyse_tools 不是200字节，如果使用 lib_aat_tools.lib 中的函数则可能出错" << endl;
		return -1;
	}

	string hashtype[] = { "md5","sha1","sha224","sha256","sha384","sha512","all", "" };	//结尾必须是""
	int intset[] = { 11, 22, 33, 123, 345, INVALID_INT_VALUE_OF_SET }; 				//结尾必须是INVALID_INT_VALUE_OF_SET

	args_analyse_tools args[] = {
		args_analyse_tools("--help",      ST_EXTARGS_TYPE::boolean, 1, false),
		args_analyse_tools("--bool",      ST_EXTARGS_TYPE::boolean, 0, true),
		args_analyse_tools("--intdef",    ST_EXTARGS_TYPE::int_with_default,        1, 12345, 0, 65535),
		args_analyse_tools("--interr",    ST_EXTARGS_TYPE::int_with_error,          1, 12345, 0, 65535),	//参数12345可为任何值，无意义
		args_analyse_tools("--intsetdef", ST_EXTARGS_TYPE::int_with_set_default,    1, 2, intset),		//参数2代表default为set中的第[2]个值，即33，如果此值超范围，缺省0
		args_analyse_tools("--intseterr", ST_EXTARGS_TYPE::int_with_set_error,      1, 2, intset),		//参数2无意义，不用
		args_analyse_tools("--str1",      ST_EXTARGS_TYPE::str,                  1, string("")),		//必须加string()，否则被适配到args_analyse(const char *arg_name, enum ST_EXTARGS_TYPE type, int ext_num, bool def)
		args_analyse_tools("--str2",      ST_EXTARGS_TYPE::str,                  1, string("Hello")),	//必须加string()，否则被适配到args_analyse(const char *arg_name, enum ST_EXTARGS_TYPE type, int ext_num, bool def)
		args_analyse_tools("--strsetdef", ST_EXTARGS_TYPE::str_with_set_default, 1, 3, hashtype),		//参数3代表default为set中的第[3]个值，即sha256，如果此值超范围，缺省0
		args_analyse_tools("--strseterr", ST_EXTARGS_TYPE::str_with_set_error,   1, 3, hashtype),		//参数3无意义，不用
		args_analyse_tools("--ipdef",     ST_EXTARGS_TYPE::ipaddr_with_default,     1, string("192.168.80.230")),
		args_analyse_tools("--iperr",     ST_EXTARGS_TYPE::ipaddr_with_error,       1, string("")),
		args_analyse_tools()  //最后一个，用于结束
	};

	int need_fixed_args = 1;	//试试改为1
	int cur_argc;

	/* 最后一个参数：1-表示除选项参数外，还需要其它参数
				  0-表示除选项参数外，不需要其它参数 */
	if ((cur_argc = args_analyse_process(argc, argv, args, need_fixed_args)) < 0)
	{
		//错误信息在函数中已打印
		return -1;
	}

	args_analyse_print(args);

	/* 参数分析完成后的错误处理 */
	if (need_fixed_args) {
		if (cur_argc == argc) {  //说明后面没有跟需要的固定参数
			cout << "指定需要固定参数，但未给出" << endl;
			return -1;
		}

		/* 此处应该处理要求的固定参数，本例中简单打印即可 */
		cout << "还有" << argc - cur_argc << "个固定参数，具体某个参数对应的动作由具体程序决定，本处忽略" << endl;
		for (int i = cur_argc; i < argc; i++)
			cout << argv[i] << endl;
	}

	cout << endl << "请认真观察打印输出中，对应项的exist是否为1，值是否为预期" << endl << endl;

	cout << "查看default与error区别的方法：" << endl;
	cout << "  给出不在指定范围内的值，会看出差别" << endl;
	cout << "  例：--intdef 100000" << endl;
	cout << "      --interr 100000" << endl;

	return 0;
}

#if 0
// 测试用例

. / test_optargs --help

. / test_optargs--bool

. / test_optargs --intdef 123
. / test_optargs --intdef 123 --intdef 456
. / test_optargs --intdef -12
. / test_optargs --intdef 654321

. / test_optargs --interr 123
. / test_optargs --interr 123 --interr 456	//报错
. / test_optargs --interr -12
. / test_optargs --interr 654321

. / test_optargs --intsetdef 11
. / test_optargs --intsetdef 12
. / test_optargs --intsetdef 11 --intsetdef 22

. / test_optargs --intseterr 11
. / test_optargs --intseterr 12
. / test_optargs --intseterr 11 --intseterr 22

. / test_optargs --str1 hello
. / test_optargs --str1 hello --str1 horse	//报错

. / test_optargs --str2 hello
. / test_optargs --str2 hello --str2 horse	//报错

. / test_optargs --strsetdef md5
. / test_optargs --strsetdef md4
. / test_optargs --strsetdef md5 --strsetdef sha1	//报错

. / test_optargs --strseterr md5
. / test_optargs --strseterr md4
. / test_optargs --strseterr md5 --strseterr sha1	//报错

. / test_optargs --ipdef 1.1.1.1
. / test_optargs --iperr 1.1.1.1234
. / test_optargs --ipdef 1.1.1.1 --ipdef 2.2.2.2	//报错

//上面各测试项的任意组合：
#endif
