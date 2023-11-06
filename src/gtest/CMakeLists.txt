cmake_minimum_required(VERSION 3.12)


include_directories(.)
message("MATH_SRC: ${MATH_SRC}")

add_library(fixed_ratio STATIC fixed_ratio_sampler.cc fixed_ratio_sampler.h)



option(CMAKE_TEMPLATE_ENABLE_TEST "Whether to enable unit tests" ON)
if (CMAKE_TEMPLATE_ENABLE_TEST)
    message(STATUS "Unit tests enabled")
    enable_testing()

    LINK_DIRECTORIES(../../release/x86/lib)

    add_executable(test_fixed_ratio fixed_ratio_sampler_test.cc)
    target_link_libraries(test_fixed_ratio fixed_ratio gtestd gtest_maind)     #依赖动态库
    add_test(NAME test_fixed_ratio COMMAND test_fixed_ratio)
endif()
