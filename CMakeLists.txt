cmake_minimum_required(VERSION 3.5)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# TODO 1. Add assembler.
# TODO 2. Add python scripts

# setup assembly
set(CMAKE_NASM_LINK_EXECUTABLE "ld -o ")
set(CAN_USE_ASSEMBLER TRUE)
set(CMAKE_ASM_NASM_FLAGS "")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")
set(CMAKE_ASM_NASM_OBJECT_FORMAT elf32)

project(AbaAbaOs VERSION 1.0
              DESCRIPTION "command line count down task runner"
              LANGUAGES CXX)
enable_language(ASM_NASM)

# use force to enforce the change
set(MY_CACHE_VAR "VALUE" CACHE STRING "XXV" FORCE)

add_executable(AbaAbaOS
    "kernel/tty.hpp"
    "kernel/tty.cc"
    "kernel/kmain.cc"
    "arch/i386/boot.s"
    )
set_property(TARGET AbaAbaOS PROPERTY CXX_STANDARD 17)
set_target_properties(${AbaAbaOS} PROPERTIES LINKER_LANGUAGE NASM)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  add_compile_definitions(TEST_DRAW)
  set(DEBUG_COMPILATION_FLAG "")
  set(DEBUG_COMPILATION_FLAG "${DEBUG_COMPILATION_FLAG} -g")
  set(DEBUG_COMPILATION_FLAG "${DEBUG_COMPILATION_FLAG} -fsanitize=address")
  set_target_properties(AbaAbaOS
    PROPERTIES
    COMPILE_FLAGS "${DEBUG_COMPILATION_FLAG}"
    LINK_FLAGS "-fsanitize=address")
else()
  add_compile_definitions(MAIN)
endif()

# target_link_libraries(tomatoclock termbox)
# add_library(termbox SHARED)
