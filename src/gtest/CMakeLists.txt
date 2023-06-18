cmake_minimum_required(VERSION 3.12)


include_directories(.)
message("MATH_SRC: ${MATH_SRC}")

add_library(fixed_ratio STATIC fixed_ratio_sampler.cc fixed_ratio_sampler.h)
