#pragma once

#include <filesystem>

#include "../Usecases/Database.hpp"

#include <sqlite3.h>

namespace NotesManager::Repository{
    /*!
        \brief SQLite implementation of IDatabase 
    */
    class SQLiteRepository : public Usecases::IDatabase{
    public:
        explicit SQLiteRepository(const std::filesystem::path& dbPath);

        virtual ~SQLiteRepository();

        virtual std::vector<Usecases::NoteDTO> getAllNotes() const;
        virtual std::optional<Usecases::NoteDTO> getNoteById(uint32_t id) const;
        virtual void insertNote(const Usecases::NoteDTO& note) const;
        virtual void removeNoteById(uint32_t id) const;
        virtual void updateNote(const Usecases::NoteDTO& note) const;
    private:
        sqlite3* DB;
    };
}   