target_sources(shooter
    PRIVATE
        Transform.hpp
        Sprite.hpp
)

target_include_directories(shooter PUBLIC ${CMAKE_CURRENT_LIST_DIR})
