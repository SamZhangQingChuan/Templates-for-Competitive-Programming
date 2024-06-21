cmake_minimum_required(VERSION 3.28)

project(CP-Templates)

file(GLOB_RECURSE ALL_CPP_FILES "*.cpp")

add_library(qc_lib ${ALL_CPP_FILES})
