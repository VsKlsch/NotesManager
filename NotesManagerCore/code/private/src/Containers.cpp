#include <memory>
#include <private/include/Containers.hpp>


namespace NotesManager::Entity::Containers{

    using namespace NotesManager;
    using Note = Entity::Note;
    
    NotEncryptedNote::NotEncryptedNote(const std::vector<uint8_t>& data): EncryptedNote(data, std::vector<uint8_t>()) {}

    NotEncryptedNote::NotEncryptedNote(std::vector<uint8_t>&& data): EncryptedNote(data, std::vector<uint8_t>()) {}

    std::optional<Note> NotEncryptedNote::decrypt(const std::wstring& pass) const {
        return Note::Deserialize(this->vEncryptedData);
    }
}
