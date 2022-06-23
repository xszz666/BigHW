/*����˳ 2152611 ��02*/


#include"fk-tools.h"

int main(int argc, char** argv)
{
	int min = 0, max = 0;
	/*��main����*/
	args_analyse_tools aats[] = {
		args_analyse_tools("--cfgfile", ST_EXTARGS_TYPE::str,1,"forbidden_keyword.cfg"),
		args_analyse_tools("--checkgname",ST_EXTARGS_TYPE::str,1,"check-1"),
		args_analyse_tools("--courseid",ST_EXTARGS_TYPE::str,1,""),
		args_analyse_tools("--stufile",ST_EXTARGS_TYPE::str,1,""),
		args_analyse_tools("--maxerror",ST_EXTARGS_TYPE::int_with_default,1,0),
		args_analyse_tools("--minerror",ST_EXTARGS_TYPE::int_with_set_default,1,0)
	};

	if ((args_analyse_process(argc, argv, aats, 0)) < 0)
		return -1;

	min = aats[5].get_int();
	max = aats[4].get_int();

	/*�������ļ�*/
	cft_gai c_f;
	c_f.set_comment_switch(CommentSwitch::on);
	c_f.open(aats[0].get_string().c_str(), OPEN_OPT_RDONLY);
	if (!c_f.is_open())
	{
		cout << "�����ļ���ʧ�ܡ�" << endl;
		return 0;
	}
	//����ֵ
	c_f.item_get_value("ϵͳ����", "����������", max);
	c_f.item_get_value("ϵͳ����", "��С��������", min);
	//�������
	string* check_group = c_f.item_get_all(aats[1].get_string().c_str());
	//����ͨ��
	int size_checkgroup = 0;
	for (; check_group[size_checkgroup] != "\0"; size_checkgroup++)
		;
		//�����ִ����simple_group��
	string** simple_group = new(nothrow) string * [size_checkgroup];
	if (simple_group == NULL)
	{
		cout << "�ڴ�����ʧ�ܡ�" << endl;
		return 0;
	}
	for (int i = 0; check_group[i] != "\0"; i++)
		simple_group[i] = c_f.item_get_all(check_group[i].c_str());
	c_f.close();

	/*��.dat�ļ�*/
	fstream dat_file;
	string datname = "./source/";
	datname += aats[2].get_string();
	datname += ".dat";
	dat_file.open(datname, ios::in);
	if (!dat_file.is_open())
	{
		cout << ".dat�ļ���ʧ�ܡ�" << endl;
		return 0;
	}
	//����ѧ������
	int num_stu = 0;
	while (1)
	{
		char ch=dat_file.get();
		if (ch == '\n' || ch == -1)
			num_stu++;
		if (ch == -1)
			break;
	}
	dat_file.clear();
	dat_file.seekg(0, ios::beg);
		//���.dat�����ѧ����Ϣ
	Stu* stu = new(nothrow)Stu[num_stu];
	if (stu == NULL)
	{
		cout << "�ڴ�����ʧ�ܡ�" << endl;
		return 0;
	}
	int i;
	for ( i = 0; i < num_stu&&!dat_file.eof(); i++)
		dat_file >> stu[i].courseid >> stu[i].no >> stu->name;
	
	dat_file.close();

	/*��ѧ����ҵ*/
	for (int i = 0; stu[i].courseid != -1; i++)
	{
		fstream stu_file;
		string sfn = "./source/";
		sfn += aats[2].get_string();
		sfn += "-";
		sfn += aats[3].get_string();
		sfn += "/";
		sfn += stu[i].no;
		sfn += "-";
		sfn += stu[i].name;
		sfn += "-";
		sfn+= aats[3].get_string();
		stu_file.open(sfn.c_str(), ios::in);
		
		if (!stu_file.is_open())
			stu[i].result = -1;
		else
			stu[i].result = check_fk();

		stu_file.close();		
	}

	/*���*/
	for (int i = 0; stu[i].courseid != -1; i++)
	{
		cout << stu[i].courseid << '-' << stu[i].no << '-' << stu[i].name << " �� ";
		if (stu[i].result == -1)
			cout << "δ�ύ" << endl;
		else if (stu[i].result <= min)
			cout << "OK" << endl;
		else
			cout << stu[i].result-min << "��Υ��" << endl;
	}

	delete []stu;
	delete[]simple_group;
	return 0;
}

