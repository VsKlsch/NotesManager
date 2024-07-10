#include <stdlib.h>
#include <ncurses.h>
#include "tui.h"
#include "NotesManagerInclude/NotesManagerCore.h"

int main(int argc, char **argv)
{
    int user_key;
     //Start curses
    initscr( );
    //No buffer for getch()
    cbreak( );
    raw( );
    nonl( );
    //no echo while entering from keyboard
    noecho( );
    //no text cursor
    curs_set(0);
    start_color();
    //Enable special keys
    keypad(stdscr, TRUE);

    init_pair(DEFAULT_COLROS, COLOR_WHITE, COLOR_BLACK);
    init_pair(BACKGROUND_COLOR_PAIR, COLOR_WHITE, COLOR_BLACK);
    init_pair(TITLE_COLOR_PAIR, COLOR_GREEN, COLOR_RED);

    int width = 20;
    int height = 10;

    NotesManagerAPI* api = NotesManagerAPI_Init();
    if (api != NULL){
        uint32_t uintNotesCount;
        CryptedNote** notes = NotesManagerAPI_GetAllNotes(api, &uintNotesCount);
        if(notes != NULL && uintNotesCount>0){
            uint32_t i;
            Window** windows = (Window**)malloc(sizeof(Window*)*uintNotesCount);
            for(i=0; i<uintNotesCount; ++i){ 
                DecryptedNote *dNote = CryptedNote_Decrypt(notes[i], L"");
                if(dNote != NULL){
                    windows[i] = Window_Init(DecryptedNote_GetTitle(dNote), 2, 4*i, 25, 3);
                    DecryptedNote_Destroy(dNote);
                }else{
                    windows[i] = Window_Init(L"Crypted Note", 2, 4*i, 25, 3);
                }
                Window_Draw(windows[i]);
            }
            do
            {
                switch ( user_key )
                {
                case KEY_RESIZE:
                    for(i=0; i<uintNotesCount; ++i){
                        Window_Draw(windows[i]);
                    }
                    break;
                default:

                break;
                }
                doupdate( );
            }
            while (( user_key = getch( )) != KEY_F(12));
            for(i=0; i<uintNotesCount; ++i){
                Window_Destroy(windows[i]);
            }
            NotesManagerAPI_FreeNotesArray(notes, uintNotesCount);
        }else{
            mvaddstr(5, 5, "No have notes in db or load error");
            while (( user_key = getch( )) != KEY_F(12));
        }

        NotesManagerAPI_Destroy(api);
    }
    endwin();
    return 0;
}
