//
// Created by max on 5/9/23.
//

#include <SFML/Graphics/RenderTarget.hpp>
#include "World/WorldSurface.hpp"

namespace Teko {
    void WorldSurface::draw(sf::RenderTarget &target, sf::RenderStates states) const {
        target.draw(*_camera);

        for (auto entity : _entities) {
            target.draw(*entity.second);
        }
    }

    Camera *WorldSurface::getCamera() {
        return _camera;
    }

    WorldSurface::WorldSurface() {
        _camera = new Camera();
    }

    WorldSurface::~WorldSurface() {
        for (auto entity : _entities) delete entity.second;
        delete _camera;
    }

    void WorldSurface::tick() {
        for (auto entity : _entities) entity.second->tick();
    }

    void WorldSurface::update(float delta) {
        for (auto entity : _entities) entity.second->update(delta);
    }

    Entity *WorldSurface::addEntity(std::string name) {
        Entity* entity = getEntity(name);
        if (entity != nullptr) return entity;
        else {
            entity = new Entity(this);
            _entities[name] = entity;
            return entity;
        }
    }

    Entity *WorldSurface::getEntity(std::string name) {
        auto it = _entities.find(name);

        if (it == _entities.end()) return nullptr;
        return it->second;
    }
}