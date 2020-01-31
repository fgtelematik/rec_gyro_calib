cmake_minimum_required(VERSION 2.8)
project(publication_recursive_mean)

set(CMAKE_CXX_STANDARD 14)

add_executable(publication_recursive_mean main.cpp baserandom.h baserandom.cpp recstats.h recstats.cpp expdata.cpp expdata.h math.cpp math.h)
