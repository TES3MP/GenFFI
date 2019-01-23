cmake_minimum_required(VERSION 3.10)
project(genffi)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/)

find_package(LibClang REQUIRED)

include_directories(SYSTEM ${LIBCLANG_INCLUDE_DIRS})

add_executable(genffi main.cpp
        ToLua.cpp ToLua.hpp
        Utils.cpp Utils.hpp
        Parser.cpp Parser.hpp
        ToMono.cpp ToMono.hpp
        ISerializer.hpp
        Version.hpp
        )

target_link_libraries(genffi ${LIBCLANG_LIBRARIES})
