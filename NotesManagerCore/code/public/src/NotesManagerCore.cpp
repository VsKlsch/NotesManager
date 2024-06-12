#include <memory>
#include <cstddef>
#include <optional>

#include "../include/NotesManagerCore.h"
#include "../../private/include/Entities/Algorithms.hpp"
#include "../../private/include/Entities/EncryptedNote.hpp"
#include "../../private/include/Entities/Note.hpp"
#include "../../private/include/Usecases/Database.hpp"
#include "../../private/include/Usecases/Signer.hpp"
#include "../../private/include/Usecases/Crypter.hpp"
#include "../../private/include/Repo/SQLite3.hpp"
#include "../../private/include/Repo/CryptoAlgorithms.hpp"
#include "../../private/include/Repo/Signers.hpp"
#include "../../private/include/CryptoAlgorithmException.hpp"
#include "../include/Algorithms.h"


using namespace NotesManager;

static const char* GetNameByAlgo(CryptoAlgorithm alg){
    switch(alg){
        case NO_ALGO:
            return NMANAGER_ALGO_NAME_NO_CRYPTO;
        case XOR:
            return NMANAGER_ALGO_NAME_XOR;
    }
    return "";
}

static std::optional<std::shared_ptr<Usecases::ICryptoAlgorithm>> GetCryptoAlgorithmByAlgo( Entity::CryptoAlgorithm alg){
    switch(alg.Value()){
        case Entity::CryptoAlgorithm::CryptoAlgorithmValue::NoCrypto:
            return std::make_shared<Repository::NoCryptoAlgorithm>();
        case Entity::CryptoAlgorithm::CryptoAlgorithmValue::Xor:
            return std::make_shared<Repository::XorCryptoAlgorithm<Repository::HMACMD5>>();
        default:
            return std::nullopt;
    }
}

static std::optional<std::shared_ptr<Usecases::ICryptoAlgorithm>> GetCryptoAlgorithmByName(const char* algName){
    auto alg = Entity::CryptoAlgorithm(algName);
    return GetCryptoAlgorithmByAlgo(alg);
}

