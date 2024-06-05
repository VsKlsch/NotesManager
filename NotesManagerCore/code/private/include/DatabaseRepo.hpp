#pragma once

#include <string>
#include <vector>
#include <cstdint>
#include <optional>

namespace NotesManager::Repository{
    struct NoteDTO{
        uint32_t noteId;
        std::string algorithmName;
        std::vector<uint8_t> data;
        std::vector<uint8_t> sign;
    };

    class IDatabase{
    public:
        virtual std::vector<NoteDTO> getAllNotes() const =0;
        virtual std::optional<NoteDTO> getNoteById(uint32_t id) const =0;
        virtual void insertNote(const NoteDTO& note) const =0;
        virtual void removeNoteById(uint32_t id) const =0;
        virtual void updateNote(const NoteDTO& note) const =0;
        virtual ~IDatabase() {}
    };

    class DatabaseException : public std::exception{
    public:
        DatabaseException(std::string msg);
        virtual const char* what() const throw() override ;
    private:
        std::string msg;
    };
}
