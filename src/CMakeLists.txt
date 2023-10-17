target_sources(shooter
    PRIVATE
        Bullet.cpp
        Platform.cpp
        Player.cpp
        WindowRenderer.cpp
)

add_subdirectory(component)
add_subdirectory(utils)