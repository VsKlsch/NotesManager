#pragma once

#include <vector>
#include <string>

#include "Algorithms.hpp"

namespace NotesManager::Entity{
    /*!
        \brief Struct Note describes decrypted data note
    */
    struct Note{
        /*!
            \memberof Note
            \brief Note title
        */
        std::wstring wsTitle;

        /*!
            \memberof Note
            \brief Note data
        */
        std::wstring wsData;

        /*!
            \memberof Note
            \brief Note algorithm
        */
        CryptoAlgorithm algorithm;
        
        /*!
            \memberof Note
            \brief Default constructor
        */
        Note() = default;

        /*!
            \brief Deserialization constructor

            \param serializedData Data serialized to byte blob
            \param alg Algorithm description object
        */
        Note(const std::vector<uint8_t>&  serializedData, CryptoAlgorithm alg) noexcept(false);

        /*!
            \brief Serialization function

            Serialize Note structure to byte blob
        */
        std::vector<uint8_t> Serialize() const;
    };
}