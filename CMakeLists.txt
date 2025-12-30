cmake_minimum_required(VERSION 3.30)
project(glad LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED true)
set(CMAKE_C_EXTENSIONS false)

set(GLAD_SOURCE source/gl.c source/egl.c)

add_library(glad STATIC)
target_include_directories(glad PUBLIC include/)

if(LINUX)
    set(GLAD_SOURCE ${GLAD_SOURCE} source/glx.c)
    target_link_libraries(glad PUBLIC X11 GL)
elseif(WIN32)
    set(GLAD_SOURCE ${GLAD_SOURCE} source/wgl.c)
    target_link_libraries(glad PUBLIC opengl32)
endif()

target_sources(glad PRIVATE ${GLAD_SOURCE})

target_compile_definitions(glad PRIVATE GLAD_API_CALL_EXPORT_BUILD PUBLIC GLAD_API_CALL_EXPORT)
