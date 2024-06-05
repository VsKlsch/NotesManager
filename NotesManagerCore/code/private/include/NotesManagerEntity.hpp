// File contains declaration of basics core classes of Note manager such as Note, IEncryptedNote and EncryptedNote
#pragma once

#include <concepts>
#include <string>
#include <optional>
#include <vector>
#include <cstdint>

namespace NotesManager::Entity{
    // Basic Note class for simple note data storing
    struct Note{
        std::wstring wTitle;
        std::wstring wContent;

        static std::vector<uint8_t> Serialize(const Note& note);
        static Note Deserialize(const std::vector<uint8_t>& rawData);
    };

    // Interface for encrypted notes
    class IEncrypted{
    public:
        virtual std::optional<Note> decrypt(const std::wstring& pass) const  =0;
    };

    template<typename VecType>
    concept ByteVector = std::convertible_to<VecType, std::vector<uint8_t>>;

    // Basic class for all notes in cryptocontainers
    class EncryptedNote : public IEncrypted{
    public:
        template<ByteVector V1, ByteVector V2>
        EncryptedNote(V1&& encryptedData, V2&& sign): 
            vEncryptedData(std::forward<V1>(encryptedData)),
            vSign(std::forward<V2>(sign))
        {

        }
        virtual std::optional<Note> decrypt(const std::wstring& pass) const override =0;
        virtual ~EncryptedNote();
    protected:
        std::vector<uint8_t> vEncryptedData;
        std::vector<uint8_t> vSign;
    };

    // Interface for crypters
    class ICrypter{
    public:
        virtual std::optional<std::vector<uint8_t>> crypt(const std::vector<uint8_t>& data) const =0;
        virtual std::optional<std::vector<uint8_t>> sign(const std::vector<uint8_t>& data) const =0;
    };

    template<typename StringType>
    concept WideString = std::convertible_to<StringType, std::wstring>;

    // Basic class for all crypters
    class Crypter : public ICrypter{
    public:
        template<WideString T>
        explicit Crypter(T&& pass): wPassword(std::forward<T>(pass)) {

        }
        virtual std::optional<std::vector<uint8_t>> crypt(const std::vector<uint8_t>& data) const override =0;
        virtual std::optional<std::vector<uint8_t>> sign(const std::vector<uint8_t>& data) const override =0;
        virtual ~Crypter();
    protected:
        std::wstring wPassword;
    };
}
