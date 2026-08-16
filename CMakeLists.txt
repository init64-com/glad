cmake_minimum_required(VERSION 4.0)
project(glext LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED true)
set(CMAKE_C_EXTENSIONS false)

# Set these options on your build instead
# set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(GLEXT_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(GLEXT_CORE
  source/gl.c
  source/egl.c
  source/vulkan.c
)

find_package(X11 REQUIRED)
if(WIN32)
  set(GLEXT_PLATFORM_SOURCE source/wgl.c)
  set(GLEXT_PLATFORM_LINK opengl32)
elseif(X11_FOUND)

  set(GLEXT_PLATFORM source/glx.c)
  set(GLEXT_PLATFORM_LINK X11)

else()
  message(WARNING "GLX or WIN32 missing. Not able to be compiled.")
endif()

set(GLEXT_SOURCES ${GLEXT_CORE} ${GLEXT_PLATFORM_SOURCE})

add_library(glext_obj OBJECT ${GLEXT_SOURCES})
target_include_directories(glext_obj PUBLIC ${GLEXT_INCLUDE})
target_link_libraries(glext_obj PUBLIC ${GLEXT_PLATFORM_LINK})
target_compile_definitions(glext_obj PRIVATE GLEXT_API_CALL_EXPORT_BUILD)
set_target_properties(glext_obj PROPERTIES POSITION_INDEPENDENT_CODE TRUE)

add_library(static_glext STATIC)
target_link_libraries(static_glext PRIVATE glext_obj)

add_library(glext SHARED)
target_link_libraries(glext PRIVATE glext_obj)

add_executable(glfw_window_test tests/window.c)
target_include_directories(glfw_window_test PRIVATE ${GLEXT_INCLUDE})
target_link_libraries(glfw_window_test PRIVATE glext glfw)

add_executable(vulkan_test tests/vulkan_test.c)
target_include_directories(vulkan_test PRIVATE ${GLEXT_INCLUDE})
target_link_libraries(vulkan_test PRIVATE glext)
