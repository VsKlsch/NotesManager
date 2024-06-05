#pragma once

#include <vector>
#include <map>

#include <private/include/NotesManagerEntity.hpp>

namespace NotesManager::Entity::Containers{

    using namespace NotesManager;

    using EncryptedNote = Entity::EncryptedNote;

    class NotEncryptedNote : public EncryptedNote{
    public:
        explicit NotEncryptedNote(const std::vector<uint8_t>& data);
        explicit NotEncryptedNote(std::vector<uint8_t>&& data);
        virtual std::optional<Note> decrypt(const std::wstring& pass) const override;
    };
}
