/* 2152611 ×ÞÁ¼Ë³ ÐÅ02 */
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<iomanip>
#include<fstream>
#include<string.h>
#include<conio.h>
#include<io.h>
#include<Windows.h>
#include "../include/cmd_console_tools.h"
using namespace std;

void menu_b1(char *b);

void fun1(int sudoku[9][9], int fix_num[9][9], int identical[3][9],int *time,struct step Steps[],char select);
void search_files(char select, char choose[20]);
void open_files(int sudoku[9][9], int fix_num[9][9], int identical[3][9], char select, char choose[20], bool& if_in_suc);
void putin_num(int sudoku[9][9], int fix_num[9][9], int* time, struct step Steps[],char select);
void print_pic(int sudoku[9][9], int fix_num[9][9], int identical[3][9], char select);
void print_cell(int sudoku[9][9], step Steps[], int* time, int choose, int fix_num[9][9]);
bool if_identical(int sudoku[9][9], int identical[3][9], bool p=1);
bool if_end(int sudoku[9][9], int identical[3][9]);
void continu(char select);
bool AI(int n, int sudoku[9][9], bool& succ, int fix_num[9][9], int identical[3][9], char select);