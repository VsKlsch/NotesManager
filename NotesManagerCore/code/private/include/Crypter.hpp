#pragma once

#include <private/include/NotesManagerEntity.hpp>

namespace NotesManager::Entity::Crypters{

    using Crypter = NotesManager::Entity::Crypter;

    class NoEncryptionCrypter : public Crypter{
    public:
        NoEncryptionCrypter();
        virtual std::optional<std::vector<uint8_t>> crypt(const std::vector<uint8_t>& data) const override;
        virtual std::optional<std::vector<uint8_t>> sign(const std::vector<uint8_t>& data) const override;
    };

    class XorCypter: public Crypter{
    public:
        XorCypter();
        virtual std::optional<std::vector<uint8_t>> crypt(const std::vector<uint8_t>& data) const override;
        virtual std::optional<std::vector<uint8_t>> sign(const std::vector<uint8_t>& data) const override;
    };
}
