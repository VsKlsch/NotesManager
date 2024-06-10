#include "../../include/Entities/Algorithms.hpp"
#include "../../include/Repo/CryptoAlgorithms.hpp"

namespace NotesManager::Repository{
    std::vector<uint8_t> NoCryptoAlgorithm::Crypt(const std::vector<uint8_t>& data, const std::vector<uint8_t>& pass) const noexcept(false){
        return data;
    }

    std::vector<uint8_t> NoCryptoAlgorithm::Decrypt(const std::vector<uint8_t>& data, const std::vector<uint8_t>& pass) const noexcept(false){
        return data;
    }

    std::vector<uint8_t> NoCryptoAlgorithm::Sign(const std::vector<uint8_t>& data, const std::vector<uint8_t>& pass) const noexcept(false){
        return std::vector<uint8_t>();
    }

    Entity::CryptoAlgorithm NoCryptoAlgorithm::GetAlgorithmType() const noexcept{
        return Entity::CryptoAlgorithm(Entity::CryptoAlgorithm::CryptoAlgorithmValue::NoCrypto);
    }
}