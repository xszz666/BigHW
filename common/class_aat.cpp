/* 2152611 ����˳ ��02 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include "../include/class_aat.h"
//���б�Ҫ�����Լ�������ͷ�ļ�
using namespace std;

#define typelen 22
#define deflen 17
#define exilen 7


#if !ENABLE_LIB_AAT_TOOLS //��ʹ��lib����Ч

/* ---------------------------------------------------------------
	 �������������Ҫstatic�������ڲ������ã�
   ---------------------------------------------------------------- */
static bool if_ip(const char* ip)
{
	int n = 0, sim = 0;
	bool out_range = 0;
	for (int i = 0; ip[i] != '\0'; i++)
	{
		if (ip[i] == '.')
		{
			n++;
			sim = 0;
			if (ip[i + 1] == '0')
			{
				out_range = 1;
				break;
			}
		}
		else if (ip[i] >= '0' && ip[i] <= '9')
		{
			sim *= 10;
			sim += ip[i] - '0';

			if (sim < 0 || sim>255)
			{
				out_range = 1;
				break;
			}
		}
		else
		{
			out_range = 1;
			break;
		}
	}

	if (n != 3)
		out_range = 1;

	return !out_range;
}

static unsigned int ip_int(const string ip)
{
	int result = 0;
	int m[4] = { 0 };
	char b[4][4];
	for (int i = 0, j = 0, k = 0; ; i++, k++)
	{
		if (ip[i] != '.' && ip[i] != '\0')
			b[j][k] = ip[i];
		else
		{
			b[j][k] = '\0';
			j++;
			k = -1;
			if (ip[i] == '\0')
				break;
		}
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; b[i][j] != '\0'; j++)
		{
			m[i] *= 10;
			m[i] += b[i][j] - '0';
		}
	}

	result = m[3] + m[2] * 256 + m[1] * 256 * 256 + m[0] * 256 * 256 * 256;

	return result;
}

static string int_ip(unsigned int n)
{
	char a[20] = "";
	unsigned int m[4];
	char b[4][4];
	m[0] = n / (256 * 256 * 256);
	m[1] = n % (256 * 256 * 256) / (256 * 256);
	m[2] = n % (256 * 256) / 256;
	m[3] = n % 256;


	for (int i = 0; i < 4; i++)
	{
		b[i][0] = m[i] / 100 + '0';
		b[i][1] = m[i] % 100 / 10 + '0';
		b[i][2] = m[i] % 10 + '0';
		b[i][3] = '\0';
	}

	for (int i = 0; i < 4; i++)
	{
		while (b[i][0] == '0')
			for (int j = 0; b[i][j] != '\0'; j++)
				b[i][j] = b[i][j + 1];
	}
	sprintf(a, "%s.%s.%s.%s", b[0], b[1], b[2], b[3]);

	return string(a);
}

