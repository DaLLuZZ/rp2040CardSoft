cmake_minimum_required(VERSION 3.16)

set(CMAKE_BUILD_TYPE DEBUG)
#set(CMAKE_BUILD_TYPE RELEASE)

# Set the target board
set(YAHAL_BOARD "rp2040-launchpad")

# Locate the YAHAL library folder
include(YAHAL_import.cmake)

project(flappy_back C CXX ASM)

add_executable(flappy_back
        flappy_back.cpp
        Game.cpp
        CharacterDrawer.cpp
        Difficulty.cpp
        ScoreEntry.cpp
        GetColors.cpp
)

# Add YAHAL to target
yahal_add_me(flappy_back)
yahal_add_library(flappy_back uGUI)

yahal_add_custom_targets(flappy_back)
yahal_add_extra_outputs(flappy_back)
