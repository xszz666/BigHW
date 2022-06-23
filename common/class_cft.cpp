/* ����˳ 2152611 ��02 */

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <io.h>
#include "../include/class_cft.h"
//�������������Ҫ��ͷ�ļ�
#include<sstream>
using namespace std;

#if ! ENABLE_LIB_TCFG_TOOLS	//����lib����ܱ���

/* ---------------------------------------------------------------
	 �������������Ҫ��struct/class/union/�����ȣ��ڲ������ã�
	 1����������Ϊ��̬��������
	 2����������ų���/������
	 3��������Ҫ��ȫ�ֱ��������һ��Ҫ�ã���static
   ---------------------------------------------------------------- */
#define size_of_n 2 //����

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
static void insert_to_file(fstream& fp, int insert_pos, int insert_size,const char*insert_s)
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
	fp << insert_s <<"\r\n";
}

bool cft::file_read(bool gai)
{
	infor.group_name = "";
	infor.item_name = "";
	infor.item_vaule = "";

	infor.if_null = 0;//�Ƿ�Ϊ����

	infor.if_true = 0;

	//�����������
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

	//�Զ������ݽ��д���
		//ע��
	//if (is_ignore_comment == CommentSwitch::on)
	//{
	//	for (int i = 0; i < n; i++)
	//		if (in_str[i] == '#' || in_str[i] == ';')
	//		{
	//			in_str[i] = '\0';
	//		}			
	//}
	//cout << in_str << "*" << endl;

	//�Ƿ�Ϊ��Ч��
	for (int i = 0; in_str[i]!='\0'&&in_str[i]!='#'&&in_str[i]!=';'; i++)
		if (in_str[i] == '=')
		{
			infor.if_true = 1;
			break;
		}

	//ȥ��ǰ�ո�
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

	//ȥ����ո�
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

	
	//�����������  ��ʱ�����СΪsize+1
	if (in_str[0] == '[' && in_str[size - 1] == ']')
	{		
		infor.include_group_name = 1;
		in_str[size - 1] = '\0';//�������infor��
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
			//����=֮��Ŀո�
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
	//������һ���س�
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
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����C++17����filesystem::resize_fileֱ�ӿ����޸��ļ���С��
            ֮ǰ�İ汾�ޣ���˱���������C��ʽ��_chsize����
		��ʵ�֣���Ҫ��
 ***************************************************************************/
int cft::file_resize(int newsize)
{
	msg.str("");
	/* �����С�Ǹ�����ֱ�ӷ���-1 */
	if (newsize < 0) {
		msg << "file_resize - invalid size(" << newsize << ")." << endl;
		return -1;
	}

	if (!fp.good())
		fp.clear();

	/* ȡfp��ǰָ��λ�� */
	int now_pos = int(fp.tellg());

	/* ���ȣ�C++��ʽ�ر� */
	fp.close();

	/* ��Σ�C��ʽ�򿪲��ı��ļ���С */
	FILE* fp_cstyle;
	fp_cstyle = fopen(filename.c_str(), "rb+"); //rw��ʽ��
	if (fp_cstyle) {
		if (_chsize(_fileno(fp_cstyle), newsize) < 0)
			msg << "file_resize - chsize failed" << endl; //����������Ϣ������ִ��(�ָ�C++��ʽ��)

		fclose(fp_cstyle); //�����Ƿ���ȷ��flcose
	}
	else
		msg << "file_resize - fopen (" << filename << ") failed" << endl;//����������Ϣ������ִ��(�ָ�C++��ʽ��)

	/* �ٴΣ�C++��ʽ���´򿪣��ܵ���resize��һ����rw�� */
	fp.open(filename, ios::in | ios::out|ios::binary);
	if (fp.is_open() == 0) {
		msg << "file_resize - reopen (" << filename << ") failed" << endl;//C++��ʽ�����򷵻�-1
		return -1;
	}
	
	/* �ļ�ָ���ƶ���ԭλ�� */
	fp.seekg(ios::beg,now_pos < newsize ? now_pos : newsize);
	
	return 0;
}

/* ---------------------------------------------------------------
	 �������class cft�г�Ա������ʵ��
	 ����ʵ�ֹ����в�Ҫ����cout�����Խ���Ϣ����msg�У���test�е���
---------------------------------------------------------------- */

/*���ļ�ʱ��Ϊ�˶�ȡ���㣬�����ļ�ĩβ����'\n'���������һ���޻س����µĴ���*/

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
cft::cft()
{
	filename = "";
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
cft::~cft()
{
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
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
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
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
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
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
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
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
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
bool cft::is_open(void)
{
	return fp.is_open(); //�����޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
void cft::close()
{
	fp.close();
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
void cft::print() const
{
	cout << msg.str() << endl;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����Ĭ��Ϊon
 ***************************************************************************/
void cft::set_comment_switch(CommentSwitch flag)
{
	is_ignore_comment = flag;	
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ������ʵ�֣���Ҫ��
 ***************************************************************************/
CommentSwitch cft::get_comment_switch() const
{
	return this->is_ignore_comment;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����Ĭ��ΪFirst_line_after_group
 ***************************************************************************/
void cft::set_insert_position(InsertPosition pos)
{
	inspos = pos;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ������ʵ�֣���Ҫ��
 ***************************************************************************/
InsertPosition cft::get_insert_position() const
{
	return this->inspos;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
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

	return 1; //�����޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
int cft::group_add(const string& group_name)
{
	return group_add(group_name.c_str());
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
  �� ɾ���ɹ�����n(ɾ���������)�����򷵻�0
  �� ���[test]�鲻���ڣ�ֱ�ӷ���0����
  �� ���[test]���ظ����ڣ����磺�ֹ��޸�ʹ����ͬ��������Ҫɾ������ͬ���鲢����2
 ***************************************************************************/
int cft::group_del(const char* group_name)
{
	fp.clear();
	fp.seekg(0,ios::beg);
	int n = 0;//ɾ����ĸ���
	while (file_read())
	{		
		int num = 0;
		if (infor.group_name == group_name)
		{			
			//��¼Ŀ������ַ���
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
			//�����ַ��� ����Ŀ��������			
			delete_in_file(fp, num);

			int size = size_of_file(fp);
			fp.seekg(ios::beg, 0);
			file_resize(size - num);

			n++;			
		}
	}

	fp.clear();
	return n; //�����޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
  �� ɾ���ɹ�����n(ɾ���������)�����򷵻�0
  �� ���[test]�鲻���ڣ�ֱ�ӷ���0����
  �� ���[test]���ظ����ڣ����磺�ֹ��޸�ʹ����ͬ��������Ҫɾ������ͬ���鲢����2
 ***************************************************************************/
int cft::group_del(const string& group_name)
{
	return group_del(group_name.c_str());
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
int cft::item_add(const char* group_name, const char* item_name, const int item_value)
{
	stringstream a;
	a << item_value;

	return item_add(group_name, item_name, a.str());
	
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
int cft::item_add(const char* group_name, const char* item_name, const double item_value)
{
	stringstream a;
	a << item_value;

	return item_add(group_name, item_name, a.str());
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
int cft::item_add(const char* group_name, const char* item_name, const char* item_value)
{
	                          //=                         \n
	int len = strlen(item_name) + 1 + strlen(item_value) + 2;
	fp.seekg(0,ios::beg);
	int num = 0,num1=0;  //��Ŀ�����������У��������ֽ�

	if (group_name == NULL)
	{
		//�ж��Ƿ�Ϊ���������ļ������ļ�
		bool is_simple = 1;
		while (file_read())		
			if (infor.include_group_name == 1)			
				return 0;
				
		fp.clear();
		fp.seekg(0, ios::beg);

		//�ж�Ŀ�����Ƿ����
		while (file_read())
			if (infor.item_name == item_name)
				return 0;

		//Ŀ�������
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
				//��Ϊ���һ���飬����޿��У�ֱ�ӵ��ļ�β���򷵻�0
				while (file_read())
				{
					//�޿���
					if (infor.name_of_group == 1)
						return 0;

					//�п���
					num +=infor.num;
					if (infor.if_null == 1)
					{
						num -=infor.num;
						move_to_last_line();
						//����������
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
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
int cft::item_add(const char* group_name, const char* item_name, const string& item_value)
{
	return item_add(group_name, item_name, item_value.c_str());
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
int cft::item_add(const char* group_name, const char* item_name, const char item_value)
{
	char a[2];
	sprintf(a, "%c", item_value);
	return item_add(group_name, item_name,a);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
int cft::item_add(const char* group_name, const char* item_name)
{
	const char *a="\0";
	return item_add(group_name, item_name, a);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int cft::item_del(const char* group_name, const char* item_name)
{
	fp.seekg(0, ios::beg);
	int n = 0;

	if (group_name == NULL)
	{
		//�ж��Ƿ�Ϊ���������ļ������ļ�
		bool is_simple = 1;

		//���������ļ�
		while (file_read())
			if (infor.include_group_name == 1)
			{
				//������
				fp.clear();
				fp.seekg(0, ios::beg);

				while (file_read())
				{
					if (infor.item_name == item_name)
					{
						//�����ַ��� ����Ŀ��������
						delete_in_file(fp,infor.num);

						int size = size_of_file(fp);
						fp.seekg(0,ios::beg);
						file_resize(size - infor.num);

						n++;
					}
				}

				return n;
			}


		//��������
		fp.clear();
		fp.seekg(0, ios::beg);

		while (file_read())
		{
			if (infor.item_name == item_name)
			{
				//�����ַ��� ����Ŀ��������
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
					
					//�����ַ��� ����Ŀ��������
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
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
int cft::item_update(const char* group_name, const char* item_name, const int item_value)
{
	stringstream a;
	a << item_value;

	return item_update(group_name, item_name, a.str());

}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
int cft::item_update(const char* group_name, const char* item_name, const double item_value)
{
	stringstream a;
	a << item_value;

	return item_update(group_name, item_name, a.str());
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
int cft::item_update(const char* group_name, const char* item_name, const char* item_value)
{
	
	int num = 0;
	fp.seekg(0,ios::beg);

	if (group_name == NULL)
	{
		//�ж��Ƿ�Ϊ���������ļ������ļ�
		bool is_simple = 1;
		while (file_read())
			if (infor.include_group_name == 1)
				return 0;

		fp.clear();
		fp.seekg(0, ios::beg);

		//�ж�Ŀ�����Ƿ����
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
		//Ŀ���鲻����
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
					//�Ȳ�����ԭλ��֮ǰ
					num -=infor.num;

					string str=item_name;
					str += '=';
					str += item_value;

					insert_to_file(fp, num, str.length()+2, str.c_str());
				
					
					//��ɾ��ԭitem
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
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
int cft::item_update(const char* group_name, const char* item_name, const string& item_value)
{
	stringstream a;
	a << item_value;

	return item_update(group_name, item_name, a.str().c_str());
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
int cft::item_update(const char* group_name, const char* item_name, const char item_value)
{
	stringstream a;
	a << item_value;

	return item_update(group_name, item_name, a.str());
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
int cft::item_update(const char* group_name, const char* item_name)
{
	char a[1];
	a[0] = '\0';
	return item_update(group_name, item_name, a);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
int cft::item_get_value(const char* group_name, const char* item_name, int& item_value)
{
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
	return 0; //�����޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
int cft::item_get_value(const char* group_name, const char* item_name, double& item_value)
{
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

	return 0; //�����޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
int cft::item_get_value(const char* group_name, const char* item_name, char* item_value, bool enable_space)
{

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

	return 0; //�����޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
int cft::item_get_value(const char* group_name, const char* item_name, string& item_value, bool enable_space)
{
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

	return 0; //�����޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
int cft::item_get_value(const char* group_name, const char* item_name, char& item_value)
{
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

	return 0; //�����޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
int cft::item_get_value(const char* group_name, const char* item_name)
{
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

	return 0; //�����޸�
}

#endif  //end of ! ENABLE_LIB_TCFG_TOOLS

