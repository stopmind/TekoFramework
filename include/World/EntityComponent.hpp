//
// Created by max on 5/13/23.
//

#ifndef ENTITYCOMPONENT_HPP
#define ENTITYCOMPONENT_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <string>
#include <map>

namespace Teko {
    class EntityComponent : public sf::Drawable {
    public:
        virtual void tick() = 0;
        virtual void update(float delta) = 0;
        virtual void setData(std::map<std::string, void*> data) = 0;
    };
}

#endif //ENTITYCOMPONENT_HPP
