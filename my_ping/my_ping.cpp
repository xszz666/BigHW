/* 2152611 ����˳ ��02 */
#include <iostream>
//�ɸ�����Ҫ�ټ���������Ҫ��ͷ�ļ�
#include "../include/class_aat.h"
using namespace std;

/* ���������������������Ҳ���Խ��Զ��庯����������cpp�� */
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

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int main(int argc, char* argv[])
{
	args_analyse_tools args[] = {
		args_analyse_tools("--l", ST_EXTARGS_TYPE::int_with_default, 1,  32, 64000, 64),		
		args_analyse_tools("--n",  ST_EXTARGS_TYPE::int_with_default, 1,  1, 1024,4),
		args_analyse_tools("--t",  ST_EXTARGS_TYPE::boolean,       1, string("")),
		args_analyse_tools()  //���һ�������ڽ���
	};


	int cur_argc, ret = 0;

	if ((cur_argc = args_analyse_process(argc, argv, args, 1)) < 0)
	{
		return -1;
	}
	
	if (argc - cur_argc!=1||if_ip(argv[cur_argc]) == 0)
	{
		cout << "IP��ַ����" << endl;
		return 0;
	}
	

	args_analyse_print(args);
	cout << endl;
	cout << "IP��ַ��" << argv[cur_argc] << endl;

	return 0;
}

