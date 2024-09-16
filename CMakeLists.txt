cmake_minimum_required(VERSION 3.10)

# Set the project name
project(Dungeons&Dragons)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" ON)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

# Include directories
include_directories(include include/Screens include/Managers)

# Add the executable (add all .cpp files here)
file(GLOB SOURCES "src/*.cpp" "src/Screens/*.cpp")
add_executable(DungeonAndDragons ${SOURCES})


target_link_libraries(DungeonAndDragons PRIVATE sfml-graphics sfml-audio sfml-system sfml-network sfml-window)
target_compile_features(DungeonAndDragons PRIVATE cxx_std_17)

add_custom_command(TARGET DungeonAndDragons POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/assets"
    "$<TARGET_FILE_DIR:DungeonAndDragons>/assets"
)

if(WIN32)
    add_custom_command(
        TARGET DungeonAndDragons
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:DungeonAndDragons>
        VERBATIM)
endif()






