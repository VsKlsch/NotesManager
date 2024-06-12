#pragma once

#include "../Usecases/Signer.hpp"

namespace NotesManager::Repository{
    
    /*!
        \brief Implementation of Signer interface for HMAC-MD5 algorithm as signer algorithm
    */
    class HMACMD5 : public Usecases::Signer{
    public:
        virtual std::vector<uint8_t> Sign(const std::vector<uint8_t>& data, const std::vector<uint8_t> pass) const noexcept(false);
    };
}