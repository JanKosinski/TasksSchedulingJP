cmake_minimum_required(VERSION 3.3)
project(TasksScheduling)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp parameters.h Task.cpp Task.h Lineup.cpp Lineup.h hybridization.cpp generate.cpp Generator.h JohnsonsAlgorithm.h JohnsonsAlgorithm.cpp Population.cpp Population.h mutation.h Loader.cpp Loader.h ExactAlgorithm.h ExactAlgorithm.cpp)
add_executable(TasksScheduling ${SOURCE_FILES} ExactAlgorithm.h)