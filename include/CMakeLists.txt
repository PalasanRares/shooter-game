target_sources(shooter
    PUBLIC
        App.h
        Bullet.h
        Platform.h
        Player.h
)

target_include_directories(shooter PUBLIC ${CMAKE_CURRENT_LIST_DIR})