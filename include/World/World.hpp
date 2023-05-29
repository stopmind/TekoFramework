//
// Created by max on 5/9/23.
//

#ifndef WORLD_HPP
#define WORLD_HPP

#include "WorldSurface.hpp"

#include <SFML/Graphics/Drawable.hpp>
#include <string>
#include <map>

namespace Teko {
    class World : public sf::Drawable {
    private:
        std::map<std::string, WorldSurface *> _surfaces;
        WorldSurface *_currentSurface;
    public:
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

        void tick();

        void update(float delta);

        void selectSurface(std::string name);

        WorldSurface *createSurface(std::string name);

        WorldSurface *getSurface(std::string name);

        World();

        ~World();
    };
}

#endif //WORLD_HPP
