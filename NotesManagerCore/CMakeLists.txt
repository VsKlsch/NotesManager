cmake_minimum_required(VERSION 3.20)

project(NotesManagerCore)

SET(LIBRARY_VERSION_MAJOR 0)
SET(LIBRARY_VERSION_MINOR 1)
SET(CMAKE_CXX_STANDARD 20)

set_property(GLOBAL PROPERTY cryptopp_include "Path to cryptopp includes")

SET(LIBRARY_BASE_PATH "${PROJECT_SOURCE_DIR}/code")

INCLUDE_DIRECTORIES( ${LIBRARY_BASE_PATH} )

find_package(PkgConfig)

pkg_check_modules(SQLITE3 REQUIRED sqlite3)

SET(CRYPTOPP_INCLUDE_DIRS "/usr/include/cryptopp")

add_library(
    NotesManagerCore SHARED
    "code/public/src/NotesManager.cpp"
    "code/private/src/Containers.cpp"
    "code/private/src/Crypters.cpp"
    "code/private/src/DatabaseRepo.cpp"
    "code/private/src/NotesManagerEntity.cpp"
    "code/private/src/SQLiteDatabaseRepo.cpp"
    "code/private/src/HMACMD5.cpp"
)

target_include_directories(NotesManagerCore PUBLIC ${SQLITE3_INCLUDE_DIRS} ${CRYPTOPP_INCLUDE_DIRS})
target_link_libraries(NotesManagerCore ${SQLITE3_LIBRARIES} cryptopp)
