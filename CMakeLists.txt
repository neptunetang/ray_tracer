cmake_minimum_required(VERSION 3.15)
project(basic_ray_tracer)

set(CMAKE_CXX_STANDARD 14)

add_executable(basic_ray_tracer main.cpp ray.cpp ray.h vec3.cpp vec3.h hitable.cpp hitable.h sphere.cpp sphere.h hitable_list.cpp hitable_list.h)