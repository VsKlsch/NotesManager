#include <memory>
#include <cstring>
#include <concepts>
#include <cstring>

#include <private/include/Containers.hpp>
#include <private/include/Crypter.hpp>
#include <private/include/DatabaseRepo.hpp>
#include <private/include/NotesManagerEntity.hpp>
#include <private/include/SQLiteDatabaseRepo.hpp>
#include <private/include/HMACMD5.hpp>

#include <public/include/Algorithms.hpp>
#include <public/include/NotesManager.h>


using namespace NotesManager;
using IDatabase = Repository::IDatabase;
using DatabaseImpl = Repository::SQLite::SQLiteRepository;
using DatabaseException = Repository::DatabaseException;
using NoteDTO = Repository::NoteDTO;

static std::optional<std::unique_ptr<Entity::Crypter>> BuildCrypterByAlgo(CryptoAlgorithm alg, std::wstring& password){
    switch(alg){
        case NO_ALGO:
            return std::make_unique<Entity::Crypters::NoEncryptionCrypter>();
    }
    return std::nullopt;
}

template<typename T>
concept ByteVector = std::same_as<T, std::vector<uint8_t>>;


template<ByteVector Vec>
static std::optional<std::unique_ptr<Entity::EncryptedNote>> BuildEncryptedNoteByAlgo(const std::string& algo, const Vec& data, const Vec& sign){
    if(algo == NO_ALGO_STR){
        return std::make_unique<Entity::Containers::NotEncryptedNote>(data);
    }
    return std::nullopt;
}

static std::string Alg2Str(CryptoAlgorithm alg){
    switch(alg){
        case NO_ALGO:
            return NO_ALGO_STR;
    }
    return "";
}

