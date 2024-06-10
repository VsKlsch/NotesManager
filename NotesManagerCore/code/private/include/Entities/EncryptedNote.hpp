#pragma once

#include <vector>
#include <cstdint>

#include "Algorithms.hpp"

namespace NotesManager::Entity{
    struct EncryptedNote{
        std::vector<uint8_t> vData;
        std::vector<uint8_t> vSign;
        CryptoAlgorithm algroithm;
    };
}