cmake_minimum_required(VERSION 3.16)

project(Tic-Tac-Toe)

find_package(SDL2 REQUIRED)

file( GLOB SRCS *.cpp *.h *.hpp )

include_directories(${SDL2_INCLUDE_DIRS})
add_executable(app ${SRCS})
target_link_libraries(app ${SDL2_LIBRARIES} SDL2_ttf SDL2_mixer SDL2_image)

