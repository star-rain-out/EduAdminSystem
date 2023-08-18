cmake_minimum_required(VERSION 3.23)
project(EduAdminSystem)

set(CMAKE_CXX_STANDARD 20)

add_executable(EduAdminSystem main.cpp inc/user.h inc/course.h inc/menu.h)
