cmake_minimum_required(VERSION 3.10)

#set the project name and version
project(Shooter)

include(FindPkgConfig)

pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2IMAGE REQUIRED SDL2_image >= 2.0.0)
pkg_search_module(SDL2TTF REQUIRED SDL2_ttf >= 2.0.0)

file(GLOB_RECURSE SRC CONFIGURE_DEPENDS "include/*.h" "src/*.c")
add_executable(Shooter ${SRC})

target_include_directories(Shooter PRIVATE include src ${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS})
target_link_libraries(Shooter ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES})