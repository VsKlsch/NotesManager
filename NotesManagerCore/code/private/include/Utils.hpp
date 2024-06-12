#pragma once

#include <vector>
#include <string>
#include <cstdint>
#include <concepts>


/*!
    \namespace NotesManager::Utils
    \brief Namespace with utility classes and functions
*/
namespace NotesManager::Utils{

    template<typename T>
    /*!
        \brief Function for transform string 2 byte vector
        \todo Make more strong algorithm
    */
    std::vector<uint8_t> String2ByteVec(T&& str){
        auto& inStr = std::forward<T>(str);
        return std::vector<uint8_t>(inStr.begin(), inStr.end());
    }
}