#pragma once

#include <vector>
#include <string>
#include <cstdint>
#include <concepts>

namespace NotesManager::Utils{

    template<typename T>
    std::vector<uint8_t> String2ByteVec(T&& str){
        auto& inStr = std::forward<T>(str);
        return std::vector<uint8_t>(inStr.begin(), inStr.end());
    }
}