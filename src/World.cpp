//
// Created by max on 5/9/23.
//

#include <SFML/Graphics/RenderTarget.hpp>
#include "World/World.hpp"

namespace Teko {
    void World::draw(sf::RenderTarget &target, sf::RenderStates states) const {
        if (_currentSurface != nullptr) target.draw(*_currentSurface);
    }

    void World::selectSurface(std::string name) {
        _currentSurface = getSurface(name);
    }

    Teko::WorldSurface *World::createSurface(std::string name) {
        if (_surfaces.count(name)) return _surfaces[name];
        else {
            WorldSurface* surf = new WorldSurface();
            _surfaces[name] = surf;
            return surf;
        }
    }

    Teko::WorldSurface *World::getSurface(std::string name) {
        if (_surfaces.count(name)) return _surfaces[name];
        else return nullptr;
    }

    World::World() {

    }

    World::~World() {
        for (auto &pair : _surfaces) delete pair.second;
    }

    void World::tick() {
        if (_currentSurface != nullptr) _currentSurface->tick();
    }

    void World::update(float delta) {
        if (_currentSurface != nullptr) _currentSurface->update(delta);
    }
}