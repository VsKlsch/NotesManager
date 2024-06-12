#pragma once

#include <vector>
#include <cstdint>
#include <concepts>

namespace NotesManager::Usecases{
    /*!
        \brief Interface class for all signers
    */
    class Signer{
    public:
        /*!
            \brief Function for generate signature by data and password

            \param data - Signed data
            \param pass - Password for signature
        */
        virtual std::vector<uint8_t> Sign(const std::vector<uint8_t>& data, const std::vector<uint8_t> pass) const noexcept(false) =0;
    };

    template <typename ClassImpl>
    /*!
        \brief Concept for all signers
    */
    concept SignAlgorithmImplementation = std::derived_from<ClassImpl, Signer>;
}