#include <memory>

#include <private/include/Crypter.hpp>

namespace NotesManager::Entity::Crypters{
    NoEncryptionCrypter::NoEncryptionCrypter():Crypter(L"") {

    }

    std::optional<std::vector<uint8_t>> NoEncryptionCrypter::crypt(const std::vector<uint8_t>& data) const{
        return data;
    }

    std::optional<std::vector<uint8_t>> NoEncryptionCrypter::sign(const std::vector<uint8_t>& data) const{
        return std::vector<uint8_t>();
    }
}
