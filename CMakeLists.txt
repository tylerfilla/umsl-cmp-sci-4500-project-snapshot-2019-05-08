#
# Cozmonaut
# Copyright 2019 The Cozmonaut Contributors
#

cmake_minimum_required(VERSION 3.4)
project(cozmonaut)

add_subdirectory(third_party/fmt)

set(cozmonaut_SRC_FILES
        src/service/console/console.c
        src/service/face/face.c
        src/service/monitor/monitor.c
        src/service/python/python.c
        src/service/speech/speech.c
        src/log.cpp
        src/main.c
        src/service.c
        )

add_executable(cozmonaut ${cozmonaut_SRC_FILES})
set_target_properties(cozmonaut PROPERTIES C_STANDARD 99 CXX_STANDARD 14)
target_link_libraries(cozmonaut PRIVATE fmt::fmt-header-only)
