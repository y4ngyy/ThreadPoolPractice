cmake_minimum_required(VERSION 3.0.0)
project(thread-pool VERSION 0.1.0)

# include(CTest)
# enable_testing()


file(GLOB native_srcs "./*.cpp")
add_executable(thread-pool ${native_srcs})
include_directories(include)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

find_package(Threads)
target_link_libraries (${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})

include(CPack)

