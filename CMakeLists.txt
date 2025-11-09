cmake_minimum_required(VERSION 3.30)
project(glad LANGUAGES C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED true)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_PDB_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/pdb)

if(LINUX)

set(GLAD_SOURCE source/glad.c source/glad_glx.c)

elseif(WIN32)

set(GLAD_SOURCE source/glad.c source/glad_wgl.c)

endif()

include_directories(include)

add_library(glad STATIC ${GLAD_SOURCE})
