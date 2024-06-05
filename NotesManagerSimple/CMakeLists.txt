cmake_minimum_required(VERSION 3.21)

project(NotesManagerSimple)

include_directories("../NotesManagerCore/code/public/include")

add_executable(NotesManagerSimple "code/main.c")

target_link_libraries(NotesManagerSimple NotesManagerCore)