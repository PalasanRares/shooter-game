target_sources(shooter
    PRIVATE
        Bullet.hpp
        Platform.hpp
        Player.hpp
        WindowRenderer.hpp
        Color.hpp
)

target_include_directories(shooter PUBLIC ${CMAKE_CURRENT_LIST_DIR})