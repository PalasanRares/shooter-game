target_sources(shooter
    PRIVATE
        Vector2.hpp
        Color.hpp
        TextureProvider.hpp
)

target_include_directories(shooter PUBLIC ${CMAKE_CURRENT_LIST_DIR})
