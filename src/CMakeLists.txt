
set(TEKOSRC
        Assets.cpp
        GameBase.cpp
        Log.cpp
        Reg.cpp
        World.cpp WorldSurface.cpp
        Exceptions.cpp AssetFuncs.hpp AssetFuncs.cpp Entity.cpp Camera.cpp ../include/World/Camera.hpp)

find_package(tinyxml2 REQUIRED)
add_library(Teko SHARED ${TEKOSRC})
target_link_libraries(Teko
        sfml-system
        sfml-graphics
        tinyxml2
        )