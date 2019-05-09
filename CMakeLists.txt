#
# Cozmonaut
# Copyright 2019 The Cozmonaut Contributors
#

cmake_minimum_required(VERSION 3.4)
project(cozmonaut)

add_subdirectory(third_party/fmt)

set(cozmonaut_SRC_FILES
        src/log.cpp
        src/main.c
        )

add_executable(cozmonaut ${cozmonaut_SRC_FILES})
set_target_properties(cozmonaut PROPERTIES C_STANDARD 99 CXX_STANDARD 14)
target_link_libraries(cozmonaut PRIVATE fmt::fmt-header-only)
