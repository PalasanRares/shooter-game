target_sources(shooter
    PRIVATE
        Platform.cpp
        Player.cpp
        WindowRenderer.cpp
)

add_subdirectory(component)
add_subdirectory(utils)
add_subdirectory(entity)
