#include <vector>
#include <cstring>

#include "../../include/Repo/Signers.hpp"

#include <cryptopp/cryptlib.h>
#include <cryptopp/hmac.h>
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include <cryptopp/md5.h>
#include <cryptopp/filters.h>

namespace NotesManager::Repository{
    std::vector<uint8_t> HMACMD5::Sign(const std::vector<uint8_t>& data, const std::vector<uint8_t> pass) const noexcept(false){
        std::vector<uint8_t> sign;
        CryptoPP::SecByteBlock innerKey(CryptoPP::Weak::MD5::BLOCKSIZE);
        std::size_t bytesToCopy;

        // Init key from password. If key larger than BLOCKSIZE, get only part of key, else fill empty part with zeros
        if(pass.size() < CryptoPP::Weak::MD5::BLOCKSIZE){
            CryptoPP::memset_z(innerKey.data(), 0, innerKey.size());
            bytesToCopy = pass.size();
        }else{
            bytesToCopy = CryptoPP::Weak::MD5::BLOCKSIZE;
        }
        CryptoPP::memcpy_s(innerKey.data(), innerKey.size(), pass.data(), bytesToCopy);

        CryptoPP::HMAC<CryptoPP::Weak::MD5> hmac(innerKey, innerKey.size());

        try{
        // Generate sign
            CryptoPP::VectorSource(data, true, 
                new CryptoPP::HashFilter(hmac,
                    new CryptoPP::VectorSink(sign)    
                )
            );
        }catch(const CryptoPP::Exception& e){

        }

        return sign;
    }
}