cmake_minimum_required(VERSION 3.30)
project(cvector LANGUAGES C CXX)

include_directories(include)

add_library(cvector STATIC src/utils.c)

add_executable(example examples/example_usage.c)
target_link_libraries(example cvector)
