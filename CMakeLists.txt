cmake_minimum_required(VERSION 3.21)
project(PQwaveform_analyzer C)

set(CMAKE_C_STANDARD 99)

add_executable(PQwaveform_analyzer main.c cmake-build-debug/waveform.c cmake-build-debug/waveform.h cmake-build-debug/io.c cmake-build-debug/io.h)
