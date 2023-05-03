
set(TEKOSRC
        Assets.cpp
        GameBase.cpp
        Log.cpp
        Reg.cpp
        )

add_library(Teko SHARED ${TEKOSRC})
target_link_libraries(Teko
        sfml-system
        sfml-graphics
        )