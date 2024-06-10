#pragma once

#include <string>

namespace NotesManager{
    class CryptoAlgorithmException : public std::exception{
    public:
        CryptoAlgorithmException(const std::string& msg);
        virtual const char* what() const noexcept override ;
    private:
        std::string msg;
    };
}