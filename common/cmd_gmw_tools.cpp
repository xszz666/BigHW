/*2152611 ����˳ ��02 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <climits>
#include <conio.h>
#include<iomanip>
#include<Windows.h>
#include "../include/cmd_console_tools.h"
#include "../include/cmd_gmw_tools.h"
using namespace std;

/* --------------------------------------------------
		�˴����Ը�����Ҫ�ľ�̬ȫ�ֱ������������٣����û�У�����̬ȫ��ֻ������/�궨�壨�������ޣ���
   -------------------------------------------------- */
   /* --------------------------------------------------
		   �˴����Ը�����Ҫ���ڲ��������ߺ���
		   1�����������ޣ�����Ϊ gmw_inner_*
		   2����������
		   3��������static������ȷ��ֻ�ڱ�Դ�ļ���ʹ��
	  -------------------------------------------------- */
int gmw_draw_block_diy(const CONSOLE_GRAPHICS_INFO* const pCGI, const int x, const int y, const int bdi_value, const BLOCK_DISPLAY_INFO* const bdi)
{
	if (bdi_value == 0)
	{
		cct_setcolor(pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
		for (int j = 0; j < pCGI->CFI.block_high; j++)
		{
			cct_gotoxy(x, j + y);
			for (int i = 0; i < pCGI->CFI.block_width; i++)
				cout << " ";
		}
		cct_setcolor();
	}
	else
	{
		int bdi_no = -1;
		for (bdi_no = 0;; bdi_no++)
			if (bdi[bdi_no].value == bdi_value)
				break;

		cct_setcolor(bdi[bdi_no].bgcolor, bdi[bdi_no].fgcolor == -1 ? 0 : bdi[bdi_no].fgcolor);
		if (pCGI->CFI.block_high <= 2 && pCGI->CFI.block_width <= 4)
		{
			cct_gotoxy(x, y);
			if (bdi[bdi_no].content == NULL)
				cout << setw(pCGI->CFI.block_width) << setiosflags(ios::left) << bdi[bdi_no].value;
			else
				cout << setw(pCGI->CFI.block_width) << setiosflags(ios::left) << bdi[bdi_no].content;
			if (pCGI->CFI.block_high == 2)
			{
				cct_gotoxy(x, 1 + y);
				cout << setw(pCGI->CFI.block_width) << setiosflags(ios::left) << " ";
			}
		}
		else
		{
			cct_gotoxy(x, y);
			cout << (pCGI->CBI.block_border ? pCGI->CBI.top_left : "  ");
			for (int i = 0; i < pCGI->CFI.block_width - 4; i += 2)
				cout << (pCGI->CBI.block_border ? pCGI->CBI.h_normal : "  ");
			cout << (pCGI->CBI.block_border ? pCGI->CBI.top_right : "  ");
			Sleep(pCGI->delay_of_draw_block);

			for (int j = 1; j < pCGI->CFI.block_high - 1; j++)
			{
				cct_gotoxy(x, y + j);
				cout << (pCGI->CBI.block_border ? pCGI->CBI.v_normal : "  ");
				for (int i = 0; i < pCGI->CFI.block_width - 4; i += 2)
					if (j == pCGI->CFI.block_high / 2)
					{
						if (bdi[bdi_no].content == NULL)
							cout << setw(pCGI->CFI.block_width - 4) << setiosflags(ios::left) << bdi[bdi_no].value;
						else
							cout << setw(pCGI->CFI.block_width - 4) << setiosflags(ios::left) << bdi[bdi_no].content;
						break;
					}
					else
						cout << "  ";
				cout << (pCGI->CBI.block_border ? pCGI->CBI.v_normal : "  ");
				Sleep(pCGI->delay_of_draw_block);
			}

			cct_gotoxy(x, y + pCGI->CFI.block_high - 1);
			cout << (pCGI->CBI.block_border ? pCGI->CBI.lower_left : "  ");
			for (int i = 0; i < pCGI->CFI.block_width - 4; i += 2)
				cout << (pCGI->CBI.block_border ? pCGI->CBI.h_normal : "  ");
			cout << (pCGI->CBI.block_border ? pCGI->CBI.lower_right : "  ");
			Sleep(pCGI->delay_of_draw_block);
		}
		cct_setcolor();
	}
	return 0; //�˾�ɸ�����Ҫ�޸�
}


	  /* -----------------------------------------------
			  ʵ����������ĺ���������������׼����
		 ----------------------------------------------- */
		 /***************************************************************************
		   �������ƣ�
		   ��    �ܣ�������Ϸ����ܵ�������
		   ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
					 const int row						������(������Ϊ0���������ޣ���Ϊ��֤��ȷ��)
					 const int col						������(������Ϊ0���������ޣ���Ϊ��֤��ȷ��)
		   �� �� ֵ��
		   ˵    ����1��ָ��������Ϸ�ľ������������ֵ
					 2�����еı仯�ᵼ��CONSOLE_GRAPHICS_INFO�ṹ����������Աֵ�ı仯��Ҫ����
		 ***************************************************************************/
int gmw_set_rowcol(CONSOLE_GRAPHICS_INFO* const pCGI, const int row, const int col)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	(*pCGI).col_num = col;
	(*pCGI).row_num = row;
	pCGI->CFI.bhigh = pCGI->CFI.block_high * pCGI->row_num + (pCGI->row_num-1)*pCGI->CFI.separator + 2;
	pCGI->CFI.bwidth = pCGI->CFI.block_width * pCGI->col_num + (pCGI->col_num-1) * 2 * pCGI->CFI.separator + 4;	
	pCGI->lines = pCGI->extern_up_lines + pCGI->extern_down_lines + pCGI->CFI.bhigh + pCGI->SLI.is_top_status_line + pCGI->SLI.is_lower_status_line + pCGI->draw_frame_with_col_no + 4;
	pCGI->cols = pCGI->extern_left_cols + pCGI->extern_right_cols + pCGI->CFI.bwidth + pCGI->draw_frame_with_row_no*2 + 1;
	pCGI->SLI.lower_start_y = pCGI->extern_up_lines + pCGI->draw_frame_with_col_no + pCGI->SLI.is_top_status_line + pCGI->CFI.bhigh;
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ������������ڣ�����Ϸ�������������ڵ�����cmd���ڣ�����ɫ
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
		   const int bg_color					��ǰ��ɫ��ȱʡCOLOR_BLACK��
		   const int fg_color					������ɫ��ȱʡCOLOR_WHITE��
		   const bool cascade					���Ƿ�����ȱʡΪtrue-������
  �� �� ֵ��
  ˵    ����1��cascade = trueʱ
				ͬ���޸���Ϸ���������ɫ
				ͬ���޸�����״̬���������ı��ı���ɫ��ǰ��ɫ����Ŀ�ı��ı���ɫ��ǰ��ɫ���䣩
			2���������ɫֵ���󼰳�ͻ����Ҫ��Ϊ��֤
				������ɫ��0-15
					ǰ��ɫ����ɫ��ֵһ�µ����޷���������
					ǰ��ɫ������״̬����Ŀǰ��ɫ�������޷�������Ŀ��ʾ
					...
***************************************************************************/
int gmw_set_color(CONSOLE_GRAPHICS_INFO* const pCGI, const int bgcolor, const int fgcolor, const bool cascade)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;

	(*pCGI).area_fgcolor = fgcolor;
	(*pCGI).area_bgcolor = bgcolor;
	if (cascade == 1)
	{
		(*pCGI).CFI.bgcolor = bgcolor;
		(*pCGI).CFI.fgcolor = fgcolor;
		(*pCGI).SLI.lower_normal_bgcolor = bgcolor;
		(*pCGI).SLI.top_normal_bgcolor = bgcolor;
		(*pCGI).SLI.lower_normal_fgcolor = fgcolor;
		(*pCGI).SLI.top_normal_fgcolor = fgcolor;
		(*pCGI).SLI.lower_catchy_bgcolor = bgcolor;
	}

	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ����ô��ڵ�����
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
		   const char *fontname					���������ƣ�ֻ����"Terminal"��"������"���֣������򷵻�-1�����ı����壩
		   const int fs_high					������߶ȣ�ȱʡ������Ϊ16�������������ƣ���Ϊ��֤��
		   const int fs_width					������߶ȣ�ȱʡ������Ϊ8�������������ƣ���Ϊ��֤��
  �� �� ֵ��
  ˵    ����1����cmd_console_tools�е�setfontsize���ƣ�Ŀǰֻ֧�֡��������塱�͡������塱
			2������������������ֱ�ӷ��أ�����ԭ�������ò���
***************************************************************************/
int gmw_set_font(CONSOLE_GRAPHICS_INFO* const pCGI, const char* fontname, const int fs_high, const int fs_width)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	(*pCGI).CFT.font_size_high = fs_high;
	(*pCGI).CFT.font_size_width = fs_width;
	if (strcmp(fontname, "Terminal") == 0 || strcmp(fontname, "������") == 0)
		strcpy((*pCGI).CFT.font_type, fontname);
	else
		return -1;
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�������ʱ
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
		   const int type						����ʱ�����ͣ�ĿǰΪ3�֣�
		   const int delay_ms					����msΪ��λ����ʱ
			   ���߿����ʱ��0 ~ �������ޣ���Ϊ��֤��ȷ��<0����0��
			   ��ɫ�����ʱ��0 ~ �������ޣ���Ϊ��֤��ȷ��<0����0��
			   ɫ���ƶ�����ʱ��BLOCK_MOVED_DELAY_MS ~ �������ޣ���Ϊ��֤��ȷ�� <BLOCK_MOVED_DELAY_MS ���� BLOCK_MOVED_DELAY_MS��
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int gmw_set_delay(CONSOLE_GRAPHICS_INFO* const pCGI, const int type, const int delay_ms)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	switch (type)
	{
	case 0:
		(*pCGI).delay_of_draw_frame = (delay_ms > 0 ? delay_ms : 0);
		break;
	case 1:
		(*pCGI).delay_of_draw_block = (delay_ms > 0 ? delay_ms : 0);
	case 2:
		(*pCGI).delay_of_block_moved = (delay_ms > BLOCK_MOVED_DELAY_MS ? delay_ms : BLOCK_MOVED_DELAY_MS);
	}
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ���������������Ϸ����ܽṹ֮����Ҫ�����Ķ�������
  ��    �ܣ�CONSOLE_GRAPHICS_INFO *const pCGI	��
		   const int up_lines					���ϲ�������У�ȱʡ������Ϊ0���������ޣ���Ϊ��֤��
		   const int down_lines				���²�������У�ȱʡ������Ϊ0���������ޣ���Ϊ��֤��
		   const int left_cols					����߶�����У�ȱʡ������Ϊ0���������ޣ���Ϊ��֤��
		   const int right_cols				���ұ߶�����У�ȱʡ������Ϊ0���������ޣ���Ϊ��֤��
  �� �� ֵ��
  ˵    �����������еı仯�ᵼ��CONSOLE_GRAPHICS_INFO�ṹ����������Աֵ�ı仯��Ҫ����
***************************************************************************/
int gmw_set_ext_rowcol(CONSOLE_GRAPHICS_INFO* const pCGI, const int up_lines, const int down_lines, const int left_cols, const int right_cols)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	(*pCGI).extern_down_lines = down_lines;
	(*pCGI).extern_up_lines = up_lines;
	(*pCGI).extern_left_cols = left_cols;
	(*pCGI).extern_right_cols = right_cols;
	//���϶���ռ�+��״̬��+�б���ʾ+������+��״̬����+ 4��1�������뷨��ʾ��+3Ԥ�����У�
//���϶���ռ�+��״̬��+�б���ʾ+������+��״̬����+ 4��1�������뷨��ʾ��+3Ԥ�����У�
	pCGI->lines = pCGI->extern_up_lines + pCGI->extern_down_lines + pCGI->CFI.bhigh + pCGI->SLI.is_top_status_line + pCGI->SLI.is_lower_status_line + pCGI->draw_frame_with_col_no + 4;
	pCGI->cols = pCGI->extern_left_cols + pCGI->extern_right_cols + pCGI->CFI.bwidth + pCGI->draw_frame_with_row_no * 2 + 1;
	pCGI->SLI.top_start_x = pCGI->extern_left_cols;
	pCGI->SLI.top_start_y = pCGI->extern_up_lines;
	pCGI->SLI.lower_start_x = pCGI->extern_left_cols;
	pCGI->SLI.lower_start_y = pCGI->extern_up_lines + pCGI->draw_frame_with_col_no + pCGI->SLI.is_top_status_line + pCGI->CFI.bhigh;
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���� CONSOLE_FRAME_TYPE �ṹ�е�11�����ͣ�ȱʡ4�֣�
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const int type						��1 - ȫ�� 2 - ȫ���� 3 - ��˫���� 4 - �ᵥ��˫
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int gmw_set_frame_default_linetype(CONSOLE_GRAPHICS_INFO* const pCGI, const int type)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	(*pCGI).CFI.type = type;
	switch ((*pCGI).CFI.type)
	{
	case 1://�U�X�T�p�m�j�g�d�a�^�[�X�U�T
		strcpy((*pCGI).CFI.top_left, "�X");			// "�X"
		strcpy((*pCGI).CFI.lower_left, "�^");		// "�^"
		strcpy((*pCGI).CFI.top_right, "�[");			// "�["
		strcpy((*pCGI).CFI.lower_right, "�a");		// "�a"
		strcpy((*pCGI).CFI.h_normal, "�T");			// "�T"	//Horizontal
		strcpy((*pCGI).CFI.v_normal, "�U");			// "�U"	//Vertical
		strcpy((*pCGI).CFI.h_top_separator, "�j");	// "�h"
		strcpy((*pCGI).CFI.h_lower_separator, "�m");	// "�k"
		strcpy((*pCGI).CFI.v_left_separator, "�d");	// "�c"
		strcpy((*pCGI).CFI.v_right_separator, "�g");	// "�f"
		strcpy((*pCGI).CFI.mid_separator, "�p");		// "��"
		break;
	case 2://���������������ȩЩة�
		strcpy((*pCGI).CFI.top_left, "��");			// "�X"
		strcpy((*pCGI).CFI.lower_left, "��");		// "�^"
		strcpy((*pCGI).CFI.top_right, "��");			// "�["
		strcpy((*pCGI).CFI.lower_right, "��");		// "�a"
		strcpy((*pCGI).CFI.h_normal, "��");			// "�T"	//Horizontal
		strcpy((*pCGI).CFI.v_normal, "��");			// "�U"	//Vertical
		strcpy((*pCGI).CFI.h_top_separator, "��");	// "�h"
		strcpy((*pCGI).CFI.h_lower_separator, "��");	// "�k"
		strcpy((*pCGI).CFI.v_left_separator, "��");	// "�c"
		strcpy((*pCGI).CFI.v_right_separator, "��");	// "�f"
		strcpy((*pCGI).CFI.mid_separator, "��");		// "��"
		break;
	case 3://�V�\�Y�_�b�k�h�n�T���e
		strcpy((*pCGI).CFI.top_left, "�V");			// "�X"
		strcpy((*pCGI).CFI.lower_left, "�\");		// "�^"
		strcpy((*pCGI).CFI.top_right, "�Y");			// "�["
		strcpy((*pCGI).CFI.lower_right, "�_");		// "�a"
		strcpy((*pCGI).CFI.h_normal, "�T");			// "�T"	//Horizontal
		strcpy((*pCGI).CFI.v_normal, "��");			// "�U"	//Vertical
		strcpy((*pCGI).CFI.h_top_separator, "�h");	// "�h"
		strcpy((*pCGI).CFI.h_lower_separator, "�k");	// "�k"
		strcpy((*pCGI).CFI.v_left_separator, "�b");	// "�c"
		strcpy((*pCGI).CFI.v_right_separator, "�e");	// "�f"
		strcpy((*pCGI).CFI.mid_separator, "�n");		// "��"
		break;
	case 4://�W�Z�`�c�f�i�l�o���U�]
		strcpy((*pCGI).CFI.top_left, "�W");			// "�X"
		strcpy((*pCGI).CFI.lower_left, "�]");		// "�^"
		strcpy((*pCGI).CFI.top_right, "�Z");			// "�["
		strcpy((*pCGI).CFI.lower_right, "�`");		// "�a"
		strcpy((*pCGI).CFI.h_normal, "��");			// "�T"	//Horizontal
		strcpy((*pCGI).CFI.v_normal, "�U");			// "�U"	//Vertical
		strcpy((*pCGI).CFI.h_top_separator, "�i");	// "�h"
		strcpy((*pCGI).CFI.h_lower_separator, "�l");	// "�k"
		strcpy((*pCGI).CFI.v_left_separator, "�c");	// "�c"
		strcpy((*pCGI).CFI.v_right_separator, "�f");	// "�f"
		strcpy((*pCGI).CFI.mid_separator, "�o");		// "��"
		break;
	}
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���� CONSOLE_FRAME_TYPE �ṹ�е�11������
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const char *...						����11�֣������.h���˴���
  �� �� ֵ��
  ˵    ����Լ��Ϊһ�������Ʊ��������ʹ���������ݣ���Ϊ��֤2�ֽ�
			1������2�ֽ���ֻȡǰ2�ֽ�
			2�������NULL���������ո����
			3�������1�ֽڣ���һ���ո������˶�������ʾ�ң������
***************************************************************************/
int gmw_set_frame_linetype(CONSOLE_GRAPHICS_INFO* const pCGI, const char* top_left, const char* lower_left, const char* top_right,
	const char* lower_right, const char* h_normal, const char* v_normal, const char* h_top_separator,
	const char* h_lower_separator, const char* v_left_separator, const char* v_right_separator, const char* mid_separator)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	/**Ĭ��Ϊ4����*/
	strcpy((*pCGI).CFI.top_left, top_left);			// "�X"
	strcpy((*pCGI).CFI.lower_left, lower_left);		// "�^"
	strcpy((*pCGI).CFI.top_right, top_right);			// "�["
	strcpy((*pCGI).CFI.lower_right, lower_right);		// "�a"
	strcpy((*pCGI).CFI.h_normal, h_normal);			// "�T"	//Horizontal
	strcpy((*pCGI).CFI.v_normal, v_normal);			// "�U"	//Vertical
	strcpy((*pCGI).CFI.h_top_separator, h_top_separator);	// "�h"
	strcpy((*pCGI).CFI.h_lower_separator, h_lower_separator);	// "�k"
	strcpy((*pCGI).CFI.v_left_separator, v_left_separator);	// "�c"
	strcpy((*pCGI).CFI.v_right_separator, v_right_separator);	// "�f"
	strcpy((*pCGI).CFI.mid_separator, mid_separator);		// "��"
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���� CONSOLE_FRAME_TYPE �ṹ�е�ɫ��������С���Ƿ���Ҫ�ָ��ߵ�
  ������������������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const int block_width						����ȣ�����ȱʡ2����ΪԼ�������Ϊ�����Ʊ�����������������Ҫ+1��
			const int block_high						���߶ȣ�����ȱʡ1��
			const bool separator						���Ƿ���Ҫ�ָ��ߣ�ȱʡΪtrue����Ҫ�ָ��ߣ�
  �� �� ֵ��
  ˵    ������ܴ�С/�Ƿ���Ҫ�ָ��ߵȵı仯�ᵼ��CONSOLE_GRAPHICS_INFO�ṹ����������Աֵ�ı仯��Ҫ����
***************************************************************************/
int gmw_set_frame_style(CONSOLE_GRAPHICS_INFO* const pCGI, const int block_width, const int block_high, const bool separator)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	(*pCGI).CFI.separator = separator;
	(*pCGI).CFI.block_high = block_high;
	(*pCGI).CFI.block_width = block_width%2?block_width+1:block_width ;
	pCGI->CFI.bhigh = pCGI->CFI.block_high * pCGI->row_num + (pCGI->row_num - 1) * pCGI->CFI.separator + 2;
	pCGI->CFI.bwidth = pCGI->CFI.block_width * pCGI->col_num + (pCGI->col_num - 1) * 2 * pCGI->CFI.separator + 4;
	pCGI->lines = pCGI->extern_up_lines + pCGI->extern_down_lines + pCGI->CFI.bhigh + pCGI->SLI.is_top_status_line + pCGI->SLI.is_lower_status_line + pCGI->draw_frame_with_col_no + 4;
	pCGI->cols = pCGI->extern_left_cols + pCGI->extern_right_cols + pCGI->CFI.bwidth + pCGI->draw_frame_with_row_no * 2 + 1;
	pCGI->SLI.lower_start_y = pCGI->extern_up_lines + pCGI->draw_frame_with_col_no + pCGI->SLI.is_top_status_line + pCGI->CFI.bhigh;

	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���� CONSOLE_BORDER_TYPE �ṹ�е���ɫ
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const int bg_color					������ɫ��ȱʡ -1��ʾ�ô��ڱ���ɫ��
			const int fg_color					��ǰ��ɫ��ȱʡ -1��ʾ�ô���ǰ��ɫ��
  �� �� ֵ��
  ˵    �����������ɫֵ���󼰳�ͻ����Ҫ��Ϊ��֤
				������ɫ��0-15��ǰ��ɫ����ɫ��ֵһ�µ����޷��������ݵ�
***************************************************************************/
int gmw_set_frame_color(CONSOLE_GRAPHICS_INFO* const pCGI, const int bgcolor, const int fgcolor)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	(*pCGI).CFI.fgcolor = fgcolor;
	(*pCGI).CFI.bgcolor = bgcolor;
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���� CONSOLE_BLOCK_INFO �ṹ�е�6�����ͣ�ȱʡ4�֣�
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const int type						��1 - ȫ˫�� 2 - ȫ���� 3 - ��˫���� 4 - �ᵥ��˫
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int gmw_set_block_default_linetype(CONSOLE_GRAPHICS_INFO* const pCGI, const int type)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	switch (type)
	{
	case 1://�U�X�T�p�m�j�g�d�a�^�[�X�U�T
		strcpy(pCGI->CBI.top_left, "�X");			// "�X"
		strcpy(pCGI->CBI.lower_left, "�^");	// "�^"
		strcpy(pCGI->CBI.top_right, "�[");			// "�["
		strcpy(pCGI->CBI.lower_right, "�a");	// "�a"
		strcpy(pCGI->CBI.h_normal, "�T");			// "�T"	//Horizontal
		strcpy(pCGI->CBI.v_normal, "�U");			// "�U"	//Vertical
		break;
	case 2://���������������ȩЩة�
		strcpy(pCGI->CBI.top_left, "��");			// "�X"
		strcpy(pCGI->CBI.lower_left, "��");	// "�^"
		strcpy(pCGI->CBI.top_right, "��");			// "�["
		strcpy(pCGI->CBI.lower_right, "��");	// "�a"
		strcpy(pCGI->CBI.h_normal, "��");			// "�T"	//Horizontal
		strcpy(pCGI->CBI.v_normal, "��");			// "�U"	//Vertical
		break;
	case 3://�V�\�Y�_�b�k�h�n�T���e
		strcpy(pCGI->CBI.top_left, "�V");			// "�X"
		strcpy(pCGI->CBI.lower_left, "�\");	// "�^"
		strcpy(pCGI->CBI.top_right, "�Y");			// "�["
		strcpy(pCGI->CBI.lower_right, "�_");	// "�a"
		strcpy(pCGI->CBI.h_normal, "�T");			// "�T"	//Horizontal
		strcpy(pCGI->CBI.v_normal, "��");			// "�U"	//Vertical
		break;
	case 4://�W�Z�`�c�f�i�l�o���U�]
		strcpy(pCGI->CBI.top_left, "�W");			// "�X"
		strcpy(pCGI->CBI.lower_left, "�]");	// "�^"
		strcpy(pCGI->CBI.top_right, "�Z");			// "�["
		strcpy(pCGI->CBI.lower_right, "�`");	// "�a"
		strcpy(pCGI->CBI.h_normal, "��");			// "�T"	//Horizontal
		strcpy(pCGI->CBI.v_normal, "�U");			// "�U"	//Vertical
		break;
	}
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���� CONSOLE_BLOCK_INFO �ṹ�е�6������
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
		   const char *...					����6�֣������.h���˴���
  �� �� ֵ��
  ˵    ����Լ��Ϊһ�������Ʊ��������ʹ���������ݣ���Ϊ��֤2�ֽ�
			1������2�ֽ���ֻȡǰ2�ֽ�
			2�������NULL���������ո����
			3�������1�ֽڣ���һ���ո������˶�������ʾ�ң������
***************************************************************************/
int gmw_set_block_linetype(CONSOLE_GRAPHICS_INFO* const pCGI, const char* top_left, const char* lower_left, const char* top_right, const char* lower_right, const char* h_normal, const char* v_normal)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	strcpy(pCGI->CBI.top_left, top_left);			// "�X"
	strcpy(pCGI->CBI.lower_left, lower_left);	// "�^"
	strcpy(pCGI->CBI.top_right, top_right);			// "�["
	strcpy(pCGI->CBI.lower_right, lower_right);	// "�a"
	strcpy(pCGI->CBI.h_normal, h_normal);			// "�T"	//Horizontal
	strcpy(pCGI->CBI.v_normal, v_normal);			// "�U"	//Vertical
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�����ÿ����Ϸɫ��(����)�Ƿ���ҪС�߿�
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
		   const bool on_off					��true - ��Ҫ flase - ����Ҫ��ȱʡfalse��
  �� �� ֵ��
  ˵    �����߿�Լ��Ϊ�����Ʊ����˫��
***************************************************************************/
int gmw_set_block_border_switch(CONSOLE_GRAPHICS_INFO* const pCGI, const bool on_off)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	pCGI->CBI.block_border = on_off;
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ������Ƿ���ʾ����״̬��
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const int type						��״̬�����ͣ���/�£�
			const bool on_off					��true - ��Ҫ flase - ����Ҫ��ȱʡtrue��
  �� �� ֵ��
  ˵    ����1��״̬�������Լ�����£�
			   1.1����״̬��ֻ��һ�У������������Ϸ�����/�б�����棬Ϊ��������ʼһ�У�����������Ͻ����������״̬�������꣩
			   1.2����״̬��ֻ��һ�У������������·����ߵ�����
			   1.3��״̬���Ŀ��Ϊ�������ȣ������Ϣ������ض�
		   2�����еı仯�ᵼ��CONSOLE_GRAPHICS_INFO�ṹ����������Աֵ�ı仯��Ҫ����
***************************************************************************/
int gmw_set_status_line_switch(CONSOLE_GRAPHICS_INFO* const pCGI, const int type, const bool on_off)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	if (type == 1)
	{
		pCGI->SLI.is_lower_status_line = on_off;
		pCGI->lower_status_line = on_off;
	}
	else if (type == 0)
	{
		pCGI->SLI.is_top_status_line = on_off;
		pCGI->top_status_line = on_off;
	}
	//���϶���ռ�+��״̬��+�б���ʾ+������+��״̬����+ 4��1�������뷨��ʾ��+3Ԥ�����У�
	pCGI->lines = pCGI->extern_up_lines + pCGI->extern_down_lines + pCGI->CFI.bhigh + pCGI->SLI.is_top_status_line + pCGI->SLI.is_lower_status_line + pCGI->draw_frame_with_col_no + 4;
	pCGI->cols = pCGI->extern_left_cols + pCGI->extern_right_cols + pCGI->CFI.bwidth + pCGI->draw_frame_with_row_no * 2 + 1;
	pCGI->SLI.lower_start_y = pCGI->extern_up_lines + pCGI->draw_frame_with_col_no + pCGI->SLI.is_top_status_line + pCGI->CFI.bhigh;
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���������״̬������ɫ
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const int type						��״̬�����ͣ���/�£�
			const int normal_bgcolor			�������ı�����ɫ��ȱʡ -1��ʾʹ�ô��ڱ���ɫ��
			const int normal_fgcolor			�������ı�ǰ��ɫ��ȱʡ -1��ʾʹ�ô���ǰ��ɫ��
			const int catchy_bgcolor			����Ŀ�ı�����ɫ��ȱʡ -1��ʾʹ�ô��ڱ���ɫ��
			const int catchy_fgcolor			����Ŀ�ı�ǰ��ɫ��ȱʡ -1��ʾʹ������ɫ��
  ���������
  �� �� ֵ��
  ˵    �����������ɫֵ���󼰳�ͻ����Ҫ��Ϊ��֤
				������ɫ��0-15��ǰ��ɫ����ɫ��ֵһ�µ����޷��������ݵ�
***************************************************************************/
int gmw_set_status_line_color(CONSOLE_GRAPHICS_INFO* const pCGI, const int type, const int normal_bgcolor, const int normal_fgcolor, const int catchy_bgcolor, const int catchy_fgcolor)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	if (type == 0)
	{
		pCGI->SLI.top_catchy_bgcolor = catchy_bgcolor;
		pCGI->SLI.top_catchy_fgcolor = catchy_fgcolor;
		pCGI->SLI.top_normal_bgcolor = normal_bgcolor;
		pCGI->SLI.top_normal_fgcolor = normal_fgcolor;
	}
	else if (type == 1)
	{
		pCGI->SLI.lower_catchy_bgcolor = catchy_bgcolor;
		pCGI->SLI.lower_catchy_fgcolor = catchy_fgcolor;
		pCGI->SLI.lower_normal_bgcolor = normal_bgcolor;
		pCGI->SLI.lower_normal_fgcolor = normal_fgcolor;
	}
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ������Ƿ���ʾ�к�
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const bool on_off					��true - ��ʾ flase - ����ʾ��ȱʡfalse��
  �� �� ֵ��
  ˵    ����1���к�Լ��Ϊ��ĸA��ʼ�������У��������26�����a��ʼ������52��ͳһΪ*��ʵ��Ӧ�ò����ܣ�
			2���Ƿ���ʾ�кŵı仯�ᵼ��CONSOLE_GRAPHICS_INFO�ṹ����������Աֵ�ı仯��Ҫ����
***************************************************************************/
int gmw_set_rowno_switch(CONSOLE_GRAPHICS_INFO* const pCGI, const bool on_off)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	pCGI->draw_frame_with_row_no = on_off;
	pCGI->cols = pCGI->extern_left_cols + pCGI->extern_right_cols + pCGI->CFI.bwidth + pCGI->draw_frame_with_row_no * 2 + 1; return 0; //�˾�ɸ�����Ҫ�޸�
	return 0;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ������Ƿ���ʾ�б�
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const bool on_off					��true - ��ʾ flase - ����ʾ��ȱʡfalse��
  �� �� ֵ��
  ˵    ����1���б�Լ��Ϊ����0��ʼ�������У�����0-99������99ͳһΪ**��ʵ��Ӧ�ò����ܣ�
			2���Ƿ���ʾ�б�ı仯�ᵼ��CONSOLE_GRAPHICS_INFO�ṹ����������Աֵ�ı仯��Ҫ����
***************************************************************************/
int gmw_set_colno_switch(CONSOLE_GRAPHICS_INFO* const pCGI, const bool on_off)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	pCGI->draw_frame_with_col_no = on_off;
	pCGI->lines = pCGI->extern_up_lines + pCGI->extern_down_lines + pCGI->CFI.bhigh + pCGI->SLI.is_top_status_line + pCGI->SLI.is_lower_status_line + pCGI->draw_frame_with_col_no + 4;
	pCGI->SLI.lower_start_y = pCGI->extern_up_lines + pCGI->draw_frame_with_col_no + pCGI->SLI.is_top_status_line + pCGI->CFI.bhigh;
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���ӡ CONSOLE_GRAPHICS_INFO �ṹ���еĸ���Աֵ
  ���������
  �� �� ֵ��
  ˵    ����1�����������ã���ӡ��ʽ�Զ���
			2������������������δ���ù������Բ�ʵ��
***************************************************************************/
int gmw_print(const CONSOLE_GRAPHICS_INFO* const pCGI)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ��� CONSOLE_GRAPHICS_INFO �ṹ����ȱʡֵ���г�ʼ��
  ���������CONSOLE_GRAPHICS_INFO *const pCGI������ṹָ��
		   const int row					����Ϸ����ɫ��������ȱʡ10��
		   const int col					����Ϸ����ɫ��������ȱʡ10��
		   const int bgcolor				���������ڱ���ɫ��ȱʡ COLOR_BLACK��
		   const int fgcolor				���������ڱ���ɫ��ȱʡ COLOR_WHITE��
  �� �� ֵ��
  ˵    �������ڱ�����/ǰ���ף�����16*8�����������޶������У�����״̬�����У����к�/�б꣬�������Ϊ˫�ߣ�ɫ����2/�߶�1/��С�߿���ɫ��
***************************************************************************/
int gmw_init(CONSOLE_GRAPHICS_INFO* const pCGI, const int row, const int col, const int bgcolor, const int fgcolor)
{
	/* �����ñ�� */
	pCGI->inited = CGI_INITED;
	/* ������ʼ�����������������ڴ˻����������޸Ĳ������ã��������Ԥ��ֵ
		��Ϸ��������ܣ�Ϊ10*10//�����ָ��ߣ�ÿ��ɫ��Ĵ�СΪ2��*1�У�ɫ�鲻���߿�//
		���ڱ���ɫ�ڣ�ǰ��ɫ��//
		����Ϊ����8*16//
		���߿�ɫ��ʱ����ʱ��ɫ���ƶ�ʱ��ʱ3ms//
		�������Ҹ�������ȫ��Ϊ0//
		��״̬�����������ı���ɫͬ���ڣ���Ŀ�ı�����ͬ���ڣ�ǰ��Ϊ����//
		��״̬�����������ı���ɫͬ���ڣ���Ŀ�ı�����ͬ���ڣ�ǰ��Ϊ����//
		����ʾ�к�//
		����ʾ�б�//
		��Ϸ����Ϊ˫�߿�//�����ָ��ߣ�ɫ���СΪ2�����2��=1�����֣�*1���߶�1�У�����ɫͬ����//
		ɫ��Ϊ˫���ߣ���ɫ��δ�꣩		*/
	gmw_set_rowcol(pCGI, row, col);//
	gmw_set_color(pCGI);//
	gmw_set_font(pCGI);//
	gmw_set_delay(pCGI, 0, 0);//
	gmw_set_delay(pCGI, 1, 0);//
	gmw_set_delay(pCGI, 2, 3);//
	gmw_set_ext_rowcol(pCGI);//

	gmw_set_frame_default_linetype(pCGI, 1);//
	gmw_set_frame_style(pCGI, 2, 1, 1);//
	gmw_set_frame_color(pCGI);

	gmw_set_block_default_linetype(pCGI, 1);
	gmw_set_block_border_switch(pCGI);

	gmw_set_status_line_switch(pCGI, 0);//
	gmw_set_status_line_switch(pCGI, 1);//
	gmw_set_status_line_color(pCGI, 0);
	gmw_set_status_line_color(pCGI, 1);

	gmw_set_rowno_switch(pCGI);//
	gmw_set_colno_switch(pCGI);//
			
	pCGI->SLI.top_catchy_fgcolor = 14;//
	pCGI->SLI.lower_catchy_fgcolor = 14;//
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�������Ϸ���
  ���������const CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
  �� �� ֵ��
  ˵    ��������ɲο�demo��Ч��
***************************************************************************/
int gmw_draw_frame(const CONSOLE_GRAPHICS_INFO* const pCGI)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;

	cct_setfontsize(pCGI->CFT.font_type,pCGI->CFT.font_size_high);
	cct_setconsoleborder(pCGI->cols, pCGI->lines);
	cct_setcolor((*pCGI).area_bgcolor, (*pCGI).area_fgcolor);
	cct_cls();

	//�б�
	if (pCGI->draw_frame_with_col_no)
	{
		cct_gotoxy(pCGI->extern_left_cols + pCGI->draw_frame_with_row_no*2+ pCGI->CFI.block_width/2+1, pCGI->extern_up_lines + pCGI->SLI.is_top_status_line);
		for (int j = 0; j < pCGI->col_num; j++)
			if(j>=100)
				cout << setw(pCGI->CFI.block_width + 2 * pCGI->CFI.separator) << setiosflags(ios::left) <<'*';
			else
				cout<<setw(pCGI->CFI.block_width+2*pCGI->CFI.separator)<<setiosflags(ios::left) <<j;
	}
	//����
	cct_setcolor((*pCGI).CFI.bgcolor, (*pCGI).CFI.fgcolor);
	cct_gotoxy(pCGI->extern_left_cols + pCGI->draw_frame_with_row_no * 2, pCGI->extern_up_lines + pCGI->draw_frame_with_col_no + pCGI->SLI.is_top_status_line);
	cout << pCGI->CFI.top_left;
	for (int j = 0; j < pCGI->col_num; j++)
	{
		for (int c = 0; c < pCGI->CFI.block_width; c += 2)
			cout << pCGI->CFI.h_normal;
		if (pCGI->CFI.separator)
			cout << pCGI->CFI.h_top_separator;
		Sleep(pCGI->delay_of_draw_frame);
	}
	if (pCGI->CFI.separator)
		cout << "\b\b";
	cout << pCGI->CFI.top_right << endl;
	Sleep(pCGI->delay_of_draw_frame);
	//�м���
	for (int i = 0; i < pCGI->row_num; i++)
	{
		for (int r = 0; r < pCGI->CFI.block_high; r++)
		{
			//�б�
			cct_setcolor((*pCGI).area_bgcolor, (*pCGI).area_fgcolor);
			cct_gotoxy(pCGI->extern_left_cols, r + 1+(i * (pCGI->CFI.separator + pCGI->CFI.block_high)) + pCGI->SLI.is_top_status_line + pCGI->extern_up_lines + pCGI->draw_frame_with_col_no);
			if (pCGI->draw_frame_with_row_no && r == (pCGI->CFI.block_high - 1) / 2)
				if (i < 52)
					cout << (i >= 26 ? (char)('a' + i-26) : (char)('A' + i));
				else
					cout << '*';
			cct_setcolor((*pCGI).CFI.bgcolor, (*pCGI).CFI.fgcolor);
			Sleep(pCGI->delay_of_draw_frame);
			//|   |
			cct_gotoxy(pCGI->extern_left_cols + pCGI->draw_frame_with_row_no * 2, r + 1+(i * (pCGI->CFI.separator + pCGI->CFI.block_high)) + pCGI->SLI.is_top_status_line + pCGI->extern_up_lines + pCGI->draw_frame_with_col_no);
			cout << pCGI->CFI.v_normal;
			for (int j = 0; j < pCGI->col_num; j++)
			{
				for (int c = 0; c < pCGI->CFI.block_width; c += 2)
					cout << "  ";
				if (pCGI->CFI.separator)
					cout << pCGI->CFI.v_normal;
				Sleep(pCGI->delay_of_draw_frame);
			}
			if (!pCGI->CFI.separator)
				cout << pCGI->CFI.v_normal;
			Sleep(pCGI->delay_of_draw_frame);
		}
		//+------+
		if (pCGI->CFI.separator)
		{
			cct_gotoxy(pCGI->extern_left_cols + pCGI->draw_frame_with_row_no * 2, pCGI->SLI.is_top_status_line + pCGI->extern_up_lines + pCGI->draw_frame_with_col_no + 1 + (i + 1) * pCGI->CFI.block_high + i * pCGI->CFI.separator);
			cout << pCGI->CFI.v_left_separator;
			for (int j = 0; j < pCGI->col_num; j++)
			{
				for (int c = 0; c < pCGI->CFI.block_width; c += 2)
					cout << pCGI->CFI.h_normal;
				cout << pCGI->CFI.mid_separator;
				Sleep(pCGI->delay_of_draw_frame);
			}
			cout <<"\b\b" << pCGI->CFI.v_right_separator;
			Sleep(pCGI->delay_of_draw_frame);
		}
	}
	//β��
	cct_gotoxy(pCGI->extern_left_cols + pCGI->draw_frame_with_row_no * 2, pCGI->extern_up_lines+ pCGI->draw_frame_with_col_no + pCGI->SLI.is_top_status_line +pCGI->CFI.bhigh -1);
	cout << pCGI->CFI.lower_left;
	for (int j = 0; j < pCGI->col_num; j++)
	{
		for (int c = 0; c < pCGI->CFI.block_width ; c += 2)			
				cout << pCGI->CFI.h_normal;
		if (pCGI->CFI.separator)
			cout << pCGI->CFI.h_lower_separator;		
	}
	if (pCGI->CFI.separator)
		cout <<"\b\b";
	cout << pCGI->CFI.lower_right << endl;
	Sleep(pCGI->delay_of_draw_frame);
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���״̬������ʾ��Ϣ
  ���������const CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
		   const int type							��ָ������/��״̬��
		   const char *msg						��������Ϣ
		   const char *catchy_msg					����Ҫ�ر��ע����Ϣ����������Ϣǰ��ʾ��
  �� �� ֵ��
  ˵    ����1���������޶�Ϊ����ܵĿ�ȣ����к��б�λ�ã����������ȥ
			2��������һ���ַ���ĳ���ֵ�ǰ������ᵼ�º������룬Ҫ����
***************************************************************************/
int gmw_status_line(const CONSOLE_GRAPHICS_INFO* const pCGI, const int type, const char* msg, const char* catchy_msg)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	if (type == 0&& pCGI->SLI.is_top_status_line)
	{
		cct_gotoxy(pCGI->SLI.top_start_x, pCGI->SLI.top_start_y);
		cct_setcolor(pCGI->SLI.top_catchy_bgcolor, pCGI->SLI.top_catchy_fgcolor);
		cout <<( catchy_msg==NULL?"" : catchy_msg);
		cct_setcolor(pCGI->SLI.top_normal_bgcolor, pCGI->SLI.top_normal_fgcolor);
		int i;
		for (i = 0;msg[i]!='\0'&&i < pCGI->CFI.bwidth + 2 * pCGI->draw_frame_with_col_no; i++)
			cout << msg[i];
		for (; i < pCGI->CFI.bwidth + 2 * pCGI->draw_frame_with_col_no; i++)
			cout << ' ';
		cct_setcolor();
	}
	else if(type==1&& pCGI->SLI.is_lower_status_line)
	{		
		cct_gotoxy(pCGI->SLI.lower_start_x, pCGI->SLI.lower_start_y);
		cct_setcolor(pCGI->SLI.lower_catchy_bgcolor, pCGI->SLI.top_catchy_fgcolor);
		cout << (catchy_msg == NULL ? "" : catchy_msg);
		cct_setcolor(pCGI->SLI.lower_normal_bgcolor, pCGI->SLI.lower_normal_fgcolor);
		int i;
		for (i = 0; msg[i] != '\0' && i < pCGI->CFI.bwidth + 2 * pCGI->draw_frame_with_col_no; i++)
			cout << msg[i];
		for (; i < pCGI->CFI.bwidth + 2 * pCGI->draw_frame_with_col_no; i++)
			cout << ' ';
		cct_setcolor();
	}	
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���ʾĳһ��ɫ��(����Ϊ�ַ���������Ϊrow/col)
  ���������const CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
		   const int row_no						���кţ���0��ʼ����Ϊ��֤��ȷ�ԣ����򲻼�飩
		   const int col_no						���кţ���0��ʼ����Ϊ��֤��ȷ�ԣ����򲻼�飩
		   const int bdi_value						����Ҫ��ʾ��ֵ
		   const BLOCK_DISPLAY_INFO *const bdi		����Ÿ�ֵ��Ӧ����ʾ��Ϣ�Ľṹ������
  �� �� ֵ��
  ˵    ����1��BLOCK_DISPLAY_INFO �ĺ����ͷ�ļ����÷��ο���������
			2��bdi_valueΪ BDI_VALUE_BLANK ��ʾ�հ׿飬Ҫ���⴦��
***************************************************************************/
int gmw_draw_block(const CONSOLE_GRAPHICS_INFO* const pCGI, const int row_no, const int col_no, const int bdi_value, const BLOCK_DISPLAY_INFO* const bdi)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	gmw_draw_block_diy(pCGI, pCGI->extern_left_cols + pCGI->draw_frame_with_row_no * 2 + 2 + col_no * (pCGI->CFI.block_width + 2 * pCGI->CFI.separator), pCGI->extern_up_lines + pCGI->draw_frame_with_col_no + pCGI->SLI.is_top_status_line + 1 + row_no * (pCGI->CFI.separator + pCGI->CFI.block_high), bdi_value, bdi);
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ��ƶ�ĳһ��ɫ��
  ���������const CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
		   const int row_no						���кţ���0��ʼ����Ϊ��֤��ȷ�ԣ����򲻼�飩
		   const int col_no						���кţ���0��ʼ����Ϊ��֤��ȷ�ԣ����򲻼�飩
		   const int bdi_value						����Ҫ��ʾ��ֵ
		   const int blank_bdi_value				���ƶ����������ڶ���Ч����ʾʱ���ڱ�ʾ�հ׵�ֵ��һ��Ϊ0���˴���Ϊ�������룬�ǿ��ǵ����ܳ��ֵ����������
		   const BLOCK_DISPLAY_INFO *const bdi		�������ʾֵ/�հ�ֵ��Ӧ����ʾ��Ϣ�Ľṹ������
		   const int direction						���ƶ�����һ�����֣������cmd_gmw_tools.h
		   const int distance						���ƶ����루��1��ʼ����Ϊ��֤��ȷ�ԣ����򲻼�飩
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int gmw_move_block(const CONSOLE_GRAPHICS_INFO* const pCGI, const int row_no, const int col_no, const int bdi_value, const int blank_bdi_value, const BLOCK_DISPLAY_INFO* const bdi, const int direction, const int distance)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	int add_x = 0, add_y = 0, s_x = 0, s_y = 0, x = 0, y = 0;
	int bdi_no = -1;
	for (bdi_no = 0; ; bdi_no++)
		if (bdi[bdi_no].value == bdi_value)
			break;
	for (int time = 0; time < distance; time++)
	{
		switch (direction)
		{
		case RIGHT_TO_LEFT:
			add_x = -time * (pCGI->CFI.block_width + 2 * pCGI->CFI.separator);
			s_x = -(pCGI->CFI.block_width + 2 * pCGI->CFI.separator) / 2;
			x = -(pCGI->CFI.block_width + 2 * pCGI->CFI.separator);
			break;
		case LEFT_TO_RIGHT:
			add_x = time * (pCGI->CFI.block_width + 2 * pCGI->CFI.separator);
			s_x = (pCGI->CFI.block_width + 2 * pCGI->CFI.separator) / 2;
			x = pCGI->CFI.block_width + 2 * pCGI->CFI.separator;
			break;
		case DOWN_TO_UP:
			add_y = -time * (pCGI->CFI.block_high + pCGI->CFI.separator);
			s_y = -(pCGI->CFI.block_high + pCGI->CFI.separator) / 2;
			y = -(pCGI->CFI.block_high + pCGI->CFI.separator);
			break;
		case UP_TO_DOWN:
			add_y = time * (pCGI->CFI.block_high + pCGI->CFI.separator);
			s_y = (pCGI->CFI.block_high + pCGI->CFI.separator) / 2;
			y = pCGI->CFI.block_high + pCGI->CFI.separator;
			break;
		}
		//�հ�1
		cct_setcolor(pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
		for (int j = 0; j < pCGI->CFI.block_high; j++)
		{
			cct_gotoxy(add_x + pCGI->extern_left_cols + pCGI->draw_frame_with_row_no * 2 + 2 + col_no * (pCGI->CFI.block_width + 2 * pCGI->CFI.separator), j + add_y + pCGI->extern_up_lines + pCGI->draw_frame_with_col_no + pCGI->SLI.is_top_status_line + 1 + row_no * (pCGI->CFI.separator + pCGI->CFI.block_high));
			for (int i = 0; i < pCGI->CFI.block_width; i++)
				cout << " ";
		}
		Sleep(pCGI->delay_of_block_moved);
		//�ǿհ�1
		gmw_draw_block_diy(pCGI, add_x + s_x + pCGI->extern_left_cols + pCGI->draw_frame_with_row_no * 2 + 2 + col_no * (pCGI->CFI.block_width + 2 * pCGI->CFI.separator), pCGI->extern_up_lines + pCGI->draw_frame_with_col_no + pCGI->SLI.is_top_status_line + 1 + row_no * (pCGI->CFI.separator + pCGI->CFI.block_high) + add_y + s_y, bdi_value, bdi);		
		Sleep(pCGI->delay_of_block_moved);
		//�հ�2
		cct_setcolor(pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
		for (int j = 0; j < pCGI->CFI.block_high; j++)
		{
			cct_gotoxy(add_x + s_x + pCGI->extern_left_cols + pCGI->draw_frame_with_row_no * 2 + 2 + col_no * (pCGI->CFI.block_width + 2 * pCGI->CFI.separator), j + add_y + s_y + pCGI->extern_up_lines + pCGI->draw_frame_with_col_no + pCGI->SLI.is_top_status_line + 1 + row_no * (pCGI->CFI.separator + pCGI->CFI.block_high));
			for (int i = 0; i < pCGI->CFI.block_width; i++)
				cout << " ";
		}
		Sleep(pCGI->delay_of_block_moved);
		//�߿�
		if (pCGI->CFI.separator)
			switch (direction)
			{
			case RIGHT_TO_LEFT:
				for (int j = 0; j < pCGI->CFI.block_high; j++)
				{
					cct_gotoxy(pCGI->CFI.block_width + add_x + x + pCGI->extern_left_cols + pCGI->draw_frame_with_row_no * 2 + 2 + col_no * (pCGI->CFI.block_width + 2 * pCGI->CFI.separator), j + pCGI->extern_up_lines + pCGI->draw_frame_with_col_no + pCGI->SLI.is_top_status_line + 1 + row_no * (pCGI->CFI.separator + pCGI->CFI.block_high) + add_y + y);
					cout << pCGI->CFI.v_normal;
				}
				break;
			case LEFT_TO_RIGHT:
				for (int j = 0; j < pCGI->CFI.block_high; j++)
				{
					cct_gotoxy(add_x + x + pCGI->extern_left_cols + pCGI->draw_frame_with_row_no * 2 + 2 + col_no * (pCGI->CFI.block_width + 2 * pCGI->CFI.separator) - 2, j + pCGI->extern_up_lines + pCGI->draw_frame_with_col_no + pCGI->SLI.is_top_status_line + 1 + row_no * (pCGI->CFI.separator + pCGI->CFI.block_high) + add_y + y);
					cout << pCGI->CFI.v_normal;
				}
				break;
			case DOWN_TO_UP:
				for (int j = 0; j < pCGI->CFI.block_width; j += 2)
				{
					cct_gotoxy(j + add_x + x + pCGI->extern_left_cols + pCGI->draw_frame_with_row_no * 2 + 2 + col_no * (pCGI->CFI.block_width + 2 * pCGI->CFI.separator), pCGI->extern_up_lines + pCGI->draw_frame_with_col_no + pCGI->SLI.is_top_status_line + 1 + row_no * (pCGI->CFI.separator + pCGI->CFI.block_high) + add_y + y + pCGI->CFI.block_high);
					cout << pCGI->CFI.h_normal;
				}
				break;
			case UP_TO_DOWN:
				for (int j = 0; j < pCGI->CFI.block_width; j += 2)
				{
					cct_gotoxy(j + add_x + x + pCGI->extern_left_cols + pCGI->draw_frame_with_row_no * 2 + 2 + col_no * (pCGI->CFI.block_width + 2 * pCGI->CFI.separator), pCGI->extern_up_lines + pCGI->draw_frame_with_col_no + pCGI->SLI.is_top_status_line + pCGI->CFI.block_high + row_no * (pCGI->CFI.separator + pCGI->CFI.block_high) + add_y + y - pCGI->CFI.block_high);
					cout << pCGI->CFI.h_normal;
				}
				break;
			}
		Sleep(pCGI->delay_of_block_moved);
		//�ǿհ�2
		gmw_draw_block_diy(pCGI, add_x + x + pCGI->extern_left_cols + pCGI->draw_frame_with_row_no * 2 + 2 + col_no * (pCGI->CFI.block_width + 2 * pCGI->CFI.separator), pCGI->extern_up_lines + pCGI->draw_frame_with_col_no + pCGI->SLI.is_top_status_line + 1 + row_no * (pCGI->CFI.separator + pCGI->CFI.block_high) + add_y + y, bdi_value, bdi);
		Sleep(pCGI->delay_of_block_moved);
	}
	cct_setcolor();
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ������̻����
  ���������const CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
		   int &MAction							��������� CCT_MOUSE_EVENT�����ֵ��Ч��Ϊ MOUSE_ONLY_MOVED/MOUSE_LEFT_BUTTON_CLICK/MOUSE_RIGHT_BUTTON_CLICK ����֮һ
													   ������� CCT_KEYBOARD_EVENT�����ֵ��Ч
		   int &MRow								��������� CCT_MOUSE_EVENT �� MAction = MOUSE_ONLY_MOVED/MOUSE_LEFT_BUTTON_CLICK�����ֵ��Ч����ʾ���ѡ�����Ϸ������кţ���0��ʼ��
												  ���������ֵ��Ч�����������Чֵ���´��󣬲��Ǳ������Ĵ�!!!��
		   int &MCol								��������� CCT_MOUSE_EVENT �� MAction = MOUSE_ONLY_MOVED/MOUSE_LEFT_BUTTON_CLICK�����ֵ��Ч����ʾ���ѡ�����Ϸ������кţ���0��ʼ��
												  ���������ֵ��Ч�����������Чֵ���´��󣬲��Ǳ������Ĵ�!!!��
		   int &KeyCode1							��������� CCT_KEYBOARD_EVENT�����ֵ��Ч��Ϊ�����ļ��루���˫���룬��Ϊ��һ����
												  ���������ֵ��Ч�����������Чֵ���´��󣬲��Ǳ������Ĵ�!!!��
		   int &KeyCode2							��������� CCT_KEYBOARD_EVENT�����ֵ��Ч��Ϊ�����ļ��루���˫���룬��Ϊ�ڶ���������ǵ����룬��Ϊ0��
												  ���������ֵ��Ч�����������Чֵ���´��󣬲��Ǳ������Ĵ�!!!��
		   const bool update_lower_status_line		������ƶ�ʱ���Ƿ�Ҫ�ڱ���������ʾ"[��ǰ���] *��*��/λ�÷Ƿ�"����Ϣ��true=��ʾ��false=����ʾ��ȱʡΪtrue��
  �� �� ֵ����������Լ��
		   1�����������ƶ����õ���MRow/MCol�봫�����ͬ(���ָ��΢С���ƶ�)���򲻷��أ�������
							  �õ����зǷ�λ�ã��򲻷��أ����� update_lower_status_line ����������״̬����ʾ"[��ǰ���] λ�÷Ƿ�"
							  �õ���MRow/MCol�봫��Ĳ�ͬ(��������һ���仯)������ update_lower_status_line ����������״̬����ʾ"[��ǰ���] *��*��"���ٷ���MOUSE_ONLY_MOVED����Щ��Ϸ���غ�Ҫ����ɫ��Ĳ�ͬ��ɫ��ʾ��
		   2������ǰ������������ҵ�ǰ���ָ��ͣ��������Ϸ�����*��*���ϣ��򷵻� CCT_MOUSE_EVENT ��MAction Ϊ MOUSE_LEFT_BUTTON_CLICK, MRow Ϊ�кţ�MCol Ϊ�б�
								  �ҵ�ǰ���ָ��ͣ���ڷǷ����򣨷���Ϸ������Ϸ�����еķָ��ߣ����򲻷��أ����� update_lower_status_line ����������״̬����ʾ"[��ǰ���] λ�÷Ƿ�"
		   3������ǰ�������Ҽ������ж����ָ��ͣ�������Ƿ�Ϸ���ֱ�ӷ��� CCT_MOUSE_EVENT ��MAction Ϊ MOUSE_RIGHT_BUTTON_CLICK, MRow��MColȡ��ǰֵ����Ϊ�������ǵ��Ҽ������Ҫ���꣩
		   4��������¼����ϵ�ĳ������˫���밴��������ֱ�ӷ��� CCT_KEYBOARD_EVENT��KeyCode1/KeyCode2��Ϊ��Ӧ�ļ���ֵ
 ˵    ����ͨ������ cmd_console_tools.cpp �е� read_keyboard_and_mouse ����ʵ��
***************************************************************************/
int gmw_read_keyboard_and_mouse(const CONSOLE_GRAPHICS_INFO* const pCGI, int& MAction, int& MRow, int& MCol, int& KeyCode1, int& KeyCode2, const bool update_lower_status_line)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	KeyCode2 = 0;
	cct_enable_mouse();
	cct_setcursor(3);
	int ret, x, y,action;
	while (1)
	{
		int this_row = -1, this_col = -1;
		ret = cct_read_keyboard_and_mouse(x, y, action, KeyCode1, KeyCode2);
		if (ret == CCT_KEYBOARD_EVENT)
		{
			cct_disable_mouse();
			return CCT_KEYBOARD_EVENT;
		}
		else if(ret== CCT_MOUSE_EVENT)
		{			
			//�ж�����
			for(int i=0;i<pCGI->row_num;i++)				
				if (pCGI->extern_up_lines + pCGI->top_status_line + pCGI->draw_frame_with_col_no + 1 + i * pCGI->CFI.block_high + i * pCGI->CFI.separator<y+1 && pCGI->extern_up_lines + pCGI->top_status_line + pCGI->draw_frame_with_col_no + 1 + (i + 1) * pCGI->CFI.block_high + (i + 1) * pCGI->CFI.separator>y+1)
				{
					this_row = i;
					break;
				}
			for (int j = 0; j < pCGI->col_num; j++)
				if (pCGI->extern_left_cols + pCGI->draw_frame_with_row_no*2 + 2 + j * pCGI->CFI.block_width + j * pCGI->CFI.separator*2<x+1 && pCGI->extern_left_cols + pCGI->draw_frame_with_row_no*2 + 2 +(j + 1) * pCGI->CFI.block_width + (j + 1) * pCGI->CFI.separator*2>x+1)
				{
					this_col = j;	
					break;
				}			
			//�жϰ���
			switch (action)
			{
			case  MOUSE_LEFT_BUTTON_CLICK:
				if (this_row != -1 && this_col != -1)
				{
					MAction = action;
					MRow = this_row;
					MCol = this_col;
					return CCT_MOUSE_EVENT;
				}
				else
				{
					if (update_lower_status_line)
						gmw_status_line(pCGI, 1, "[��ǰ���] λ�÷Ƿ�   ");
					continue;
				}
				break;
			case MOUSE_RIGHT_BUTTON_CLICK:
				MAction = action;
				MRow = this_row==-1? MRow:this_row;
				MCol = this_col==-1?MCol:this_col;
				return CCT_MOUSE_EVENT;
				break;				
			}
			if (this_row == -1 || this_col == -1)
			{
				if (update_lower_status_line)
					gmw_status_line(pCGI, 1, "[��ǰ���] λ�÷Ƿ�    ");
			}
			else if (this_row == MRow && this_col == MCol)
				;
			else
			{
				MAction = MOUSE_ONLY_MOVED;
				MRow = this_row;
				MCol = this_col;
				char temp[20];
				sprintf(temp, "[��ǰ���] %c��%d��  ", (char)(MRow + 'A'), MCol);
				gmw_status_line(pCGI, LOWER_STATUS_LINE, temp);
				return CCT_MOUSE_EVENT;
			}
			
		}
	}
		
	return 0; //�˾�ɸ�����Ҫ�޸�
}
