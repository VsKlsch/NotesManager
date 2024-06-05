#include <string>

#include <private/include/DatabaseRepo.hpp>

namespace NotesManager::Repository{
    DatabaseException::DatabaseException(std::string msg): msg(msg) {}

    const char* NotesManager::Repository::DatabaseException::what() const throw()
{
        return this->msg.data();
    }
}
