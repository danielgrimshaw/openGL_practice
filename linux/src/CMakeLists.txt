cmake_minimum_required(VERSION 2.8)
# Project Name
PROJECT(Practice)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

add_definitions(-std=c++11)

#########################################################
# FIND OPENGL
#########################################################
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)
#########################################################
# FIND GLUT
#########################################################
find_package(GLFW REQUIRED)
include_directories(${GLFW_INCLUDE_DIRS})
link_directories(${GLFW_LIBRARY_DIRS})
add_definitions(${GLFW_DEFINITIONS})
if(NOT GLFW_FOUND)
    message(ERROR " GLFW not found!")
endif(NOT GLFW_FOUND)
#########################################################
# FIND GLEW
#########################################################
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
link_directories(${GLEW_LIBRARY_DIRS})
add_definitions(${GLEW_DEFINITIONS})
if(NOT GLEW_FOUND)
	message(ERROR " GLEW not found!")
endif(NOT GLEW_FOUND)
#########################################################
# FIND MATH
#########################################################
find_library(M_LIB m)
#########################################################
# Include Files
#########################################################
add_executable(Practice Practice.cpp Shader.cpp util.cpp Program.cpp)

########################################################
# Linking
#########################################################
# create the program "Plotter"
target_link_libraries(Practice ${OPENGL_LIBRARIES} ${GLFW_LIBRARY} ${GLEW_LIBRARY} ${M_LIB})
