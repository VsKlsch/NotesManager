#pragma once

#include <vector>
#include <cstdint>

namespace NotesManager::Repository{
    class IHMAC {
    public:
        virtual std::vector<uint8_t> SignData(const std::vector<uint8_t>& data, const std::vector<uint8_t>& key) const =0;
    };
}
