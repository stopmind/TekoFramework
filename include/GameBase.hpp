#pragma once

#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace Teko {
    class GameBase {
        private:
        sf::Clock *_frameClock;
        sf::Clock *_tickClock;
        sf::Clock *_deltaClock;

        float _minTimeBetwenFrames;
        float _minTimeBetwenTicks;

        protected:
        sf::RenderWindow *_window;
        bool _stopped{};

        virtual void init() = 0;
        virtual void update(float delta) = 0;
        virtual void tick() = 0;
        virtual void draw() = 0;
        virtual void event(sf::Event *event) = 0;

        public:
        virtual void close() = 0;

        void setMaxTPS(int tickCount);
        void setMaxFPS(int frameCount);
        void start();

        GameBase();
        ~GameBase();
    };
}