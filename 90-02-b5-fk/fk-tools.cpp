/*×ÞÁ¼Ë³ 2152611 ÐÅ02*/
#include"fk-tools.h"

bool if_exist(char* file_line, string keyword, string* expect_words)
{

}

void check_simple_word(fstream&file,int &n,int max,string keyword,string *expect_words=NULL)
{
	file.clear();
	file.seekg(0, ios::beg);
	while (1)
	{
		char* file_line;
		file.getline(file_line, 1024, '\n');
		if (file.eof())
			break;
		n += if_exist(file_line, keyword, expect_words);
	}
}


int check_fk(const int max,fstream&file,string**keywords,int size_checkgroup)
{
	int n = 0;
	for(int i=0;i<size_checkgroup;i++)
		for (int j = 0; keywords[i][j] != "\0"; j++)
		{

		}
	return n;
}