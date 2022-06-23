/* ÷Ï‘Ûø≠ 2051995 º√√¿ */
#include <Windows.h>
#include <cmath>
#include "../include/cmd_hdc_tools.h"

#define PI 3.14159


static void draw_begin(const int base_x, const int base_y)
{
    hdc_rectangle(base_x + 0, base_y + 0, 600, 600, 0, 1, 2, RGB(255, 204, 0));
}

static void draw_finish(const int base_x, const int base_y)
{
    hdc_rectangle(base_x + 0, base_y + 601, 600, 100, 0, true, 2, RGB(192, 192, 192));
}

static void draw_TOTO_eye(const int X, const int Y)
{
    hdc_circle(X, Y, 65, true, 2, RGB(0, 0, 0));
    hdc_circle(X, Y, 55, true, 2, RGB(255, 255, 255));
    hdc_circle(X, Y, 10, true, 2, RGB(0, 0, 0));
}

static void draw_flower(const int X, const int Y, const int radius)
{
    const int N = 6;
    for (int i = 0, a = 0, da = 360 / N, x, y; i < N; i++, a += da) {
        x = X + int(cos(a * PI / 180) * radius / 4);
        y = Y + int(sin(a * PI / 180) * radius / 4);
        hdc_ellipse(x, y, radius * 3 / 4, radius * 1 / 2, a, true, 2, RGB(0, 0, 0));
    }
    for (int i = 0, a = 0, da = 360 / N, x, y; i < N; i++, a += da) {
        x = X + int(cos(a * PI / 180) * radius / 4);
        y = Y + int(sin(a * PI / 180) * radius / 4);
        hdc_ellipse(x, y, radius / 2, radius * 2 / 7, a, true, 2, RGB(241, 80, 51));
    }
    hdc_circle(X, Y, max(radius / 4, 2), true, 2, RGB(231, 182, 1));
}

static void draw_BOBO(const int base_x, const int base_y)
{
    //÷·∂‘≥∆µƒ

    //∂˙
    hdc_circle(base_x + 140, base_y + 340, 53, true, 2, RGB(0, 0, 0));    //◊Û∂˙
    hdc_circle(base_x + 460, base_y + 340, 53, true, 2, RGB(0, 0, 0));    //”“∂˙

    //300,455£¨¡≥
    hdc_ellipse(base_x + 300, base_y + 455, 234, 140, 0, true, 1, RGB(0, 0, 0));
    hdc_ellipse(base_x + 300, base_y + 470, 215, 145, 0, true, 1, RGB(248, 245, 240));
    //hdc_sector(base_x + 300, base_y + 390, 225, 120, 240, true, 2, RGB(248, 245, 240));

    hdc_triangle(base_x + 0, base_y + 600, base_x + 50, base_y + 480, base_x + 200, base_y + 600, true, 2, RGB(0, 0, 0));
    hdc_triangle(base_x + 600, base_y + 600, base_x + 550, base_y + 480, base_x + 400, base_y + 600, true, 2, RGB(0, 0, 0));

    hdc_triangle(base_x + 150, base_y + 557, base_x + 450, base_y + 557, base_x + 300, base_y + 685, true, 2, RGB(248, 245, 240));

    hdc_triangle(base_x + 50, base_y + 480, base_x + 70, base_y + 432, base_x + 85, base_y + 510, true, 2, RGB(0, 0, 0));
    hdc_triangle(base_x + 550, base_y + 480, base_x + 530, base_y + 432, base_x + 515, base_y + 510, true, 2, RGB(0, 0, 0));

    //—€
    hdc_rectangle(base_x + 205, base_y + 370, 55, 9, 0, true, 2, RGB(0, 0, 0));
    hdc_circle(base_x + 205, base_y + 375, 4, true, 2, RGB(0, 0, 0));
    hdc_circle(base_x + 260, base_y + 375, 4, true, 2, RGB(0, 0, 0));

    hdc_rectangle(base_x + 340, base_y + 370, 55, 9, 0, true, 2, RGB(0, 0, 0));
    hdc_circle(base_x + 340, base_y + 375, 4, true, 2, RGB(0, 0, 0));
    hdc_circle(base_x + 395, base_y + 375, 4, true, 2, RGB(0, 0, 0));

    //◊Ï
    hdc_ellipse(base_x + 300, base_y + 420, 27, 55, 0, true, 2, RGB(0, 0, 0));
    hdc_ellipse(base_x + 300, base_y + 426, 15, 35, 0, true, 2, RGB(245, 65, 95));
    hdc_rectangle(base_x + 277, base_y + 417, 46, 9, 0, true, 2, RGB(0, 0, 0));
    hdc_rectangle(base_x + 270, base_y + 360, 60, 56, 0, true, 2, RGB(248, 245, 240));

    //æ∆Œ—
    hdc_circle(base_x + 180, base_y + 403, 13, true, 2, RGB(245, 65, 95));
    hdc_circle(base_x + 420, base_y + 403, 13, true, 2, RGB(245, 65, 95));
}

