#include "../include/Entities/Note.hpp"

#include <exception>
#include <stdexcept>
#include <cstring>

namespace NotesManager::Entity{
    Note::Note(const std::vector<uint8_t>&  serializedData, CryptoAlgorithm alg) noexcept(false) :algorithm(alg){
        if(serializedData.size()<sizeof(uint32_t)*2+sizeof(wchar_t)*2){
            throw std::invalid_argument("Too small serialized data argument");
        }

        const uint8_t* ptr = serializedData.data();
        const uint32_t* ptrSzTitle = reinterpret_cast<const uint32_t*>(ptr);

        ptr += sizeof(uint32_t);
        const wchar_t* ptrTitle = reinterpret_cast<const wchar_t*>(ptr);

        ptr += *ptrSzTitle;
        const uint32_t* ptrSzContent = reinterpret_cast<const uint32_t*>(ptr);
            
        ptr += sizeof(uint32_t);
        const wchar_t* ptrContent = reinterpret_cast<const wchar_t*>(ptr);

        wsTitle = std::wstring(ptrTitle);
        wsData = std::wstring(ptrContent);
    }

    std::vector<uint8_t> Note::Serialize() const{
        std::vector<uint8_t> out;

        uint32_t szTitle = (wsTitle.length()+1)*sizeof(wchar_t);
        uint32_t szContent = (wsData.length()+1)*sizeof(wchar_t);

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
        std::memcpy(ptrTitle, wsTitle.c_str(), szTitle);
        std::memcpy(ptrSzContent, &szContent, sizeof(uint32_t));
        std::memcpy(ptrContent, wsData.c_str(), szContent);

        return out;
    }
}