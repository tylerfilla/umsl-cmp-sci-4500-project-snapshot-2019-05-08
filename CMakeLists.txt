#
# Cozmonaut
# Copyright 2019 The Cozmonaut Contributors
#

cmake_minimum_required(VERSION 3.4)
project(cozmonaut)

set(cozmonaut_SRC_FILES
        src/main.c
        )

add_executable(cozmonaut ${cozmonaut_SRC_FILES})
set_target_properties(cozmonaut PROPERTIES C_STANDARD 99)
