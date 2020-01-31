cmake_minimum_required(VERSION 2.8)
project(rec_gyro_calib)

set(CMAKE_CXX_STANDARD 14)

add_executable(rec_gyro_calib main.cpp baserandom.h baserandom.cpp recstats.h recstats.cpp expdata.cpp expdata.h math.cpp math.h)
