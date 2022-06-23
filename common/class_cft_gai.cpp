/* ����˳ 2152611 ��02 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <io.h>
#include "../include/class_cft.h"
#include "../include/class_cft_gai.h"
//�������������Ҫ��ͷ�ļ�
using namespace std;

#define size_of_n 2

#if ! ENABLE_LIB_TCFG_TOOLS	//����lib����ܱ���

/* ---------------------------------------------------------------
	 �������������Ҫ��struct/class/union/�����ȣ��ڲ������ã�
	 1����������Ϊ��̬��������
	 2����������ų���/������
	 3��������Ҫ��ȫ�ֱ��������һ��Ҫ�ã���static
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

//δ�ı��ļ���С  ɾ��ָ�뵱ǰλ��ǰm���ֽ�  ָ�����m�ֽ�
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

//�������ý�����ָ��ָ��д��λ��
static void insert_to_file(fstream& fp, int insert_pos, int insert_size, const char* insert_s)
{

	fp.seekg(0, ios::end);
	//�������insert_size
		//���insert_size�ֽ�
	for (int i = 0; i < insert_size; i++)
	{
		fp.seekg(-insert_size, ios::cur);
		char ch = fp.get();
		fp.seekg(insert_size - 1, ios::cur);
		fp << ch;
	}

	//�����ֽ�
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

	//����ǰ��  insert_pos�ֽ�						
	fp.seekg(0, ios::beg);
	for (int i = 0; i < insert_pos; i++)
	{
		fp.seekg(insert_size, ios::cur);
		char ch = fp.get();
		fp.seekg(-insert_size - 1, ios::cur);
		fp << ch;
	}

	//д��
	fp.clear();
	fp.seekp(insert_pos, ios::beg);
	fp << insert_s << "\r\n";
}

/* ---------------------------------------------------------------
    �������class cft_gai�г�Ա������ʵ��
    ����ʵ�ֹ����в�Ҫ����cout�����Խ���Ϣ����msg�У���test�е���
  ---------------------------------------------------------------- */

/***************************************************************************
  �������ƣ�
  ��    �ܣ���class ctf��ͬ
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
int cft_gai::item_add(const char* group_name, const char* item_value)
{
	
	fp.clear();
	fp.seekg(0, ios::beg);

	int num = 0;

	//�ж��Ƿ�Ϊ���������ļ������ļ�
	if (group_name == NULL)
	{
		//�ж��Ƿ�Ϊ���������ļ������ļ�
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
	
	return 0; //�����޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���class ctf��ͬ
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
int cft_gai::item_add(const char* group_name, const string& item_value)
{
	return item_add(group_name, item_value.c_str());
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���class ctf��ͬ
  ���������
  �� �� ֵ��
  ˵    ����
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
	
	//�ж��Ƿ�Ϊ���������ļ������ļ�
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
	return 0; //�����޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���class ctf��ͬ
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
int cft_gai::item_del(const char* group_name, const string& item_value)
{
	return item_del(group_name, item_value.c_str());
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�ȡ��ĳgroup�µ�ȫ����Ч�У����С������ո�/tab���еȶ��ų���
  ���������
  �� �� ֵ����̬����һ��string���飬ÿ��Ԫ�ش�һ�У������׵�ַ����
  ˵    �����������룬��Ҫ�˷ѣ����ó��ǵ��ͷ�
 ***************************************************************************/
string* cft_gai::item_get_all(const char* group_name)
{
	string* str=NULL;
	int n=0,m=0;//n��¼��������m��¼������

	fp.clear();
	fp.seekg(0,ios::beg);

	//�ж��Ƿ�Ϊ���������ļ������ļ�
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

	
	return str; //�����޸�
}

#endif
