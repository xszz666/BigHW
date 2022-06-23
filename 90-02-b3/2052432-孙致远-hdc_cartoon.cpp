/*2052432 ��12 ����Զ*/
#include <iostream>
#include <Windows.h>
#include <stdio.h>  
#include <stdlib.h>  
#include <conio.h>  
#include <math.h>
#include <time.h>
#include "../include/cmd_hdc_tools.h"
#define COLOR_HEAD RGB(243, 180, 145)
#define COLOR_HEAD_ARC RGB(124, 53, 14)
#define COLOR_EAR RGB(124, 53, 14)
#define COLOR_YELLOW_HEAD RGB(243, 208, 129)
#define COLOR_MOUSE RGB(250,122,177)
#define COLOR_BACKGROUND_UP RGB(140, 141, 135)
void background()
{
	hdc_rectangle(0,0, 800, 600, 0, true, 4, COLOR_BACKGROUND_UP);
}
void head(const int base_x, const int base_y)
{
	hdc_circle(base_x, base_y - 50,180,true,3,COLOR_HEAD);//����Բ
	hdc_circle(base_x - 120, base_y - 180,45, true, 3, COLOR_HEAD);//��߶���
	hdc_arc(base_x, base_y - 50, 180, 245, 150, 8, COLOR_HEAD_ARC);//����ͷ���ϰ벿�ֵĺڱ�
	hdc_circle(base_x + 120, base_y - 180, 40, true, 3, COLOR_HEAD);//�ұߵĶ���
	hdc_arc(base_x - 120, base_y - 180, 45, 220, 54, 8, COLOR_HEAD_ARC);//��߶����ϵĺڱ�
	hdc_arc(base_x + 120, base_y - 180, 40, -65, 170, 10, COLOR_HEAD_ARC);//�ұ߶����ϵĺڱ�
	hdc_sector(base_x - 120, base_y - 180, 25, 220, 45, true, 3, COLOR_EAR);//��ߵ�С����
	hdc_sector(base_x + 110, base_y - 170, 27, -40, 140, true, 3, COLOR_EAR);//�ұߵ�С����
	hdc_circle(base_x - 145, base_y + 55, 45, true, 3, COLOR_HEAD);//��������ӵĵ�һ��СԲ
	hdc_circle(base_x - 130, base_y + 60, 45, true, 3, COLOR_HEAD);//��������ӵĵڶ���СԲ
	hdc_circle(base_x - 115, base_y + 60, 50, true, 3, COLOR_HEAD);//��������ӵĵ�����СԲ
	hdc_circle(base_x - 150, base_y + 55, 40, true, 3, COLOR_YELLOW_HEAD);//��������ӵĻ�ɫСԲ
	hdc_circle(base_x + 70, base_y + 55, 40, true, 3, COLOR_YELLOW_HEAD);//�ұ������ӵĻ�ɫСԲ
	hdc_arc(base_x - 145, base_y + 55,45,190, 345, 8, COLOR_HEAD_ARC);//��������ӵĵ�һ���ڱ�
	hdc_arc(base_x - 125, base_y + 50, 60, 150, 220, 8, COLOR_HEAD_ARC);//��������ӵĵڶ����ڱ�
	hdc_circle(base_x - 90, base_y-15, 20, true, 3, COLOR_HEAD_ARC);//����۾�
	hdc_circle(base_x + 50, base_y - 10, 20, true, 3, COLOR_HEAD_ARC);//�ұ��۾�
	hdc_ellipse(base_x - 18, base_y + 15, 10, 20, 0, true, 2, COLOR_MOUSE);//��ͷ
	hdc_ellipse(base_x - 18, base_y + 15, 10, 20, 0, false, 4, COLOR_HEAD_ARC);//��ͷ�ĺڱ�
	hdc_arc(base_x -30, base_y - 15, 15, 130, 260, 6, COLOR_HEAD_ARC);//������
	hdc_arc(base_x -8, base_y - 15, 15, 130, 260, 6, COLOR_HEAD_ARC);//������
}
void body(int base_x,int base_y)
{
	hdc_rectangle(base_x - 90, base_y + 110, 180, 150, 0, true, 4, COLOR_HEAD);//��������岿��
	hdc_sector(base_x-5, base_y + 190, 120,225,315,true, 4, COLOR_HEAD);//���������䲿��
	hdc_sector(base_x - 5, base_y + 190, 120, 45, 135, true, 4, COLOR_HEAD);//���������䲿��
	hdc_rectangle(base_x-25, base_y + 260, 20, 10, 0, true, 4, COLOR_HEAD);//�����±ߵ���䲿��
	hdc_ellipse(base_x - 55, base_y + 265, 40, 20, 5, true, 2, COLOR_HEAD);//��ߵĽ�
	hdc_ellipse(base_x+40, base_y + 270, 40, 20, 5, true, 2, COLOR_HEAD);//�ұߵĽ�
	hdc_ellipse(base_x - 55, base_y + 265, 40, 20, 5, false, 8, COLOR_HEAD_ARC);//��ߵĽŵ�����
	hdc_ellipse(base_x + 40, base_y + 270, 40, 20, 5, false, 8, COLOR_HEAD_ARC);//�ұߵĽŵ�����
	hdc_arc(base_x - 5, base_y + 190, 120, 225, 315, 8, COLOR_HEAD_ARC);//������ߵĺڱ�
	hdc_arc(base_x - 5, base_y + 190, 120, 45, 135, 8, COLOR_HEAD_ARC);//�����ұߵĺڱ�
	hdc_line(base_x - 25, base_y + 270, base_x+10, base_y + 273, 10, COLOR_HEAD_ARC);//�·��ĺ���
	hdc_rectangle(base_x - 98, base_y + 230, 60, 25, 0, true, 4, COLOR_HEAD);//�·�����������Բ����(���)
	hdc_rectangle(base_x+30, base_y + 230, 50, 40, 0, true, 4, COLOR_HEAD);//�·�����������Բ����(�ұ�)
	hdc_ellipse(base_x - 70, base_y + 190, 40, 30, 60, false, 8, COLOR_HEAD_ARC);//��ߵ���
	hdc_rectangle(base_x - 107, base_y + 140, 60, 30, 0, true, 4, COLOR_HEAD);//��ߵ��ֵ���������
	hdc_ellipse(base_x + 50, base_y + 200, 40, 30, 150, false, 8, COLOR_HEAD_ARC);//�ұߵ���
	hdc_rectangle(base_x + 65, base_y + 135, 90, 30, 60, true, 4, COLOR_HEAD);//��ߵ��ֵ���������
}

/* ��ʦ�������ֺ�������ע�ͣ����� */
void hdc_draw_cartoon_2052432(const int base_x, const int base_y)
{
	hdc_cls();
	background();
	head(base_x, base_y);
	body(base_x, base_y);
}