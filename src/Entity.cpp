//
// Created by max on 5/13/23.
//

#include "World/Entity.hpp"
#include "World/WorldSurface.hpp"

namespace Teko {
    void Entity::draw(sf::RenderTarget &target, sf::RenderStates states) const {
        for (auto &comps : _components) {
            for (auto comp : comps.second){
                states.transform.combine(getTransform());
                target.draw(*comp, states);
            }
        }
    }

    void Entity::tick() {
        for (auto &comps : _components) {
            for (auto comp : comps.second) comp->tick();
        }
    }

    void Entity::update(float delta) {
        for (auto &comps : _components) {
            for (auto comp : comps.second) comp->update(delta);
        }
    }

    WorldSurface *Entity::getSurface() {
        return _surface;
    }

    Entity::~Entity() {
        for (auto &comps : _components) {
            for (auto &comp : comps.second){
                delete comp;
            }
        }
    }

    Entity::Entity(WorldSurface *surface) {
        _surface = surface;
    }
}