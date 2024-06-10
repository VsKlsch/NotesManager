cmake_minimum_required(VERSION 3.20)

project(NotesManagerCore)

SET(LIBRARY_VERSION_MAJOR 0)
SET(LIBRARY_VERSION_MINOR 1)

SET(CMAKE_CXX_STANDARD 20)

SET(LIBRARY_BASE_PATH "${PROJECT_SOURCE_DIR}/code")

INCLUDE_DIRECTORIES( ${LIBRARY_BASE_PATH} )

SET(CRYPTOPP_INCLUDE_DIRS "/usr/include/cryptopp")

find_package(PkgConfig)

pkg_check_modules(SQLITE3 REQUIRED sqlite3)

add_library(
    NotesManagerCore SHARED
    "code/private/src/Note.cpp"
    "code/private/src/Crypter.cpp"
    "code/private/src/CryptoAlgorithmException.cpp"
    "code/private/src/Database.cpp"
    "code/private/src/Signers/HMACMD5.cpp"
    "code/private/src/CryptoAlgorithms/BasicCryptoAlgorithm.cpp"
    "code/private/src/CryptoAlgorithms/NoCryptoAlgorithm.cpp"
    "code/private/src/Database/SQLite3.cpp"
    "code/public/src/NotesManagerCore.cpp"
)

target_include_directories(NotesManagerCore PUBLIC ${SQLITE3_INCLUDE_DIRS} ${CRYPTOPP_INCLUDE_DIRS})
target_link_libraries(NotesManagerCore ${SQLITE3_LIBRARIES} cryptopp)