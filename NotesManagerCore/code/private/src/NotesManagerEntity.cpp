#include <cstring>
#include <private/include/NotesManagerEntity.hpp>

namespace NotesManager::Entity{

    std::vector<uint8_t> Note::Serialize(const Note& note){
        std::vector<uint8_t> out;

        // Size = Title len with zero + Content len with zero + sizes
        uint32_t szTitle = (note.wTitle.length()+1)*sizeof(wchar_t);
        uint32_t szContent = (note.wContent.length()+1)*sizeof(wchar_t);

        uint32_t arraySize = szTitle + szContent + sizeof(wchar_t)*2;

        out = std::vector<uint8_t>(arraySize, 0);

        uint8_t* ptr = out.data();      
        uint32_t* ptrSzTitle = reinterpret_cast<uint32_t*>(ptr);

        ptr += sizeof(uint32_t);
        wchar_t* ptrTitle = reinterpret_cast<wchar_t*>(ptr);

        ptr += szTitle;
        uint32_t* ptrSzContent = reinterpret_cast<uint32_t*>(ptr);

        ptr += sizeof(uint32_t);
        wchar_t* ptrContent = reinterpret_cast<wchar_t*>(ptr);

        std::memcpy(ptrSzTitle, &szTitle, sizeof(uint32_t));
        std::memcpy(ptrTitle, note.wTitle.c_str(), szTitle);
        std::memcpy(ptrSzContent, &szContent, sizeof(uint32_t));
        std::memcpy(ptrContent, note.wContent.c_str(), szContent);

        return out;
    }

    Note Note::Deserialize(const std::vector<uint8_t>& rawData){
        Note out;
        if (rawData.size() > (sizeof(uint32_t)*2+sizeof(wchar_t)*2)){
            const uint8_t* ptr = rawData.data();
            const uint32_t* ptrSzTitle = reinterpret_cast<const uint32_t*>(ptr);

            ptr += sizeof(uint32_t);
            const wchar_t* ptrTitle = reinterpret_cast<const wchar_t*>(ptr);

            ptr += *ptrSzTitle;
            const uint32_t* ptrSzContent = reinterpret_cast<const uint32_t*>(ptr);
            
            ptr += sizeof(uint32_t);
            const wchar_t* ptrContent = reinterpret_cast<const wchar_t*>(ptr);

            out.wTitle = std::wstring(ptrTitle);
            out.wContent = std::wstring(ptrContent);
        }
        return out;
    }

    Crypter::~Crypter(){}
    EncryptedNote::~EncryptedNote(){}
}