static int char_to_int(const char* c)
{
	int a = 0;
	for (int i = 0; c[i] != '\0'; i++)
	{
		a *= 10;
		a += c[i] - '0';
	}
	return a;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����null
 ***************************************************************************/
args_analyse_tools::args_analyse_tools()
{
	args_name = "";
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����boolean
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const ST_EXTARGS_TYPE type, const int ext_num, const bool def)
{
	args_existed = 0;
	args_name = name;
	extargs_type = type;
	extargs_num = ext_num;
	extargs_bool_default = 1;
	
	if (extargs_num != 0)
	{
		cout << "args_analyse�ĸ��Ӳ�����������Ϊ0(type=" << int(type) << ")" << endl;
		exit(0);
	}
	

	if (extargs_bool_default == 1)
		vue_len = 5;
	else
		vue_len = 4;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����int_with_default��int_with_error
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const ST_EXTARGS_TYPE type, const int ext_num, const int def, const int _min, const int _max)
{
	
	args_existed = 0;
	args_name = name;
	extargs_type = type;
	extargs_num = ext_num;
	extargs_int_default = def;
	extargs_int_min = _min;
	extargs_int_max = _max;

	if (extargs_num != 1)
	{
		cout << "args_analyse�ĸ��Ӳ�����������Ϊ1(type=" << int(type) << ")" << endl;
		exit(0);
	}

	if (type == ST_EXTARGS_TYPE::int_with_default)
	{

		vue_len = 17;
		extargs_int_value = extargs_bool_default;
	}
	else
	{

		vue_len = 17;
	}
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����int_with_set_default��int_with_set_error
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const ST_EXTARGS_TYPE type, const int ext_num, const int def_of_set_pos, const int* const set)
{
	args_existed = 0;
	args_name = name;
	extargs_type = type;
	extargs_num = ext_num;
	extargs_int_default = set[def_of_set_pos];
	extargs_int_set = (int*)set;
	if (extargs_num != 1)
	{
		cout << "args_analyse�ĸ��Ӳ�����������Ϊ1(type=" << int(type) << ")" << endl;
		exit(0);
	}
	if (type == ST_EXTARGS_TYPE::int_with_set_default)	
		extargs_int_value = extargs_int_default;
	

	vue_len = 17;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����str��ipaddr_with_default��ipaddr_with_error
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const ST_EXTARGS_TYPE type, const int ext_num, const string def)
{
	args_existed = 0;
	args_name = name;
	extargs_type = type;
	extargs_num = ext_num;
	if (type == ST_EXTARGS_TYPE::str)
		extargs_string_default = def;
	else
		extargs_ipaddr_default = ip_int(def);
	if (extargs_num != 1)
	{
		cout << "args_analyse�ĸ��Ӳ�����������Ϊ1(type=" << int(type) << ")" << endl;
		exit(0);
	}
	if (type == ST_EXTARGS_TYPE::str)
		extargs_string_value = extargs_string_default;	
	else if (type == ST_EXTARGS_TYPE::ipaddr_with_default)
		extargs_ipaddr_value = extargs_ipaddr_default;
	


	vue_len = def.length();
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����str_with_set_default��str_with_set_error
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const ST_EXTARGS_TYPE type, const int ext_num, const int def_of_set_pos, const string* const set)
{
	args_existed = 0;
	args_name = name;
	extargs_type = type;
	extargs_num = ext_num;
	extargs_string_default = set[def_of_set_pos];
	extargs_string_set = (string*)set;
	if (extargs_num != 1)
	{
		cout << "args_analyse�ĸ��Ӳ�����������Ϊ1(type=" << int(type) << ")" << endl;
		exit(0);
	}
	if (type == ST_EXTARGS_TYPE::str_with_set_default)
	{

		vue_len = extargs_string_default.length();
		extargs_string_value = extargs_string_default;
	}
	else
		vue_len = 17;
	
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
args_analyse_tools::~args_analyse_tools()
{

}

/* ---------------------------------------------------------------
	 ����AAT���Զ����Ա������ʵ�֣�private��
   ---------------------------------------------------------------- */

   /***************************************************************************
	 �������ƣ�
	 ��    �ܣ�
	 ���������
	 �� �� ֵ��
	 ˵    ������ʵ�֣���Ҫ��
	***************************************************************************/
const string args_analyse_tools::get_name() const
{
	return args_name;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ������!!��ֻ����0/1
			��ʵ�֣���Ҫ��
 ***************************************************************************/
const int args_analyse_tools::existed() const
{
	return !!args_existed;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ������ʵ�֣���Ҫ��
 ***************************************************************************/
const int args_analyse_tools::get_int() const
{
	return extargs_int_value;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ������ʵ�֣���Ҫ��
 ***************************************************************************/
const string args_analyse_tools::get_string() const
{
	return extargs_string_value;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ������ʵ�֣���Ҫ��
 ***************************************************************************/
const unsigned int args_analyse_tools::get_ipaddr() const
{
	return extargs_ipaddr_value;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ������ extargs_ipaddr_value ��ֵ�� 0x7f000001 תΪ "127.0.0.1"
 ***************************************************************************/
const string args_analyse_tools::get_str_ipaddr() const
{

	return int_ip(extargs_ipaddr_value); //�˾������Ҫ�޸�
}


/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������follow_up_args���Ƿ��к�������
			./log_login --limit 10 --user root                    ���޺�����������0
			./ulimits_check --memory 256 --cpu 1 [./log_login ***]���к�����������1
  �� �� ֵ��
  ˵    ������Ԫ����
***************************************************************************/
int args_analyse_process(const int argc, const char* const* const argv, args_analyse_tools* const args, const int follow_up_args)
{
	
	int i;
	for ( i = 1; i < argc ; i++)
	{
		bool yes = 0;
		for (int j = 0; args[j].args_name != ""; j++)
		{
			if (argv[i] == args[j].args_name)
			{
				yes = 1;
				if (args[j].args_existed == 1)
				{
					cout << "����[" << args[j].args_name << "]�ظ�." << endl;
					return -1;
				}

				args[j].args_existed = 1;
				bool if_need_def = 1;

				switch (args[j].extargs_type)
				{
					case ST_EXTARGS_TYPE::boolean:
						args[j].def = 1;
						break;
					case ST_EXTARGS_TYPE::int_with_default:
						if (argv[i + 1][0] == '-' && argv[i + 1][1] == '-')
						{
							cout << "����[" << args[j].args_name << "]�ĸ��Ӳ������� (����:int, ��Χ[" << args[j].extargs_int_min << ".." << args[j].extargs_int_max << "] ȱʡ:" << args[j].extargs_int_default << endl;
							return -1;
						}
						for(int m=0;argv[i+1][m]!='\0';m++)
							if (argv[i + 1][m] < '0' || argv[i + 1][m] < '9')
							{
								cout << "����[" << args[j].args_name << "]�ĸ��Ӳ���ֵ(" << argv[i + 1] << ")��������. (����:int, ��Χ[" << args[j].extargs_int_min << ".." << args[j].extargs_int_max << "])" << endl;
								return -1;
							}
						args[j].extargs_int_value = char_to_int(argv[i + 1]);
						if (args[j].extargs_int_value<args[j].extargs_int_min || args[j].extargs_int_value > args[j].extargs_int_max)
							args[j].extargs_int_value = args[j].extargs_int_default;
						i++;
						args[j].def = 1;
						break;
					case ST_EXTARGS_TYPE::int_with_error:
						if (argv[i + 1][0] == '-' && argv[i + 1][1] == '-')
						{
							cout << "����[" << args[j].args_name << "]�ĸ��Ӳ������� (����:int, ��Χ[" << args[j].extargs_int_min << ".." << args[j].extargs_int_max << "])" << endl;
							return -1;
						}
						for (int m = 0; argv[i + 1][m] != '\0'; m++)
							if (argv[i + 1][m] < '0' || argv[i + 1][m] < '9')
							{
								cout << "����[" << args[j].args_name << "]�ĸ��Ӳ���ֵ(" << argv[i + 1] << ")��������. (����:int, ��Χ[" << args[j].extargs_int_min << ".." << args[j].extargs_int_max << "])" << endl;
								return -1;
							}
						args[j].extargs_int_value = char_to_int(argv[i + 1]);
						if (args[j].extargs_int_value<args[j].extargs_int_min || args[j].extargs_int_value > args[j].extargs_int_max)
						{
							cout << "����[" << args[j].args_name << "]�ĸ��Ӳ���ֵ(" << argv[i + 1] << ")�Ƿ�. (����:int, ��Χ[" << args[j].extargs_int_min << ".." << args[j].extargs_int_max << "])" << endl;
							return -1;
						}
						i++;
						break;
					case ST_EXTARGS_TYPE::int_with_set_default:
						if (argv[i + 1][0] == '-' && argv[i + 1][1] == '-')
						{
							cout << "����[" << args[j].args_name << "]�ĸ��Ӳ������� (����:int, ��ȡֵ[";
							for (int m = 0; args[j].extargs_int_set[m] != INVALID_INT_VALUE_OF_SET; m++)
							{
								if (m != 0)
									cout << "/";
								cout << args[j].extargs_int_set[m];
							}
							cout << "] ȱʡ:" << args[j].extargs_int_default << ")" << endl;
							return -1;
						}for (int m = 0; argv[i + 1][m] != '\0'; m++)
							if (argv[i + 1][m] < '0' || argv[i + 1][m] < '9')
							{
								cout << "����[" << args[j].args_name << "]�ĸ��Ӳ���ֵ(" << argv[i + 1] << ")��������. (����:int, ��Χ[" << args[j].extargs_int_min << ".." << args[j].extargs_int_max << "])" << endl;
								return -1;
							}
						args[j].def = 1;
						args[j].extargs_int_value = char_to_int(argv[i + 1]);
						for (int m = 0; args[j].extargs_int_set[m] != INVALID_INT_VALUE_OF_SET; m++)
						{
							if (args[j].extargs_int_value == args[j].extargs_int_set[m])
							{
								if_need_def = 0;
								break;
							}
						}
						if (if_need_def == 1)
							args[j].extargs_int_value = args[j].extargs_int_default;
						i++;
						break;
					case ST_EXTARGS_TYPE::int_with_set_error:
						if (argv[i + 1][0] == '-' && argv[i + 1][1] == '-')
						{
							cout << "����[" << args[j].args_name << "]�ĸ��Ӳ������� (����:int, ��ȡֵ[";
							for (int m = 0; args[j].extargs_int_set[m] != INVALID_INT_VALUE_OF_SET; m++)
							{
								if (m != 0)
									cout << "/";
								cout << args[j].extargs_int_set[m];
							}
							cout << "])" << endl;
							return -1;
						}for (int m = 0; argv[i + 1][m] != '\0'; m++)
							if (argv[i + 1][m] < '0' || argv[i + 1][m] < '9')
							{
								cout << "����[" << args[j].args_name << "]�ĸ��Ӳ���ֵ(" << argv[i + 1] << ")��������. (����:int, ��Χ[" << args[j].extargs_int_min << ".." << args[j].extargs_int_max << "])" << endl;
								return -1;
							}
						args[j].extargs_int_value = char_to_int(argv[i + 1]);
						for (int m = 0; args[j].extargs_int_set[m] != INVALID_INT_VALUE_OF_SET; m++)
						{
							if (args[j].extargs_int_value == args[j].extargs_int_set[m])
							{
								if_need_def = 0;
								break;
							}
						}
						if (if_need_def == 1)
						{
							cout << "����[" << args[j].args_name << "]�ĸ��Ӳ���ֵ(" << argv[i + 1] << ")�Ƿ�. (����:int, ��ȡֵ[";
							for (int m = 0; args[j].extargs_int_set[m] != INVALID_INT_VALUE_OF_SET; m++)
							{
								if (m != 0)
									cout << "/";
								cout << args[j].extargs_int_set[m];
							}
							cout << "])" << endl;
							return -1;
						}
						i++;
						break;
					case ST_EXTARGS_TYPE::str:
						if (argv[i + 1][0] == '-' && argv[i + 1][1] == '-')
						{
							cout << "����[" << args[j].args_name << "]�ĸ��Ӳ������� (����:string)" << endl;
							return -1;
						}
						args[j].vue_len = strlen(argv[i + 1]);
						if (args[j].extargs_string_default != "")
							args[j].def = 1;
						args[j].extargs_string_value = argv[i + 1];
						i++;
						break;
					case ST_EXTARGS_TYPE::str_with_set_default:
						if (argv[i + 1][0] == '-' && argv[i + 1][1] == '-')
						{
							cout << "����[" << args[j].args_name << "]�ĸ��Ӳ������� (����:string)" << endl;
							return -1;
						}
						args[j].vue_len = strlen(argv[i + 1]);
						args[j].def = 1;
						args[j].extargs_string_value = argv[i + 1];
						for (int m = 0; args[j].extargs_string_set[m] != ""; m++)
						{
							if (args[j].extargs_string_value == args[j].extargs_string_set[m])
							{
								if_need_def = 0;
								break;
							}
						}
						if (if_need_def == 1)
							args[j].extargs_string_value = args[j].extargs_string_default;
						i++;
						break;
					case ST_EXTARGS_TYPE::str_with_set_error:
						if (argv[i + 1][0] == '-' && argv[i + 1][1] == '-')
						{
							cout << "����[" << args[j].args_name << "]�ĸ��Ӳ������� (����:string, ��ȡֵ[";
							for (int m = 0; args[j].extargs_string_set[m] != ""; m++)
							{
								if (m != 0)
									cout << "/";
								cout << args[j].extargs_string_set[m];
							}
							cout << "])" << endl;
							return -1;
						}
						args[j].extargs_string_value = argv[i + 1];
						args[j].vue_len = strlen(argv[i + 1]);
						for (int m = 0; args[j].extargs_string_set[m] != ""; m++)
						{
							if (args[j].extargs_string_value == args[j].extargs_string_set[m])
							{
								if_need_def = 0;
								break;
							}
						}
						if (if_need_def == 1)
						{
							cout << "����[" << args[j].args_name << "]�ĸ��Ӳ���ֵ(" << argv[i + 1] << ")�Ƿ�. (����:string, ��ȡֵ[";
							for (int m = 0; args[j].extargs_string_set[m] != ""; m++)
							{
								if (m != 0)
									cout << "/";
								cout << args[j].extargs_string_set[m];
							}
							cout << "])" << endl;
							return -1;
						}
						i++;
						break;
					case ST_EXTARGS_TYPE::ipaddr_with_default:
						if (argv[i + 1][0] == '-' && argv[i + 1][1] == '-')
						{
							cout << "����[" << args[j].args_name << "]�ĸ��Ӳ������� (����:IP��ַ ȱʡ:" << int_ip(args[j].extargs_ipaddr_default) << ")" << endl;
							return -1;
						}
						args[j].def = 1;
						args[j].vue_len = strlen(argv[i + 1]);
						//�Ƿ�Ϊ�Ϸ�ip
						if (if_ip(argv[i + 1]) == 0)
							args[j].extargs_ipaddr_value = args[j].extargs_ipaddr_default;
						else
							args[j].extargs_ipaddr_value = ip_int(argv[i + 1]);
						i++;
						break;
					case ST_EXTARGS_TYPE::ipaddr_with_error:
						if (argv[i + 1][0] == '-' && argv[i + 1][1] == '-')
						{
							cout << "����[" << args[j].args_name << "]�ĸ��Ӳ������� (����:IP��ַ ȱʡ:" << int_ip(args[j].extargs_ipaddr_default) << ")" << endl;
							return -1;
						}
						args[j].vue_len = strlen(argv[i + 1]);
						//�Ƿ�Ϊ�Ϸ�ip
						if (if_ip(argv[i + 1]) == 0)
						{
							cout << "����[--iperr]�ĸ��Ӳ���ֵ(" << argv[i + 1] << ")�Ƿ�. (����:IP��ַ)" << endl;
							return -1;
						}
						args[j].extargs_ipaddr_value = ip_int(argv[i + 1]);
						i++;
						break;
				}
				break;
			}
		}
		if (!yes && !follow_up_args)
		{
			cout << "����[" << argv[i] << "]�Ƿ�." << endl;
			return -1;
		}
		else if (!yes && follow_up_args)
			return i;
	}
	return i<argc-1?i:argc-1;	
}


/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ������Ԫ����
***************************************************************************/
int args_analyse_print(const args_analyse_tools* const args)
{

	int len_name = 0, len_vue = 17;

	for (int i = 0; args[i].args_name != ""; i++)
	{
		if (int(args[i].args_name.length()) > len_name)
			len_name = args[i].args_name.length();

		if(args[i].vue_len>len_vue)
			len_vue=args[i].vue_len;
	}

	cout << setiosflags(ios::left) << setw(len_name + 2) << "name" << setw(typelen) << "type"<<setw(deflen)<<"default"<<setw(exilen) << "exists" <<setw(len_vue+1) << "value" << "range / set" << endl;
	cout << setfill('=') << setw(len_name + 2) << '=';
	cout << setfill(' ');
	cout << "=======================================================================================================" << endl;

	for (int i = 0; args[i].args_name != ""; i++)
	{
		cout << setiosflags(ios::left) << setw(len_name + 2) << args[i].args_name;

		switch (args[i].extargs_type)
		{
			case ST_EXTARGS_TYPE::boolean:
				cout << setw(typelen) << "Bool" << setw(deflen) << (args[i].extargs_bool_default ? "true" : "false") << setw(exilen) << args[i].args_existed << setw(len_vue + 1);
				if (args[i].args_existed)
					cout << (args[i].extargs_bool_default ? "true" : "false");
				else
					cout << "/";
				cout  << '/' << endl;
				break;
			case ST_EXTARGS_TYPE::int_with_default:
				cout << setw(typelen) << "IntWithDefault" << setw(deflen) << args[i].extargs_int_default << setw(exilen) << args[i].args_existed << setw(len_vue + 1);
				if (args[i].args_existed)
					cout << args[i].extargs_int_value ;
				else
					cout << "/";
				cout << "[" << args[i].extargs_int_min << ".." << args[i].extargs_int_max << "]" << endl;
				break;
			case ST_EXTARGS_TYPE::int_with_error:
				cout << setw(typelen) << "IntWithError" << setw(deflen) << '/' << setw(exilen) << args[i].args_existed << setw(len_vue + 1);
				if (args[i].args_existed)
					cout << args[i].extargs_int_value ;
				else
					cout << "/";
				cout << "[" << args[i].extargs_int_min << ".." << args[i].extargs_int_max << "]" << endl;
				break;
			case ST_EXTARGS_TYPE::int_with_set_default:
				cout << setw(typelen) << "IntSETWithDefault" << setw(deflen) << args[i].extargs_int_default << setw(exilen) << args[i].args_existed << setw(len_vue + 1);
				if (args[i].args_existed)
					cout << args[i].extargs_int_value;
				else
					cout << "/";
				for (int m = 0; args[i].extargs_int_set[m] != INVALID_INT_VALUE_OF_SET; m++)
				{
					if (m != 0)
						cout << "/";
					cout << args[i].extargs_int_set[m];
				}
				cout << endl;
				break;
			case ST_EXTARGS_TYPE::int_with_set_error:
				cout << setw(typelen) << "IntSETWithError" << setw(deflen) << "/" << setw(exilen) << args[i].args_existed << setw(len_vue + 1);
				if (args[i].args_existed)
					cout << args[i].extargs_int_value;
				else
					cout << "/";
				for (int m = 0; args[i].extargs_int_set[m] != INVALID_INT_VALUE_OF_SET; m++)
				{
					if (m != 0)
						cout << "/";
					cout << args[i].extargs_int_set[m];
				}
				cout << endl;
				break;
			case ST_EXTARGS_TYPE::str:
				cout << setw(typelen) << "String" << setw(deflen) << (args[i].extargs_string_default[0] ? args[i].extargs_string_default : "/") << setw(exilen) << args[i].args_existed << setw(len_vue + 1);
				if (args[i].args_existed)
					cout << args[i].extargs_string_value ;
				else
					cout << "/";
				cout << "/" << endl;
				break;
			case ST_EXTARGS_TYPE::str_with_set_default:
				cout << setw(typelen) << "StringSETWithDefault" << setw(deflen) << args[i].extargs_string_default << setw(exilen) << args[i].args_existed << setw(len_vue + 1);
				if (args[i].args_existed)
					cout << args[i].extargs_string_value ;
				else
					cout << "/";
				for (int m = 0; args[i].extargs_string_set[m] != ""; m++)
				{
					if (m != 0)
						cout << "/";
					cout << args[i].extargs_string_set[m];
				}
				cout << endl;
				break;
			case ST_EXTARGS_TYPE::str_with_set_error:
				cout << setw(typelen) << "StringSETWithError" << setw(deflen) << "/" << setw(exilen) << args[i].args_existed << setw(len_vue + 1);
				if (args[i].args_existed)
					cout << args[i].extargs_string_value ;
				else
					cout << "/";
				for (int m = 0; args[i].extargs_string_set[m] != ""; m++)
				{
					if (m != 0)
						cout << "/";
					cout << args[i].extargs_string_set[m];
				}
				cout << endl;
				break;
			case ST_EXTARGS_TYPE::ipaddr_with_default:
				cout << setw(typelen) << "IPAddrWithDefault" << setw(deflen) << int_ip(args[i].extargs_ipaddr_default) << setw(exilen) << args[i].args_existed << setw(len_vue + 1);
				if (args[i].args_existed)
					cout << int_ip(args[i].extargs_ipaddr_value) ;
				else
					cout << "/";
				cout << "/" << endl;
				break;
			case ST_EXTARGS_TYPE::ipaddr_with_error:
				cout << setw(typelen) << "IPAddrWithError" << setw(deflen) << "/" << setw(exilen) << args[i].args_existed << setw(len_vue + 1);
				if (args[i].args_existed)
					cout << int_ip(args[i].extargs_ipaddr_value);
				else
					cout << "/";
				cout << "/" << endl;
				break;
		}
	}

	return 0; //�˾������Ҫ�޸�
}
#endif // !ENABLE_LIB_AAT_TOOLS
