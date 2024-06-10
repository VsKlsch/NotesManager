#include <cstddef>

#include "../../include/Repo/CryptoAlgorithms.hpp"
#include <new>

namespace NotesManager::Repository{
    bool BasicCryptoAlgorithm::Verify(const std::vector<uint8_t>& sign1, const std::vector<uint8_t>& sign2) const noexcept{
        if(sign1.size() != sign2.size()){
            return false;
        }

        for(std::size_t i = 0; i<sign1.size(); ++i ){
            if(sign1[i] != sign2[i])
                return false;
        }
        return true;
    }
}