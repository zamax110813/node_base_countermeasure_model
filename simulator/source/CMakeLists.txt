# CMakeのバージョンを設定
cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall -Wfatal-errors -Wundef")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# プロジェクト名と使用する言語を設定
project(node_base_countermeasure_model_simulator CXX)

add_compile_options(-std=c++11)
# a.outという実行ファイルをmain.cppとhello.cppから作成
add_executable(a.out main.cpp BA_Graph.cpp Complete_Graph.cpp Event_Generator.cpp functions.cpp Graph.cpp Node.cpp Scheduler.cpp WS_Graph.cpp)
add_executable(average average.cpp)
add_executable(st_host st_host.cpp)
add_executable(param param.cpp)
add_executable(node_init node_init.cpp)
add_executable(judge judge.cpp)
add_executable(build_BA_model build_BA_model.cpp functions.cpp)