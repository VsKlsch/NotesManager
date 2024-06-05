#include <vector>

#include <private/include/HMACMD5.hpp>

#include <cryptlib.h>
#include <hmac.h>

namespace NotesManager::Repository::HMAC{
    HMACMD5::HMACMD5()= default;

    std::vector<uint8_t> HMACMD5::SignData(const std::vector<uint8_t>& data, const std::vector<uint8_t>& key) const{
        std::vector<uint8_t> sign;

        return sign;
    }
}
