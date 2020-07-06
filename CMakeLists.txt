cmake_minimum_required(VERSION 3.15)
project(basic_ray_tracer)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

add_executable(basic_ray_tracer main.cpp geometry/ray.h geometry/vec3.cpp geometry/vec3.h shapes/hitable.h shapes/sphere.cpp shapes/sphere.h shapes/hitable_list.h geometry/camera.h material/material.h material/diffuse.h material/metal.h material/dielectric.cpp material/dielectric.h shapes/moving_sphere.cpp shapes/moving_sphere.h texture/texture.h texture/stb_image.h texture/image.h geometry/common_method.h shapes/box.h shapes/diffuse_light.h shapes/rectangle.cpp shapes/rectangle.h geometry/translate.h geometry/rotate.h shapes/triangle.h geometry/light.h geometry/orthnormal_base.h geometry/scene.h bdpt.h nne.h pt.h erpt.h geometry/multithread_session.h geometry/random.h run.h material/material.cpp)