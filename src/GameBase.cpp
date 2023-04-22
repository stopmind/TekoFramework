#include "GameBase.hpp"
#include "Log.hpp"

namespace Teko {
    void GameBase::setMaxTPS(int tickCount) {
        minTimeBetwenTicks = 1.f / tickCount;
    }

    void GameBase::setMaxFPS(int frameCount) {
        minTimeBetwenFrames = 1.f / frameCount;
    }

    void GameBase::start() {
        stopped = false;
        Log::init();

        init();
        Log::info("Game init.");

        while (true) {
            update();

            if (tickClock->getElapsedTime().asSeconds() >= minTimeBetwenTicks) {
                tickClock->restart();
                tick();
            }

            if (stopped) continue;

            if (frameClock->getElapsedTime().asSeconds() >= minTimeBetwenFrames) {
                frameClock->restart();
                draw();
            }
        }

        Log::info("Game ended.");
        Log::close();
    }

    GameBase::GameBase() {
        frameClock = new sf::Clock();
        tickClock = new sf::Clock();
    }

    GameBase::~GameBase() {
        delete frameClock;
        delete tickClock;
    }
}