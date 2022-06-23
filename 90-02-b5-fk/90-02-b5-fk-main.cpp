/*邹良顺 2152611 信02*/


#include"fk-tools.h"

int main(int argc, char** argv)
{
	int min = 0, max = 0;
	/*读main参数*/
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

	/*读配置文件*/
	cft_gai c_f;
	c_f.set_comment_switch(CommentSwitch::on);
	c_f.open(aats[0].get_string().c_str(), OPEN_OPT_RDONLY);
	if (!c_f.is_open())
	{
		cout << "配置文件打开失败。" << endl;
		return 0;
	}
	//读最值
	c_f.item_get_value("系统设置", "最大错误数量", max);
	c_f.item_get_value("系统设置", "最小错误数量", min);
	//读检查组
	string* check_group = c_f.item_get_all(aats[1].get_string().c_str());
	//读普通组
	int size_checkgroup = 0;
	for (; check_group[size_checkgroup] != "\0"; size_checkgroup++)
		;
		//禁用字存放在simple_group里
	string** simple_group = new(nothrow) string * [size_checkgroup];
	if (simple_group == NULL)
	{
		cout << "内存申请失败。" << endl;
		return 0;
	}
	for (int i = 0; check_group[i] != "\0"; i++)
		simple_group[i] = c_f.item_get_all(check_group[i].c_str());
	c_f.close();

	/*读.dat文件*/
	fstream dat_file;
	string datname = "./source/";
	datname += aats[2].get_string();
	datname += ".dat";
	dat_file.open(datname, ios::in);
	if (!dat_file.is_open())
	{
		cout << ".dat文件打开失败。" << endl;
		return 0;
	}
	//计算学生人数
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
		//存放.dat读入的学生信息
	Stu* stu = new(nothrow)Stu[num_stu];
	if (stu == NULL)
	{
		cout << "内存申请失败。" << endl;
		return 0;
	}
	int i;
	for ( i = 0; i < num_stu&&!dat_file.eof(); i++)
		dat_file >> stu[i].courseid >> stu[i].no >> stu->name;
	
	dat_file.close();

	/*读学生作业*/
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

	/*输出*/
	for (int i = 0; stu[i].courseid != -1; i++)
	{
		cout << stu[i].courseid << '-' << stu[i].no << '-' << stu[i].name << " ： ";
		if (stu[i].result == -1)
			cout << "未提交" << endl;
		else if (stu[i].result <= min)
			cout << "OK" << endl;
		else
			cout << stu[i].result-min << "项违规" << endl;
	}

	delete []stu;
	delete[]simple_group;
	return 0;
}

