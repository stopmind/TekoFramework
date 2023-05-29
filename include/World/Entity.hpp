//
// Created by max on 5/13/23.
//

#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <string>
#include <vector>
#include <map>
#include <typeinfo>

#include "EntityComponent.hpp"

namespace Teko {
    class WorldSurface;

    class Entity : public sf::Transformable, public sf::Drawable {
    private:
        WorldSurface *_surface;
        std::map<std::string, std::vector<EntityComponent *>> _components;
    public:
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

        void tick();

        void update(float delta);

        // CompT MUST BE CHILD OF EntityComponent
        template<class CompT>
        CompT *GetComponent(int number = 0) {
            static_assert(std::is_base_of<EntityComponent, CompT>(), "Incorrect type");

            std::string compName = std::string(typeid(CompT).name());
            if (_components[compName].size() > number) return _components[compName][number];
            else return nullptr;
        }

        // CompT MUST BE CHILD OF EntityComponent
        template<class CompT>
        void AddComponent(CompT *component) {
            static_assert(std::is_base_of<EntityComponent, CompT>(), "Incorrect type");
            _components[std::string(typeid(CompT).name())].push_back(component);
        }

        WorldSurface* getSurface();

        Entity(WorldSurface *surface);

        ~Entity();
    };
}

#endif //ENTITY_HPP
