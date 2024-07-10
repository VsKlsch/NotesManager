#pragma once

#include <ncurses.h>

#define DEFAULT_COLROS 1
#define BACKGROUND_COLOR_PAIR 2
#define TITLE_COLOR_PAIR 3

typedef struct WindowStr{
    WINDOW* wBackground;
    WINDOW* wTitle;
    int x;
    int y;
    int width;
    int height;
    wchar_t cTitle[256];
    int iTitleLen;
} Window;

Window* Window_Init(wchar_t title[256], int x, int y, int width, int height);
void Window_Draw(Window*);
void Window_Clear(Window*);
void Window_MoveAndResize(Window*, int x, int y, int width, int height);
void Window_Destroy(Window*);