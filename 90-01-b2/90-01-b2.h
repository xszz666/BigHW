//2152611 ����˳ ��02
#pragma once
void input(int& r, int& c, int& obj, int select);
void first(int a[8][10], int row, int column);
void output(int row, int column, int a[8][10]);
void search(char s1, int s2, int row, int column, int a[8][10], char in[8][10]);
void outputchar(int row, int column, char in[8][10]);
void outputcolour(int row, int column, int a[8][10], char in[8][10]);
void search_digui(int a[8][10], char in[8][10], char s1, int s2, int column, int row);
void merge(int a[8][10], char in[8][10], int row, int column, char s1, int s2);
void mis_zero(int a[8][10], int row, int column, bool if_draw);
void outputmiszero(int row, int column, int a[8][10], char in[8][10]);
void putin(int row, int column, int a[8][10], char in[8][10], int max);
int simple_score(int a[8][10], char in[8][10], int column, int row, char s1, int s2);
void add_score(int& sim_s, int& score, int& obj, int a[8][10], char in[8][10], int column, int row, char s1, int s2);
void max_(int a[8][10], int row, int column, int& max);
bool end(int a[8][10], int row, int column);
void background(int a[8][10], int row, int column);
void element(int a[8][10], int row, int column);
void _background(int a[8][10], int row, int column, bool if_sleep = 1);
void _element(int a[8][10], int row, int column, bool if_sleep = 1);
void mouse_keyboard(int row, int column, int a[8][10], char in[8][10], char& s1, int& s2, int select);
void draw_element(int i, int j, int a[8][10], int c);
void continu();
void stop(int aa = 0);
int can_(int row, int column, char s1, int s2, char in[8][10]);
void draw_null(int j, int i);
void draw_merge(int a[8][10], int row, int column);
void re_write(int row);
int is_net(char select);
int rand_num(int max);
int give_rand(int max);
bool end(int a[8][10], int row, int column);