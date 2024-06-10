#include<string>

#include "../include/Usecases/Database.hpp"

namespace NotesManager::Usecases{
    DatabaseException::DatabaseException(std::string msg):msg(msg) {}
    
    const char* DatabaseException::what() const noexcept{
        return this->msg.data();
    }
}