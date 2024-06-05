#pragma once

#include <filesystem>

#include <private/include/DatabaseRepo.hpp>
#include <private/include/Crypter.hpp>

#include <sqlite3.h>

namespace NotesManager::Repository::SQLite{

    using IDatabase = NotesManager::Repository::IDatabase;

    class SQLiteRepository : public IDatabase{
    public:
        explicit SQLiteRepository(const std::filesystem::path& dbPath);

        virtual ~SQLiteRepository();

        virtual std::vector<NoteDTO> getAllNotes() const;
        virtual std::optional<NoteDTO> getNoteById(uint32_t id) const;
        virtual void insertNote(const NoteDTO& note) const;
        virtual void removeNoteById(uint32_t id) const;
        virtual void updateNote(const NoteDTO& note) const;
    private:
        sqlite3* DB;
    };
}
