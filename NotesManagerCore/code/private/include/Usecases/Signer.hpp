#pragma once

#include <vector>
#include <cstdint>
#include <concepts>

namespace NotesManager::Usecases{

    class Signer{
    public:
        virtual std::vector<uint8_t> Sign(const std::vector<uint8_t>& data, const std::vector<uint8_t> pass) const noexcept(false) =0;
    };

    template <typename ClassImpl>
    concept SignAlgorithmImplementation = std::derived_from<ClassImpl, Signer>;
}