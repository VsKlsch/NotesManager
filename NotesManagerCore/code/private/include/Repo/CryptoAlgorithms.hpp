#pragma once

#include "../Usecases/Signer.hpp"
#include "../Usecases/CryptoAlgorithm.hpp"

/*!
    \namespace NotesManager::Repository

    \brief Namespace that contains interfaces and object for interaction with external resources in usecases
*/
namespace NotesManager::Repository{

    /*!
        \brief Basic realisation of ICryptoAlgorithm with function Verify for verify signers
    */
    class BasicCryptoAlgorithm : public Usecases::ICryptoAlgorithm{
    public:
        virtual std::vector<uint8_t> Crypt(const std::vector<uint8_t>& data, const std::vector<uint8_t>& pass) const noexcept(false) override =0;
        virtual std::vector<uint8_t> Decrypt(const std::vector<uint8_t>& data, const std::vector<uint8_t>& pass) const noexcept(false) override =0;
        virtual std::vector<uint8_t> Sign(const std::vector<uint8_t>& data, const std::vector<uint8_t>& pass) const noexcept(false) override =0;
        virtual bool Verify(const std::vector<uint8_t>& sign1, const std::vector<uint8_t>& sign2) const noexcept override;
        virtual Entity::CryptoAlgorithm GetAlgorithmType() const noexcept override =0;
   };

    /*!
        \brief Cryptography algorithm implementation without crypt. Crypt and decrypt return its params and password is empty
    */
    class NoCryptoAlgorithm : public BasicCryptoAlgorithm{
    public:
        virtual std::vector<uint8_t> Crypt(const std::vector<uint8_t>& data, const std::vector<uint8_t>& pass) const noexcept(false) override;
        virtual std::vector<uint8_t> Decrypt(const std::vector<uint8_t>& data, const std::vector<uint8_t>& pass) const noexcept(false) override;
        virtual std::vector<uint8_t> Sign(const std::vector<uint8_t>& data, const std::vector<uint8_t>& pass) const noexcept(false) override;
        virtual Entity::CryptoAlgorithm GetAlgorithmType() const noexcept override;
    };


    /*!
        \brief Cryptography algorithm implementation with xor as crypto algorithm.

        \warning Password must be not empty. If password will empty then Crypt, Decrypt and Sign throws CryptoAlgorithmException

        \param SignerAlg - Class that implement Signer interface. Need for Sign function.
    */
    template<Usecases::SignAlgorithmImplementation SignerAlg>
    class XorCryptoAlgorithm : public BasicCryptoAlgorithm{
    public:
        virtual std::vector<uint8_t> Crypt(const std::vector<uint8_t>& data, const std::vector<uint8_t>& pass) const noexcept(false) override{
            if(pass.size() == 0)
                throw CryptoAlgorithmException("Short password");
            std::vector<uint8_t> out;
            std::size_t offPass, offData;
            for(offPass = 0, offData = 0; offData<data.size(); ++offPass, ++offData){
                offPass %= pass.size();
                out.push_back(pass[offPass]^data[offData]);
            }
            return out;
        }

        virtual std::vector<uint8_t> Decrypt(const std::vector<uint8_t>& data, const std::vector<uint8_t>& pass) const noexcept(false) override{
            if(pass.size() == 0)
                throw CryptoAlgorithmException("Short password");
            return this->Crypt(data, pass);
        }

        virtual std::vector<uint8_t> Sign(const std::vector<uint8_t>& data, const std::vector<uint8_t>& pass) const noexcept(false) override{
            if(pass.size() == 0)
                throw CryptoAlgorithmException("Short password");
            return alg.Sign(data, pass);
        }

        virtual Entity::CryptoAlgorithm GetAlgorithmType() const noexcept override{
            return Entity::CryptoAlgorithm(Entity::CryptoAlgorithm::CryptoAlgorithmValue::Xor); 
        }

    private:
        SignerAlg alg;
    };
}