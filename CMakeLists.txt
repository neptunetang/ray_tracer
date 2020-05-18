cmake_minimum_required(VERSION 3.15)
project(basic_ray_tracer)

set(CMAKE_CXX_STANDARD 14)

add_executable(basic_ray_tracer main.cpp ray.h vec3.cpp vec3.h hitable.h sphere.cpp sphere.h hitable_list.h camera.cpp camera.h material.cpp material.h diffuse.h metal.cpp metal.h dielectric.cpp dielectric.h moving_sphere.cpp moving_sphere.h texture.h constant_texture.h checker_texture.cpp checker_texture.h image_texture.cpp image_texture.h stb_image.h image.h common_method.h noise_texture.h perlin.cpp perlin.h box.cpp box.h diffuse_light.h rectangle.cpp rectangle.h translate.h rotate.cpp rotate.h constant_medium.cpp constant_medium.h isotropic.h object_loader.h triangle.cpp triangle.h light.h)