extern "C"{
    typedef struct NotesManagerStr{
        std::unique_ptr<IDatabase> database;
    } NotesManagerAPI;

    static char _last_error[1024] = {0,};

    const char* GetLastError(){
        return _last_error;
    }

    NotesManagerAPI* NotesManagerAPI_Init(){
        NotesManagerAPI* api = new NotesManagerAPI;
        try{
            api->database = std::make_unique<DatabaseImpl>("notes.db");
        }catch(DatabaseException& e){
            std::strcpy(_last_error, e.what());
            return NULL;
        }
        return api;
    }

    void NotesManagerAPI_Destroy(NotesManagerAPI* api){
        if(api != NULL)
            delete api;
    }

    typedef struct CryptedNoteStr{
        uint32_t id;
        std::unique_ptr<Entity::EncryptedNote> note;
    } CryptedNote;

    typedef struct DecryptedNoteStr{
        uint32_t id;
        std::unique_ptr<Entity::Note> note;
    } DecryptedNote;

    uint32_t CryptedNote_GetID(CryptedNote* note){
        if(note != NULL){
            return note->id;
        }
        return 0;
    }

    uint32_t DecryptedNote_GetID(DecryptedNote* note){
        if(note != NULL){
            return note->id;
        }
        return 0;
    }

    DecryptedNote* DecryptedNote_Init(){
        DecryptedNote* outNote = new DecryptedNote;
        outNote->note = std::make_unique<Entity::Note>();
        return outNote;
    }

    DecryptedNote* CryptedNote_Decrypt(CryptedNote* cNote, const wchar_t* password){
        if(cNote == NULL || password == NULL)
            return NULL;
        auto decryptedNote = cNote->note->decrypt(std::wstring(password));
        if(decryptedNote.has_value()){
            DecryptedNote* out = new DecryptedNote;
            out->note = std::make_unique<Entity::Note>(std::move(decryptedNote.value()));
            out->id = cNote->id;
            return out;
        }
        return NULL;
    }

    void CryptedNote_Destroy(CryptedNote* cNote){
        if(cNote != NULL)
            delete cNote;
    }

    uint32_t DecryptedNote_GetDataSize(DecryptedNote* note){
        if(note == NULL)
            return 0;
        return note->note->wContent.size();
    }

    const wchar_t* DecryptedNote_GetData(DecryptedNote* note){
        if(note == NULL)
            return NULL;
        return note->note->wContent.c_str();
    }

    uint32_t DecryptedNote_GetTitleSize(DecryptedNote* note){
         if(note == NULL)
            return 0;
        return note->note->wTitle.size();
    }

    const wchar_t* DecryptedNote_GetTitle(DecryptedNote* note){
         if(note == NULL)
            return NULL;
        return note->note->wTitle.c_str();
    }

    void DecryptedNote_SetTitle(DecryptedNote* note, wchar_t* title){
        if(note == NULL || title == NULL)
            return;
        note->note->wTitle = std::wstring(title);
    }

    void DecryptedNote_SetData(DecryptedNote* note, wchar_t* data){
        if(note == NULL || data == NULL)
            return;
        note->note->wContent = std::wstring(data);
    }

    void DecryptedNote_Destroy(DecryptedNote* note){
        if(note != NULL)
            delete note;
    }

    CryptedNote** NotesManagerAPI_GetAllNotes(NotesManagerAPI* api, uint32_t* cntNotes){
        CryptedNote** out = NULL;
        if(api != NULL && cntNotes != NULL){
            auto notes = api->database->getAllNotes();
            if (notes.size()>0){
                uint32_t index = 0;
                out = new CryptedNote*[notes.size()];
                for(auto& cryptedNote : notes){
                    out[index] = new CryptedNote;
                    std::string& algName = cryptedNote.algorithmName;
                    std::vector<uint8_t>& data = cryptedNote.data;
                    std::vector<uint8_t>& sign = cryptedNote.sign;
                    auto note = BuildEncryptedNoteByAlgo(algName, data, sign);
                    if (note.has_value()){
                        auto& val = note.value();
                        out[index]->id = cryptedNote.noteId;
                        out[index]->note = std::move(*note);
                    }
                    ++index;
                }
            }
            *cntNotes = notes.size();
        }
        return out;
    }
    
    CryptedNote* NotesManagerAPI_GetNoteById(NotesManagerAPI* api, uint32_t id){
        CryptedNote* out = NULL;
        if(api != NULL){
            auto note = api->database->getNoteById(id);
            if(note.has_value()){
                auto& cryptedNote = note.value();
                std::string& algName = cryptedNote.algorithmName;
                std::vector<uint8_t>& data = cryptedNote.data;
                std::vector<uint8_t>& sign = cryptedNote.sign;
                auto cryptedNoteObj = BuildEncryptedNoteByAlgo(algName, data, sign);
                if(cryptedNoteObj.has_value()){
                    out = new CryptedNote;
                    auto& val = cryptedNoteObj.value();
                    out->id = cryptedNote.noteId;
                    out->note = std::move(*cryptedNoteObj);
                }
            }
        }
        return out;
    }

    static std::optional<NoteDTO> BuildDTO(uint32_t id, DecryptedNote* note, CryptoAlgorithm algo, wchar_t* passwordRaw){
        std::optional<NoteDTO> out = std::nullopt;
        if(note != NULL && passwordRaw!=NULL){
            std::string algoString = Alg2Str(algo);
            std::wstring password(passwordRaw);
            auto crypterOpt = BuildCrypterByAlgo(algo, password);
            if(crypterOpt.has_value()){
                auto& crypter = crypterOpt.value();
                std::vector<uint8_t> data = Entity::Note::Serialize(*(note->note.get()));
                auto cryptedDataOpt = crypter->crypt(data);
                if(cryptedDataOpt.has_value()){
                    auto signOpt = crypter->sign(data);
                    if(signOpt.has_value()){
                        out = NoteDTO{
                            id,
                            algoString,
                            cryptedDataOpt.value(),
                            signOpt.value()
                        };
                    }
                }else{
                    std::strcpy(_last_error, "Bad password");
                }
            }
        }
        return out;
    }

    void NotesManagerAPI_UpdateNote(NotesManagerAPI* api, uint32_t id, DecryptedNote* note, CryptoAlgorithm algo, wchar_t* passwordRaw){
        if(api != NULL && note != NULL && passwordRaw!=NULL){
            auto noteDTOOpt = BuildDTO(id, note, algo, passwordRaw);
            if(noteDTOOpt.has_value()){
                api->database->updateNote(*noteDTOOpt);
            }
        }
    }

    void NotesManagerAPI_DeleteNote(NotesManagerAPI* api, uint32_t id){
        if(api != NULL){
            api->database->removeNoteById(id);
        }
    }

    void NotesManagerAPI_InsertNote(NotesManagerAPI* api, DecryptedNote* note, CryptoAlgorithm algo, wchar_t* passwordRaw){
         if(api != NULL && note != NULL && passwordRaw!=NULL){
            auto noteDTOOpt = BuildDTO(0, note, algo, passwordRaw);
            if(noteDTOOpt.has_value()){
                api->database->insertNote(*noteDTOOpt);
            }
        }
    }

    void NotesManagerAPI_FreeNotesArray(CryptedNote** notes, uint32_t cntNotes){
        if(notes != NULL){
            for(int i =0; i<cntNotes; ++i)
                delete notes[i];
            delete[] notes;
        }
    }
}
