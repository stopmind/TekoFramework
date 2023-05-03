#include "GameBase.hpp"
#include "Reg.hpp"
#include "Log.hpp"
#include "Assets.hpp"
#include <SFML/Window/Event.hpp>

namespace Teko {
    void GameBase::setMaxTPS(int tickCount) {
        minTimeBetwenTicks = 1.f / (float)tickCount;
    }

    void GameBase::setMaxFPS(int frameCount) {
        minTimeBetwenFrames = 1.f / (float)frameCount;
    }

    void GameBase::start() {
        stopped = false;
        Log::init();
        Reg::init();
        Assets::init();

        init();
        Log::info("Game init.");

        while (true) {
            for (sf::Event ev {}; window->pollEvent(ev);) event(&ev);
            update();

            if (tickClock->getElapsedTime().asSeconds() >= minTimeBetwenTicks) {
                tickClock->restart();
                tick();
            }

            if (stopped) break;

            if (frameClock->getElapsedTime().asSeconds() >= minTimeBetwenFrames) {
                frameClock->restart();
                draw();
                window->display();
            }
        }

        Log::info("Game ended.");

        Assets::close();
        Reg::close();
        Log::close();
    }

    GameBase::GameBase() {
        frameClock = new sf::Clock();
        tickClock = new sf::Clock();

        minTimeBetwenFrames = 0;
        minTimeBetwenTicks = 0;
    }

    GameBase::~GameBase() {
        delete frameClock;
        delete tickClock;
        delete window;
    }
}