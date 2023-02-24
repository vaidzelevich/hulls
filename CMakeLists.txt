cmake_minimum_required(VERSION 3.12)

project(hulls)

add_subdirectory(third_party/pybind11 pybind11)

pybind11_add_module(hulls src/wrapper.cpp)

target_compile_features(hulls PRIVATE cxx_std_17)