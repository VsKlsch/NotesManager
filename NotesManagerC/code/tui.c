#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include "tui.h"

Window* Window_Init(wchar_t title[256], int x, int y, int width, int height){
    Window* out = (Window*)malloc(sizeof(Window));
    if(out != NULL){
        out -> x = x;
        out -> y = y;
        out -> width = width;
        out -> height = height;
        out->wBackground = NULL;
        out->wTitle = NULL;
        out->iTitleLen = wcslen(title);
        wcscpy(out->cTitle, title);
    }
    return out;
}

void Window_Clear(Window* pWin){
    int i,j;
    if(pWin == NULL)
        return;
    for(i = pWin->x; i<pWin->x+pWin->width; ++i){
        for(j = pWin->y; j<pWin->y+pWin->height; ++j){
            mvaddch(j, i, ' ');
        }
    }
    wrefresh(pWin->wBackground);
}

void Window_Draw(Window* pWin){
    if(pWin == NULL)
        return;

    if(pWin->wBackground)
        delwin(pWin->wBackground);

    if(pWin->wTitle)
        delwin(pWin->wTitle);

    pWin -> wBackground = newwin(pWin->height, pWin->width, pWin->y, pWin ->x);
    box(pWin->wBackground, 0, 0);
    wbkgd(pWin->wBackground, COLOR_PAIR(BACKGROUND_COLOR_PAIR));

    pWin -> wTitle = newwin(1, pWin->width-2, pWin->y+1, pWin->x+1);
    box(pWin->wBackground, 0, 0);
    wbkgd(pWin->wTitle, COLOR_PAIR(TITLE_COLOR_PAIR));
    refresh();

    attron(COLOR_PAIR(TITLE_COLOR_PAIR));
    if(pWin->iTitleLen > pWin->width-2){
        wchar_t title[256];
        wcscpy(title, pWin->cTitle);
        title[pWin->width-2] = 0;
        mvprintw(pWin->y+1, pWin->x+1, "%ls", title);
    }else{
        int startX = pWin->x+1;
        int offset = pWin->width/2 - pWin->iTitleLen/2;
        startX += offset;
        mvprintw(pWin->y+1, startX, "%ls", pWin->cTitle);
    }
    attroff(COLOR_PAIR(TITLE_COLOR_PAIR));
    wrefresh(pWin->wBackground);
    wrefresh(pWin->wTitle);
}

void Window_MoveAndResize(Window* pWin, int x, int y, int width, int height){
    if(pWin){
        pWin->x = x;
        pWin->y = y;
        pWin->width = width;
        pWin->height = height;
    }
}

void Window_Destroy(Window* pWin){
    if(pWin){
        if(pWin->wBackground){
            delwin(pWin->wBackground);
        }
        if(pWin->wTitle){
            delwin(pWin->wTitle);
        }
        free(pWin);
    }
}