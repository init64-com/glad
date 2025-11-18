cmake_minimum_required(VERSION 3.30)
project(glad LANGUAGES C)

set(CMAKE_C_STANDARD_REQUIRED true)

set(GLAD_SOURCE source/gl.c source/egl.c)

if(LINUX)
    set(GLAD_SOURCE ${GLAD_SOURCE} source/glx.c)
elseif(WIN32)
    set(GLAD_SOURCE ${GLAD_SOURCE} source/wgl.c)
endif()

add_library(glad SHARED ${GLAD_SOURCE})
target_include_directories(glad PUBLIC include/)
if(LINUX)
    target_link_libraries(glad PUBLIC X11)
endif()
target_compile_definitions(glad PRIVATE GLAD_API_CALL_EXPORT_BUILD PUBLIC GLAD_API_CALL_EXPORT)
