#pragma once

#include <private/include/IHMAC.hpp>

namespace NotesManager::Repository::HMAC{
    using IHMAC = NotesManager::Repository::IHMAC;

    class HMACMD5 : public IHMAC{
    public:
        HMACMD5();
        virtual std::vector< uint8_t > SignData(const std::vector< uint8_t >& data, const std::vector< uint8_t >& key) const override;
    };
}
