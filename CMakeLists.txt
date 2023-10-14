cmake_minimum_required(VERSION 3.13)
project(Shooter)

# 1. Look for a SDL3 package,
# 2. look for the SDL3-shared component, and
# 3. fail if the shared component cannot be found.
find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)
find_package(SDL3_image REQUIRED CONFIG REQUIRED COMPONENTS SDL3_image-shared)

# Create your game executable target as usual   
add_executable(shooter main.c)

add_subdirectory(src)
add_subdirectory(include)

# Link to the actual SDL3 library.
target_link_libraries(shooter PRIVATE SDL3::SDL3 SDL3_image::SDL3_image)