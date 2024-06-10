#pragma once

#include "../Usecases/Signer.hpp"

namespace NotesManager::Repository{
    class HMACMD5 : public Usecases::Signer{
    public:
        virtual std::vector<uint8_t> Sign(const std::vector<uint8_t>& data, const std::vector<uint8_t> pass) const noexcept(false);
    };
}