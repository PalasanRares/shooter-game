target_sources(shooter
    PRIVATE
        Bullet.hpp
        Platform.hpp
)

target_include_directories(shooter PUBLIC ${CMAKE_CURRENT_LIST_DIR})
