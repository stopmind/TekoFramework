add_executable(test main.cpp TestComponent.cpp TestComponent.hpp)
target_link_libraries(test
        Teko
        )