cmake_minimum_required(VERSION 3.0.0)
project(thread-pool VERSION 0.1.0)

# include(CTest)
# enable_testing()

add_executable(thread-pool main.cpp threadpool.cpp thread.cpp)
include_directories(include)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

find_package(Threads)
target_link_libraries (${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})

include(CPack)

