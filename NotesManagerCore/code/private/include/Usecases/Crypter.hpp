#pragma once

#include <concepts>
#include <memory>

#include "../Entities/EncryptedNote.hpp"
#include "../Entities/Note.hpp"
#include "../CryptoAlgorithmException.hpp"
#include "../Utils.hpp"
#include "CryptoAlgorithm.hpp"

/*!
    \namespace NotesManager::Usecases

    \brief Namespace that contains c++ part classes for main part of software algorithms
*/

namespace NotesManager::Usecases {

    /*!
        \brief Class for crypt, decrypt and sign any data in Usecases.
    */
    class Crypter{
    public:
        /*!
            \brief Main constructor. Build crypter from pointer to algorithm. Allow transformation between Note and EncryptedNote

            \warning Prevent automatic construction from algorithm ptr

            \param alg - Shared Pointer to Cryptographic algorithm implementation
        */
        explicit Crypter(std::shared_ptr<ICryptoAlgorithm> alg);

        /*!
            \brief Function for crypt note with pass

            \param note - Reference to note for crypting
            \param pass - Reference to password stored in wide-char string

            \return EncryptedNote object
        */
        NotesManager::Entity::EncryptedNote Crypt(const Entity::Note& note, const std::wstring& pass) const noexcept(false);

        
        /*!
            \brief Function for decrypt note with pass

            \param encNote - Reference to note for decrypting
            \param pass - Reference to password stored in wide-char string

            \return Note object
        */
        NotesManager::Entity::Note Decrypt(const Entity::EncryptedNote& encNote, const std::wstring& pass) const noexcept(false);
        
    private:
        std::shared_ptr<ICryptoAlgorithm> cryptoAlgorithmImpl;
    };
} // namespace NotesManager::Usecases 