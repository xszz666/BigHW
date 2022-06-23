/* 朱泽凯 2051995 济美 */

#include "../include/cmd_hdc_tools.h"
#include <conio.h>
#include <cmath>
#include <vector>
#include <cstring>
#include <iostream>
#include <Windows.h>
using namespace std;

static const double Pi = 3.14159;

//流畅组合：（20,40） 折衷组合：（50,50）  清晰组合：（100,80）
static const int A_DIV = 50;    //取样数(越大越密)
static const int B_DIV = 50;    //取样数
static const double DA = 2 * Pi / A_DIV;
static const double DB = 2 * Pi / B_DIV;

static const int a1_DIV = 30;   //转动速率(表示转这么多次到一圈)
static const int a2_DIV = 30;   //转动速率

static const double XMIN = -3.5;
static const double XMAX = 3.5;
static const double YMIN = -3.5;
static const double YMAX = 3.5;
static const int ROW = 400;
static const int COL = 400;
static const int PIXDEP = 512;		//最大颜色深度

struct vector3d {
    double x, y, z;

    vector3d() {}
    vector3d(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}

    /// 旋转, U' :a  , L' : b  (Pi/180 rad)
    vector3d rotate(double a, double b)
    {
        a = a * Pi / 180;
        b = b * Pi / 180;
        static double sa, sb, ca, cb;
        sa = sin(a);
        ca = cos(a);
        sb = sin(b);
        cb = cos(b);
        return vector3d(
            x * (ca)+y * (-sa * cb) + z * (-sa * sb),
            x * (sa)+y * (ca * cb) + z * (ca * sb),
            0 + y * (-sb) + z * (cb)
        );
    }

    /// 甜甜圈该点法向量 
    vector3d normalVector()
    {
        return vector3d(
            x - (x + x) / sqrt(x * x + y * y),
            y - (y + y) / sqrt(x * x + y * y),
            z
        );
    }

    /// 模 
    double norm()
    {
        return sqrt(x * x + y * y + z * z);
    }

    /// cos(夹角) 
    friend double angle(vector3d &P, vector3d &Q)
    {
        return (P.x * Q.x + P.y * Q.y + P.z * Q.z) / (P.norm() + Q.norm());
    }
};


void hdc_draw_Mathematical_curve_2051995()
{
    hdc_cls();
    cct_setcolor();
    cout << "动态甜甜圈，操作说明：a/d/w/s单个方向调整，q/e两个方向同时调整，z/x光源调整，c退出(请先关闭输入法!)" << endl;
    hdc_rectangle(20, 20, COL, ROW, 0, true, 2, RGB(0, 0, 0));

    vector<vector<double>> graph(ROW, vector<double>(COL));		        //新页面累计光点
    vector<vector<int>> pixs(ROW, vector<int>(COL));					//旧页面
    vector<vector3d> pointSamples;


    // 取点样 
    for (int i = 0; i < A_DIV; i++) {
        for (int j = 0; j < B_DIV; j++) {
            pointSamples.emplace_back(vector3d(cos(i * DA) * (2 + cos(j * DB)), sin(i * DA) * (2 + cos(j * DB)), sin(j * DB)));
        }
    }

    int opr;
    int a1 = 0, a2 = 0;     //甜甜圈旋转
    vector3d tmp, tmpN, light(0, 0, 1);
    int indexCol, indexRow;
    double ang;


    while (1) {
        // 渲染
        for (int i = 0; i < ROW; i++)
            for (int j = 0; j < COL; j++)
                graph[i][j] = 0;
        for (vector3d &I : pointSamples) {
            tmp = I.rotate(a1 * 360 / a1_DIV, a2 * 360 / a2_DIV);
            tmpN = I.normalVector().rotate(a1 * 360 / a1_DIV, a2 * 360 / a2_DIV);
            if (tmp.x >= XMIN && tmp.x <= XMAX)
                indexCol = int((tmp.x - XMIN) / ((XMAX - XMIN) / COL));
            else continue;

            if (tmp.y >= YMIN && tmp.y <= YMAX)
                indexRow = int((tmp.y - YMIN) / ((YMAX - YMIN) / ROW));
            else
                continue;

            if (tmpN.z > 0) {
                ang = angle(tmpN, light);
                graph[indexRow][indexCol] += max(ang, 0.0);
            }
        }


        // 打印 
        for (int i = 0, color; i < ROW; i++) {
            for (int j = 0; j < COL; j++) {
                color = min(PIXDEP - 1, int(graph[i][j] / (1.3 / PIXDEP)));
                if (color != pixs[i][j]) {
                    hdc_point(j + 20, i + 20, 1, RGB(color, color, color));
                    pixs[i][j] = color;
                }
            }
        }

        //光线方向示意
        hdc_rectangle(20+COL, 20, 100, 100, 0, true, 2, RGB(50, 50, 50));
#define STX (20+COL+50)
#define STY (20+50)
        if (light.z > 0) {
            hdc_point(int(STX - light.x * 45), int(STY - light.y * 45),8, RGB(500, 500, 500));
            hdc_point(STX, STY, 4, RGB(200, 50, 0));
            hdc_line(int(STX - light.x * 45), int(STY - light.y * 45), STX, STY, 3, RGB(200, 50, 0));
        }
        else {
            hdc_point(STX, STY, 4, RGB(30, 100, 200));
            hdc_line(int(STX - light.x * 45), int(STY - light.y * 45), STX, STY, 3, RGB(30, 100, 200));
            hdc_point(int(STX - light.x * 45), int(STY - light.y * 45), 8, RGB(500, 500, 500));
        }
#undef STX
#undef STY

        // 输入 
        opr = _getch();
        if (opr == 'd')
            a1 = (a1 + 1) % a1_DIV;
        else if (opr == 'a')
            a1 = (a1 - 1 + a1_DIV) % a1_DIV;
        else if (opr == 'w')
            a2 = (a2 + 1) % a2_DIV;
        else if (opr == 's')
            a2 = (a2 - 1 + a2_DIV) % a2_DIV;
        else if (opr == 'q')
            a1 = (a1 - 1 + a1_DIV) % a1_DIV, a2 = (a2 + 1) % a2_DIV;
        else if (opr == 'e')
            a1 = (a1 + 1) % a1_DIV, a2 = (a2 - 1 + a2_DIV) % a2_DIV;
        else if (opr == 'z')
            light = light.rotate(0, 10);
        else if (opr == 'x')
            light = light.rotate(10, 0);
        else if (opr == 'c')
            break;

        //break;
    }
}