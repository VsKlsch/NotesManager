#pragma once

#include <concepts>
#include <memory>

#include "../Entities/EncryptedNote.hpp"
#include "../Entities/Note.hpp"
#include "../CryptoAlgorithmException.hpp"
#include "../Utils.hpp"
#include "CryptoAlgorithm.hpp"

namespace NotesManager::Usecases {

    class Crypter{
    public:
        explicit Crypter(std::shared_ptr<ICryptoAlgorithm> alg);

        NotesManager::Entity::EncryptedNote Crypt(const Entity::Note& note, const std::wstring& pass) const noexcept(false);

        NotesManager::Entity::Note Decrypt(const Entity::EncryptedNote& encNote, const std::wstring& pass) const noexcept(false);
        
    private:
        std::shared_ptr<ICryptoAlgorithm> cryptoAlgorithmImpl;
    };
} // namespace NotesManager::Usecases 