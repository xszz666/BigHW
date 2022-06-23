/*邹良顺 2152611 信02*/
#define _CRT_SECURE_NO_WARNINGS
#include"../90-01-b2-gmw-cft/90-01-b2-gmw-cft-tools.h"

void set_by_cft(CONSOLE_GRAPHICS_INFO& Mto10_CGI, cft& file, int& MAX, int* f_n, int* b_n, int& d_f, int& d_b, int& s_f, int& s_b, int& f_f, int& f_b)
{	
	//1、字体字号可设
	//Mto10_CGI.CFT.font_type;                //[区域设置] 字体
	//Mto10_CGI.CFT.font_size_width;          //[区域设置] 字号
	char a[25] = "";
	strcpy(Mto10_CGI.CFT.font_type, "点阵字体");
	Mto10_CGI.CFT.font_size_width = 8;
	Mto10_CGI.CFT.font_size_high = Mto10_CGI.CFT.font_size_width * 2;

	if(file.item_get_value("区域设置", "字体", a)>0)
		if(strcmp(a,"点阵字体")==0|| strcmp(a, "新宋体") == 0)
			strcpy(Mto10_CGI.CFT.font_type, a);

	int i = 0;
	if (file.item_get_value("区域设置", "字号", i) > 0)
	{
		if (strcmp(Mto10_CGI.CFT.font_type, "点阵字体") == 0)		
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

	//2、起始行列、右侧下侧空余行列可设
	
	//以下两项需要修改
	//Mto10_CGI.start_x;		*********				//[区域设置] 起始列号
	//Mto10_CGI.start_y;		*********				//[区域设置] 起始行号
	Mto10_CGI.start_x = 0;
	Mto10_CGI.start_y = 0;
	if (file.item_get_value("区域设置", "起始行号", i) > 0)
		if (i >= 0 && i <= 15)
			Mto10_CGI.start_y = i;
	if (file.item_get_value("区域设置", "起始列号", i) > 0)
		if (i >= 0 && i <= 15)
			Mto10_CGI.start_x = i;


	//Mto10_CGI.extern_down_lines;						//[区域设置] 下方空行
	//Mto10_CGI.extern_right_cols;						//[区域设置] 右侧空行
	Mto10_CGI.extern_down_lines = 0;
	Mto10_CGI.extern_right_cols=0;
	if (file.item_get_value("区域设置", "下方空行", i) > 0)
		if (i >= 0 && i <= 15)
			Mto10_CGI.extern_down_lines = i;
	if (file.item_get_value("区域设置", "右侧空行", i) > 0)
		if (i >= 0 && i <= 15)
			Mto10_CGI.extern_right_cols = i;

	//3、游戏区域（行数 / 列数）大小可设
	//Mto10_CGI.col_num;                    //列数
	//Mto10_CGI.row_num;                    //行数
	Mto10_CGI.col_num = 5;                   
	Mto10_CGI.row_num = 5;
	if (file.item_get_value("区域设置", "行数", i) > 0)
		if (i >= 5 && i <= 8)
			Mto10_CGI.row_num = i;
	if (file.item_get_value("区域设置", "列数", i) > 0)
		if (i >= 5 && i <= 10)
			Mto10_CGI.col_num = i;

	//4、屏幕前景 / 背景色可设
	//Mto10_CGI.CFI.fgcolor;           //前景色
	//Mto10_CGI.CFI.bgcolor;           //背景色
	Mto10_CGI.CFI.fgcolor = 7;
	Mto10_CGI.CFI.bgcolor = 0;
	if (file.item_get_value("区域设置", "前景色", i) > 0)
		if (i >= 0 && i <= 15)
			Mto10_CGI.CFI.fgcolor = i;
	if (file.item_get_value("区域设置", "背景色", i) > 0)
		if (i >= 0 && i <= 15)
			Mto10_CGI.CFI.bgcolor = i;
	
	//5、延时（两种）可设
	//Mto10_CGI.delay_of_draw_frame;     //画边框延时
	//Mto10_CGI.delay_of_block_moved;    //色块移动延时
	Mto10_CGI.delay_of_draw_frame = 0;
	Mto10_CGI.delay_of_block_moved = 10;
	if (file.item_get_value("区域设置", "画边框延时", i) > 0)
		if (i >= 0 && i <= 100)
			Mto10_CGI.delay_of_draw_frame = i;
	if (file.item_get_value("区域设置", "色块移动延时", i) > 0)
		if (i >= 3 && i <= 100)
			Mto10_CGI.delay_of_block_moved = i;

	//合成目标
	MAX = 5;
	if (file.item_get_value("区域设置", "合成目标", i) > 0)
		if (i >= 5 && i <= 99)
			MAX= i;

	//[边框设置]
	//6、游戏区域外框线条类型可设、前景 / 背景色可设
	//Mto10_CGI.CFI.lower_left;      //边框线-左下角
	char b[25];
	if (file.item_get_value("边框设置", "边框线-左上角", b) > 0)
	{
		char c[3];
		c[0] = b[0];
		c[1] = b[1];
		c[2] = '\0';
		strcpy(Mto10_CGI.CFI.top_left, c);
	}
	if (file.item_get_value("边框设置", "边框线-左下角", b) > 0)
	{
		char c[3];
		c[0] = b[0];
		c[1] = b[1];
		c[2] = '\0';
		strcpy(Mto10_CGI.CFI.lower_left, c);
	}
	if (file.item_get_value("边框设置", "边框线-右上角", b) > 0)
	{
		char c[3];
		c[0] = b[0];
		c[1] = b[1];
		c[2] = '\0';
		strcpy(Mto10_CGI.CFI.top_right, c);
	}
	if (file.item_get_value("边框设置", "边框线-右下角", b) > 0)
	{
		char c[3];
		c[0] = b[0];
		c[1] = b[1];
		c[2] = '\0';
		strcpy(Mto10_CGI.CFI.lower_right, c);
	}
	if (file.item_get_value("边框设置", "边框线-横线", b) > 0)
	{
		char c[3];
		c[0] = b[0];
		c[1] = b[1];
		c[2] = '\0';
		strcpy(Mto10_CGI.CFI.h_normal, c);
	}
	if (file.item_get_value("边框设置", "边框线-竖线", b) > 0)
	{
		char c[3];
		c[0] = b[0];
		c[1] = b[1];
		c[2] = '\0';
		strcpy(Mto10_CGI.CFI.v_normal, c);
	}
	if (file.item_get_value("边框设置", "边框线-上分隔线", b) > 0)
	{
		char c[3];
		c[0] = b[0];
		c[1] = b[1];
		c[2] = '\0';
		strcpy(Mto10_CGI.CFI.h_top_separator, c);
	}
	if (file.item_get_value("边框设置", "边框线-下分隔线", b) > 0)
	{
		char c[3];
		c[0] = b[0];
		c[1] = b[1];
		c[2] = '\0';
		strcpy(Mto10_CGI.CFI.h_lower_separator, c);
	}
	if (file.item_get_value("边框设置", "边框线-左分隔线", b) > 0)
	{
		char c[3];
		c[0] = b[0];
		c[1] = b[1];
		c[2] = '\0';
		strcpy(Mto10_CGI.CFI.v_left_separator, c);
	}
	if (file.item_get_value("边框设置", "边框线-右分隔线", b) > 0)
	{
		char c[3];
		c[0] = b[0];
		c[1] = b[1];
		c[2] = '\0';
		strcpy(Mto10_CGI.CFI.v_right_separator, c);
	}
	if (file.item_get_value("边框设置", "边框线-中分隔线", b) > 0)
	{
		char c[3];
		c[0] = b[0];
		c[1] = b[1];
		c[2] = '\0';
		strcpy(Mto10_CGI.CFI.mid_separator, c);
	}

	//Mto10_CGI.area_bgcolor;			//背景色
	//Mto10_CGI.area_fgcolor;			//前景色
	Mto10_CGI.area_bgcolor = 15;
	Mto10_CGI.area_fgcolor = 0;
	if (file.item_get_value("边框设置", "背景色", i) > 0)
		if (i >= 0 && i <= 15)
			Mto10_CGI.area_bgcolor = i;
	if (file.item_get_value("边框设置", "前景色", i) > 0)
		if (i >= 0 && i <= 15)
			Mto10_CGI.area_fgcolor = i;

	//7、是否需要分隔线可设、是否需要显示行号列表可设

	//YyNn
	//Mto10_CGI.draw_frame_with_col_no;     //行号列标显示
	//Mto10_CGI.draw_frame_with_row_no;     //行号列标显示
	char m;
	Mto10_CGI.draw_frame_with_col_no = 1;
	Mto10_CGI.draw_frame_with_row_no = 1;
	if (file.item_get_value("边框设置", "行号列标显示", m) > 0)
		if (m == 'y' || m == 'Y')
			Mto10_CGI.draw_frame_with_col_no = Mto10_CGI.draw_frame_with_row_no = 1;
		else if (m == 'n' || m == 'N')
			Mto10_CGI.draw_frame_with_col_no = Mto10_CGI.draw_frame_with_row_no = 0;

	//Mto10_CGI.CFI.separator;              //需要分隔线
	Mto10_CGI.CFI.separator = 1;
	if (file.item_get_value("边框设置", "需要分隔线", m) > 0)
		if (m == 'y' || m == 'Y')
			Mto10_CGI.CFI.separator = 1;
		else if (m == 'n' || m == 'N')
			Mto10_CGI.CFI.separator = 0;


	//[色块设置]
	//8、色块大小可设（色块中的内容，行列方向都居中显示)、色块边框类型可设
	//Mto10_CGI.CFI.block_high;              //高度
	//Mto10_CGI.CFI.block_width;             //宽度
	Mto10_CGI.CFI.block_high = 3;
	Mto10_CGI.CFI.block_width = 6;
	if (file.item_get_value("色块设置", "宽度", i) > 0)
		if (i>=6||i<=16)
			Mto10_CGI.CFI.block_width = i;
	if (file.item_get_value("色块设置", "高度", i) > 0)
		if (i >= 3 || i <= 6)
			Mto10_CGI.CFI.block_high = i;

	//Mto10_CGI.CBI.lower_left;             //边框线-左下角
	if (file.item_get_value("色块设置", "边框线-左上角", b) > 0)
		strcpy(Mto10_CGI.CBI.top_left, b);
	if (file.item_get_value("色块设置", "边框线-左下角", b) > 0)
		strcpy(Mto10_CGI.CBI.lower_left, b);
	if (file.item_get_value("色块设置", "边框线-右上角", b) > 0)
		strcpy(Mto10_CGI.CBI.top_right, b);
	if (file.item_get_value("色块设置", "边框线-右下角", b) > 0)
		strcpy(Mto10_CGI.CBI.lower_right, b);
	if (file.item_get_value("色块设置", "边框线-横线", b) > 0)
		strcpy(Mto10_CGI.CBI.h_normal, b);
	if (file.item_get_value("色块设置", "边框线-竖线", b) > 0)
		strcpy(Mto10_CGI.CBI.v_normal, b);

	//9、每种色块前景 / 背景色可设（共5种)、已消除 / 反显 / 选中色块的前景 / 背景色可设
	//******
	if (file.item_get_value("色块设置", "被消除色块-背景色", i) > 0)
		if (i >= -1 && i <= 15)
			d_b = i;
	if (file.item_get_value("色块设置", "被消除色块-前景色", i) > 0)
		if (i >= -1 && i <= 15)
			d_f = i;
	if (file.item_get_value("色块设置", "选中色块背景色", i) > 0)
		if (i >= -1 && i <= 15)
			s_b = i;
	if (file.item_get_value("色块设置", "选中色块前景色", i) > 0)
		if (i >= -1 && i <= 15)
			s_f = i;
	if (file.item_get_value("色块设置", "反显色块背景色", i) > 0)
		if (i >= -1 && i <= 15)
			f_b = i;
	if (file.item_get_value("色块设置", "反显色块前景色", i) > 0)
		if (i >= -1 && i <= 15)
			f_f = i;

	for (int n = 1; n <= 10; n++)
	{
		string str = "色块";
		if (n == 10)
			str += "10";
		else
			str += n+'0';
		str += "-前景色";

		if (file.item_get_value("色块设置", str.c_str(), i) > 0)
			if (i >0 && i <= 15)
				f_n[n-1] = i;
	}
	for (int n = 1; n<= 10; n++)
	{
		string str = "色块";
		if (n == 10)
			str += "10";
		else
			str += n + '0';
		str += "-背景色";

		if (file.item_get_value("色块设置", str.c_str(), i) > 0)
			if (i > 0 && i <= 15)
				b_n[n - 1] = i;
	}

	//[状态栏设置]
	//10、是否需要上下状态栏、状态栏的前景 / 背景色可设
	//Mto10_CGI.SLI.is_lower_status_line;				//下状态栏
	//Mto10_CGI.SLI.is_top_status_line;				//上状态栏
	Mto10_CGI.SLI.is_lower_status_line = Mto10_CGI.SLI.is_top_status_line = 1;
	if (file.item_get_value("状态栏设置", "上状态栏", m) > 0)
		if (m == 'y' || m == 'Y')
			Mto10_CGI.SLI.is_top_status_line = 1;
		else if (m == 'n' || m == 'N')
			Mto10_CGI.SLI.is_top_status_line = 0;
	if (file.item_get_value("状态栏设置", "下状态栏", m) > 0)
		if (m == 'y' || m == 'Y')
			Mto10_CGI.SLI.is_lower_status_line = 1;
		else if (m == 'n' || m == 'N')
			Mto10_CGI.SLI.is_lower_status_line = 0;


	//Mto10_CGI.SLI.lower_normal_bgcolor;				//正常文字背景色
	//Mto10_CGI.SLI.lower_catchy_bgcolor;				//错误文字背景色

	//Mto10_CGI.SLI.lower_normal_fgcolor;				//正常文字前景色
	//Mto10_CGI.SLI.lower_catchy_fgcolor;				//错误文字前景色
	// 
	//Mto10_CGI.SLI.top_normal_bgcolor;				//正常文字背景色
	//Mto10_CGI.SLI.top_catchy_bgcolor;				//错误文字背景色

	//Mto10_CGI.SLI.top_normal_fgcolor;				//正常文字前景色
	//Mto10_CGI.SLI.top_catchy_fgcolor;				//错误文字前景色
	Mto10_CGI.SLI.lower_normal_bgcolor = Mto10_CGI.SLI.top_normal_bgcolor = -1;
	Mto10_CGI.SLI.lower_normal_fgcolor = Mto10_CGI.SLI.top_normal_fgcolor = -1;
	Mto10_CGI.SLI.lower_catchy_bgcolor = Mto10_CGI.SLI.top_catchy_bgcolor = -1;
	Mto10_CGI.SLI.top_catchy_fgcolor = Mto10_CGI.SLI.lower_catchy_fgcolor = 14;
	if (file.item_get_value("状态栏设置", "正常文字背景色", i) > 0)
		if (i >= -1 && i <= 15)
			Mto10_CGI.SLI.lower_normal_bgcolor = Mto10_CGI.SLI.top_normal_bgcolor = i;
	if (file.item_get_value("状态栏设置", "正常文字前景色", i) > 0)
		if (i >= -1 && i <= 15)
			Mto10_CGI.SLI.lower_normal_fgcolor = Mto10_CGI.SLI.top_normal_fgcolor = i;
	if (file.item_get_value("状态栏设置", "错误文字前景色", i) > 0)
		if (i >= -1 && i <= 15)
			Mto10_CGI.SLI.lower_catchy_fgcolor = Mto10_CGI.SLI.top_catchy_fgcolor = i;
	if (file.item_get_value("状态栏设置", "错误文字背景色", i) > 0)
		if (i >= -1 && i <= 15)
			Mto10_CGI.SLI.lower_catchy_bgcolor = Mto10_CGI.SLI.top_catchy_bgcolor = i;



	//左   上   多余的行列数
	Mto10_CGI.extern_left_cols = Mto10_CGI.start_x ;
	Mto10_CGI.extern_up_lines = Mto10_CGI.start_y;

	Mto10_CGI.CFI.bhigh = Mto10_CGI.CFI.block_high * Mto10_CGI.row_num + (Mto10_CGI.row_num - 1) * Mto10_CGI.CFI.separator + 2;
	Mto10_CGI.CFI.bwidth = Mto10_CGI.CFI.block_width * Mto10_CGI.col_num + (Mto10_CGI.col_num - 1) * 2 * Mto10_CGI.CFI.separator + 4;

	Mto10_CGI.lines = Mto10_CGI.extern_up_lines + Mto10_CGI.extern_down_lines + Mto10_CGI.CFI.bhigh + Mto10_CGI.SLI.is_top_status_line + Mto10_CGI.SLI.is_lower_status_line + Mto10_CGI.draw_frame_with_col_no + 4;
	Mto10_CGI.cols = Mto10_CGI.extern_left_cols + Mto10_CGI.extern_right_cols + Mto10_CGI.CFI.bwidth + Mto10_CGI.draw_frame_with_row_no * 2 + 5;

	Mto10_CGI.SLI.lower_start_y = Mto10_CGI.extern_up_lines + Mto10_CGI.draw_frame_with_col_no + Mto10_CGI.SLI.is_top_status_line + Mto10_CGI.CFI.bhigh;
}