#pragma once

#include <vector>
#include <cstdint>

#include "../Entities/Algorithms.hpp"

namespace NotesManager::Usecases{

    /*!
        \brief General interface for all Cryptography Algorithms realisations
    */
    class ICryptoAlgorithm{
    public:

        /*!
            \brief Pure function for crypt vector with password

            \param data Data for crypt
            \param pass Password for crypt

            \return Crypted data 

            \warning This function may throw exception
        */
        virtual std::vector<uint8_t> Crypt(const std::vector<uint8_t>& data, const std::vector<uint8_t>& pass) const noexcept(false) =0;

        /*!
            \brief Pure function for decrypt vector with password

            \param data Data for decrypt
            \param pass Password for decrypt

            \return Derypted data 

            \warning This function may throw exception if password is incorrect or another error occured
        */
        virtual std::vector<uint8_t> Decrypt(const std::vector<uint8_t>& data, const std::vector<uint8_t>& pass) const noexcept(false) =0;

        /*!
            \brief Pure function for sign vector with password

            \param data Data for sign
            \param pass Password for sign

            \return Signature 

            \warning This function may throw exception if password is incorrect or another error occured
        */
        virtual std::vector<uint8_t> Sign(const std::vector<uint8_t>& data, const std::vector<uint8_t>& pass) const noexcept(false) =0;

        /*!
            \brief Pure function for verification sign

            \param sign1 Signature for comparison
            \param sign2 Signature for comparison

            \return bool result
        */
        virtual bool Verify(const std::vector<uint8_t>& sign1, const std::vector<uint8_t>& sign2) const noexcept =0;

        /*!
            \brief Pure function for return crypto algorithm description

            \return Algorithm description object
        */
        virtual Entity::CryptoAlgorithm GetAlgorithmType() const noexcept =0;

        virtual ~ICryptoAlgorithm() = default;
    };
}