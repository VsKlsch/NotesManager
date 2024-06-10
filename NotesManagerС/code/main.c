#include <stdio.h>

#include "Algorithms.h"
#include "NotesManagerCore.h"

int main(){
    NotesManagerAPI* api = NotesManagerAPI_Init();
    if(api != NULL){
        DecryptedNote* note = DecryptedNote_Init();
        CryptedNote** cNote;
        uint32_t notesCount;


        if (note != NULL){
            //DecryptedNote_SetData(note, L"Crypted Data String");
           // DecryptedNote_SetTitle(note, L"Note Title");
            //NotesManagerAPI_InsertNote(api, note, XOR, L"123123");
           // DecryptedNote_Destroy(note);
        }
        cNote = NotesManagerAPI_GetAllNotes(api, &notesCount);
        if(cNote != NULL){
            int i;
            for(i=0; i<notesCount; ++i){
                uint32_t noteId = CryptedNote_GetID(cNote[i]);
                DecryptedNote* note = CryptedNote_Decrypt(cNote[i], L"");
                if(note == NULL){
                    DecryptedNote* tNote;
                    wprintf(L"ID: %d\n<<NOTE ENCRYPTED>>\n", noteId);
                    wprintf(L"Try to decrypt with password 123123\n\n");
                    tNote = CryptedNote_Decrypt(cNote[i], L"123123");
                    if(tNote != NULL){
                        const wchar_t* title = DecryptedNote_GetTitle(tNote);
                        const wchar_t* data = DecryptedNote_GetData(tNote);
                        wprintf(L"ID: %d\nTitle: %ls\nData: %ls\n\n", noteId, title, data);
                        DecryptedNote_Destroy(tNote);
                    }
                }else{
                    const wchar_t* title = DecryptedNote_GetTitle(note);
                    const wchar_t* data = DecryptedNote_GetData(note);
                    wprintf(L"ID: %d\nTitle: %ls\nData: %ls\n\n", noteId, title, data);
                    DecryptedNote_Destroy(note);
                }
            }
            NotesManagerAPI_FreeNotesArray(cNote, notesCount);
        }
        NotesManagerAPI_Destroy(api);
    }
    return 0;
}