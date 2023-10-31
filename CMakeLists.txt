cmake_minimum_required(VERSION 3.21)

project(cpp_tutorials LANGUAGES CXX)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

function(add_executable_tutorials name)
    add_executable(${name}
        ${name}.cpp)
    target_compile_features(${name} PRIVATE cxx_std_17)
endfunction()

add_executable_tutorials(00_copy_move_constructors)