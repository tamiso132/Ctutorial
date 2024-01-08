# Set the minimum required CMake version
cmake_minimum_required(VERSION 3.5)

# set( CMAKE_CXX_COMPILER "C:/Users/tomalb21/Desktop/mingw32/bin")
# set( CMAKE_C_COMPILER "C:/Users/tomalb21/Desktop/mingw32/bin" )

# Define the project and the language used
project(MyProjectC C)

# Set C standard to C11
set(CMAKE_C_STANDARD 11)

# Enable compiler warnings
if (CMAKE_COMPILER_IS_GNUCC OR CMAKE_C_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wall -Wextra -pedantic)
endif()

# Define sources and headers    
file(GLOB_RECURSE SOURCES "src/**/*.c")
file(GLOB_RECURSE HEADERS "src/**/*.h")

# Add the executable target
add_executable(myexecutable ${SOURCES} ${HEADERS} src/main.c)

# Set output name and folder
set_target_properties(myexecutable PROPERTIES OUTPUT_NAME MyProjectC)
set_target_properties(myexecutable PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# Add the test executable target
add_executable(test_executable ${SOURCES} ${HEADERS} src/main_test.c)




# TEST EXECUTABLE

set_target_properties(test_executable PROPERTIES OUTPUT_NAME test_executable)
set_target_properties(test_executable PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

if(UNIX)
if (CMAKE_COMPILER_IS_GNUCC OR CMAKE_C_COMPILER_ID MATCHES "Clang")
target_compile_options(test_executable PRIVATE
    $<$<CONFIG:Debug>:
        -O0       # No optimization
        -g        # Generate debugging information
        -Wall
        -fsanitize=undefined
        -fsanitize=address
    >
)

target_link_libraries(test_executable PRIVATE
$<$<CONFIG:Debug>:
    -fsanitize=undefined
    -fsanitize=address
    >
)

target_compile_options(myexecutable PRIVATE
    $<$<CONFIG:Debug>:
        -O0       # No optimization
        -g        # Generate debugging information
        -Wall
        -fsanitize=undefined
        -fsanitize=address
    >
)

target_link_libraries(myexecutable PRIVATE
$<$<CONFIG:Debug>:
    -fsanitize=undefined
    -fsanitize=address
    >
)
endif()
endif()


if (MSVC)
    target_compile_options(test_executable PRIVATE
    $<$<CONFIG:Debug>:
        -O0       # No optimization
        -g        # Generate debugging information
        -Wall
        -Wextra
        -Werror
    >
)

target_compile_options(myexecutable PRIVATE
    $<$<CONFIG:Debug>:
        -O0       # No optimization
        -g        # Generate debugging information
        -Wall
        -Wextra
        -Werror
    >
)


endif()



# Compiler options for Release build
target_compile_options(test_executable PRIVATE
    $<$<CONFIG:Release>:
        -O3       # Aggressive optimization
    >
)

# Compiler options for Release build
target_compile_options(myexecutable PRIVATE
    $<$<CONFIG:Release>:
        -O3       # Aggressive optimization
    >
)

