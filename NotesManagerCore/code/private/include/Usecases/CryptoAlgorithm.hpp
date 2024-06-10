#pragma once

#include <vector>
#include <cstdint>

#include "../Entities/Algorithms.hpp"

namespace NotesManager::Usecases{

    class ICryptoAlgorithm{
    public:
        virtual std::vector<uint8_t> Crypt(const std::vector<uint8_t>& data, const std::vector<uint8_t>& pass) const noexcept(false) =0;
        virtual std::vector<uint8_t> Decrypt(const std::vector<uint8_t>& data, const std::vector<uint8_t>& pass) const noexcept(false) =0;
        virtual std::vector<uint8_t> Sign(const std::vector<uint8_t>& data, const std::vector<uint8_t>& pass) const noexcept(false) =0;
        virtual bool Verify(const std::vector<uint8_t>& sign1, const std::vector<uint8_t>& sign2) const noexcept =0;
        virtual Entity::CryptoAlgorithm GetAlgorithmType() const noexcept =0;

        virtual ~ICryptoAlgorithm() = default;
    };
}