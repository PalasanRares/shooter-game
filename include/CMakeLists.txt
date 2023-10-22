target_sources(shooter
    PRIVATE
        Platform.hpp
        Player.hpp
        WindowRenderer.hpp
        Color.hpp
)

target_include_directories(shooter PUBLIC ${CMAKE_CURRENT_LIST_DIR})

add_subdirectory(component)
add_subdirectory(utils)
add_subdirectory(entity)
