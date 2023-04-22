#include "Log.hpp"
#include "GameBase.hpp"
#include <iostream>

using namespace Teko;

class Game : public GameBase {
    protected:

    void init() override {
        setMaxTPS(7);
        setMaxFPS(60);
    }

    void update() override {
        
    }

    void tick() override {
        std::cout << "Tick" << std::endl;
    }

    void draw() override {
        std::cout << "Draw!" << std::endl;
    }

    void close() override {
        stopped = true;
    }
};

int main() {
    Game g = Game();

    g.start();
}