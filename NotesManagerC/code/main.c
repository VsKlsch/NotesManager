#include <stdio.h>

#include "Algorithms.h"
#include "NotesManagerCore.h"

int main(){
    NotesManagerAPI* api = NotesManagerAPI_Init();
    {
        DecryptedNote* dnote = DecryptedNote_Init();
        if(dnote){
            DecryptedNote_SetData(dnote, L"Data String");
            DecryptedNote_SetTitle(dnote, L"Note Title");
            NotesManagerAPI_InsertNote(api, dnote, NO_ALGO, L"");
            DecryptedNote_Destroy(dnote);
        }
    }
    {
        DecryptedNote* dnote = DecryptedNote_Init();
        if(dnote){
            DecryptedNote_SetData(dnote, L"Crypted Data String");
            DecryptedNote_SetTitle(dnote, L"Note Title");
            NotesManagerAPI_InsertNote(api, dnote, XOR, L"123123");
            DecryptedNote_Destroy(dnote);
        }
    }

    if(api != NULL){
        while(1){
            uint32_t id;
            CryptedNote* cNote;
            DecryptedNote* note;

            wprintf(L"Enter node id or 0 to exit: ");
            wscanf(L"%d", &id);

            if(id == 0){
                break;
            }

            cNote = NotesManagerAPI_GetNoteById(api, id);
            if(cNote == NULL){
                wprintf(L"Note not found\n");
            }else{
                note = CryptedNote_Decrypt(cNote, L"");
                if(note == NULL){
                    wchar_t pass[1024];
                    wprintf(L"Enter password: ");
                    wscanf(L"%1023ls", pass);
                    wprintf(L"\n");
                    DecryptedNote* dnote = CryptedNote_Decrypt(cNote, pass);
                    if(dnote == NULL){
                        wprintf(L"Bad password\n");
                    }else{
                        const wchar_t* title = DecryptedNote_GetTitle(dnote);
                        const wchar_t* data = DecryptedNote_GetData(dnote);
                        wprintf(L"ID: %d\nTitle: %ls\nData: %ls\n\n", id, title, data);
                        DecryptedNote_Destroy(dnote);
                    }
                    wprintf(L"\n");
                }else{
                    const wchar_t* title = DecryptedNote_GetTitle(note);
                    const wchar_t* data = DecryptedNote_GetData(note);
                    wprintf(L"ID: %d\nTitle: %ls\nData: %ls\n\n", id, title, data);
                    DecryptedNote_Destroy(note);
                }
                CryptedNote_Destroy(cNote);
            }
        }
        printf("Exit\n");
        NotesManagerAPI_Destroy(api);

    }
    return 0;
}