cmake_minimum_required(VERSION 3.21)
project(RTWeekend)

set(CMAKE_CXX_STANDARD 23)

include_directories(./ RTWeekend)

add_executable(RTWeekend main.cpp
        device.h
        vec3.h
        color.h
        ray.h
        hittable.h
        hittable.h
        sphere.h
        hittableList.h
        hittableList.h
        rtweekend.h
        interval.h
        interval.h
        camera.h
        material.h
        material.h
)
