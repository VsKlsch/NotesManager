#pragma once

#include <string>
#include <cstdint>

#include "../CryptoAlgorithmException.hpp"

namespace NotesManager::Entity{
    /*!
        \brief Class-Wrapper for inner enum class for used crypto algorithms in library

        \todo Add more crypto algorithms

        Nowaday that class can describe No Algo and Xor crypto algorithms.
    */
    class CryptoAlgorithm{
    public:
        /*!
            \brief Enum class for algorithm types

            Enum describes all algorithms that can be used from library
        */
        enum class CryptoAlgorithmValue{
            NoCrypto,
            Xor
        };

        /*!
            \brief Standart constructor

            \warning Do not use it constructor directly
        */
        constexpr CryptoAlgorithm () = default;

        /*!
            \brief Constructor from enum value

            \param enumVal - value of inner enum class

            Wrapper-object constructor from enum variable
        */
        constexpr explicit CryptoAlgorithm (CryptoAlgorithmValue enumVal): value(enumVal) {}
        

        /*!
            \brief Constructor from string representation

            \warning If no exists algorithm represented by strPresentation param then throws CryptoAlgorithmException

            \param strPresentation - String representation of algorithm

            Wrapper-object constructor from string representation of crypto algorithm
        */
        constexpr explicit CryptoAlgorithm (const std::string& strPresentation) noexcept(false) {
            if(strPresentation == "NO_ALGO"){
                this->value = CryptoAlgorithm::CryptoAlgorithmValue::NoCrypto;
            }else if (strPresentation == "XOR"){
                this->value = CryptoAlgorithm::CryptoAlgorithmValue::Xor;
            }else{
                throw CryptoAlgorithmException("Bad Crypto ALgorithm string representation");
            }
        }

        /*!
            \brief Cast function from CryptoAlgorithm object to string
        */
        constexpr std::string to_string() const noexcept{
            switch(this->value){
            case CryptoAlgorithm::CryptoAlgorithmValue::NoCrypto:
                return "NO_ALGO";
            case CryptoAlgorithm::CryptoAlgorithmValue::Xor:
                return "XOR";
            }
        }

        /*!
            \brief Inner enum value getter
        */
        CryptoAlgorithmValue Value() const{
            return value;
        }
    private:
        /*!
            \memberof CryptoAlgorithm
            Enum value describes cryptography algorithm
        */
        CryptoAlgorithmValue value;
    };
}