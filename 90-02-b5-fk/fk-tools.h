/*邹良顺 2152611 信02*/
#pragma once
#include"../include/class_aat.h"
#include"../include/class_cft.h"
#include"../include/class_cft_gai.h"

//存放.dat文件中学生信息的结构体
struct Stu
{
	int courseid=-1;
	int no;
	string name;
	int result;
};

int check_fk();