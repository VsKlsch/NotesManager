cmake_minimum_required(VERSION 3.20)

project(NotesManagerC)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(NotesManagerC "code/main.c" "code/tui.c")

target_link_libraries(NotesManagerC NotesManagerCore)
target_link_libraries(NotesManagerC ${CURSES_LIBRARIES} panel menu cdk)