cmake_minimum_required(VERSION 3.16)

project(Tic-Tac-Toe)


if(NOT CMAKE_RUNTIME_OUTPUT_DIRECTORY)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
endif()
if(NOT CMAKE_LIBRARY_OUTPUT_DIRECTORY)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
endif()
if(NOT CMAKE_ARCHIVE_OUTPUT_DIRECTORY)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
endif()


find_package(SDL2 REQUIRED)

file( GLOB SRCS *.cpp *.h *.hpp )

add_executable(app ${SRCS})
target_include_directories(app PUBLIC ${SDL2_INCLUDE_DIRS})
target_link_libraries(app ${SDL2_LIBRARIES} SDL2_ttf SDL2_mixer SDL2_image)

add_custom_target(copy_resources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/music ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/music
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/assets ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets
    )
