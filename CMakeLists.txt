cmake_minimum_required(VERSION 4.0)
project(RayTracer)

set(CMAKE_CXX_STANDARD 20)

add_executable(RayTracer main.cpp
        Sphere.h
        Camera.h
        Camera.cpp
        World.cpp
        World.h
        Vector3.h
        Ray.h
        Light.h
        SceneObject.h)
