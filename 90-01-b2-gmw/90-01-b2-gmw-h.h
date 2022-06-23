//2152611 ×ÞÁ¼Ë³ ÐÅ02
#pragma once
#include"../include/cmd_gmw_tools.h"
#include<Windows.h>

#define  ROW   8
#define  COL   10
#define SLEEP  500

bool search_identical(int in[ROW][COL], int mto10[ROW][COL], const BLOCK_DISPLAY_INFO bdi_normal[], const BLOCK_DISPLAY_INFO bdi_related[], const BLOCK_DISPLAY_INFO bdi_selected[]);
void draw_identical(CONSOLE_GRAPHICS_INFO Mto10_CGI, int in[ROW][COL], int mto10[ROW][COL], const BLOCK_DISPLAY_INFO bdi_normal[], const BLOCK_DISPLAY_INFO bdi_related[], const BLOCK_DISPLAY_INFO bdi_selected[]);
void add_score(int& sim_s, int& score, int a[ROW][COL], int in[ROW][COL], int x, int y);
int simple_score(int a[ROW][COL], int in[ROW][COL], int x, int y);
int rand_num(int max);