extern "C"{

    static char _last_error[1024] = {0,};

    typedef struct NotesManagerStr{
        std::unique_ptr<Usecases::IDatabase> db;
    } NotesManagerAPI;

    NotesManagerAPI* NotesManagerAPI_Init(){
        NotesManagerAPI* api = new NotesManagerAPI;
        try{
            api->db = std::make_unique<Repository::SQLiteRepository>("notes.db");
        }catch(const Usecases::DatabaseException& e ){
            delete api;
            return nullptr;
        }
        return api;
    }

    void NotesManagerAPI_Destroy(NotesManagerAPI* api){
        if(api != nullptr){
            api->db.reset();
            delete api;
        }
    }

    
    typedef struct CryptedNoteStr{
        uint32_t id;
        std::unique_ptr<Entity::EncryptedNote> note;
    } CryptedNote;

    typedef struct DecryptedNoteStr{
        uint32_t id;
        std::unique_ptr<Entity::Note> note;
    } DecryptedNote;

    uint32_t CryptedNote_GetID(CryptedNote* ptrNote){
        if(ptrNote == nullptr){
            return 0;
        }
        return ptrNote->id;
    }

    DecryptedNote* CryptedNote_Decrypt(CryptedNote* ptrNote, const wchar_t* password){
        DecryptedNote* out = nullptr;
        if(ptrNote == nullptr || password == nullptr){
            return nullptr;
        }
        auto& algorithm = ptrNote->note->algroithm;
        auto cryptoAlgOpt = GetCryptoAlgorithmByAlgo(algorithm);
        if(cryptoAlgOpt.has_value()){
            auto& cryptoAlg = cryptoAlgOpt.value();
            Usecases::Crypter crypter(cryptoAlg);
            out = new DecryptedNote;
            out->id = ptrNote->id;
            try{
                out->note = std::make_unique<Entity::Note>(crypter.Decrypt(*ptrNote->note, password));
            }catch(const std::exception& e){
                std::strcpy(_last_error, e.what());
                delete out;
                out = nullptr;
            }
        }
        return out;
    }

    void CryptedNote_Destroy(CryptedNote* ptrNote){
        if(ptrNote != nullptr){
            ptrNote->note.reset();
            delete ptrNote;
        }
    }


    DecryptedNote* DecryptedNote_Init(){
        DecryptedNote* out = new DecryptedNote;
        out -> note = std::make_unique<Entity::Note>();
        return out;
    }

    uint32_t DecryptedNote_GetID(DecryptedNote* ptrNote){
        if(ptrNote == nullptr)
            return 0;
        return ptrNote->id;
    }

    uint32_t DecryptedNote_GetDataSize(DecryptedNote* ptrNote){
        if(ptrNote == nullptr)
            return 0;
        return  ptrNote->note->wsData.size();
    }

    const wchar_t* DecryptedNote_GetData(DecryptedNote* ptrNote){
        if(ptrNote == nullptr)
            return nullptr;
        return ptrNote->note->wsData.data();
    }

    uint32_t DecryptedNote_GetTitleSize(DecryptedNote* ptrNote){
        if(ptrNote == nullptr)
            return 0;
        return ptrNote->note->wsTitle.size();
    }

    const wchar_t* DecryptedNote_GetTitle(DecryptedNote* ptrNote){
        if(ptrNote == nullptr)
            return nullptr;
        return ptrNote->note->wsTitle.data();        
    }

    void DecryptedNote_SetTitle(DecryptedNote* ptrNote, wchar_t* ptrTitle){
        if(ptrNote == nullptr)
            return;
        ptrNote->note->wsTitle = std::wstring(ptrTitle);
    }

    void DecryptedNote_SetData(DecryptedNote* ptrNote, wchar_t* ptrTitle){
        if(ptrNote == nullptr)
            return;
        ptrNote->note->wsData = std::wstring(ptrTitle);
    }

    void DecryptedNote_Destroy(DecryptedNote* ptrNote){
        if(ptrNote != nullptr){
            ptrNote->note.reset();
            delete ptrNote;
        }
    }

    CryptedNote** NotesManagerAPI_GetAllNotes(NotesManagerAPI* api, uint32_t* cntNotes){
        CryptedNote** out = nullptr;
        if(api != nullptr && cntNotes != nullptr){
            auto notes = api->db->getAllNotes();
            if(notes.size() > 0){
                uint32_t index = 0;
                out = new CryptedNote*[notes.size()];
                for(auto& cryptedNote : notes){
                    out[index] = new CryptedNote;
                    std::string& algName = cryptedNote.algorithmName;
                    std::vector<uint8_t>& data = cryptedNote.data;
                    std::vector<uint8_t>& sign = cryptedNote.sign;
                    out[index]->id = cryptedNote.noteId;
                    out[index]->note = std::make_unique<Entity::EncryptedNote>();
                    out[index]->note->vData = data;
                    out[index]->note->vSign = sign;
                    out[index]->note->algroithm = Entity::CryptoAlgorithm(algName);
                    ++index;
                }
            }
            *cntNotes = notes.size(); 
        }
        return out;
    }
     
    CryptedNote* NotesManagerAPI_GetNoteById(NotesManagerAPI* api, uint32_t id){
        CryptedNote* out = nullptr;
        if(api != nullptr){
            auto note = api->db->getNoteById(id);
            if(note.has_value()){
                auto& cryptedNote = note.value();
                std::string& algName = cryptedNote.algorithmName;
                std::vector<uint8_t>& data = cryptedNote.data;
                std::vector<uint8_t>& sign = cryptedNote.sign;
                out = new CryptedNote;
                out->note = std::make_unique<Entity::EncryptedNote>();
                out->id = cryptedNote.noteId;
                out->note->vData = data;
                out->note->vSign = sign;
                out->note->algroithm = Entity::CryptoAlgorithm(algName);
            }
        }
        return out;
    }

    static std::optional<Usecases::NoteDTO> BuildDTO(uint32_t id, DecryptedNote* note, CryptoAlgorithm algo, wchar_t* passwordRaw){
        std::optional<Usecases::NoteDTO> out = std::nullopt;
        if(note != nullptr && passwordRaw!=nullptr){
            std::string algoString = GetNameByAlgo(algo);
            auto algorithmOpt = GetCryptoAlgorithmByName(algoString.data());
            if(algorithmOpt.has_value()){
                auto algorithm = algorithmOpt.value();
                std::wstring password(passwordRaw);
                Usecases::Crypter crypter(algorithm);
                try{
                    auto encNote = crypter.Crypt(*note->note, passwordRaw);
                    Usecases::NoteDTO dto;
                    dto.algorithmName = algorithm->GetAlgorithmType().to_string();
                    dto.data = std::move(encNote.vData);
                    dto.sign = std::move(encNote.vSign);
                    dto.noteId = id;
                    out = std::move(dto);                
                }catch (const std::exception& e){

                }
            }
        }
        return out;
    }

    void NotesManagerAPI_UpdateNote(NotesManagerAPI* api, uint32_t id, DecryptedNote* note, enum CryptoAlgorithm algo, wchar_t* passwordRaw){
        if(api != nullptr && note != nullptr && passwordRaw != nullptr){
            auto dtoOpt = BuildDTO(id, note, algo, passwordRaw);
            if(dtoOpt.has_value()){
                auto &val = dtoOpt.value();
                api->db->updateNote(val);
            }
        }
    }

    void NotesManagerAPI_DeleteNote(NotesManagerAPI* api, uint32_t id){
        if(api != nullptr){
            api->db->removeNoteById(id);
        }
    }
    
    void NotesManagerAPI_InsertNote(NotesManagerAPI* api, DecryptedNote* note, enum CryptoAlgorithm algo, wchar_t* passwordRaw){
        if(api != nullptr && note != nullptr && passwordRaw != nullptr){
            auto dtoOpt = BuildDTO(0, note, algo, passwordRaw);
            if(dtoOpt.has_value()){
                auto &val = dtoOpt.value();
                api->db->insertNote(val);
            }
        }
    }

    void NotesManagerAPI_FreeNotesArray(CryptedNote** notesList, uint32_t cntNotes){
        if(notesList != nullptr){
            for(int i =0; i<cntNotes; ++i){
                if(notesList[i] != nullptr)
                    delete notesList[i];
            }
            delete[] notesList;
        }
    }

    const char* GetLastError(){
        return _last_error;
    }
}