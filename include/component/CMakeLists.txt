target_sources(shooter
    PRIVATE
        Transform.hpp
        Sprite.hpp
        PhysicalBody.hpp
        Collider.hpp
        Animation.hpp
)

target_include_directories(shooter PUBLIC ${CMAKE_CURRENT_LIST_DIR})
