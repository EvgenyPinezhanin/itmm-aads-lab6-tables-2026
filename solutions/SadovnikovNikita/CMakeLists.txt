cmake_minimum_required(VERSION 3.8)

project(
    Lab2_Tables
    LANGUAGES CXX
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

add_executable(main
    main.cpp
    linear_table.cpp
    search_tree.cpp
    hash_chain.cpp
    hash_open.cpp
)