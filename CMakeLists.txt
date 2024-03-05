cmake_minimum_required(VERSION 3.14)

PROJECT(dataset_tool)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# fetch latest argparse
include(FetchContent)

FetchContent_Declare(
        argparse
        GIT_REPOSITORY https://github.com/p-ranav/argparse.git
)

FetchContent_MakeAvailable(argparse)

include_directories(lib)

add_executable(dataset_tool
        src/main.cpp
        lib/subcommand/split_command.h
        lib/subcommand/split_command.cpp
        lib/subcommand/command_runner.h
        lib/subcommand/offset_command.h
        lib/subcommand/offset_command.cpp
        lib/utility/annotations/annotations.cpp
        lib/utility/annotations/annotations.h
)

target_link_libraries(dataset_tool argparse)
