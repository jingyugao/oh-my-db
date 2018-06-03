cmake_minimum_required(VERSION 2.8)

project(oh-my-db)
add_executable(${PROJECT_NAME} "main.cpp" "b_plus_tree.h")
add_executable("b_plus_tree_test" "b_plus_tree_test.cpp" "b_plus_tree.h")
