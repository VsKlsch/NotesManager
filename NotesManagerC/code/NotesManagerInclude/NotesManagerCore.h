#pragma once

#ifdef __cplusplus
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <cwchar>
extern "C"{
#else
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <wchar.h>
#endif

    enum CryptoAlgorithm{
        NO_ALGO,
        XOR
    };

    typedef struct NotesManagerStr NotesManagerAPI;

    NotesManagerAPI* NotesManagerAPI_Init();

    void NotesManagerAPI_Destroy(NotesManagerAPI*);

    typedef struct CryptedNoteStr CryptedNote;
    typedef struct DecryptedNoteStr DecryptedNote;

    uint32_t CryptedNote_GetID(CryptedNote*);
    DecryptedNote* CryptedNote_Decrypt(CryptedNote*, const wchar_t* password);
    void CryptedNote_Destroy(CryptedNote*);

    DecryptedNote* DecryptedNote_Init();
    uint32_t DecryptedNote_GetID(DecryptedNote*);
    uint32_t DecryptedNote_GetDataSize(DecryptedNote*);
    const wchar_t* DecryptedNote_GetData(DecryptedNote*);
    uint32_t DecryptedNote_GetTitleSize(DecryptedNote*);
    const wchar_t* DecryptedNote_GetTitle(DecryptedNote*);
    void DecryptedNote_SetTitle(DecryptedNote*, wchar_t*);
    void DecryptedNote_SetData(DecryptedNote*, wchar_t*);
    void DecryptedNote_Destroy(DecryptedNote*);

    CryptedNote** NotesManagerAPI_GetAllNotes(NotesManagerAPI*, uint32_t* cntNotes);
    CryptedNote* NotesManagerAPI_GetNoteById(NotesManagerAPI*, uint32_t id);
    void NotesManagerAPI_UpdateNote(NotesManagerAPI*, uint32_t id, DecryptedNote*, enum CryptoAlgorithm, wchar_t*);
    void NotesManagerAPI_DeleteNote(NotesManagerAPI*, uint32_t id);
    void NotesManagerAPI_InsertNote(NotesManagerAPI*, DecryptedNote*, enum CryptoAlgorithm, wchar_t*);

    void NotesManagerAPI_FreeNotesArray(CryptedNote**, uint32_t cntNotes);

    const char* GetLastError();

#ifdef __cplusplus
}
#endif