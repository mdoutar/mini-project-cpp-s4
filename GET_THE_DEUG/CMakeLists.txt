cmake_minimum_required(VERSION 3.31.6)
project(GET_THE_DEUG)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.2
    GIT_SHALLOW TRUE
)

# Disable/Enable specific modules to speed up build times
set(SFML_BUILD_AUDIO    ON)
set(SFML_BUILD_GRAPHICS ON)
set(SFML_BUILD_WINDOW   ON)
set(SFML_BUILD_NETWORK  OFF)

FetchContent_MakeAvailable(SFML)

# Find all .cpp files in the src folder
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS 
    "src/*.cpp" 
    "src/*.hpp"
)

# Create the executable using the SOURCES variable
add_executable(GET_THE_DEUG ${SOURCES})

# Tell the compiler where to find your header files
target_include_directories(GET_THE_DEUG PRIVATE src/)

# Link SFML libraries to the executable
target_link_libraries(GET_THE_DEUG
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
)

# Copy the assets folder to the build directory after compiling
add_custom_command(TARGET GET_THE_DEUG POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    $<TARGET_FILE_DIR:GET_THE_DEUG>/assets
)