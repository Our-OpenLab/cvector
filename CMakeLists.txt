cmake_minimum_required(VERSION 3.22)
project(cvector LANGUAGES C CXX)

option(BUILD_TESTS "Build tests" ON)

include_directories(include)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-g -fprofile-arcs -ftest-coverage)
    add_link_options(-fprofile-arcs -ftest-coverage)
endif()

add_library(cvector STATIC
        src/cvector_core.c
        src/cvector_insert_erase.c
        src/cvector_resize.c
)

# Exemple d'utilisation
add_executable(example examples/example_usage.c)
target_link_libraries(example cvector)

# Tests
if(BUILD_TESTS)
    enable_testing()
    find_package(GTest REQUIRED)

    add_executable(test_cvector tests/test_cvector.cpp)
    target_link_libraries(test_cvector PRIVATE cvector gtest::gtest)
    add_test(NAME cvector_tests COMMAND test_cvector)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    find_program(GCOVR_EXECUTABLE gcovr REQUIRED)
    add_custom_target(coverage
            COMMAND ${GCOVR_EXECUTABLE} --root ${CMAKE_SOURCE_DIR} --filter ${CMAKE_SOURCE_DIR}/src/ --html --html-details --output coverage.html
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMENT "Generating code coverage report"
    )
endif()