static void draw_TOTO(const int base_x, const int base_y)
{

    //π⁄
    for (int i = 3; i <= 20; i += 3) {
        hdc_arc(base_x + 491, base_y + 220, 115 + i, 260, 335 - i, 5, RGB(241, 80, 51));
    }
    for (int i = 7; i <= 30; i += 3) {
        hdc_arc(base_x + 407, base_y + 212, 105 - i, -18, 24 - i, 10, RGB(241, 80, 51));
    }
    for (int i = 5; i <= 80; i += 3) {
        hdc_arc(base_x + 396, base_y + 178, 113 - i, 310, 345, 10, RGB(241, 80, 51));
    }
    for (int i = 5; i <= 130; i += 3) {
        hdc_arc(base_x + 408, base_y + 194, 170 - i, 250, 316, 10, RGB(241, 80, 51));
    }
    //hdc_circle(300, 226, 5, true, 2, RGB(0, 0, 0));
    hdc_circle(base_x + 440, base_y + 115, 5, true, 2, RGB(0, 0, 0));
    hdc_circle(base_x + 382, base_y + 111, 5, true, 2, RGB(0, 0, 0));
    hdc_circle(base_x + 370, base_y + 68, 5, true, 2, RGB(0, 0, 0));
    hdc_circle(base_x + 311, base_y + 100, 5, true, 2, RGB(0, 0, 0));
    hdc_circle(base_x + 293, base_y + 70, 5, true, 2, RGB(0, 0, 0));
    //
    hdc_arc(base_x + 491, base_y + 220, 115, 260, 335, 10, RGB(0, 0, 0));
    hdc_arc(base_x + 407, base_y + 212, 105, -13, 19, 10, RGB(0, 0, 0));
    hdc_line(base_x + 382, base_y + 113, base_x + 370, base_y + 65, 10, RGB(0, 0, 0));
    hdc_arc(base_x + 396, base_y + 178, 113, 313, 347, 10, RGB(0, 0, 0));
    hdc_line(base_x + 311, base_y + 100, base_x + 293, base_y + 70, 10, RGB(0, 0, 0));
    hdc_arc(base_x + 408, base_y + 194, 172, 250, 318, 10, RGB(0, 0, 0));


    //◊Ï
    hdc_triangle(base_x + 200, base_y + 350, base_x + 280, base_y + 350, base_x + 245, base_y + 290, true, 1, RGB(0, 0, 0));
    hdc_triangle(base_x + 267, base_y + 350, base_x + 300, base_y + 392, base_x + 372, base_y + 296, true, 1, RGB(0, 0, 0));
    hdc_triangle(base_x + 221, base_y + 340, base_x + 325, base_y + 340, base_x + 300, base_y + 220, true, 1, RGB(233, 180, 2));
    hdc_sector(base_x + 300, base_y + 375, 120, -37, 37, true, 2, RGB(233, 180, 2));


    //∫˙
    hdc_ellipse(base_x + 367, base_y + 330, 28, 26, 30, true, 2, RGB(0, 0, 0));
    hdc_ellipse(base_x + 367, base_y + 330, 17, 15, 30, true, 2, RGB(229, 78, 7));


    //—€
    draw_TOTO_eye(base_x + 240, base_y + 250);
    draw_TOTO_eye(base_x + 360, base_y + 250);

    //ª®
    draw_flower(base_x + 220, base_y + 161, 40);
}

static void draw_logo(const int base_x, const int base_y)
{
    //√‘ƒ„BOBO
    hdc_sector(base_x + 300, base_y + 538, 16, -90, 90,false, 2, RGB(0, 0, 0));
    hdc_sector(base_x + 290, base_y + 527, 5, 210, 70, true, 1, RGB(0, 0, 0));
    hdc_sector(base_x + 312, base_y + 527, 5, -60, 150, true, 1, RGB(0, 0, 0));
    hdc_point(base_x + 296, base_y + 532,4, RGB(0, 0, 0));
    hdc_point(base_x + 305, base_y + 532,4, RGB(0, 0, 0));
    //hdc_circle(294, 530, 2, true, 2, RGB(0, 0, 0));
    //hdc_circle(306, 530, 2, true, 2, RGB(0, 0));

    //ª®
    hdc_line(base_x + 300, base_y + 522, base_x + 300, base_y + 515, 2, RGB(0, 0, 0));
    draw_flower(base_x + 300, base_y + 515, 6);
}

/* ¿œ ¶µ„∆¿£∫∑÷∫Ø ˝°¢º”◊¢ Õ£¨∫√∆¿ */
void hdc_draw_cartoon_2051995(const int base_x, const int base_y)
{
    hdc_cls();

    int b_x = base_x - 400, b_y = base_y - 400;

    draw_begin(b_x, b_y);

    draw_BOBO(b_x, b_y);

    draw_TOTO(b_x, b_y);

    draw_logo(b_x, b_y);

    draw_finish(b_x, b_y);
}