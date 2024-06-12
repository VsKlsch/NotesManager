#pragma once

#include <cstdint>
#include <vector>
#include <optional>
#include <string>

namespace NotesManager::Usecases{

    /*!
        \brief Basic model for database
    */
    struct NoteDTO{
        /*!
            \memberof NoteDTO
            \brief Database id of note
        */
        uint32_t noteId;

        /*!
            \memberof NoteDTO
            \brief String representation of cryptoalgorithm
        */
        std::string algorithmName;

        /*!
            \memberof NoteDTO
            \brief Byte blob of encrypted data
        */
        std::vector<uint8_t> data;

        /*!
            \memberof NoteDTO
            \brief Byte blob of signature
        */
        std::vector<uint8_t> sign;
    };

    /*!
        \brief Basic interface for all databases implementations
    */
    class IDatabase{
    public:
        /*!
            \brief Pure virtual function for selecting all notes from databse

            \return Vector of all NoteDTO
        */
        virtual std::vector<NoteDTO> getAllNotes() const =0;

        /*!
            \brief Pure virtual function for get certain note by its id

            \param id Note database identificator
            \return NoteDTO or Nullopt if not exists
        */
        virtual std::optional<NoteDTO> getNoteById(uint32_t id) const =0;

        /*!
            \brief Pure virtual function for inserting note by

            \param note Referenece to NoteDTO with data for inserting
        */
        virtual void insertNote(const NoteDTO& note) const =0;

        /*!
            \brief Pure virtual function for removing note by id

            \param id Note database identificator
        */
        virtual void removeNoteById(uint32_t id) const =0;

        /*!
            \brief Pure virtual function for update note in database

            \param note Reference to NoteDTO with updated info
        */
        virtual void updateNote(const NoteDTO& note) const =0;

        /*!
            \brief Pure virtual destructor
        */
        virtual ~IDatabase() = default;
    };

    /*!
        \brief Exception for database functions
    */
    class DatabaseException : public std::exception{
    public:
        DatabaseException(std::string msg);
        virtual const char* what() const throw() override ;
    private:
        std::string msg;
    };
}