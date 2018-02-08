cmake_minimum_required(VERSION 2.8)

# Specify a project name
project(homework1)

# Find the packages needed
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
#find_package(GLEW REQUIRED)

# Add OpenGL and GLUT header files include path (or other include paths you may want to add)
# to those the compiler uses to search for include files.
# OPENGL_INCLUDE_DIR, GLUT_INCLUDE_DIR are built-in variables defined when the packages are found.
include_directories(${OPENGL_INCLUDE_DIR} ${GLUT_INCLUDE_DIR})

# Add an executable named Example using the specified source file(s).
# Currently we only have one source file, you may want to add more here.
add_executable(sample sample.cpp)
add_executable(hw1 hw1.c)

# Link the executable to given libraries.
target_link_libraries(sample ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} m)
target_link_libraries(hw1 ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} m)
