#pragma once

#include <string>

/*!
    \namespace NotesManager
    \brief General namespace for all classes, structures and functions of C++ part of Library
*/
namespace NotesManager{
    /*!
        \brief Exception class for cryptographic algorithms
    */
    class CryptoAlgorithmException : public std::exception{
    public:
        CryptoAlgorithmException(const std::string& msg);
        virtual const char* what() const noexcept override ;
    private:
        std::string msg;
    };
}