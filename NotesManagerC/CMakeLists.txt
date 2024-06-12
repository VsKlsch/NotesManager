cmake_minimum_required(VERSION 3.20)

project(NotesManagerC)

add_executable(NotesManagerC "code/main.c")

target_link_libraries(NotesManagerC NotesManagerCore)