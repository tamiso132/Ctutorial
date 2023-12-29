# Set the minimum required CMake version
cmake_minimum_required(VERSION 3.5)

# Define the project and the language used
project(MyProjectC)

file(GLOB_RECURSE SOURCES "src/**/*.c")
file(GLOB_RECURSE HEADERS "src/**/*.h")

# Add the executable target
add_executable(myexecutable ${SOURCES} ${HEADERS} src/main.c)

set_target_properties(myexecutable PROPERTIES OUTPUT_NAME MyProjectC)