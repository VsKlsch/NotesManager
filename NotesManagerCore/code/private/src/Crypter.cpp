
#include "../include/Usecases/Crypter.hpp"

namespace NotesManager::Usecases{

    Crypter::Crypter(std::shared_ptr<ICryptoAlgorithm> alg) {
        this->cryptoAlgorithmImpl =  alg;
    }

    NotesManager::Entity::EncryptedNote Crypter::Crypt(const Entity::Note& note, const std::wstring& pass) const noexcept(false){
        NotesManager::Entity::EncryptedNote encNote;
        std::vector<uint8_t> vPass = Utils::String2ByteVec(pass);
        std::vector<uint8_t> vData = note.Serialize();
        encNote.vData = cryptoAlgorithmImpl->Crypt(vData, vPass);
        encNote.vSign = cryptoAlgorithmImpl->Sign(encNote.vData, vPass);
        encNote.algroithm = cryptoAlgorithmImpl->GetAlgorithmType();
        return encNote;
    }

    NotesManager::Entity::Note Crypter::Decrypt(const Entity::EncryptedNote& encNote, const std::wstring& pass) const noexcept(false){
        std::vector<uint8_t> vPass = Utils::String2ByteVec(pass);
        std::vector<uint8_t> sign = cryptoAlgorithmImpl->Sign(encNote.vData, vPass);
        if(!cryptoAlgorithmImpl->Verify(sign, encNote.vSign)){
            throw std::invalid_argument("Bad password");
        }
        std::vector<uint8_t> serializedNote = cryptoAlgorithmImpl->Decrypt(encNote.vData, vPass);
        return Entity::Note(serializedNote, cryptoAlgorithmImpl->GetAlgorithmType());
    }
}