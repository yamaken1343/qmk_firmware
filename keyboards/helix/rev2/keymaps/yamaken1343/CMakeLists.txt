cmake_minimum_required(VERSION 3.6)
project(yamaken1343)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    config.h
    keymap.c)

set(qmk_root ../../../../../.)
include_directories(${qmk_root}/tmk_core/common/ ${qmk_root}/keyboards/helix/ ${qmk_root}/quantum/ ${qmk_root}/lib/lufa/)


add_executable(yamaken1343 ${SOURCE_FILES})