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

    /*!
        \brief Not full API struct, realized in cpp file
    */
    typedef struct NotesManagerStr NotesManagerAPI;

    /*!
        \brief Initilize API

        \return Ptr to API struct or NULL if error has occured
    */
    NotesManagerAPI* NotesManagerAPI_Init();

    /*!
        \brief Destroy API object
    */
    void NotesManagerAPI_Destroy(NotesManagerAPI*);

    /*!
        \brief Not fully struct that describes Crypted Note. 

        \param ptrNote Pointer to API
    */
    typedef struct CryptedNoteStr CryptedNote;

    /*!
        \brief Not fully struct that describes Decrypted Note. 
    */
    typedef struct DecryptedNoteStr DecryptedNote;

    /*!
        \brief Crypted Note API. ID Getter

        \param ptrNote Ptr to Crypted Note structure

        \return ID or 0 if error has occured
    */
    uint32_t CryptedNote_GetID(CryptedNote*);

    /*!
        \brief Crypted Note API. Decrypt function.
        \param ptrNote Ptr to Crypted Note structure
        \param password Pointer to wide-char c-style string

        \return Pointer to Decrypted Note or NULL if error has occured
    */
    DecryptedNote* CryptedNote_Decrypt(CryptedNote*, const wchar_t* password);

    /*!
        \brief Crypted Note API. Destroy function

        \param ptrNote Pointer to Crypted Note struct
    */
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