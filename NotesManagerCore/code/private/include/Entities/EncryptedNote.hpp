#pragma once

#include <vector>
#include <cstdint>

#include "Algorithms.hpp"

/*!
 * \namespace NotesManager::Entity
 * \brief Namespace for entity classes and structures

 * Namespace NotesManager::Entity contains basics structures such as Encrypted Note, Note
 * and CryptoALgorithm
*/
namespace NotesManager::Entity{
    /*!
        \brief Struct EncryptedNote describes encrypted data note using encrypted data blob, signature and algorithm struct
    */
    struct EncryptedNote{
        /*!
            \memberof EncryptedNote
            Encrypted data blob
        */
        std::vector<uint8_t> vData;

        /*!
            \memberof EncryptedNote
            Signature data blob
        */
        std::vector<uint8_t> vSign;

        /*!
            \memberof EncryptedNote
            CryptoAlgorith description object
        */
        CryptoAlgorithm algroithm;
    };
}