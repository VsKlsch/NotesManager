#pragma once

#include <string>
#include <cstdint>

#include "../CryptoAlgorithmException.hpp"

namespace NotesManager::Entity{
    class CryptoAlgorithm{
    public:
        enum class CryptoAlgorithmValue{
            NoCrypto,
            Xor
        };

        constexpr CryptoAlgorithm () {}

        constexpr explicit CryptoAlgorithm (CryptoAlgorithmValue enumVal): value(enumVal) {}
        
        constexpr explicit CryptoAlgorithm (const std::string& strPresentation) noexcept(false) {
            if(strPresentation == "NO_ALGO"){
                this->value = CryptoAlgorithm::CryptoAlgorithmValue::NoCrypto;
            }else if (strPresentation == "XOR"){
                this->value = CryptoAlgorithm::CryptoAlgorithmValue::Xor;
            }else{
                throw CryptoAlgorithmException("Bad Crypto ALgorithm string representation");
            }
        }

        constexpr std::string to_string() const noexcept{
            switch(this->value){
            case CryptoAlgorithm::CryptoAlgorithmValue::NoCrypto:
                return "NO_ALGO";
            case CryptoAlgorithm::CryptoAlgorithmValue::Xor:
                return "XOR";
            }
        }

        CryptoAlgorithmValue Value() const{
            return value;
        }
    private:
        CryptoAlgorithmValue value;
    };
}