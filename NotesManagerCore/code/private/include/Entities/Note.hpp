#pragma once

#include <vector>
#include <string>

#include "Algorithms.hpp"

namespace NotesManager::Entity{
    struct Note{
        std::wstring wsTitle;
        std::wstring wsData;
        CryptoAlgorithm algorithm;
        
        Note() = default;
        Note(const std::vector<uint8_t>&  serializedData, CryptoAlgorithm alg) noexcept(false);

        std::vector<uint8_t> Serialize() const;
    };
}