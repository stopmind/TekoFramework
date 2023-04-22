#pragma once

#include <SFML/System/Clock.hpp>

namespace Teko {
    class GameBase {
        private:
        sf::Clock *frameClock;
        sf::Clock *tickClock;

        float minTimeBetwenFrames;
        float minTimeBetwenTicks;

        protected:
        bool stopped;

        virtual void init() = 0;
        virtual void update() = 0;
        virtual void tick() = 0;
        virtual void draw() = 0;

        public:
        virtual void close() = 0;

        void setMaxTPS(int tickCount);
        void setMaxFPS(int frameCount);
        void start();

        GameBase();
        ~GameBase();
    };
}