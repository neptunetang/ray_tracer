cmake_minimum_required(VERSION 3.15)
project(basic_ray_tracer)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

add_executable(basic_ray_tracer main.cpp ray.h vec3.cpp vec3.h hitable.h sphere.cpp sphere.h hitable_list.h camera.h material.h diffuse.h metal.h dielectric.cpp dielectric.h moving_sphere.cpp moving_sphere.h texture.h stb_image.h image.h common_method.h box.h diffuse_light.h rectangle.cpp rectangle.h translate.h rotate.h triangle.h light.h orthnormal_base.h scene.h bdpt.h nne.h pt.h erpt.h multithread_session.h random.h run.h material.cpp)