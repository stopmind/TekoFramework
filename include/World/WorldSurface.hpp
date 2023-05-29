//
// Created by max on 5/9/23.
//

#ifndef WORLDSURFACE_HPP
#define WORLDSURFACE_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <map>
#include <string>

#include "Entity.hpp"
#include "Camera.hpp"

namespace Teko {
    class WorldSurface : public sf::Drawable {
    private:
        std::map<std::string, Entity*> _entities;
        Camera* _camera;
    public:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void tick();
        void update(float delta);

        Entity* addEntity(std::string name);
        Entity* getEntity(std::string name);
        Camera* getCamera();

        WorldSurface();
        ~WorldSurface();
    };
}

#endif //WORLDSURFACE_HPP
