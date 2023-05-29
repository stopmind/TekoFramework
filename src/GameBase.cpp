#include "GameBase.hpp"
#include "Reg.hpp"
#include "Log.hpp"
#include "Assets.hpp"
#include <SFML/Window/Event.hpp>

namespace Teko {
    void GameBase::setMaxTPS(int tickCount) {
        _minTimeBetwenTicks = 1.f / (float)tickCount;
    }

    void GameBase::setMaxFPS(int frameCount) {
        _minTimeBetwenFrames = 1.f / (float)frameCount;
    }

    void GameBase::start() {
        _stopped = false;
        Log::init();
        Reg::init();
        Assets::init();

        init();
        Log::info("Game init.");

        while (true) {
            for (sf::Event ev {}; _window->pollEvent(ev);) event(&ev);
            update(_deltaClock->getElapsedTime().asSeconds());
            _deltaClock->restart();

            if (_tickClock->getElapsedTime().asSeconds() >= _minTimeBetwenTicks) {
                _tickClock->restart();
                tick();
            }

            if (_stopped) break;

            if (_frameClock->getElapsedTime().asSeconds() >= _minTimeBetwenFrames) {
                _frameClock->restart();
                draw();
                _window->display();
            }
        }

        Log::info("Game ended.");

        Assets::close();
        Reg::close();
        Log::close();
    }

    GameBase::GameBase() {
        _frameClock = new sf::Clock();
        _tickClock = new sf::Clock();
        _deltaClock = new sf::Clock();

        _minTimeBetwenFrames = 0;
        _minTimeBetwenTicks = 0;
    }

    GameBase::~GameBase() {
        delete _frameClock;
        delete _tickClock;
        delete _window;
    }
}