#include "../include/CryptoAlgorithmException.hpp"

namespace NotesManager{
    CryptoAlgorithmException::CryptoAlgorithmException(const std::string& msg) : msg(msg) {}

    const char* CryptoAlgorithmException::what() const noexcept{
        return this->msg.c_str();
    }
}