/*����˳ 2152611 ��02*/
#define _CRT_SECURE_NO_WARNINGS
#include"../90-01-b2-gmw-cft/90-01-b2-gmw-cft-tools.h"

void set_by_cft(CONSOLE_GRAPHICS_INFO& Mto10_CGI, cft& file, int& MAX, int* f_n, int* b_n, int& d_f, int& d_b, int& s_f, int& s_b, int& f_f, int& f_b)
{	
	//1�������ֺſ���
	//Mto10_CGI.CFT.font_type;                //[��������] ����
	//Mto10_CGI.CFT.font_size_width;          //[��������] �ֺ�
	char a[25] = "";
	strcpy(Mto10_CGI.CFT.font_type, "��������");
	Mto10_CGI.CFT.font_size_width = 8;
	Mto10_CGI.CFT.font_size_high = Mto10_CGI.CFT.font_size_width * 2;

	if(file.item_get_value("��������", "����", a)>0)
		if(strcmp(a,"��������")==0|| strcmp(a, "������") == 0)
			strcpy(Mto10_CGI.CFT.font_type, a);

	int i = 0;
	if (file.item_get_value("��������", "�ֺ�", i) > 0)
	{
		if (strcmp(Mto10_CGI.CFT.font_type, "��������") == 0)		
			if (i == 6 || i == 8 || i == 10)
				Mto10_CGI.CFT.font_size_width = i;		
		else
		{
			if (i >= 8 && i <= 24)
				Mto10_CGI.CFT.font_size_width = i;
			else
				Mto10_CGI.CFT.font_size_width = 12;
		}
		Mto10_CGI.CFT.font_size_high = Mto10_CGI.CFT.font_size_width * 2;
	}

	//2����ʼ���С��Ҳ��²�������п���
	
	//����������Ҫ�޸�
	//Mto10_CGI.start_x;		*********				//[��������] ��ʼ�к�
	//Mto10_CGI.start_y;		*********				//[��������] ��ʼ�к�
	Mto10_CGI.start_x = 0;
	Mto10_CGI.start_y = 0;
	if (file.item_get_value("��������", "��ʼ�к�", i) > 0)
		if (i >= 0 && i <= 15)
			Mto10_CGI.start_y = i;
	if (file.item_get_value("��������", "��ʼ�к�", i) > 0)
		if (i >= 0 && i <= 15)
			Mto10_CGI.start_x = i;


	//Mto10_CGI.extern_down_lines;						//[��������] �·�����
	//Mto10_CGI.extern_right_cols;						//[��������] �Ҳ����
	Mto10_CGI.extern_down_lines = 0;
	Mto10_CGI.extern_right_cols=0;
	if (file.item_get_value("��������", "�·�����", i) > 0)
		if (i >= 0 && i <= 15)
			Mto10_CGI.extern_down_lines = i;
	if (file.item_get_value("��������", "�Ҳ����", i) > 0)
		if (i >= 0 && i <= 15)
			Mto10_CGI.extern_right_cols = i;

	//3����Ϸ�������� / ��������С����
	//Mto10_CGI.col_num;                    //����
	//Mto10_CGI.row_num;                    //����
	Mto10_CGI.col_num = 5;                   
	Mto10_CGI.row_num = 5;
	if (file.item_get_value("��������", "����", i) > 0)
		if (i >= 5 && i <= 8)
			Mto10_CGI.row_num = i;
	if (file.item_get_value("��������", "����", i) > 0)
		if (i >= 5 && i <= 10)
			Mto10_CGI.col_num = i;

	//4����Ļǰ�� / ����ɫ����
	//Mto10_CGI.CFI.fgcolor;           //ǰ��ɫ
	//Mto10_CGI.CFI.bgcolor;           //����ɫ
	Mto10_CGI.CFI.fgcolor = 7;
	Mto10_CGI.CFI.bgcolor = 0;
	if (file.item_get_value("��������", "ǰ��ɫ", i) > 0)
		if (i >= 0 && i <= 15)
			Mto10_CGI.CFI.fgcolor = i;
	if (file.item_get_value("��������", "����ɫ", i) > 0)
		if (i >= 0 && i <= 15)
			Mto10_CGI.CFI.bgcolor = i;
	
	//5����ʱ�����֣�����
	//Mto10_CGI.delay_of_draw_frame;     //���߿���ʱ
	//Mto10_CGI.delay_of_block_moved;    //ɫ���ƶ���ʱ
	Mto10_CGI.delay_of_draw_frame = 0;
	Mto10_CGI.delay_of_block_moved = 10;
	if (file.item_get_value("��������", "���߿���ʱ", i) > 0)
		if (i >= 0 && i <= 100)
			Mto10_CGI.delay_of_draw_frame = i;
	if (file.item_get_value("��������", "ɫ���ƶ���ʱ", i) > 0)
		if (i >= 3 && i <= 100)
			Mto10_CGI.delay_of_block_moved = i;

	//�ϳ�Ŀ��
	MAX = 5;
	if (file.item_get_value("��������", "�ϳ�Ŀ��", i) > 0)
		if (i >= 5 && i <= 99)
			MAX= i;

	//[�߿�����]
	//6����Ϸ��������������Ϳ��衢ǰ�� / ����ɫ����
	//Mto10_CGI.CFI.lower_left;      //�߿���-���½�
	char b[25];
	if (file.item_get_value("�߿�����", "�߿���-���Ͻ�", b) > 0)
	{
		char c[3];
		c[0] = b[0];
		c[1] = b[1];
		c[2] = '\0';
		strcpy(Mto10_CGI.CFI.top_left, c);
	}
	if (file.item_get_value("�߿�����", "�߿���-���½�", b) > 0)
	{
		char c[3];
		c[0] = b[0];
		c[1] = b[1];
		c[2] = '\0';
		strcpy(Mto10_CGI.CFI.lower_left, c);
	}
	if (file.item_get_value("�߿�����", "�߿���-���Ͻ�", b) > 0)
	{
		char c[3];
		c[0] = b[0];
		c[1] = b[1];
		c[2] = '\0';
		strcpy(Mto10_CGI.CFI.top_right, c);
	}
	if (file.item_get_value("�߿�����", "�߿���-���½�", b) > 0)
	{
		char c[3];
		c[0] = b[0];
		c[1] = b[1];
		c[2] = '\0';
		strcpy(Mto10_CGI.CFI.lower_right, c);
	}
	if (file.item_get_value("�߿�����", "�߿���-����", b) > 0)
	{
		char c[3];
		c[0] = b[0];
		c[1] = b[1];
		c[2] = '\0';
		strcpy(Mto10_CGI.CFI.h_normal, c);
	}
	if (file.item_get_value("�߿�����", "�߿���-����", b) > 0)
	{
		char c[3];
		c[0] = b[0];
		c[1] = b[1];
		c[2] = '\0';
		strcpy(Mto10_CGI.CFI.v_normal, c);
	}
	if (file.item_get_value("�߿�����", "�߿���-�Ϸָ���", b) > 0)
	{
		char c[3];
		c[0] = b[0];
		c[1] = b[1];
		c[2] = '\0';
		strcpy(Mto10_CGI.CFI.h_top_separator, c);
	}
	if (file.item_get_value("�߿�����", "�߿���-�·ָ���", b) > 0)
	{
		char c[3];
		c[0] = b[0];
		c[1] = b[1];
		c[2] = '\0';
		strcpy(Mto10_CGI.CFI.h_lower_separator, c);
	}
	if (file.item_get_value("�߿�����", "�߿���-��ָ���", b) > 0)
	{
		char c[3];
		c[0] = b[0];
		c[1] = b[1];
		c[2] = '\0';
		strcpy(Mto10_CGI.CFI.v_left_separator, c);
	}
	if (file.item_get_value("�߿�����", "�߿���-�ҷָ���", b) > 0)
	{
		char c[3];
		c[0] = b[0];
		c[1] = b[1];
		c[2] = '\0';
		strcpy(Mto10_CGI.CFI.v_right_separator, c);
	}
	if (file.item_get_value("�߿�����", "�߿���-�зָ���", b) > 0)
	{
		char c[3];
		c[0] = b[0];
		c[1] = b[1];
		c[2] = '\0';
		strcpy(Mto10_CGI.CFI.mid_separator, c);
	}

	//Mto10_CGI.area_bgcolor;			//����ɫ
	//Mto10_CGI.area_fgcolor;			//ǰ��ɫ
	Mto10_CGI.area_bgcolor = 15;
	Mto10_CGI.area_fgcolor = 0;
	if (file.item_get_value("�߿�����", "����ɫ", i) > 0)
		if (i >= 0 && i <= 15)
			Mto10_CGI.area_bgcolor = i;
	if (file.item_get_value("�߿�����", "ǰ��ɫ", i) > 0)
		if (i >= 0 && i <= 15)
			Mto10_CGI.area_fgcolor = i;

	//7���Ƿ���Ҫ�ָ��߿��衢�Ƿ���Ҫ��ʾ�к��б����

	//YyNn
	//Mto10_CGI.draw_frame_with_col_no;     //�к��б���ʾ
	//Mto10_CGI.draw_frame_with_row_no;     //�к��б���ʾ
	char m;
	Mto10_CGI.draw_frame_with_col_no = 1;
	Mto10_CGI.draw_frame_with_row_no = 1;
	if (file.item_get_value("�߿�����", "�к��б���ʾ", m) > 0)
		if (m == 'y' || m == 'Y')
			Mto10_CGI.draw_frame_with_col_no = Mto10_CGI.draw_frame_with_row_no = 1;
		else if (m == 'n' || m == 'N')
			Mto10_CGI.draw_frame_with_col_no = Mto10_CGI.draw_frame_with_row_no = 0;

	//Mto10_CGI.CFI.separator;              //��Ҫ�ָ���
	Mto10_CGI.CFI.separator = 1;
	if (file.item_get_value("�߿�����", "��Ҫ�ָ���", m) > 0)
		if (m == 'y' || m == 'Y')
			Mto10_CGI.CFI.separator = 1;
		else if (m == 'n' || m == 'N')
			Mto10_CGI.CFI.separator = 0;


	//[ɫ������]
	//8��ɫ���С���裨ɫ���е����ݣ����з��򶼾�����ʾ)��ɫ��߿����Ϳ���
	//Mto10_CGI.CFI.block_high;              //�߶�
	//Mto10_CGI.CFI.block_width;             //���
	Mto10_CGI.CFI.block_high = 3;
	Mto10_CGI.CFI.block_width = 6;
	if (file.item_get_value("ɫ������", "���", i) > 0)
		if (i>=6||i<=16)
			Mto10_CGI.CFI.block_width = i;
	if (file.item_get_value("ɫ������", "�߶�", i) > 0)
		if (i >= 3 || i <= 6)
			Mto10_CGI.CFI.block_high = i;

	//Mto10_CGI.CBI.lower_left;             //�߿���-���½�
	if (file.item_get_value("ɫ������", "�߿���-���Ͻ�", b) > 0)
		strcpy(Mto10_CGI.CBI.top_left, b);
	if (file.item_get_value("ɫ������", "�߿���-���½�", b) > 0)
		strcpy(Mto10_CGI.CBI.lower_left, b);
	if (file.item_get_value("ɫ������", "�߿���-���Ͻ�", b) > 0)
		strcpy(Mto10_CGI.CBI.top_right, b);
	if (file.item_get_value("ɫ������", "�߿���-���½�", b) > 0)
		strcpy(Mto10_CGI.CBI.lower_right, b);
	if (file.item_get_value("ɫ������", "�߿���-����", b) > 0)
		strcpy(Mto10_CGI.CBI.h_normal, b);
	if (file.item_get_value("ɫ������", "�߿���-����", b) > 0)
		strcpy(Mto10_CGI.CBI.v_normal, b);

	//9��ÿ��ɫ��ǰ�� / ����ɫ���裨��5��)�������� / ���� / ѡ��ɫ���ǰ�� / ����ɫ����
	//******
	if (file.item_get_value("ɫ������", "������ɫ��-����ɫ", i) > 0)
		if (i >= -1 && i <= 15)
			d_b = i;
	if (file.item_get_value("ɫ������", "������ɫ��-ǰ��ɫ", i) > 0)
		if (i >= -1 && i <= 15)
			d_f = i;
	if (file.item_get_value("ɫ������", "ѡ��ɫ�鱳��ɫ", i) > 0)
		if (i >= -1 && i <= 15)
			s_b = i;
	if (file.item_get_value("ɫ������", "ѡ��ɫ��ǰ��ɫ", i) > 0)
		if (i >= -1 && i <= 15)
			s_f = i;
	if (file.item_get_value("ɫ������", "����ɫ�鱳��ɫ", i) > 0)
		if (i >= -1 && i <= 15)
			f_b = i;
	if (file.item_get_value("ɫ������", "����ɫ��ǰ��ɫ", i) > 0)
		if (i >= -1 && i <= 15)
			f_f = i;

	for (int n = 1; n <= 10; n++)
	{
		string str = "ɫ��";
		if (n == 10)
			str += "10";
		else
			str += n+'0';
		str += "-ǰ��ɫ";

		if (file.item_get_value("ɫ������", str.c_str(), i) > 0)
			if (i >0 && i <= 15)
				f_n[n-1] = i;
	}
	for (int n = 1; n<= 10; n++)
	{
		string str = "ɫ��";
		if (n == 10)
			str += "10";
		else
			str += n + '0';
		str += "-����ɫ";

		if (file.item_get_value("ɫ������", str.c_str(), i) > 0)
			if (i > 0 && i <= 15)
				b_n[n - 1] = i;
	}

	//[״̬������]
	//10���Ƿ���Ҫ����״̬����״̬����ǰ�� / ����ɫ����
	//Mto10_CGI.SLI.is_lower_status_line;				//��״̬��
	//Mto10_CGI.SLI.is_top_status_line;				//��״̬��
	Mto10_CGI.SLI.is_lower_status_line = Mto10_CGI.SLI.is_top_status_line = 1;
	if (file.item_get_value("״̬������", "��״̬��", m) > 0)
		if (m == 'y' || m == 'Y')
			Mto10_CGI.SLI.is_top_status_line = 1;
		else if (m == 'n' || m == 'N')
			Mto10_CGI.SLI.is_top_status_line = 0;
	if (file.item_get_value("״̬������", "��״̬��", m) > 0)
		if (m == 'y' || m == 'Y')
			Mto10_CGI.SLI.is_lower_status_line = 1;
		else if (m == 'n' || m == 'N')
			Mto10_CGI.SLI.is_lower_status_line = 0;


	//Mto10_CGI.SLI.lower_normal_bgcolor;				//�������ֱ���ɫ
	//Mto10_CGI.SLI.lower_catchy_bgcolor;				//�������ֱ���ɫ

	//Mto10_CGI.SLI.lower_normal_fgcolor;				//��������ǰ��ɫ
	//Mto10_CGI.SLI.lower_catchy_fgcolor;				//��������ǰ��ɫ
	// 
	//Mto10_CGI.SLI.top_normal_bgcolor;				//�������ֱ���ɫ
	//Mto10_CGI.SLI.top_catchy_bgcolor;				//�������ֱ���ɫ

	//Mto10_CGI.SLI.top_normal_fgcolor;				//��������ǰ��ɫ
	//Mto10_CGI.SLI.top_catchy_fgcolor;				//��������ǰ��ɫ
	Mto10_CGI.SLI.lower_normal_bgcolor = Mto10_CGI.SLI.top_normal_bgcolor = -1;
	Mto10_CGI.SLI.lower_normal_fgcolor = Mto10_CGI.SLI.top_normal_fgcolor = -1;
	Mto10_CGI.SLI.lower_catchy_bgcolor = Mto10_CGI.SLI.top_catchy_bgcolor = -1;
	Mto10_CGI.SLI.top_catchy_fgcolor = Mto10_CGI.SLI.lower_catchy_fgcolor = 14;
	if (file.item_get_value("״̬������", "�������ֱ���ɫ", i) > 0)
		if (i >= -1 && i <= 15)
			Mto10_CGI.SLI.lower_normal_bgcolor = Mto10_CGI.SLI.top_normal_bgcolor = i;
	if (file.item_get_value("״̬������", "��������ǰ��ɫ", i) > 0)
		if (i >= -1 && i <= 15)
			Mto10_CGI.SLI.lower_normal_fgcolor = Mto10_CGI.SLI.top_normal_fgcolor = i;
	if (file.item_get_value("״̬������", "��������ǰ��ɫ", i) > 0)
		if (i >= -1 && i <= 15)
			Mto10_CGI.SLI.lower_catchy_fgcolor = Mto10_CGI.SLI.top_catchy_fgcolor = i;
	if (file.item_get_value("״̬������", "�������ֱ���ɫ", i) > 0)
		if (i >= -1 && i <= 15)
			Mto10_CGI.SLI.lower_catchy_bgcolor = Mto10_CGI.SLI.top_catchy_bgcolor = i;



	//��   ��   �����������
	Mto10_CGI.extern_left_cols = Mto10_CGI.start_x ;
	Mto10_CGI.extern_up_lines = Mto10_CGI.start_y;

	Mto10_CGI.CFI.bhigh = Mto10_CGI.CFI.block_high * Mto10_CGI.row_num + (Mto10_CGI.row_num - 1) * Mto10_CGI.CFI.separator + 2;
	Mto10_CGI.CFI.bwidth = Mto10_CGI.CFI.block_width * Mto10_CGI.col_num + (Mto10_CGI.col_num - 1) * 2 * Mto10_CGI.CFI.separator + 4;

	Mto10_CGI.lines = Mto10_CGI.extern_up_lines + Mto10_CGI.extern_down_lines + Mto10_CGI.CFI.bhigh + Mto10_CGI.SLI.is_top_status_line + Mto10_CGI.SLI.is_lower_status_line + Mto10_CGI.draw_frame_with_col_no + 4;
	Mto10_CGI.cols = Mto10_CGI.extern_left_cols + Mto10_CGI.extern_right_cols + Mto10_CGI.CFI.bwidth + Mto10_CGI.draw_frame_with_row_no * 2 + 5;

	Mto10_CGI.SLI.lower_start_y = Mto10_CGI.extern_up_lines + Mto10_CGI.draw_frame_with_col_no + Mto10_CGI.SLI.is_top_status_line + Mto10_CGI.CFI.bhigh;
}